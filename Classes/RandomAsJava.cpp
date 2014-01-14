#include "RandomAsJava.h"
#include <time.h>


RandomAsJava::RandomAsJava(void)
{
}


RandomAsJava::~RandomAsJava(void)
{
}

long long RandomAsJava::multiplier = 0x5DEECE66DL;
long long RandomAsJava::addend = 0xBL;
long long RandomAsJava::mask_lli = 1;
long long RandomAsJava::mask = (mask_lli << 48) - 1;
long long RandomAsJava::seed = time(0);

// 非线程安全
int RandomAsJava::next(int bits)
{
    static long long oldSeed, nextSeed;
    static int init = 1;
    if (init)
    {
        init = 0;
        oldSeed = seed;
    }
    nextSeed = (oldSeed * multiplier + addend) & mask;
    oldSeed = nextSeed;

    return (int) (nextSeed >> (48 - bits));
}

int RandomAsJava::nextInt(int max)
{
    unsigned randomNumber = next(31);
    return randomNumber % (max + 1);
}