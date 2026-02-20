project(ignis_pcf8575_test VERSION 1.0 LANGUAGES C CXX)
include(GoogleTest)

set(SOURCES
        ignis_pcf8575_test.cpp
        ../src/ignis_pcf8575.c
)

set(PUBLIC_INCLUDES
        ../include
)

set(PRIVATE_INCLUDES
        ../src
)

set(PRIVATE_LINKS
        k_hal_mock
        k_osal_mock
        GTest::gtest_main
)

set(PUBLIC_LINKS
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PUBLIC_LINKS})
gtest_discover_tests(${PROJECT_NAME})