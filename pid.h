#ifndef __PID_H__
#define __PID_H__

#include "features.h"

struct Pid {
  float kp, ki, kd;
  float previous;
  float integral;
  float (*update)(struct Pid *pid, float error, float dt);
  union PidFeaturesOption option;
};

/// Create a new PID controller (default)
///
/// - kp: proportional gain
/// - ki: integral gain
/// - kd: derivative gain
///
/// # Example
///
/// ```c
/// struct Pid pid = pid_new(0.5, 0.1, 0.01);
/// pid_update(&pid, 0, 0, 1);
/// ```
struct Pid pid_new(float kp, float ki, float kd);

/// Update the PID controller
///
/// - pid: PID controller
/// - target: target value
/// - actual: actual value
///   - error = target - actual
/// - dt: time since last update
///   - The unit is preferably seconds. If the unit is other, ki kd needs to
///   change accordingly
///   - Used to calculate integral += error * dt and derivative = (error -
///   previous) / dt
///   - If you use equal time updates, dt is best set to the time interval, or
///   it can be set to 1.0
///   - dt must be greater than 0.0 (not equal to 0.0), otherwise nan or inf
///   will appear
///
/// # Example
///
/// ```c
/// void unknown_control(float thrust);
/// float unknown_sensor();
///
/// int main() {
///   struct Pid pid = pid_new(1, 0, 0);
///   float target = 0;
///   while (true) {
///     float actual = unknown_sensor();
///     float thrust = pid_update(&pid, target, actual, 0.1);
///     unknown_control(thrust);
///   }
/// }
float pid_update(struct Pid *pid, float target, float actual, float dt);

/// Calculate the Proportional Integral Derivative and sum it with the weights
float pid_weighted_sum(struct Pid *pid, float proportional, float integral,
                       float derivative);

#endif // !__PID_H__
