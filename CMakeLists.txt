cmake_minimum_required(VERSION 3.10)
project(sv)

set(CMAKE_CXX_STANDARD 17)
set(PQXX /usr/local/include/pqxx)

find_package(OpenSSL REQUIRED)
find_package(OpenCV  REQUIRED)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIR})

set(SOURCE_FILES
    main.cpp
    server.h
    server.cpp
    request.h
    request.cpp
    database.h
    database.cpp
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
add_executable(sv ${SOURCE_FILES})
target_link_libraries(sv ${OPENSSL_LIBRARIES})
target_link_libraries(sv ${OpenCV_LIBS})
target_link_libraries(sv stdc++fs)
target_link_libraries(sv  ${PQXX_LIB} ${PQ_LIB})

