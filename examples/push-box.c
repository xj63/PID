#include "../simulate/push-box.h"
#include "../pid.h"
#include <stdio.h>

static struct Pid pid;
static const float target = 100.0;
static const float dt = 1;
static float speed = 0.0;
static float force = 0.0;
static float time = 0.0;

void interrupt_callback() {
  force = pid_update(&pid, target, speed, dt);

  push_box(&speed, force, dt);
  printf("time: %.0fs, \t speed: %.1f, \t force: %.2f\n", time, speed, force);

  time += dt;
}

int main() {
  pid = pid_new_with_integral_clamp(1, 2, 0.1, -300, 300);

  for (unsigned i = 0; i < 10; i++) {
    // need #include <unistd.h>
    // sleep(1);
    interrupt_callback();
  }
}
