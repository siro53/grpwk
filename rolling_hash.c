#include <stdio.h>
#include <string.h>
#include "string_s.h"

#define ROLLINGHASH_MAX_SIZE 500000

typedef struct
{
    long long int first, second;
} Hashtype;

typedef struct
{
    long long int base1;
    long long int base2;
    long long int mod1;
    long long int mod2;
    long long int hash1[ROLLINGHASH_MAX_SIZE];
    long long int hash2[ROLLINGHASH_MAX_SIZE];
    long long int pow1[ROLLINGHASH_MAX_SIZE];
    long long int pow2[ROLLINGHASH_MAX_SIZE];
} RollingHash;

void RollingHash_init(long long int base1, long long int base2, long long int mod1, long long int mod2, RollingHash *rl, string_s *s)
{
    int i, n;

    rl->base1 = base1;
    rl->base2 = base2;
    rl->mod1 = mod1;
    rl->mod2 = mod2;

    n = s->len;

    for (i = 0; i < n + 1; i++)
    {
        rl->hash1[i] = 0;
        rl->hash2[i] = 0;
        rl->pow1[i] = 1;
        rl->pow2[i] = 1;
    }

    for (i = 0; i < n; i++)
    {
        rl->hash1[i + 1] = (rl->hash1[i] + s->str[i]) * rl->base1 % rl->mod1;
        rl->hash2[i + 1] = (rl->hash2[i] + s->str[i]) * rl->base2 % rl->mod2;
        rl->pow1[i + 1] = rl->pow1[i] * rl->base1 % rl->mod1;
        rl->pow2[i + 1] = rl->pow2[i] * rl->base2 % rl->mod2;
    }
}

Hashtype RollingHash_get(int l, int r, RollingHash *rl)
{
    long long int t1 = ((rl->hash1[r] - rl->hash1[l] * rl->pow1[r - l]) % rl->mod1 + rl->mod1) % rl->mod1;
    long long int t2 = ((rl->hash2[r] - rl->hash2[l] * rl->pow1[r - l]) % rl->mod2 + rl->mod2) % rl->mod2;
    Hashtype res;
    res.first = t1;
    res.second = t2;
    return res;
}



int main(void)
{
}