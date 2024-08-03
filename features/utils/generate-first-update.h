#ifndef __GENERATE_FIRST_UPDATE_H__
#define __GENERATE_FIRST_UPDATE_H__

#define PID_UPDATE_GENERATE_IS_FIRST(feature)                                  \
  float pid_update_with_##feature##_is_first(struct Pid *pid, float error,     \
                                             float dt) {                       \
    pid->previous = error;                                                     \
    pid->update = pid_update_with_##feature;                                   \
    return pid_update_with_##feature(pid, error, dt);                          \
  }

#endif // !__GENERATE_FIRST_UPDATE_H__
