#include "../pid.h"
#include "../utils/generate-first-update.h"

float pid_update_with_default(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  float average = (error + pid->previous) / 2.0;
  pid->integral += average * dt;

  pid->previous = error;

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(default)

struct Pid pid_new_with_default(float kp, float ki, float kd) {
  struct Pid pid;

  pid.kp = kp;
  pid.ki = ki;
  pid.kd = kd;
  pid.previous = 0;
  pid.integral = 0;

  pid.update = pid_update_with_default_is_first;

  return pid;
}
