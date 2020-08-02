#ifndef __GBA_MATH_H__
#define __GBA_MATH_H__

#include "gba_types.h"

/*
 * The RNG seed
 */
extern s32 gba_rand_seed;

/*
 * Sets the RNG seed to the given value
 */
extern s32 setRandomSeed(s32 seed);

/*
 * Returns a random number
 */
extern s32 getRandom();

/*
 * Returns a random number in the given range
 */
extern s32 getRandomInRange(s32 min, s32 max);

/*
 * Returns the absolute value of the given number
 */
extern s32 abs(s32 val);

#endif //__GBA_MATH_H__