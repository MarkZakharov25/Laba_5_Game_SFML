cmake_minimum_required(VERSION 3.27)
project(Game_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(Game_1 main.cpp
        Player.cpp
        Player.h
        Skeleton.cpp
        Skeleton.h
        FireBall.cpp
        FireBall.h
        Math.cpp
        Math.h)

set(SFML_DIR "C:\\Users\\D\\CLionProjects\\lib\\SFML\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(Game_1 sfml-graphics)
target_include_directories(Game_1 PUBLIC "C:\\Users\\D\\CLionProjects\\lib\\SFML\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\include")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)