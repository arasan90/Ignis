project(ignis_core_mock VERSION 1.0 LANGUAGES C)


add_library(${PROJECT_NAME} ignis_core_mock.c)
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_link_libraries(${PROJECT_NAME} PUBLIC fff)
