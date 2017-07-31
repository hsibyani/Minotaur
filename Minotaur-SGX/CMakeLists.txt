cmake_minimum_required(VERSION 3.6)
project(Minotaur)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        app.cpp
        Client.cpp
        Client.h
        count.cpp
        Server.cpp
        Server.h
        splitter.cpp
        spout.cpp
        utils.cpp
        utils.hpp
        zhelpers.hpp
        zmq.hpp)

add_executable(Minotaur ${SOURCE_FILES})
include_directories(/usr/local/Cellar/zeromq/4.2.2/include /usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)
TARGET_LINK_LIBRARIES(Minotaur zmq)