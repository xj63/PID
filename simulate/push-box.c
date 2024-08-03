#include "../utils/num-limit-macro.h"

const float BOX_MASS = 1.0; // kg

const float GRAVITY_ACCELERATION = 9.8;                // m/s^2
const float GRAVITY = BOX_MASS * GRAVITY_ACCELERATION; // N

const float STATIC_FRICTION_COEFFICIENT = 0.5;
const float STATIC_FRICTION_FORCE = GRAVITY * STATIC_FRICTION_COEFFICIENT; // N

const float KINETIC_FRICTION_COEFFICIENT = 0.4;
const float KINETIC_FRICTION_FORCE =
    GRAVITY * KINETIC_FRICTION_COEFFICIENT; // N

const float AIR_DRAG_COEFFICIENT = 0.47;
const float AIR_DENSITY = 1.225; // kg/m^3
const float BOX_AREA = 0.1;      // m^2
#define AIR_RESISTANCE_FORMULA(v)                                              \
  ((v >= 0 ? -1 : 1) *                                                         \
   (0.5 * AIR_DRAG_COEFFICIENT * AIR_DENSITY * BOX_AREA * v * v))

/// Simulate push the box in the direction of the force.
///
///             ──► v
///            ┌─────┐
///  ──► force │ BOX │ ◄── air resistance
/// ───────────┴─────┴───────────────────► x
///          ◄── friction
///
/// return box speed_increase.
float push_box(float *speed_addr, float force, float dt) {
  const float speed = *speed_addr;
  if (ABS(speed) < 1e-6 && ABS(force) < STATIC_FRICTION_FORCE) {
    *speed_addr = 0.0;
    return 0.0;
  }

  float kf_force;
  if (ABS(speed) < 1e-6)
    kf_force = force >= 0 ? -KINETIC_FRICTION_FORCE : KINETIC_FRICTION_FORCE;
  else
    kf_force = speed >= 0 ? -KINETIC_FRICTION_FORCE : KINETIC_FRICTION_FORCE;

  float air_resistance = AIR_RESISTANCE_FORMULA(speed);

  float acc = (force + kf_force + air_resistance) / BOX_MASS;

  float delta = acc * dt;
  *speed_addr = speed + delta;
  return delta;
}

#include "stdio.h"
int main(int argc, char *argv[]) {
  float force = 100;
  float dt = 0.01;
  printf("force=%f, dt=%f\n", force, dt);

  unsigned times = 1000000;
  float speed = 0.0;
  for (unsigned i = 0; i < times; i++) {
    push_box(&speed, force, dt);
    printf("speed=%f\n", speed);
  }
}
