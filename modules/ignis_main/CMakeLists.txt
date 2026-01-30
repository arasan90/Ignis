set(MAIN_TARGET)

set(PRIVATE_LIBS
        ignis_core
        k_osal
)

if (IDF_TARGET)
    idf_component_register(SRCS src/esp32c3/ignis_main.c src/ignis_main.c)
    set(MAIN_TARGET ${COMPONENT_LIB})
    set(PRIVATE_LIBS ${PRIVATE_LIBS})
else ()
    project(Ignis)
    set(CMAKE_BUILD_TYPE Debug)
    add_executable(${PROJECT_NAME} src/${TARGET_PLATFORM}/ignis_main.c src/ignis_main.c)
    set(MAIN_TARGET ${PROJECT_NAME})
    set(PRIVATE_LIBS ${PRIVATE_LIBS})
endif ()

target_link_libraries(${MAIN_TARGET} PRIVATE ${PRIVATE_LIBS})
target_include_directories(${MAIN_TARGET} PRIVATE src)
