//
// Created by Saaketh Vangati on 3/3/21.
//

#include "../include/doubletap_eval.h"

#include <string.h>
#include <stdio.h>

static int16_t DTT_5[2598960];
static int16_t DTT_6[20358520];
static int16_t DTT_7[133784560];

int doubletap_5_initialize(const char *path)
{
    memset(DTT_5, 0, sizeof(DTT_5));
    FILE *f = fopen(path, "rb");
    if(f == NULL)
        return 0;
    fread(DTT_5, sizeof(DTT_5), 1, f);
    fclose(f);
    return 1;
}

int doubletap_6_initialize(const char *path)
{
    memset(DTT_6, 0, sizeof(DTT_6));
    FILE *f = fopen(path, "rb");
    if(f == NULL)
        return 0;
    fread(DTT_6, sizeof(DTT_6), 1, f);
    fclose(f);
    return 1;
}

int doubletap_7_initialize(const char *path)
{
    memset(DTT_7, 0, sizeof(DTT_7));
    FILE *f = fopen(path, "rb");
    if(f == NULL)
        return 0;
    fread(DTT_7, sizeof(DTT_7), 1, f);
    fclose(f);
    return 1;
}

static inline int choose(int n, int k)
{
    static const int lookup[8][52] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                      {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
                                      {0, 0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210, 231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666, 703, 741, 780, 820, 861, 903, 946, 990, 1035, 1081, 1128, 1176, 1225, 1275},
                                      {0, 0, 0, 1, 4, 10, 20, 35, 56, 84, 120, 165, 220, 286, 364, 455, 560, 680, 816, 969, 1140, 1330, 1540, 1771, 2024, 2300, 2600, 2925, 3276, 3654, 4060, 4495, 4960, 5456, 5984, 6545, 7140, 7770, 8436, 9139, 9880, 10660, 11480, 12341, 13244, 14190, 15180, 16215, 17296, 18424, 19600, 20825},
                                      {0, 0, 0, 0, 1, 5, 15, 35, 70, 126, 210, 330, 495, 715, 1001, 1365, 1820, 2380, 3060, 3876, 4845, 5985, 7315, 8855, 10626, 12650, 14950, 17550, 20475, 23751, 27405, 31465, 35960, 40920, 46376, 52360, 58905, 66045, 73815, 82251, 91390, 101270, 111930, 123410, 135751, 148995, 163185, 178365, 194580, 211876, 230300, 249900},
                                      {0, 0, 0, 0, 0, 1, 6, 21, 56, 126, 252, 462, 792, 1287, 2002, 3003, 4368, 6188, 8568, 11628, 15504, 20349, 26334, 33649, 42504, 53130, 65780, 80730, 98280, 118755, 142506, 169911, 201376, 237336, 278256, 324632, 376992, 435897, 501942, 575757, 658008, 749398, 850668, 962598, 1086008, 1221759, 1370754, 1533939, 1712304, 1906884, 2118760, 2349060},
                                      {0, 0, 0, 0, 0, 0, 1, 7, 28, 84, 210, 462, 924, 1716, 3003, 5005, 8008, 12376, 18564, 27132, 38760, 54264, 74613, 100947, 134596, 177100, 230230, 296010, 376740, 475020, 593775, 736281, 906192, 1107568, 1344904, 1623160, 1947792, 2324784, 2760681, 3262623, 3838380, 4496388, 5245786, 6096454, 7059052, 8145060, 9366819, 10737573, 12271512, 13983816, 15890700, 18009460},
                                      {0, 0, 0, 0, 0, 0, 0, 1, 8, 36, 120, 330, 792, 1716, 3432, 6435, 11440, 19448, 31824, 50388, 77520, 116280, 170544, 245157, 346104, 480700, 657800, 888030, 1184040, 1560780, 2035800, 2629575, 3365856, 4272048, 5379616, 6724520, 8347680, 10295472, 12620256, 15380937, 18643560, 22481940, 26978328, 32224114, 38320568, 45379620, 53524680, 62891499, 73629072, 85900584, 99884400, 115775100}};
    return lookup[k][n];
}

