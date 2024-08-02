#include "../pid.h"

float pid_update_with_integral_decay(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  pid->integral *= pid->option.integral_decay_factor;
  pid->integral += error * dt;

  float proportional = pid->kp * error;
  float integral = pid->ki * pid->integral;
  float derivative = pid->kd * differential;

  return proportional + integral + derivative;
}

float pid_update_with_integral_decay_is_first(struct Pid *pid, float error,
                                              float dt) {
  pid->previous = error;
  pid->update = pid_update_with_integral_decay;
  return pid_update_with_integral_decay(pid, error, dt);
}

struct Pid pid_new_with_integral_decay(float kp, float ki, float kd,
                                       float integral_decay_factor) {
  struct Pid pid = pid_new(kp, ki, kd);
  pid.option.integral_decay_factor = integral_decay_factor;
  pid.update = pid_update_with_integral_decay_is_first;
  return pid;
}
