cmake_minimum_required(VERSION 4.0)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

# Сборка основной программы (меню)
add_executable(laba_1_main
        main.c
        DynamicArray.c
        DynamicArray.h
        TypesInfo.h
        DoubleType.h
        DoubleType.c
        ComplexType.h
        ComplexType.c
        operations.h
        operations.c)

# Сборка программы с тестами
add_executable(laba_1_tests
        tests.c
        DynamicArray.c
        DynamicArray.h
        TypesInfo.h
        DoubleType.h
        DoubleType.c
        ComplexType.h
        ComplexType.c
        operations.h
        operations.c)