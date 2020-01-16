#include "acorn.h"

#include "stdio.h"

#define STORED_NUMBERS 64
#define DISCARDED_NUMBERS_PER_ROW 10
#define STORED_NUMBERS_PER_ROW 16
#define NUMBERS_PER_ROW (DISCARDED_NUMBERS_PER_ROW + STORED_NUMBERS_PER_ROW)
#define ITERATIONS (STORED_NUMBERS / STORED_NUMBERS_PER_ROW)
#define M 1152921504606846976L
#define DEFAULT_SEED 520197125585483671L

long y_column_1[NUMBERS_PER_ROW] = { DEFAULT_SEED };
long y_column_2[NUMBERS_PER_ROW];
long (*y_last_ptr)[NUMBERS_PER_ROW] = &y_column_1;
long (*y_current_ptr)[NUMBERS_PER_ROW] = &y_column_2;

int current_index = STORED_NUMBERS;
double random_numbers[STORED_NUMBERS];

void init_acorn(long seed)
{
    long* y_last = *y_last_ptr;
    long* y_current = *y_current_ptr;
    if (seed > 0)
    {
        long y_n_0 = seed + (seed % 2);
        for (long* y_last_iter = y_last; y_last_iter < y_last + NUMBERS_PER_ROW; ++y_last_iter)
        {
            *y_last_iter = y_n_0;   
        }
    }

    double* random_numbers_iter = random_numbers;
    for (int m = 0; m < ITERATIONS; ++m)
    {
        y_current[0] = y_last[0];
        for (int n = 1; n < NUMBERS_PER_ROW; ++n)
        {
            y_current[n] = (y_last[n] + y_current[n - 1]) % M;
            if (n >= DISCARDED_NUMBERS_PER_ROW)
            {
                *random_numbers_iter = (double)y_current[n] / M;
                random_numbers_iter += 1;
            }
        }
        long (*tmp)[NUMBERS_PER_ROW] = y_last_ptr;
        y_last_ptr = y_current_ptr;
        y_current_ptr = tmp;
        y_last = *y_last_ptr;
        y_current = *y_current_ptr;
    }

    current_index = 0;
}

double acorn_rand()
{
    if (current_index >= 64)
    {
        init_acorn(-1);
    }
    return random_numbers[current_index++];
}

long acorn_randint(long start, long end)
{
    return (long)((acorn_rand() * (end - start)) + start);
}
