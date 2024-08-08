#ifndef __FEATURES_H__
#define __FEATURES_H__

#define PID_FEATURE_FIXED_SAMPLING

#define PID_FEATURE_INTEGRAL_DECAY
#define PID_FEATURE_INTEGRAL_CLAMP
#define PID_FEATURE_INTEGRAL_SEPARATION
// #define PID_FEATURE_INTEGRAL_SLIDING_WINDOW

#if defined(PID_FEATURE_INTEGRAL_CLAMP) ||                                     \
    defined(PID_FEATURE_INTEGRAL_SEPARATION)
struct BoundRange {
  float min;
  float max;
};
#endif // PID_FEATURE_INTEGRAL_CLAMP || PID_FEATURE_INTEGRAL_SEPARATION

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
  struct BoundRange integral_clamp_bound;
#endif

#ifdef PID_FEATURE_INTEGRAL_SEPARATION
  struct BoundRange integral_separation_error_threshold;
#endif

#ifdef PID_FEATURE_INTEGRAL_SLIDING_WINDOW
  struct IntegralSlidingWindow integral_sliding_window;
#endif
};

/// Create a default PID controller
///
/// derivative = (previous - error) / dt
/// integral += ((error + previous) / 2) * dt
struct Pid pid_new_with_default(float kp, float ki, float kd);

#ifdef PID_FEATURE_FIXED_SAMPLING
/// Create a PID controller with fixed sampling
///
/// ki = K_i * T_s
/// kd = K_d / T_s
///
/// - Ts = sampling time
/// - Ts must be greater than 0
/// - Ts unit is seconds (s)
struct Pid pid_new_with_fixed_sampling(float Kp, float Ki, float Kd, float Ts);
#endif // PID_FEATURE_FIXED_SAMPLING

#ifdef PID_FEATURE_INTEGRAL_DECAY
/// Create a PID controller with integral decay
///
/// integral *= integral_decay_factor
/// integral += ((error + previous) / 2) * dt
struct Pid pid_new_with_integral_decay(float kp, float ki, float kd,
                                       float integral_decay_factor);
#endif

#ifdef PID_FEATURE_INTEGRAL_CLAMP
/// Create a PID controller with integral clamp
///
/// integral += ((error + previous) / 2) * dt
/// integral = CLAMP(integral, min, max)
///
/// # Warning
/// - min <= max
struct Pid pid_new_with_integral_clamp(float kp, float ki, float kd,
                                       float integral_clamp_bound_min,
                                       float integral_clamp_bound_max);
#endif

#ifdef PID_FEATURE_INTEGRAL_SEPARATION
/// Create a PID controller with integral separation
///
/// if (lower < error && error < upper)
///   integral += ((error + previous) / 2) * dt
///
/// # Warning
/// - lower < upper
struct Pid pid_new_with_integral_separation(
    float kp, float ki, float kd,
    float integral_separation_error_threshold_lower,
    float integral_separation_error_threshold_upper);
#endif

#ifdef PID_FEATURE_INTEGRAL_SLIDING_WINDOW
/// Create a PID controller with integral sliding window
///
/// integral = /int_{t-finite_time}^t error dt
struct Pid pid_new_with_integral_sliding_window(float kp, float ki, float kd,
                                                float finite_time);
#endif

#endif // !__FEATURES_H__
