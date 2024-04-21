cmake_minimum_required(VERSION 3.6.0)
project(shad_workspace VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_CXX_FLAGS "-Wall -Werror -Wsign-compare")

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all -O2"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

set(CMAKE_CXX_FLAGS_SHADREL "-O2 -DNDEBUG"
    CACHE STRING "Compiler flags for the release version that executes on Yandex.Contest"
    FORCE)

message("General compiler flags: " ${CMAKE_CXX_FLAGS})
message("Debug build compiler flags: " ${CMAKE_CXX_FLAGS_DEBUG})
message("ASAN build compiler flags: " ${CMAKE_CXX_FLAGS_ASAN})
message("ShadRel build compiler flags: " ${CMAKE_CXX_FLAGS_SHADREL})

add_executable(naiv_alghoritm naiv_algorithm.cpp SubstringSearcher.hpp)
add_executable(boyer_mur_mur boyer_mur_mur.cpp SubstringSearcher.hpp)
add_executable(knuta_morisa_prata knuta_morisa_prata.cpp SubstringSearcher.hpp)