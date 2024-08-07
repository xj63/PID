#define PID_FEATURE_INTEGRAL_SEPARATION

#include "../pid.h"
#include "../utils/generate-first-update.h"
#include "../utils/num-limit-macro.h"

float pid_update_with_integral_separation(struct Pid *pid, float error,
                                          float dt) {
  float differential = (error - pid->previous) / dt;

  // integral separation
  if (IN_RANGE(error, pid->option.integral_separation_error_threshold.min,
               pid->option.integral_separation_error_threshold.max)) {
    float average = (error + pid->previous) / 2.0;
    pid->integral += average * dt;
  }

  pid->previous = error;

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(integral_separation)

struct Pid pid_new_with_integral_separation(
    float kp, float ki, float kd,
    float integral_separation_error_threshold_lower,
    float integral_separation_error_threshold_upper) {
  struct Pid pid = pid_new(kp, ki, kd);

  struct BoundRange integral_separation_error_threshold = {
      .min = integral_separation_error_threshold_lower,
      .max = integral_separation_error_threshold_upper,
  };
  pid.option.integral_separation_error_threshold =
      integral_separation_error_threshold;

  pid.update = pid_update_with_integral_separation_is_first;

  return pid;
}
