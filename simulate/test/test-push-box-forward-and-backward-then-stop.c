#include "../../utils/num-limit-macro.h"
#include "../push-box.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
  float force = 100.0;
  float speed = 0.0;

  printf("time: %.2fs, speed: %.3f\n", 0.0, speed);

  {
    float previous = speed;
    float delta = push_box(&speed, force, 1);

    if (ABS((speed - previous) - delta) >= 1e-6)
      exit(1);

    printf("time: %.2fs, speed: %.3f\n", 1.0, speed);
  }

  force = -force;
  {
    float previous = speed;
    float delta = push_box(&speed, force, 1);

    if (ABS((speed - previous) - delta) >= 1e-6)
      exit(1);

    printf("time: %.2fs, speed: %.3f\n", 2.0, speed);
  }

  force = 0;
  {
    float previous = speed;
    float delta = push_box(&speed, force, 1);

    if (ABS((speed - previous) - delta) >= 1e-6)
      exit(1);
    printf("time: %.2fs, speed: %.3f\n", 3.0, speed);
  }
}
