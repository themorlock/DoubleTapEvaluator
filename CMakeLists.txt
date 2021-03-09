cmake_minimum_required(VERSION 3.17)
project(DoubleTapEvaluator C)

set(CMAKE_C_FLAGS_RELEASE "-Ofast -march=native")

add_library(${PROJECT_NAME} STATIC src/doubletap_eval.c include/doubletap_eval tests/all_hands_test.c)

add_executable (AllHandsTest tests/all_hands_test.c)
target_link_libraries (AllHandsTest ${PROJECT_NAME})

add_executable (RandomHandsTest tests/random_hands_test.c)
target_link_libraries (RandomHandsTest ${PROJECT_NAME})