#define SWAP(x,y) if (cards[y] < cards[x]) { int tmp = cards[x]; cards[x] = cards[y]; cards[y] = tmp; }
static inline void sort_cards_5(int cards[5])
{
    SWAP(0, 1)
    SWAP(3, 4)
    SWAP(2, 4)
    SWAP(2, 3)
    SWAP(0, 3)
    SWAP(0, 2)
    SWAP(1, 4)
    SWAP(1, 3)
    SWAP(1, 2)
}

static inline void sort_cards_6(int cards[6])
{
    SWAP(1, 2)
    SWAP(0, 2)
    SWAP(0, 1)
    SWAP(4, 5)
    SWAP(3, 5)
    SWAP(3, 4)
    SWAP(0, 3)
    SWAP(1, 4)
    SWAP(2, 5)
    SWAP(2, 4)
    SWAP(1, 3)
    SWAP(2, 3)
}

static inline void sort_cards_7(int cards[7])
{
    SWAP(1, 2)
    SWAP(0, 2)
    SWAP(0, 1)
    SWAP(3, 4)
    SWAP(5, 6)
    SWAP(3, 5)
    SWAP(4, 6)
    SWAP(4, 5)
    SWAP(0, 4)
    SWAP(0, 3)
    SWAP(1, 5)
    SWAP(2, 6)
    SWAP(2, 5)
    SWAP(1, 3)
    SWAP(2, 4)
    SWAP(2, 3)
}
#undef COND
#undef SWAP

static inline int get_index_5(int cards[5])
{
    sort_cards_5(cards);
    return (((choose(cards[0], 1) + choose(cards[1], 2)) + (choose(cards[2], 3)
            + choose(cards[3], 4))) + choose(cards[4], 5));
}

static inline int get_index_6(int cards[6])
{
    sort_cards_6(cards);
    return (((choose(cards[0], 1) + choose(cards[1], 2)) + (choose(cards[2], 3)
           + choose(cards[3], 4))) + (choose(cards[4], 5) + choose(cards[5], 6)));
}

static inline int get_index_7(int cards[7])
{
    sort_cards_7(cards);
    return (((choose(cards[0], 1) + choose(cards[1], 2)) + (choose(cards[2], 3)
            + choose(cards[3], 4))) + ((choose(cards[4], 5) + choose(cards[5], 6))
            + choose(cards[6], 7)));

}

static inline int ctzl(unsigned long long num)
{
#if __has_builtin(__builtin_ctzl)
    return __builtin_ctzl(num);
#else
    int count;
    for(count = 0; count < 7 && !(num & 1); ++count)
    {
        num >>= 1;
    }
    return count;
#endif
}

static inline int get_index_5_fast(unsigned long long cards)
{
    int sum = choose(ctzl(cards), 1);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 2);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 3);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 4);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 5);
    return sum;
}

static inline int get_index_6_fast(unsigned long long cards)
{
    int sum = choose(ctzl(cards), 1);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 2);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 3);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 4);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 5);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 6);
    return sum;
}

static inline int get_index_7_fast(unsigned long long cards)
{
    int sum = choose(ctzl(cards), 1);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 2);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 3);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 4);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 5);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 6);
    cards &= cards - 1;
    sum += choose(ctzl(cards), 7);
    return sum;
}

int16_t doubletap_eval_5(int cards[5])
{
    return DTT_5[get_index_5(cards)];
}

int16_t doubletap_eval_6(int cards[6])
{
    return DTT_6[get_index_6(cards)];
}

int16_t doubletap_eval_7(int cards[7])
{
    return DTT_7[get_index_7(cards)];
}

int16_t doubletap_eval_5_fast(unsigned long long cards)
{
    return DTT_5[get_index_5_fast(cards)];
}

int16_t doubletap_eval_6_fast(unsigned long long cards)
{
    return DTT_6[get_index_6_fast(cards)];
}

int16_t doubletap_eval_7_fast(unsigned long long cards)
{
    return DTT_7[get_index_7_fast(cards)];
}
