https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#ifndef TEST_RATIONAL_H
#define TEST_RATIONAL_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool testCreate(uint32_t* const ptsEarned, uint32_t* const maxPts);

bool testNegate(uint32_t* const ptsEarned, uint32_t* const maxPts);
bool testAbsVal(uint32_t* const ptsEarned, uint32_t* const maxPts);
bool testCeiling(uint32_t* const ptsEarned, uint32_t* const maxPts);

bool testAdd(uint32_t* const ptsEarned, uint32_t* const maxPts);
bool testMultiply(uint32_t* const ptsEarned, uint32_t* const maxPts);
bool testDivide(uint32_t* const ptsEarned, uint32_t* const maxPts);

bool testEQ(uint32_t* const ptsEarned, uint32_t* const maxPts);
bool testLT(uint32_t* const ptsEarned, uint32_t* const maxPts);

#endif

