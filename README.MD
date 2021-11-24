`DoubleTap Evaluator`
=

### Prerequisites:
- `gcc`, `clang`, or another C compiler

- `cmake>=3.17`

### Build instructions:
```shell
$ git clone https://github.com/themorlock/DoubleTapEvaluator.git
$ cd DoubleTapEvaluator
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
$ unzip ../data/DOUBLETAP_TABLES_COMPRESSED.zip -d ../data/ 
```

### Benchmark:
|       Test          | Evaluations/Second |
| ----------------    | ------------------ |
| All 5-Card Hands    |     292840676.1    |
| All 6-Card Hands    |     221372489.5    |
| All 7-Card Hands    |     235819763.9    |
| Random 5-Card Hands |     161421182.3    |
| Random 6-Card Hands |     167186224.5    |
| Random 7-Card Hands |     132665991.9    |

### Usage:
```c
#include "doubletap_eval.h"

int main()
{
    doubletap_5_initialize("DOUBLETAP_TABLE_5.dat");
    doubletap_6_initialize("DOUBLETAP_TABLE_6.dat");
    doubletap_7_initialize("DOUBLETAP_TABLE_7.dat");

    unsigned long long hand5 = 34376582145ULL;
    doubletap_eval_5_fast(hand5);
    
    unsigned long long hand6 = 34376582153ULL;
    doubletap_eval_6_fast(hand6);
    
    unsigned long long hand7 = 584132396041ULL;
    doubletap_eval_7_fast(hand7);

    return 0;
}
```

### Algorithm:

| Card  | Value |
| ----- | ----- |
|  2c   |    1  |
|  2d   |    2  |
|  2h   |    3  |
|  2s   |    4  |
|  3c   |    5  |
|  3d   |    6  |
|  3h   |    7  |
|  3s   |    8  |
|  4c   |    9  |
|  4d   |   10  |
|  4h   |   11  |
|  4s   |   12  |
|  5c   |   13  |
|  5d   |   14  |
|  5h   |   15  |
|  5s   |   16  |
|  6c   |   17  |
|  6d   |   18  |
|  6h   |   19  |
|  6s   |   20  |
|  7c   |   21  |
|  7d   |   22  |
|  7h   |   23  |
|  7s   |   24  |
|  8c   |   25  |
|  8d   |   26  |
|  8h   |   27  |
|  8s   |   28  |
|  9c   |   29  |
|  9d   |   30  |
|  9h   |   31  |
|  9s   |   32  |
|  tc   |   33  |
|  td   |   34  |
|  th   |   35  |
|  ts   |   36  |
|  jc   |   37  |
|  jd   |   38  |
|  jh   |   39  |
|  js   |   40  |
|  qc   |   41  |
|  qd   |   42  |
|  qh   |   43  |
|  qs   |   44  |
|  kc   |   45  |
|  kd   |   46  |
|  kh   |   47  |
|  ks   |   48  |
|  ac   |   49  |
|  ad   |   50  |
|  ah   |   51  |
|  as   |   52  |

```
Hand is represented as a 64-bit(unsigned long long) number:
000000000000000000000000100000000001000000010000010000000001
Hand = ts - 8c - 6c - 4h - 2c
```
Set-bit position from the right corresponds to the card.

Evaluator supports 5, 6, and 7 card hand evaluations.

First, the evaluator finds the positions of all the set bits.
Next, it computes the lexicographical rank of the hand.
Finally, it uses this rank to jump into the large lookup table.
DoubleTap comes from the algorithm first jumping into a small
lookup table to compute the lexicographical rank then jumping
into the much larger lookup table.
