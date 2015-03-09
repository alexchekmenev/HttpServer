cmake_minimum_required(VERSION 2.8.4)
project(LiveChat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES    server/main.cpp
                    server/debug/debug.cpp
                    server/tcp/socket.cpp
                    server/tcp/io_service.cpp
                    server/tcp/server.cpp
                    server/tcp/signaler.cpp
                    server/http/http.cpp
                    server/http/request.cpp
                    server/http/response.cpp)

add_executable(LiveChat ${SOURCE_FILES})