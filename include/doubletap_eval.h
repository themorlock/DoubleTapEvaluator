//
// Created by Saaketh Vangati on 3/3/21.
//

#ifndef DOUBLETAPEVALUATOR_DOUBLETAP_EVAL_H
#define DOUBLETAPEVALUATOR_DOUBLETAP_EVAL_H

#include <stdint.h>

#define NUM_5_CARD_HANDS (2598960)
#define FIRST_5_CARD_HAND (31ULL)
#define LAST_5_CARD_HAND (4362862139015168ULL)

#define NUM_6_CARD_HANDS (20358520)
#define FIRST_6_CARD_HAND (63ULL)
#define LAST_6_CARD_HAND (4433230883192832ULL)

#define NUM_7_CARD_HANDS (133784560)
#define FIRST_7_CARD_HAND (127ULL)
#define LAST_7_CARD_HAND (4468415255281664ULL)

int doubletap_5_initialize(const char *path);

int doubletap_6_initialize(const char *path);

int doubletap_7_initialize(const char *path);

int16_t doubletap_eval_5(int cards[5]);

int16_t doubletap_eval_6(int cards[6]);

int16_t doubletap_eval_7(int cards[7]);

int16_t doubletap_eval_5_fast(unsigned long long cards);

int16_t doubletap_eval_6_fast(unsigned long long cards);

int16_t doubletap_eval_7_fast(unsigned long long cards);

#endif //DOUBLETAPEVALUATOR_DOUBLETAP_EVAL_H
