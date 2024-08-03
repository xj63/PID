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

/// F_air_resistance = sign(v) * 1/2 * C * rho * S * v^2
#define AIR_RESISTANCE_FORMULA(v)                                              \
  (-SIGN(v) * (0.5 * AIR_DRAG_COEFFICIENT * AIR_DENSITY * BOX_AREA * v * v))

/// Simulate push the box in the direction of the force.
/// Right is the positive direction.
float push_box(float *speed_addr, float force, float dt) {
  const float speed = *speed_addr;

  // The thrust is less than the static friction.
  if (ABS(speed) < 1e-6 && ABS(force) < STATIC_FRICTION_FORCE) {
    *speed_addr = 0.0;
    return 0.0;
  }

  float kf_force;
  if (ABS(speed) < 1e-6)
    // When the object moves at a very low speed, the direction of movement is
    // almost determined by the thrust.
    kf_force = -SIGN(force) * KINETIC_FRICTION_FORCE;
  else
    // Sliding friction is opposite to the direction of motion.
    kf_force = -SIGN(speed) * KINETIC_FRICTION_FORCE;

  // Air resistance is proportional to the square of the speed
  float air_resistance = AIR_RESISTANCE_FORMULA(speed);

  // Total force
  float acc = (force + kf_force + air_resistance) / BOX_MASS;

  float delta = acc * dt;
  *speed_addr = speed + delta;
  return delta;
}
