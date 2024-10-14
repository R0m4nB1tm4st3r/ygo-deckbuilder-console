cmake_minimum_required(VERSION 3.29)
project(deckbuilder)

set(CMAKE_CXX_STANDARD 26)

add_executable(deckbuilder main.cpp
        HttpRequestHandler/HttpRequestHandler.cpp
        HttpRequestHandler/HttpRequestHandler.h)
target_link_libraries(deckbuilder curl jsoncpp)
