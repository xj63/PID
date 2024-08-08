#define PID_FEATURE_FIXED_SAMPLING

#include "../pid.h"
#include "../utils/generate-first-update.h"

float pid_update_with_fixed_sampling(struct Pid *pid, float error,
                                     float dt_ignore) {
  float differential = error - pid->previous;

  float average = (error + pid->previous) / 2.0;
  pid->integral += average;

  pid->previous = error;

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(fixed_sampling)

struct Pid pid_new_with_fixed_sampling(float Kp, float Ki, float Kd, float Ts) {
  struct Pid pid = pid_new(Kp, Ki * Ts, Kd / Ts);

  pid.update = pid_update_with_fixed_sampling_is_first;

  return pid;
}
