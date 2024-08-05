#include "../../utils/num-limit-macro.h"
#include "../push-box.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
  const float force = 100.0;
  const float dt = 0.5;
  float speed = 0.0;
  float time = 0.0;

  printf("time: %.2fs, speed: %.3f\n", time, speed);

  for (int i = 0; i < 5; i++) {
    float previous = speed;
    float delta = push_box(&speed, force, dt);
    time += dt;

    if (ABS((speed - previous) - delta) >= 1e-6)
      exit(1);

    printf("time: %.2fs, speed: %.3f\n", time, speed);
  }
}
