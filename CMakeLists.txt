cmake_minimum_required(VERSION 4.0)
project(NetworkingProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetworkingProject main.cpp)

include(cmake/get_cpm.cmake)

CPMAddPackage(
        NAME Boost
        VERSION 1.89.0
        URL https://github.com/boostorg/boost/releases/download/boost-1.89.0/boost-1.89.0-cmake.tar.xz
        URL_HASH SHA256=67acec02d0d118b5de9eb441f5fb707b3a1cdd884be00ca24b9a73c995511f74
        OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_SKIP_INSTALL_RULES ON" # Set `OFF` for installation
        "BUILD_SHARED_LIBS OFF" "BOOST_INCLUDE_LIBRARIES container\\\;asio\\\;endian" # Note the escapes!
)