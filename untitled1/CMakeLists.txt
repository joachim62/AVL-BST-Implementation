cmake_minimum_required(VERSION 3.29)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp
        include/BST.h
        tests/test_main.cpp
        tests/test_basic.h
        tests/test_advanced.h
        cases/stock_market.cpp
        tests/Performance_tests.h
        include/AVL.h
        cases/Contacts.cpp
)
