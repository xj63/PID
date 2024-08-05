#ifndef __FEATURES_H__
#define __FEATURES_H__

#define PID_FEATURE_INTEGRAL_DECAY
#define PID_FEATURE_INTEGRAL_CLAMP
#define PID_FEATURE_INTEGRAL_SEPARATION
// #define PID_FEATURE_INTEGRAL_SLIDING_WINDOW

#ifdef PID_FEATURE_INTEGRAL_SLIDING_WINDOW
// default sliding window size
#ifndef INTEGRAL_SLIDING_WINDOW_SIZE
#define INTEGRAL_SLIDING_WINDOW_SIZE 10
#endif

struct IntegralSlidingWindow {
  float err[INTEGRAL_SLIDING_WINDOW_SIZE];
  float dt[INTEGRAL_SLIDING_WINDOW_SIZE];
  unsigned offset;
  float finite_time;
};
#endif

union PidFeaturesOption {
#ifdef PID_FEATURE_INTEGRAL_DECAY
  float integral_decay_factor;
#endif

#ifdef PID_FEATURE_INTEGRAL_CLAMP
  float integral_clamp_bound;
#endif

#ifdef PID_FEATURE_INTEGRAL_SEPARATION
  float integral_separation_error_threshold;
#endif

#ifdef PID_FEATURE_INTEGRAL_SLIDING_WINDOW
  struct IntegralSlidingWindow integral_sliding_window;
#endif
};

struct Pid pid_new_with_default(float kp, float ki, float kd);

#ifdef PID_FEATURE_INTEGRAL_DECAY
struct Pid pid_new_with_integral_decay(float kp, float ki, float kd,
                                       float integral_decay_factor);
#endif

#ifdef PID_FEATURE_INTEGRAL_CLAMP
struct Pid pid_new_with_integral_clamp(float kp, float ki, float kd,
                                       float integral_clamp_bound);
#endif

#ifdef PID_FEATURE_INTEGRAL_SEPARATION
struct Pid
pid_new_with_integral_separation(float kp, float ki, float kd,
                                 float integral_separation_error_threshold);
#endif

#ifdef PID_FEATURE_INTEGRAL_SLIDING_WINDOW
struct Pid pid_new_with_integral_sliding_window(float kp, float ki, float kd,
                                                float finite_time);
#endif

#endif // !__FEATURES_H__
