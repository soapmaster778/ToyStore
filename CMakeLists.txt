cmake_minimum_required(VERSION 3.25)
project(ToyStoreRoleUA_FULL)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToyStoreRoleUA_FULL
        main.cpp
        UserManager.cpp
        ToyManager.cpp
        Toy.cpp
        LuxuryToy.cpp
        SoldRecord.cpp
        AbstractItem.cpp
        InputValidator.cpp
)
