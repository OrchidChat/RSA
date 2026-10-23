cmake_minimum_required(VERSION 3.25)
project(RSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(RSA
        RivestShamirAdlemanEncryption.hpp
        RSAwrapper.cpp
)


target_include_directories(RSA PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external)


target_link_libraries(RSA PRIVATE embind)