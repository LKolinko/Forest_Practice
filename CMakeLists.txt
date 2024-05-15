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
        src/TreeDrawer.cpp
        core/TreeDrawer.h
        src/RoundedRectangle.cpp
        src/App.cpp
        app/App.h
        src/Treap.cpp
        core/Treap.h
        app/Button.h
        src/Button.cpp
        src/TextBox.cpp
        src/TextBox.cpp
        core/Splay.h
        src/Table.cpp
        app/Table.h
        src/RBTree.cpp
        core/RBTree.h
)

target_link_libraries(Forest PRIVATE sfml-graphics)
