cmake_minimum_required(VERSION 3.10)

project(webcpp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

set(SOURCE_FILES
   
    src/server.h
    src/server.cpp
    src/request.h
    src/request.cpp
    src/page.h
    src/page.cpp
    src/client.h
    src/client.cpp
    src/httprespone.h
    src/httprespone.cpp
    src/file.h
    src/file.cpp
    src/files.h
    src/files.cpp
    src/bytearray.h
    src/bytearray.cpp

)
add_library(webcpp ${SOURCE_FILES})
target_link_libraries(webcpp ${OPENSSL_LIBRARIES})
target_link_libraries(webcpp stdc++fs)
