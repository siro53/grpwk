cmake_minimum_required(VERSION 3.15)
project(grpwk_ C)

set(CMAKE_C_STANDARD 99)

add_executable(grpwk_ ./middlesub/BM+.c ./middlesub/BM.h ./middlesub/grpwk.c ./middlesub/grpwk.h ./middlesub/itoi.c ./middlesub/itoi.h linked_list.c ahocorasick.c ahocorasick.h ahotrie.c ahotrie.h  linked_list.h string_info.h input_win.c constructions.c constructions.h)