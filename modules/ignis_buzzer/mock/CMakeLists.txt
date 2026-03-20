project(ignis_buzzer_mock VERSION 1.0 LANGUAGES C)


add_library(${PROJECT_NAME} ignis_buzzer_mock.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ../include)
target_link_libraries(${PROJECT_NAME} PUBLIC fff)
