project(ignis_keymap VERSION 1.0 LANGUAGES C)


if (IDF_TARGET)
endif ()

add_library(${PROJECT_NAME} src/ignis_keymap.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
#target_include_directories(${PROJECT_NAME} PRIVATE ${K_OSAL_PRIVATE_INCLUDES})
#target_link_libraries(${PROJECT_NAME} PUBLIC ${K_OSAL_PUBLIC_LINKS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${K_OSAL_PRIVATE_LINKS})
if (NOT IDF_TARGET)
    add_subdirectory(mock)
endif ()