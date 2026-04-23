cmake_minimum_required(VERSION 4.2)
project(Progetto_info)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Progetto_info
        catalogo.h
        combat.cpp
        combat.h
        entity.h
        main.cpp
        mappa.cpp
        mappa.h
        menu.cpp
        menu.h
        palette.h)