https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdint.h>
#include <stdbool.h>

/** !!  DO NOT MODIFY THIS FILE IN ANY WAY !! **/


/**  Represents a rational number (the ratio of two integers).
 */
struct _Rational {
   int64_t Top;
   int64_t Bottom;
};
typedef struct _Rational Rational;

/** A Rational object is said to be proper if Top and Bottom have been
 *  initialized and Bottom != 0.
 */

//-------------------------------------------------------------------- creator
/**
 *  Creates and initializes a new Rational object.
 *  Pre:
 *        Denominator != 0
 *  Returns:
 *        A Rational object X that represents the rational number
 *        Numerator / Demonimator.
 */
Rational Rational_Create(int64_t Numerator, int64_t Denominator);

//-------------------------------------------------------------------- unary fns
/**
 *   Compute the arithmetic negation of R.
 *   Pre:
 *        R has been properly initialized.
 *   Returns:
 *        A Rational object X such that X + R = 0.
 */
Rational Rational_Negate(const Rational R);

/**
 *   Compute the absolute value of R.
 *   Pre:
 *        R is proper.
 *   Returns:
 *        A proper Rational object X such that X = |R|.
 */
Rational Rational_AbsVal(const Rational R);

/**
 *   Compute the arithmetic ceiling of R.
 *   Pre:
 *        R is proper.
 *   Returns:
 *        The smallest integer N such that N >= R.
 */
int64_t Rational_Ceiling(const Rational R);

//-------------------------------------------------------------------- binary fns
/**
 *   Compute the sum of Left and Right.
 *   Pre:
 *        Left and Right are proper.
 *   Returns:
 *        A proper Rational object X equal to Left + Right.
 */
Rational Rational_Add(const Rational Left, const Rational Right);

/**
 *   Compute the product of Left and Right.
 *   Pre:
 *        Left and Right are proper.
 *   Returns:
 *        A proper Rational object X equal to Left * Right.
 */
Rational Rational_Multiply(const Rational Left, const Rational Right);

/**
 *   Compute the quotient of Left and Right.
 *   Pre:
 *        Left and Right are proper.
 *   Returns:
 *        A proper Rational object X equal to Left / Right.
 */
Rational Rational_Divide(const Rational Left, const Rational Right);

//-------------------------------------------------------------------- relational fns
/**
 *   Determine whether Left and Right are equal.
 *   Pre:
 *        Left and Right are proper.
 *   Returns:
 *        True if Left == Right, false otherwise.
 */
bool Rational_Equals(const Rational Left, const Rational Right);

/**
 *   Determine whether Left is less than Right.
 *   Pre:
 *        Left and Right are proper.
 *   Returns:
 *        True if Left < Right, false otherwise.
 */
bool Rational_LessThan(const Rational Left, const Rational Right);

#endif

