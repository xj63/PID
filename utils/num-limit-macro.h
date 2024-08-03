#ifndef __NUM_LIMIT_MACRO_H__
#define __NUM_LIMIT_MACRO_H__

/// Computes the absolute value of `x`.
///
/// Returns `-x` if `x` is negative,
/// Otherwise this returns `x`.
///
/// Equivalent expression `x >= 0 ? x : -x`.
///
/// # Example
///
/// ```c
/// int x = -1;
/// assert(ABS(x) == 1);
///
/// int y = 1;
/// assert(ABS(y) == 1);
/// ```
#define ABS(x) ((x) >= 0 ? (x) : -(x))

/// Signum function
///
/// Returns `+1` if `x` is positive,
///     and `-1` if `x` is negative,
///     and `0`  if `x` is zero.
///
/// Equivalent expression `x == 0 ? 0 : (x > 0 ? 1 : -1)`.
///
/// # Example
///
/// ```c
/// int x = -3;
/// assert(SIGN(x) == -1);
/// assert(SIGN(3.14) == 1);
/// assert(SIGN(0) == 0);
/// ```
#define SIGN(x) ((x) == 0 ? 0 : ((x) > 0 ? 1 : -1))

/// Computes the maximum value of `x` and `y`.
///
/// Equivalent expression `x > y ? x : y`.
///
/// # Example
///
/// ```c
/// int x = 1, y = 2;
/// assert(MAX(x, y) == 2);
/// ```
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/// Computes the minimum value of `x` and `y`.
///
/// Equivalent expression `x < y ? x : y`.
///
/// # Example
///
/// ```c
/// int x = 1, y = 2;
/// assert(MIN(x, y) == 1);
/// ```
#define MIN(x, y) ((x) < (y) ? (x) : (y))

/// Limit the maximum value of `x` to no more than `max`
///
/// Returns `max` if `x` is more than `max`,
/// Otherwise this returns `x`.
///
/// Equivalent expression `x <= max ? x : max`.
///
/// # Example
///
/// ```c
/// int x = 1, max = 2;
/// assert(LIMIT_MAX(x, max) == 1);
///
/// assert(LIMIT_MAX(3, 2) == 2);
/// ```
#define LIMIT_MAX(x, max) MIN(x, max)

/// Limit the minimum value of `x` to no less than `min`
///
/// Returns `min` if `x` is less than `min`,
/// Otherwise this returns `x`.
///
/// Equivalent expression `x >= min ? x : min`.
///
/// # Example
///
/// ```c
/// int x = 3, min = 2;
/// assert(LIMIT_MIN(x, min) == 3);
///
/// assert(LIMIT_MIN(1, 2) == 2);
/// ````
#define LIMIT_MIN(x, min) MAX(x, min)

/// Restrict `x` to a certain interval [min, max]
///
/// Returns `max` if `x` is greater than `max`,
///     and `min` if `x` is less than `min`,
///     otherwise this returns `x.
///
/// Equivalent expression
///   v = LIMIT_MAX(x, max)
///   v = LIMIT_MIN(v, min)
///
/// # Warning
/// `min` must be less than `max`.
///
/// # Example
///
/// ```c
/// int x = 3, min = 2, max = 4;
/// assert(LIMIT(x, min, max) == 3);
///
/// assert(LIMIT(1, 2, 4) == 2);
/// assert(LIMIT(5, 2, 4) == 4);
/// ```
#define LIMIT(x, min, max) LIMIT_MIN(LIMIT_MAX(x, max), min)

/// Restrict `x` to a certain interval [-range, range]
///
/// Returns `range` if `x` is greater than `range`,
///     and `-range` if `x` is less than `-range`,
///     otherwise this returns `x.
///
/// Equivalent expression
///   v = LIMIT(x, -range, range)
///
/// # Warning
/// `range` must be greater than 0.
///
/// # Example
///
/// ```c
/// int x = 3, range = 4;
/// assert(CLAMP(x, range) == 3);
///
/// assert(CLAMP(5, 4) == 4);
/// assert(CLAMP(-5, 4) == -4);
/// ```
#define CLAMP(x, range) LIMIT(x, -(range), range)

#endif // !__NUM_LIMIT_MACRO_H__
