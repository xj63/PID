#include "../pid.h"
#include "utils/generate-first-update.h"
#include "utils/num-limit-macro.h"

float pid_update_with_integral_clamp(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  pid->integral += error * dt;

  // clamp integral
  float clamp = pid->option.integral_clamp_bound;
  pid->integral = CLAMP(pid->integral, clamp);

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(integral_clamp)

struct Pid pid_new_with_integral_clamp(float kp, float ki, float kd,
                                       float integral_clamp_bound) {
  struct Pid pid = pid_new(kp, ki, kd);
  pid.option.integral_clamp_bound = integral_clamp_bound;
  pid.update = pid_update_with_integral_clamp_is_first;
  return pid;
}
