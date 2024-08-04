#include "../../utils/num-limit-macro.h"
#include "../push-box.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
  const float target = 100.0;
  const float dt = 0.1;
  const unsigned times = 10;
  float force = 100.0;
  float speed = 0.0;
  for (unsigned i = 0; i < times; i++) {
    float previous = speed;
    float delta = push_box(&speed, force, dt);

    if (ABS(speed - previous - delta) >= 1e-6)
      exit(1);

    printf("%.3f\n", speed);
  }
  force = -force;
  for (unsigned i = 0; i < times; i++) {
    float previous = speed;
    float delta = push_box(&speed, force, dt);

    if (ABS(speed - previous - delta) >= 1e-6)
      exit(1);

    printf("%.3f\n", speed);
  }
  push_box(&speed, 0.0, 3.5);
  printf("%.3f\n", speed);
}
