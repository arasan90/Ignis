project(k_osal VERSION 1.0 LANGUAGES C)

if (TARGET_PLATFORM STREQUAL "esp32c3")
    set(K_OSAL_PLATFORM "espressif")
else ()
    set(K_OSAL_PLATFORM ${TARGET_PLATFORM})
endif ()

include(k_osal/k_osal.cmake)

if (TARGET_PLATFORM STREQUAL "esp32c3")
    set(K_OSAL_PRIVATE_LINKS ${K_OSAL_PRIVATE_LINKS} idf::freertos)
endif ()

add_library(${PROJECT_NAME} ${K_OSAL_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${K_OSAL_PUBLIC_INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE ${K_OSAL_PRIVATE_INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${K_OSAL_PUBLIC_LINKS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${K_OSAL_PRIVATE_LINKS})