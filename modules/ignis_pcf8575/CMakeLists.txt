project(ignis_pcf8575 VERSION 1.0 LANGUAGES C)

set(SRC_FOLDER)
set(PUBLIC_LINKS)
set(PRIVATE_LINKS)

if (IDF_TARGET)
    set(PUBLIC_LINKS
            ${PUBLIC_LINKS}
            k_hal
            k_osal
    )
else ()
    message(FATAL_ERROR "pcf8575 driver is not supported on host platform")
endif ()

add_library(${PROJECT_NAME} src/ignis_pcf8575.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_FOLDER} src)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PUBLIC_LINKS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})