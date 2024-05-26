cmake_minimum_required(VERSION 3.27)
project(Game_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "C:/Users/D/CLionProjects/lib/SFML/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

set(TINYXML2_DIR "C:/Users/D/CLionProjects/Game_1")
add_library(tinyxml2 STATIC ${TINYXML2_DIR}/tinyxml2.cpp)
include_directories(${TINYXML2_DIR})

set(SOURCES
        main.cpp
        Player.cpp
        Skeleton.cpp
        FireBall.cpp
        Math.cpp
        TileMap.cpp
        Trap.cpp
        Trap.h
        Shield.cpp
        Shield.h
)

add_executable(Game_1 ${SOURCES})

target_link_libraries(Game_1 sfml-graphics sfml-window sfml-system)

target_link_libraries(Game_1 tinyxml2)

target_include_directories(Game_1 PUBLIC "C:/Users/D/CLionProjects/lib/SFML/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/include")


