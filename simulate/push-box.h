#ifndef __PUSH_BOX_H__
#define __PUSH_BOX_H__

/// Simulate push the box in the direction of the force.
///
/// Right is the positive direction.
/// The velocity changes under the action of force for a period of time dt.
///
///             ──► v
///            ┌─────┐
///  ──► force │ BOX │ ◄── air resistance
/// ───────────┴─────┴───────────────────► x
///          ◄── friction
///
/// Change the speed of the box (*speed_addr)
/// Return box speed_increase.
///
/// # Example
/// ```c
/// #include "../pid.h"
/// #include "stdio.h"
///
/// int main() {
///   struct Pid pid = pid_new(1.0, 0, 0);
///
///   float speed = 0.0;
///   float force = 0.0;
///   const float dt = 0.01;
///   const float target = 100.0;
///   const unsigned times = 100;
///   for (unsigned i = 0; i < times; i++) {
///     force = pid_update(&pid, target, speed, dt);
///     float delta = push_box(&speed, force, dt);
///     printf("speed=%.3f, delta=%.3f\n", speed, delta);
///   }
/// }
/// ```
float push_box(float *speed_addr, float force, float dt);

#endif // !__PUSH_BOX_H__
