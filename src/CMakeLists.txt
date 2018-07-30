cmake_minimum_required(VERSION 3.10)
project(CPP_Networking)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

find_package(Boost REQUIRED system thread regex)

message(${Boost_LIBRARY_DIRS})

add_subdirectory(server)
add_subdirectory(messaging)

add_executable(cpp_networking main.cpp)
target_link_libraries(cpp_networking server messaging)
