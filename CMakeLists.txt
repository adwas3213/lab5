cmake_minimum_required(VERSION 3.20)
project(lab_5_do_wsl C)

set(CMAKE_C_STANDARD 11)

include_directories(zad_2)
include_directories(zad_2/pomiar_czasu)

add_executable(lab_5_do_wsl
        zad_2/pomiar_czasu/pomiar_czasu.c
        zad_2/pomiar_czasu/pomiar_czasu.h
        zad_2/dekompozycja_obszaru.c
        zad_2/dekompozycja_petli.c
        zad_2/obliczanie_calki.c
        zad_2/pomiar_czasu.h)
