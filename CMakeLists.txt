cmake_minimum_required(VERSION 3.16)

project(VampireSurvivors)

include(cmake/Config.cmake)

include(cmake/SetupSFML.cmake)

add_subdirectory(src)

include(cmake/Install.cmake)
