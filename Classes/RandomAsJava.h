#ifndef __RANDOMASJAVA__
#define __RANDOMASJAVA__

class RandomAsJava
{
private:
    static long long multiplier;
    static long long addend;
    static long long mask_lli;
    static long long mask;
    static long long seed;

    static int next(int bits);
public:
    RandomAsJava(void);
    ~RandomAsJava(void);

    static int nextInt(int max);
};

#endif