install(TARGETS ${PROJECT_NAME})
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
