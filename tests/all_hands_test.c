//
// Created by Saaketh Vangati on 3/7/21.
//

#include <stdio.h>
#include <time.h>

#include "../include/doubletap_eval.h"

static void benchmark_all_hands();

int main()
{
    doubletap_5_initialize("../data/DOUBLETAP_TABLE_5.dat");
    doubletap_6_initialize("../data/DOUBLETAP_TABLE_6.dat");
    doubletap_7_initialize("../data/DOUBLETAP_TABLE_7.dat");

    benchmark_all_hands();

    return 0;
}

void next_hand(unsigned long long *x)
{
    unsigned long long u = *x & -*x;
    unsigned long long v = u + *x;
    *x = v + (((v ^ *x) >> __builtin_ctz(u)) >> 2);
}

static void benchmark_all_5_hands()
{
    int hand_num;
    unsigned long long x = FIRST_5_CARD_HAND;
    clock_t start = clock();
    for(hand_num = 0; hand_num < NUM_5_CARD_HANDS; ++hand_num)
    {
        doubletap_eval_5_fast(x);
        next_hand(&x);
    }
    clock_t end = clock();
    double elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    double evals_per_sec = (double) (hand_num + 1) / elapsed;
    printf("[All 5-Card Hands] %.1lf Evaluations/Second\n", evals_per_sec);
}

static void benchmark_all_6_hands()
{
    int hand_num;
    unsigned long long x = FIRST_6_CARD_HAND;
    clock_t start = clock();
    for(hand_num = 0; hand_num < NUM_6_CARD_HANDS; ++hand_num)
    {
        doubletap_eval_6_fast(x);
        next_hand(&x);
    }
    clock_t end = clock();
    double elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    double evals_per_sec = (double) (hand_num + 1) / elapsed;
    printf("[All 6-Card Hands] %.1lf Evaluations/Second\n", evals_per_sec);
}

static void benchmark_all_7_hands()
{
    int hand_num;
    unsigned long long x = FIRST_7_CARD_HAND;
    clock_t start = clock();
    for(hand_num = 0; hand_num < NUM_7_CARD_HANDS; ++hand_num)
    {
        doubletap_eval_7_fast(x);
        next_hand(&x);
    }
    clock_t end = clock();
    double elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    double evals_per_sec = (double) (hand_num + 1) / elapsed;
    printf("[All 7-Card Hands] %.1lf Evaluations/Second\n", evals_per_sec);
}

void benchmark_all_hands()
{
    benchmark_all_5_hands();
    benchmark_all_6_hands();
    benchmark_all_7_hands();
}
