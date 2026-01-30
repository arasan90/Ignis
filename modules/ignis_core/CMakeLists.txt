project(ignis_core VERSION 1.0 LANGUAGES C)

set(SOURCES
        src/ignis_core.c
)

set(PUBLIC_INCLUDES
        include
)

set(PRIVATE_INCLUDES
        src
)

set(PRIVATE_LINKS
        k_osal
        ignis_keymap
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})

if (NOT TARGET_PLATFORM STREQUAL "esp32c3")
    add_subdirectory(test)
    add_subdirectory(mock)
endif ()