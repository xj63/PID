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
/// float force = 100;
/// float dt = 0.01;
/// printf("force=%f, dt=%f\n", force, dt);
///
/// unsigned times = 100;
/// float speed = 0.0;
/// for (unsigned i = 0; i < times; i++) {
///   float delta = push_box(&speed, force, dt);
///   printf("speed=%.3f, delta=%.3f\n", speed, delta);
/// }
/// ```
float push_box(float *speed_addr, float force, float dt);

#endif // !__PUSH_BOX_H__
