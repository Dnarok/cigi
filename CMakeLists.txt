cmake_minimum_required(VERSION 3.20)

set(MY_PROJECT_NAME name)

project(
    ${MY_PROJECT_NAME}
    LANGUAGES CXX
    VERSION   1.0
)

set(CMAKE_CXX_STANDARD 23)

option(BUILD_TESTS "Build the tests" ON)
add_subdirectory(external)

add_library(${MY_PROJECT_NAME}
    include/header.hpp
    source/source.cpp
)

target_include_directories(${MY_PROJECT_NAME}
    PUBLIC include
)

target_link_libraries(${MY_PROJECT_NAME}
    PUBLIC spdlog::spdlog
    PUBLIC fmt::fmt
    PUBLIC contract::contract
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()