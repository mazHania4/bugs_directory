cmake_minimum_required(VERSION 3.27)
project(bugs_directory)

set(CMAKE_CXX_STANDARD 17)

add_executable(bugs_directory main.cpp
        hash_table/HashTable.cpp
        hash_table/Pair.cpp
        hash_table/Pair.h
        Tree.cpp
        List.cpp
        Controller.cpp
        Controller.h
        model/Field.cpp
        model/Field.h
        FileManager.cpp
)
