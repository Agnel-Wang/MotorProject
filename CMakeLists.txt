cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy) 
set(CMAKE_SIZE arm-none-eabi-size)

project(controller)
add_definitions(
-DUSE_STDPERIPH_DRIVER
-DSTM32F405xx
-DSTM32F40X_HD
)

set(MCU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -Wall -Wno-unknown-pragmas")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g2 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(
    Inc
    Drivers/CMSIS/Core/Include
    Drivers/STM32F4xx_StdPeriph_Driver/inc
    uCOSII/Include
    uCOSII/Ports/ARM-Cortex-M4/Generic/GNU
)

add_subdirectory(Drivers)
add_subdirectory(uCOSII)

aux_source_directory(./Src DIR_SRCS)
set_property(SOURCE startup_stm32f405xx.s PROPERTY LANGUAGE C)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F405RGTx_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS
"--specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref -Wl,--gc-sections"
)

add_executable(${PROJECT_NAME}.elf startup_stm32f405xx.s ${DIR_SRCS})
target_link_libraries(${PROJECT_NAME}.elf drivers ucosii)


set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET "${PROJECT_NAME}.elf" POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex  ${ELF_FILE} ${HEX_FILE}
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"

    COMMAND ${CMAKE_COMMAND} -E copy ${HEX_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin"

    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Invoking: Cross ARM GNU Print Size"
)

add_custom_command(TARGET "${PROJECT_NAME}.elf" POST_BUILD
    COMMAND openocd -f interface/jlink.cfg -c 'transport select swd' -f target/stm32f4x.cfg
	-c 'program ${ELF_FILE}' -c 'reset' -c 'exit'
    COMMENT "Flash to device"
)