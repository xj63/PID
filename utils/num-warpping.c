#include "num-warpping.h"

#define WARPPING_FN_DEFINE(type)                                               \
  type warpping_##type(type var, type min, type max) {                         \
    type range = max - min;                                                    \
    while (var > max)                                                          \
      var -= range;                                                            \
    while (var < min)                                                          \
      var += range;                                                            \
    return var;                                                                \
  }

WARPPING_FN_DEFINE(float)
WARPPING_FN_DEFINE(double)

WARPPING_FN_DEFINE(long)
WARPPING_FN_DEFINE(int)
WARPPING_FN_DEFINE(short)
WARPPING_FN_DEFINE(char)

WARPPING_FN_DEFINE(ulong)
WARPPING_FN_DEFINE(uint)
WARPPING_FN_DEFINE(ushort)
WARPPING_FN_DEFINE(uchar)
