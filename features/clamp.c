#include "../pid.h"
#include "is_first.h"

float pid_update_with_integral_clamp(struct Pid *pid, float error, float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  pid->integral += error * dt;

  // clamp integral
  float clamp = pid->option.integral_clamp_bound;
  pid->integral = pid->integral > clamp ? clamp : pid->integral;
  pid->integral = pid->integral < -clamp ? -clamp : pid->integral;

  float proportional = pid->kp * error;
  float integral = pid->ki * pid->integral;
  float derivative = pid->kd * differential;

  return proportional + integral + derivative;
}

PID_UPDATE_GENERATE_IS_FIRST(integral_clamp)

struct Pid pid_new_with_integral_clamp(float kp, float ki, float kd,
                                       float integral_clamp_bound) {
  struct Pid pid = pid_new(kp, ki, kd);
  pid.option.integral_clamp_bound = integral_clamp_bound;
  pid.update = pid_update_with_integral_clamp_is_first;
  return pid;
}
