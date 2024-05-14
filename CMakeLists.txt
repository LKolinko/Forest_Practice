cmake_minimum_required(VERSION 3.28)
project(Forest)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 23)

add_executable(Forest main.cpp
        core/AVL.h
        app/Screen.h
        app/Singleton.h
        scr/TreeDrawer.cpp
        core/TreeDrawer.h
        scr/RoundedRectangle.cpp
        scr/App.cpp
        app/App.h
        scr/Treap.cpp
        core/Treap.h
        app/Button.h
        scr/Button.cpp
        scr/TextBox.cpp
        scr/TextBox.cpp
        core/Splay.h
        scr/Table.cpp
        app/Table.h
        scr/RBTree.cpp
        core/RBTree.h
)

target_link_libraries(Forest PRIVATE sfml-graphics)
