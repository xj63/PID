#include "pid.h"

struct Pid pid_new(float kp, float ki, float kd) {
  return pid_new_with_default(kp, ki, kd);
}

float pid_update(struct Pid *pid, float target, float actual, float dt) {
  float error = target - actual;
  return pid->update(pid, error, dt);
}
