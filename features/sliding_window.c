#define PID_FEATURE_INTEGRAL_SLIDING_WINDOW

#include "../pid.h"
#include "../utils/generate-first-update.h"

inline unsigned sliding_window_index(unsigned offset) {
  return offset % INTEGRAL_SLIDING_WINDOW_SIZE;
}

inline void sliding_window_merge_current_and_next_to_next(
    struct IntegralSlidingWindow *window, unsigned offset) {
  float current_err = window->err[offset];
  float current_dt = window->dt[offset];

  unsigned next = sliding_window_index(offset + 1);
  float next_err = window->err[next];
  float next_dt = window->dt[next];

  window->err[next] =
      (current_err * current_dt + next_err * next_dt) / (current_dt + next_dt);
  window->dt[next] = current_dt + next_dt;
}

float integral_sliding_window_forward(struct IntegralSlidingWindow *window,
                                      float error, float dt) {
  float delta = error * dt;

  while (dt > window->dt[window->offset]) {
    delta -= window->err[window->offset] * window->dt[window->offset];
    window->err[window->offset] = error;
    dt -= window->dt[window->offset];

    window->offset = sliding_window_index(window->offset + 1);
  }

  delta -= window->err[window->offset] * dt;
  window->dt[window->offset] -= dt;

  sliding_window_merge_current_and_next_to_next(window, window->offset);

  window->dt[window->offset] = dt;
  window->err[window->offset] = error;
  window->offset = sliding_window_index(window->offset + 1);
  return delta;
}

float pid_update_with_integral_sliding_window(struct Pid *pid, float error,
                                              float dt) {
  float differential = (error - pid->previous) / dt;

  pid->previous = error;
  pid->integral += integral_sliding_window_forward(
      &pid->option.integral_sliding_window, error, dt);

  return pid_weighted_sum(pid, error, pid->integral, differential);
}

PID_UPDATE_GENERATE_IS_FIRST(integral_sliding_window)

struct Pid pid_new_with_integral_sliding_window(float kp, float ki, float kd,
                                                float finite_time) {
  struct Pid pid = pid_new(kp, ki, kd);

  pid.option.integral_sliding_window.offset = 0;
  pid.option.integral_sliding_window.finite_time = finite_time;

  float average_dt = finite_time / INTEGRAL_SLIDING_WINDOW_SIZE;
  for (unsigned i = 0; i < INTEGRAL_SLIDING_WINDOW_SIZE; i++) {
    pid.option.integral_sliding_window.err[i] = 0.0;
    pid.option.integral_sliding_window.dt[i] = average_dt;
  }

  pid.update = pid_update_with_integral_sliding_window_is_first;
  return pid;
}
