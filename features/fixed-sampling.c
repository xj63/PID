#define PID_FEATURE_FIXED_SAMPLING

#include "../pid.h"

struct Pid pid_new_with_fixed_sampling(float Kp, float Ki, float Kd, float Ts) {
  return pid_new(Kp, Ki * Ts, Kd / Ts);
}
