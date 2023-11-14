cmake_minimum_required(VERSION 3.27)
project(HotelProject2)

set(CMAKE_CXX_STANDARD 17)

add_executable(HotelProject2 main.cpp
        includes/menu.cpp
        includes/menu.h
        includes/room.cpp
        includes/room.h
        includes/hotel.cpp
        includes/hotel.h
        includes/includes.h)
