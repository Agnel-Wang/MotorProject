# Motor Controller

## compile

```shell
cmake -DCMAKE_TOOLCHAIN_FILE="cmake/toolchain-arm-none-eabi.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
make -j8
```

```shell
cmake -DCMAKE_TOOLCHAIN_FILE="cmake/toolchain-arm-none-eabi.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
