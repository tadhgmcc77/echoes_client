cmake_minimum_required(VERSION 3.30) # Use a valid CMake version. CMake 3.30 does not exist.
project(ECHOES_CLIENT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)



add_executable(ECHOES_CLIENT src/main.cpp)



target_link_libraries(ECHOES_CLIENT
    PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)
