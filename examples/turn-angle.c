#include "../pid.h"
#include "../utils/num-limit-macro.h"
#include "../utils/num-warpping.h"

static float direction = 0.0;

/// read MPU6050 and return current direction.
///
///       ^ 0
/// -90 <   > 90
///       v 180
/// return (-180, 180] left - right +
float get_direction() { return direction; }

/// set motor thrust
void motor_thrust(float left, float right) {
  // if left 10, right -6 then average is 2
  float average = (left + right) / 2.0;
  // then turn = left - average = 10 - 2 = 8
  float turn = left - average;
  // turn right 8°
  direction += turn;
}

/// turn angle with PID
///
/// turn: left - right +
///
/// # Example
/// ```c
/// turn_angle(90.0); // Turn right 90°
/// turn_angle(-45.0); // Turn left 45°
/// ```
void turn_angle(float turn) {
  motor_thrust(0, 0);
  struct Pid pid = pid_new(1, 0, 0);
  const float origin = get_direction();
  // if origin < -90 turn 90 then target = 0 ^
  const float target = WARPPING(origin + turn, -180, 180);

  float current = get_direction();
  // if current <- -90 target ^ 0 then diff = 90
  // For the truth, the target is on his right. diff = 90.
  // so he need to turn right.
  float diff = WARPPING(target - current, -180, 180);

  // |diff| < 1.0 is turning angle to target value.
  while (ABS(diff) > 1.0) {
    // error = target - current = 0 - 90 = -90
    // The angle between target truth and target angle is zero.
    // but actual angle diff is 90.
    // return diff_thrust is negative because error and kp is negative.
    // and need turn right. left speed + and right speed -
    float diff_thrust = pid_update(&pid, 0, diff, 1.0);
    motor_thrust(-diff_thrust, diff_thrust);

    current = get_direction();
    diff = WARPPING(target - current, -180, 180);
  }
}

#include "stdio.h"
int main() {
  float origin = get_direction();
  float angle = 90;
  turn_angle(angle);
  float final = get_direction();
  printf("origin: %f°, turn %f°, final: %f°\n", origin, angle, final);
}
