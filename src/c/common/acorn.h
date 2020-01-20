#pragma once

#include "time.h"

extern void init_acorn(long seed);
extern double acorn_rand(void);
extern long acorn_randint(long start, long end);
