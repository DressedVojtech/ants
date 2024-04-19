cmake_minimum_required (VERSION 3.11)


project ( ants CXX )

set (CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release")
    message (STATUS "Build type not specified: Use Release by default")
endif (NOT CMAKE_BUILD_TYPE)

# executable
add_executable (ants main.cpp)
#target_include_directories(ants src)

# link SFML
find_package (SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries (ants PRIVATE sfml-graphics sfml-window sfml-system)