#include "gba_math.h"

s32 gba_rand_seed = 42;

s32 setRandomSeed(s32 seed) {
	s32 old_seed = gba_rand_seed;
	gba_rand_seed = seed;
	return old_seed;
}

s32 getRandom() {
	gba_rand_seed = 1664525 * gba_rand_seed + 1013904223;
	return (gba_rand_seed >> 16) & 0x7FFF;
}

s32 getRandomInRange(s32 min, s32 max) {
	return (getRandom() * (max - min) >> 15) + min;
}

s32 abs(s32 val) {
	// Branchless. Effectively, un-sets the sign bit if it is set
	s32 mask = val >> 31;
	return (val ^ mask) - mask;
}