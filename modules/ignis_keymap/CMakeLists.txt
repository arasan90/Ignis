project(ignis_keymap VERSION 1.0 LANGUAGES C)

set(SRC_FOLDER)
set(PUBLIC_LINKS)

if (IDF_TARGET)
    set(SRC_FOLDER src/${IDF_TARGET})
else ()
    set(SRC_FOLDER src/host)
endif ()

add_library(${PROJECT_NAME} ${SRC_FOLDER}/ignis_keymap.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_FOLDER})
#target_link_libraries(${PROJECT_NAME} PUBLIC ${K_OSAL_PUBLIC_LINKS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${K_OSAL_PRIVATE_LINKS})
if (NOT IDF_TARGET)
    add_subdirectory(mock)
endif ()