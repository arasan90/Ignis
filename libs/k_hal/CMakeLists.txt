project(k_hal VERSION 1.0 LANGUAGES C)

if (TARGET_PLATFORM STREQUAL "esp32c3")
    set(K_HAL_PLATFORM "espressif")
else ()
    set(K_HAL_PLATFORM "host")
endif ()

include(k_hal/k_hal.cmake)

if (TARGET_PLATFORM STREQUAL "esp32c3")
    set(K_HAL_PRIVATE_LINKS ${K_HAL_PRIVATE_LINKS} idf::driver)
endif ()

add_library(${PROJECT_NAME} ${K_HAL_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${K_HAL_PUBLIC_INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE ${K_HAL_PRIVATE_INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${K_HAL_PUBLIC_LINKS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${K_HAL_PRIVATE_LINKS})

if (NOT IDF_TARGET)
    create_mock_library()
endif ()