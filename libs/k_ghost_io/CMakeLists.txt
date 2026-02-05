project(k_ghost_io VERSION 1.0 LANGUAGES C)

if (TARGET_PLATFORM STREQUAL "esp32c3")
    message(FATAL_ERROR "K_ghost_io is only supported on hosts platforms")
endif ()

include(k_ghost_io/k_ghost_io.cmake)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${public_includes})
target_include_directories(${PROJECT_NAME} PRIVATE ${private_includes})
target_link_libraries(${PROJECT_NAME} PUBLIC ${public_linked_libs})
target_link_libraries(${PROJECT_NAME} PRIVATE ${private_linked_libs})

k_ghost_io_create_mock_library()
k_ghost_io_create_dep_libraries()