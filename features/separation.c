#include "../pid.h"

float pid_update_with_integral_separation(struct Pid *pid, float error,
                                          float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  // integral separation
  if (error < pid->option.integral_separation_error_threshold)
    pid->integral += error * dt;

  float proportional = pid->kp * error;
  float integral = pid->ki * pid->integral;
  float derivative = pid->kd * differential;

  return proportional + integral + derivative;
}

float pid_update_with_integral_separation_is_first(struct Pid *pid, float error,
                                                   float dt) {
  pid->previous = error;
  pid->update = pid_update_with_integral_separation;
  return pid_update_with_integral_separation(pid, error, dt);
}

struct Pid
pid_new_with_integral_separation(float kp, float ki, float kd,
                                 float integral_separation_error_threshold) {
  struct Pid pid = pid_new(kp, ki, kd);
  pid.option.integral_separation_error_threshold =
      integral_separation_error_threshold;
  pid.update = pid_update_with_integral_separation_is_first;
  return pid;
}
