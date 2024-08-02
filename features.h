#ifndef __FEATURES_H__
#define __FEATURES_H__

#define PID_FEATURE_INTEGRAL_DECAY
#define PID_FEATURE_INTEGRAL_CLAMP
#define PID_FEATURE_INTEGRAL_SEPARATION

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

#endif // __FEATURES_H__
