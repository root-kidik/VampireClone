set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC ${SRCROOT}/Main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
