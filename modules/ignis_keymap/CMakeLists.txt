project(ignis_keymap VERSION 1.0 LANGUAGES C)

set(SRC_FOLDER)
set(PUBLIC_LINKS)
set(PRIVATE_LINKS k_osal)

if (IDF_TARGET)
    set(SRC_FOLDER src/${IDF_TARGET})
    set(PRIVATE_LINKS
            ${PRIVATE_LINKS}
            k_hal
            ignis_pcf8575
    )
else ()
    set(SRC_FOLDER src/host)
    set(PRIVATE_LINKS ${PRIVATE_LINKS} k_ghost_io)
endif ()

add_library(${PROJECT_NAME} ${SRC_FOLDER}/ignis_keymap.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_FOLDER} src)
#target_link_libraries(${PROJECT_NAME} PUBLIC ${PUBLIC_LINKS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})
if (NOT IDF_TARGET)
    add_subdirectory(mock)
endif ()