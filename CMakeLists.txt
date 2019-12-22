cmake_minimum_required(VERSION 3.15)
project(grpwk C)

set(CMAKE_C_STANDARD 99)

add_executable(grpwk  ./middlesub linked_list.c linked_list.h string_info.h input_win.c example/BM.h example/grpwk.h example/Algorithm_template.c constructions.c constructions.h example/BM.c example/BM+.c example/test.c example/Speedtest.c example/BM_temp.c example/BM_temp2.c example/adeumeru.c)