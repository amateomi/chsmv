cmake_minimum_required(VERSION 3.15..3.23)

project(chsmv
        VERSION 0.1.0
        DESCRIPTION "Chess move validation library"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
