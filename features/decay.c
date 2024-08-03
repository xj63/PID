#include "../pid.h"
#include "is_first.h"

float pid_update_with_integral_decay(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  // integral decay
  pid->integral *= pid->option.integral_decay_factor;
  pid->integral += error * dt;

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(integral_decay)

struct Pid pid_new_with_integral_decay(float kp, float ki, float kd,
                                       float integral_decay_factor) {
  struct Pid pid = pid_new(kp, ki, kd);
  pid.option.integral_decay_factor = integral_decay_factor;
  pid.update = pid_update_with_integral_decay_is_first;
  return pid;
}
