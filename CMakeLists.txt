cmake_minimum_required(VERSION 3.10)

project(webcpp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

set(SOURCE_FILES
   
    server.h
    server.cpp
    request.h
    request.cpp
    page.h
    page.cpp
    client.h
    client.cpp
    httprespone.h
    httprespone.cpp
    file.h
    file.cpp
    files.h
    files.cpp
    bytearray.h
    bytearray.cpp

)
add_library(webcpp ${SOURCE_FILES})
target_link_libraries(webcpp ${OPENSSL_LIBRARIES})
target_link_libraries(webcpp stdc++fs)
