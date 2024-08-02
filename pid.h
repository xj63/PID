#ifndef __PID_H__
#define __PID_H__

#include "features.h"

struct Pid {
  float kp, ki, kd;
  float previous;
  float integral;
  float (*update)(struct Pid *pid, float error, float dt);
  union PidFeaturesOption option;
};

struct Pid pid_new(float kp, float ki, float kd);
float pid_update(struct Pid *pid, float target, float actual, float dt);

#endif // !__PID_H__
