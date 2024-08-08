#define PID_FEATURE_INTEGRAL_CLAMP

#include "../pid.h"
#include "../utils/generate-first-update.h"
#include "../utils/num-limit-macro.h"

float pid_update_with_integral_clamp(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  float average = (error + pid->previous) / 2.0;
  pid->integral += average * dt;

  // clamp integral
  struct BoundRange clamp = pid->option.integral_clamp_bound;
  pid->integral = LIMIT(pid->integral, clamp.min, clamp.max);

  pid->previous = error;

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(integral_clamp)

struct Pid pid_new_with_integral_clamp(float kp, float ki, float kd,
                                       float integral_clamp_bound_min,
                                       float integral_clamp_bound_max) {
  struct Pid pid = pid_new(kp, ki, kd);

  struct BoundRange integral_clamp_bound = {
      .min = integral_clamp_bound_min,
      .max = integral_clamp_bound_max,
  };
  pid.option.integral_clamp_bound = integral_clamp_bound;

  pid.update = pid_update_with_integral_clamp_is_first;

  return pid;
}
