#define WARPPING_FN_DECLARE(type)                                              \
  type warpping_##type(type var, type min, type max);

WARPPING_FN_DECLARE(float)
WARPPING_FN_DECLARE(double)

WARPPING_FN_DECLARE(long)
WARPPING_FN_DECLARE(int)
WARPPING_FN_DECLARE(short)
WARPPING_FN_DECLARE(char)

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

WARPPING_FN_DECLARE(ulong)
WARPPING_FN_DECLARE(uint)
WARPPING_FN_DECLARE(ushort)
WARPPING_FN_DECLARE(uchar)

#define WARPPING_FN_GENERIC(x)                                                 \
  _Generic((x),                                                                \
      double: warpping_double,                                                 \
      float: warpping_float,                                                   \
      long: warpping_long,                                                     \
      int: warpping_int,                                                       \
      short: warpping_short,                                                   \
      char: warpping_char,                                                     \
      ulong: warpping_ulong,                                                   \
      uint: warpping_uint,                                                     \
      ushort: warpping_ushort,                                                 \
      uchar: warpping_uchar)

/// Warps `var` from `min` to `max`. [min, max]
///
/// range = max - min
/// n is make sure `var +/- range * n` is between `min` and `max`
///
/// Returns `var` if `var` is between `min` and `max`,
///     and `var + range * n` if `var` is less than `min`,
///     and `var - range * n` if `var` is greater than `max`.
///
/// # Warning
/// `min` must be less than `max`.
///
/// # Example
///
/// ```c
/// int x = 3, min = 2, max = 4;
/// assert(WARPPING(x, min, max) == 3);
/// assert(WARPPING(1, min, max) == 3);
/// assert(WARPPING(5, min, max) == 3);
/// ```
#define WARPPING(var, min, max) WARPPING_FN_GENERIC(var)(var, min, max)
