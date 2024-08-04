#include "push-box.h"
#include "../utils/num-limit-macro.h"
#include <math.h>

const float BOX_MASS = 1.0; // kg

const float GRAVITY_ACCELERATION = 9.8;                // m/s^2
const float GRAVITY = BOX_MASS * GRAVITY_ACCELERATION; // N

// static friction
const float STATIC_FRICTION_COEFFICIENT = 0.5;
const float STATIC_FRICTION_FORCE = GRAVITY * STATIC_FRICTION_COEFFICIENT; // N

// kinetic friction
const float KINETIC_FRICTION_COEFFICIENT = 0.4;
const float KINETIC_FRICTION_FORCE =
    GRAVITY * KINETIC_FRICTION_COEFFICIENT; // N

// air resistance
const float AIR_DRAG_COEFFICIENT = 0.47;
const float AIR_DENSITY = 1.225; // kg/m^3
const float BOX_AREA = 0.1;      // m^2

/// F_air_resistance = -sign(v) * 1/2 * C * rho * S * v^2
const float AIR_RESISTANCE_SCALE =
    0.5 * AIR_DRAG_COEFFICIENT * AIR_DENSITY * BOX_AREA; // 1/2 * C * rho * S
#define AIR_RESISTANCE_FORMULA(v)                                              \
  (-SIGN(v) * (AIR_RESISTANCE_SCALE * SQUARE(v)))

/// Simulate push the box in the direction of the force.
/// Right is the positive direction.
float push_box(float *speed_addr, float force, float duration) {
  const float k = AIR_RESISTANCE_SCALE;
  const float m = BOX_MASS;
  const float v0 = *speed_addr;
  const float F = force;

  // Initial speed is zero.
  if (ABS(v0) < 1e-9) {
    // The thrust is less than the static friction.
    // - When the speed is 0, if the thrust is less than the static friction,
    //   the force on the box will remain stationary.
    //
    // Refer to the analysis of
    // [push-box.md###Speed_0_and_thrust_less_than_the_static_friction]
    if (ABS(F) < STATIC_FRICTION_FORCE) {
      *speed_addr = 0.0;
      return 0.0;
    }

    // The thrust is greater than the static friction.
    // - When the initial velocity is 0 and the thrust is greater than the
    //   static friction, the box will move in the direction of the thrust
    //   because the sliding friction is less than the static friction and
    //   less than the thrust. The direction of the sliding friction is
    //   opposite to the thrust.
    //
    // Refer to the analysis of
    // [push-box.md###Speed_0_and_thrust_greater_than_the_static_friction]
    float A = ABS(F) - KINETIC_FRICTION_FORCE;
    float t = duration;
    float v1 = sqrtf(A / k) * tanf((sqrtf(A * k) / m) * t);
    v1 = SIGN(F) * v1;
    *speed_addr = v1;
    return v1 - v0;
  }

  // Refer to the analysis of push-box.md
  // ### Speed and thrust are in the same direction, and speed is greater than
  // sliding friction.
  if (F * v0 >= 0.0 && ABS(F) > KINETIC_FRICTION_FORCE) {
    float A = ABS(F) - KINETIC_FRICTION_FORCE;
    float t0 = duration;
    float z = tanf((sqrtf(A * k) / m) * t0);
    float v1 = (sqrtf(A / k) * z + v0) / (1 - sqrtf(k / A) * z * v0);
    v1 = v1 * SIGN(v0);
    *speed_addr = v1;
    return v1 - v0;
  }

  // Refer to the analysis of push-box-md
  // ### Speed is opposite to thrust or speed and thrust are in the same
  // direction(but thrust is less than sliding friction).
  float B = F * v0 >= 0.0 ? KINETIC_FRICTION_FORCE - ABS(F)
                          : KINETIC_FRICTION_FORCE + ABS(F);
  float t0 = (m / sqrtf(B * k)) * atanf(sqrtf(k / B) * v0);
  if (t0 >= duration) {
    float t1 = duration;
    float v1 = sqrtf(B / k) * tanf((sqrtf(B * k) / m) * (-t1 + t0));
    v1 = SIGN(v0) * v1;
    *speed_addr = v1;
    return v1 - v0;
  }

  // Speed pass zero point.
  float v1 = 0.0;
  *speed_addr = 0.0;
  return v1 - v0 + push_box(speed_addr, force, duration - t0);
}
