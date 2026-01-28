cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (TARGET_PLATFORM STREQUAL "esp32c3")
    include(cmake/esp32c3-toolchain.cmake)
    set(EXTRA_COMPONENT_DIRS "modules/ignis_main")
endif ()

project(Ignis VERSION 1.0.0 LANGUAGES C CXX)
message(STATUS "Target platform: ${TARGET_PLATFORM}")

if (NOT TARGET_PLATFORM STREQUAL "esp32c3")
    add_subdirectory(modules/ignis_main)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
    add_compile_definitions(HOST_COMPILATION)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        include(FetchContent)
        FetchContent_Declare(
                gtest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG v1.16.0
        )
        set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")

        if (TARGET_PLATFORM STREQUAL "linux")
            set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
        elseif (TARGET_PLATFORM STREQUAL "darwin")
        endif ()

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
        FetchContent_MakeAvailable(gtest)
        enable_testing()
        include(CTest)
        add_subdirectory(libs/fff)
    endif ()
endif ()
