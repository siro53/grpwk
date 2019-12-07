cmake_minimum_required(VERSION 3.15)
project(grpwk C)

set(CMAKE_C_STANDARD 99)

add_executable(grpwk  string_info.h input_win.c example/grpwk.c example/grpwk.h example/Algorithm_template.c constructions.c constructions.h example/algorithm.h example/BM.c)