set_property(SOURCE Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_a.s PROPERTY LANGUAGE C)
aux_source_directory(Source SRC)
add_library(
    ucosii
    Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_a.s
    Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_c.c
    Ports/ARM-Cortex-M4/Generic/GNU/os_dbg.c
    ${SRC}
)