project(ignis_core_test VERSION 1.0 LANGUAGES C CXX)
include(GoogleTest)

set(SOURCES
        ignis_core_test.cpp
        ../src/ignis_core.c
)

set(PUBLIC_INCLUDES
        ../include
)

set(PRIVATE_INCLUDES
        ../src
)

set(PRIVATE_LINKS
        ignis_keymap_mock
        ignis_display_mock
        k_osal_mock
        GTest::gtest_main
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})
target_link_libraries(${PROJECT_NAME} PRIVATE k_osal)
gtest_discover_tests(${PROJECT_NAME})