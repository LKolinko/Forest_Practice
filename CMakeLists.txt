cmake_minimum_required(VERSION 3.28)
project(Forest)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 23)

add_executable(Forest main.cpp
        AVL.h
        Screen.h
        Singleton.h
        TreeDrawer.cpp
        TreeDrawer.h
        RoundedRectangle.cpp
        App.cpp
        App.h
        Treap.cpp
        Treap.h
        Button.h
        Button.cpp
        TextBox.cpp
        TextBox.cpp
        Splay.h
        Table.cpp
        Table.h
        RBTree.cpp
        RBTree.h
)

target_link_libraries(Forest PRIVATE sfml-graphics)
