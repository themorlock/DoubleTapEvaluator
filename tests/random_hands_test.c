//
// Created by Saaketh Vangati on 3/8/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/doubletap_eval.h"

#define NUM_ITERATIONS (1 << 16)

#define NUM_RANDOM_HANDS (1 << 10)

static void initialize_random_hands();

static void benchmark_random_hands();

int main()
{
    doubletap_5_initialize("../data/DOUBLETAP_TABLE_5.dat");
    doubletap_6_initialize("../data/DOUBLETAP_TABLE_6.dat");
    doubletap_7_initialize("../data/DOUBLETAP_TABLE_7.dat");

    initialize_random_hands();

    benchmark_random_hands();

    return 0;
}

static int deck[52];
static unsigned long long random_5_hands[NUM_RANDOM_HANDS];
static unsigned long long random_6_hands[NUM_RANDOM_HANDS];
static unsigned long long random_7_hands[NUM_RANDOM_HANDS];

static void initialize_deck()
{
    for(int i = 0; i < 52; ++i)
    {
        deck[i] = i;
    }
}

static void shuffle_deck()
{
    for(int i = 51; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

static unsigned long long build_hand(int *cards, int len)
{
    unsigned long long hand = 0;
    for(int i = 0; i < len; ++i)
    {
        hand |= (1ULL << cards[i]);
    }
    return hand;
}

static void initialize_random_5_hands()
{
    for(int i = 0; i < NUM_RANDOM_HANDS; ++i)
    {
        shuffle_deck();
        random_5_hands[i] = build_hand(deck, 5);
    }
}

static void initialize_random_6_hands()
{
    for(int i = 0; i < NUM_RANDOM_HANDS; ++i)
    {
        shuffle_deck();
        random_6_hands[i] = build_hand(deck, 6);
    }
}

static void initialize_random_7_hands()
{
    for(int i = 0; i < NUM_RANDOM_HANDS; ++i)
    {
        shuffle_deck();
        random_7_hands[i] = build_hand(deck, 7);
    }
}

static void initialize_random_hands()
{
    initialize_deck();
    initialize_random_5_hands();
    initialize_random_6_hands();
    initialize_random_7_hands();
}

static void benchmark_random_5_hands()
{
    int hand_num;
    clock_t start = clock();
    for(hand_num = 0; hand_num < NUM_ITERATIONS; ++hand_num)
    {
        doubletap_eval_5_fast(random_5_hands[hand_num % NUM_RANDOM_HANDS]);
    }
    clock_t end = clock();
    double elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    double evals_per_sec = (double) (hand_num + 1) / elapsed;
    printf("[Random 5-Card Hands] %.1lf Evaluations/Second\n", evals_per_sec);
}

static void benchmark_random_6_hands()
{
    int hand_num;
    clock_t start = clock();
    for(hand_num = 0; hand_num < NUM_ITERATIONS; ++hand_num)
    {
        doubletap_eval_6_fast(random_6_hands[hand_num % NUM_RANDOM_HANDS]);
    }
    clock_t end = clock();
    double elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    double evals_per_sec = (double) (hand_num + 1) / elapsed;
    printf("[Random 6-Card Hands] %.1lf Evaluations/Second\n", evals_per_sec);
}

static void benchmark_random_7_hands()
{
    int hand_num;
    clock_t start = clock();
    for(hand_num = 0; hand_num < NUM_ITERATIONS; ++hand_num)
    {
        doubletap_eval_7_fast(random_7_hands[hand_num % NUM_RANDOM_HANDS]);
    }
    clock_t end = clock();
    double elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    double evals_per_sec = (double) (hand_num + 1) / elapsed;
    printf("[Random 7-Card Hands] %.1lf Evaluations/Second\n", evals_per_sec);
}

static void benchmark_random_hands()
{
    benchmark_random_5_hands();
    benchmark_random_6_hands();
    benchmark_random_7_hands();
}
