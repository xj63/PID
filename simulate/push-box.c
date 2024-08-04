#include "push-box.h"
#include "../utils/num-limit-macro.h"

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
  const float speed = *speed_addr;

  // The thrust is less than the static friction.
  if (ABS(speed) < 1e-6 && ABS(force) < STATIC_FRICTION_FORCE) {
    *speed_addr = 0.0;
    return 0.0;
  }

  // Sliding friction is opposite to the direction of motion.
  float kf_force = -SIGN(speed) * KINETIC_FRICTION_FORCE;

  // Air resistance is proportional to the square of the speed
  float air_resistance = AIR_RESISTANCE_FORMULA(speed);

  // Total force
  float acc = (force + kf_force + air_resistance) / BOX_MASS;

  float dt = 1e-3;
  float delta = acc * dt;

  if (duration < 1e-6) {
    return delta;
  } else if (duration < 1e-3) {
    dt = duration;
    delta = acc * dt;
  } else {
    delta += push_box(speed_addr, force, duration - dt);
  }

  *speed_addr = speed + delta;
  return delta;
}
