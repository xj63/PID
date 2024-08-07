#include "../simulate/push-box.h"
#include "../pid.h"

#include <stdio.h>
int main() {
  struct Pid pid = pid_new_with_integral_clamp(1, 2, 0.1, -300, 300);

  float time = 0.0;
  float speed = 0.0;
  float force = 0.0;
  const float dt = 1;
  const float target = 100.0;

  for (unsigned i = 0; i < 10; i++) {
    push_box(&speed, force, dt);
    printf("time: %.0fs, \t speed: %.1f, \t force: %.2f\n", time, speed, force);

    force = pid_update(&pid, target, speed, dt);
    time += dt;
  }
}
