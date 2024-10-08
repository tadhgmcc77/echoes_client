cmake_minimum_required(VERSION 3.30) # Use a valid CMake version. CMake 3.30 does not exist.
project(ECHOES_CLIENT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(Boost_DIR "C:/Users/tadhg/OneDrive/Desktop/boost_install/boots-test/boost_1_86_0/stage/lib/cmake/Boost-1.86.0")
    set(CURL_INCLUDE_DIR "C:/Users/tadhg/OneDrive/Desktop/boost_install/curl/include")
    set(CURL_LIBRARY "C:/Users/tadhg/OneDrive/Desktop/boost_install/curl/lib/libcurl.a")
    set(nlohmann_json_DIR "C:/Program Files/vcpkg/installed/x64-windows/share/nlohmann_json")
    #target_include_directories(ECHOES_BACKEND PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/asio/include)    
endif()


find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)



add_executable(ECHOES_CLIENT src/main.cpp)



target_link_libraries(ECHOES_CLIENT
    PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Boost::system
)
