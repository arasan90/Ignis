set(K_OSAL_SRCS
        ${CMAKE_CURRENT_LIST_DIR}/src/${K_OSAL_PLATFORM}/thread.c
        ${CMAKE_CURRENT_LIST_DIR}/src/${K_OSAL_PLATFORM}/mutex.c
)
set(K_OSAL_PUBLIC_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include)
set(K_OSAL_PRIVATE_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/src/${K_OSAL_PLATFORM})
set(K_OSAL_PUBLIC_LINKS)
set(K_OSAL_PRIVATE_LINKS)

function(create_mock_library)
    add_library(k_osal_mock ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/mock/k_osal_mock.c)
    target_include_directories(k_osal_mock PUBLIC
            ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include
            ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/mock
    )
    target_link_libraries(k_osal_mock PUBLIC fff)
endfunction()