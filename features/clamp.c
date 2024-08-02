#include "../pid.h"

float pid_update_with_integral_clamp(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  pid->integral += error * dt;

  // clamp integral
  float clamp = pid->option.integral_clamp_bound;
  pid->integral = pid->integral > clamp ? clamp : pid->integral;
  pid->integral = pid->integral < -clamp ? -clamp : pid->integral;

  float proportional = pid->kp * error;
  float integral = pid->ki * pid->integral;
  float derivative = pid->kd * differential;

  return proportional + integral + derivative;
}

float pid_update_with_integral_clamp_is_first(struct Pid *pid, float error,
                                              float dt) {
  pid->previous = error;
  pid->update = pid_update_with_integral_clamp;
  return pid_update_with_integral_clamp(pid, error, dt);
}

struct Pid pid_new_with_integral_clamp(float kp, float ki, float kd,
                                       float integral_clamp_bound) {
  struct Pid pid = pid_new(kp, ki, kd);
  pid.option.integral_clamp_bound = integral_clamp_bound;
  pid.update = pid_update_with_integral_clamp_is_first;
  return pid;
}
