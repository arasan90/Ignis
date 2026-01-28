set(IDF_TARGET "esp32c3")
set(CMAKE_TOOLCHAIN_FILE $ENV{IDF_PATH}/tools/cmake/toolchain-esp32c3.cmake)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
