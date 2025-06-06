cmake_minimum_required(VERSION 3.10)
project(WebSocketTest)

# For drogon
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)

# For JWT
set(JWT_BUILD_EXAMPLES OFF)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR})

file(GLOB WSTEST_SOURCES "src/*.cpp" "src/*/*.cpp")
list(FILTER WSTEST_SOURCES EXCLUDE REGEX "src/client.cpp")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    WebSocketTest

    ${WSTEST_SOURCES}
)

add_executable(
    WebSocketClient

    src/client.cpp
)

target_link_libraries(WebSocketTest drogon jwt-cpp)
target_link_libraries(WebSocketClient drogon)

include_directories(${CMAKE_SOURCE_DIR}/include/)

target_include_directories(WebSocketTest PUBLIC ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(libraries/drogon)
add_subdirectory(libraries/jwt-cpp)
