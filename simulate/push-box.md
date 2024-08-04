# Push Box

## Problem Description

Simulates pushing a box with an initial speed using a force F for a time dt.

- Right is the positive direction. `->`
- Consider static friction. $f_s \leq \mu_s mg \quad \text{if} \; v = 0$
- Consider sliding friction. $f_k = -\operatorname{sgn}v \cdot \mu_k mg$
- Consider air resistance. $f_d = -\operatorname{sgn}v \cdot \frac{1}{2} \rho C_d A v^2$

## Problem Analysis

- When the speed is 0, if the thrust is less than the static friction,
  the force on the box will remain stationary.

- When the initial velocity is 0 and the thrust is greater than the static friction,
  the box will move in the direction of the thrust because the sliding friction is
  less than the static friction and less than the thrust.
  The direction of the sliding friction is opposite to the thrust.

At this point, you can ignore the direction and only focus on the size.
The direction of the velocity is consistent with the thrust F,
and the air resistance and sliding friction are opposite to the velocity and the thrust.
The combined force of thrust and sliding friction $A = |F| - |f_k| > 0$
Air resistance coefficient $k = \frac{1}{2} \rho C_d A$

$$
m \frac{dv}{dt} = A - k v^2
$$

1. Variable separation

$$
\frac{m}{A - kv^2} dv = dt
$$

2. Constant separation

$$
\frac{m}{A} \cdot \frac{1}{1 + \frac{k}{A} \cdot v^2} dv = dt
$$

3. Integrate both sides of the equation

$$
\frac{m}{A} \cdot \int \frac{1}{1 + \frac{k}{A} \cdot v^2} dv = \int dt
$$

4. The left-hand side integral uses trigonometric substitution.

$$
v = \sqrt{\frac{A}{k}}\tan{\theta}
$$

$$
dv = \sqrt{\frac{A}{k}}\sec^2{\theta} d\theta
$$

$$
\frac{m}{A} \cdot \int \frac{1}{1 - \tan^2{\theta}} \sqrt{\frac{A}{k}}\sec^2{\theta} d\theta = \int dt
$$

$$
\sqrt{\frac{m^2}{Ak}} \int d\theta = \int dt
$$

5. Integral

$$
\sqrt{\frac{m^2}{Ak}} \theta = t + C_1
$$

$$
\theta = \arctan{(\sqrt{\frac{k}{A}}v)}
$$

$$
\sqrt{\frac{m^2}{Ak}} \arctan{(\sqrt{\frac{k}{A}}v)} = t + C_1
$$

$$
v(t) = \sqrt{\frac{A}{k}} \tan{\left(\sqrt{\frac{Ak}{m^2}}(t + C_1)\right)}
$$

6. $v(0) = 0$

$$
v(0) = \sqrt{\frac{A}{k}} \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot C_1 \right)} = 0
$$

$$
C_1 = 0
$$

7. End

$$
v(t) = \sqrt{\frac{A}{k}} \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot t\right)}
$$

- The magnitude of sliding friction is constant during the process,
  but its direction changes with the direction of speed.
  It needs to be discussed before and after the speed reaches 0.

- The magnitude of air resistance is proportional to the square of the speed.
  When the speed is near 0, the air resistance tends to 0.

## Solving first-order differential equations

$$
m \frac{dv}{dt} = F + f_k + f_d
$$
