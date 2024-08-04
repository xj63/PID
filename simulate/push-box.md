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

- The magnitude of sliding friction is constant during the process,
  but its direction changes with the direction of speed.
  It needs to be discussed before and after the speed reaches 0.

- The magnitude of air resistance is proportional to the square of the speed.
  When the speed is near 0, the air resistance tends to 0.

## Solving first-order differential equations

$$
m \frac{dv}{dt} = F + f_k + f_d
$$

## Solution

### Speed 0 and thrust less than the static friction

The box remains stationary

### Speed 0 and thrust greater than the static friction

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

2. Search lists of integrals

$$
\int \frac{1}{x^2 - \alpha^2} dx = \frac{1}{2 \alpha} \cdot \ln{\left|\frac{x- \alpha}{x + \alpha}\right|} + C
$$

3. Unified form

$$
- \frac{m}{k} \cdot \int \frac{1}{v^2 - \sqrt{\frac{A}{k}}^2} dv = \int dt
$$

4. Substitute into the formula

$$
- \frac{m}{k} \cdot \left[ \frac{1}{2 \sqrt{\frac{A}{k}}} \cdot \ln{\left|\frac{v - \sqrt{\frac{A}{k}}}{v + \sqrt{\frac{A}{k}}}\right|} \right] = t + C
$$

5. $v(0) = 0$

$$
C = 0
$$

6. $v_1 = v(t_0)$

$$
\alpha = \sqrt{\frac{A}{k}}
$$

$$
\left| \frac{v_1 - \alpha}{v_1 + \alpha} \right| = e^{- 2 \frac{k}{m} \alpha \cdot t_0}
$$

7. Classification discussion

if $v_1 - \alpha > 0$ then

$$
v_1 > \sqrt{\frac{A}{k}}
$$

$$
k \cdot v_1^2 > A
$$

$k \cdot v^2$ is air resistance, A is the combined force of thrust and sliding friction.
The speed starts to increase from 0 and will not exceed the speed at the balance point
of thrust, friction and air resistance. So $v - \alpha < 0$

$$
\frac{\alpha - v_1}{v_1 + \alpha} = e^{- 2 \frac{k}{m} \alpha \cdot t_0}
$$

$$
\begin{cases}
v_1 = \frac{\alpha \cdot (1-z)}{1 + z}
\\
z = e^{- 2 \frac{k}{m} \alpha \cdot t_0}
\end{cases}
$$

$t_0 = \text{duration}$
Now the speed is consistent with the thrust direction.

### Speed and thrust are in the same direction, and force is greater than sliding friction.

The car will tend to a certain speed, and the direction of the speed will not change.

$$
V = \lim_{t \to \infty} |v| = \sqrt{\frac{F-f}{k}}
$$

if $v_0 > V$ then Slow down to V
if $v_0 < V$ then Speed up to V

The combined force of thrust and sliding friction $A = |F| - |f_k| > 0$

$$
m \frac{dv}{dt} = A - k v^2
$$

Refer to [ ### Speed 0 and thrust greater than the static friction ]

$$
- \frac{m}{k} \cdot \left[ \frac{1}{2 \sqrt{\frac{A}{k}}} \cdot \ln{\left|\frac{v - \sqrt{\frac{A}{k}}}{v + \sqrt{\frac{A}{k}}}\right|} \right] = t + C_1
$$

$$
\begin{cases}
\left| \frac{v - \alpha}{v + \alpha} \right| = z
\\
\alpha = \sqrt{\frac{A}{k}}
\\
z = C_2 e^{- 2 \frac{k}{m} \alpha \cdot t}
\end{cases}
$$

1. $v(0) = v_0$

$$
C_2 = \left| \frac{v_0 - \alpha}{v_0 + \alpha} \right|
$$

2. $v_1 = v(t_0)$

$$
\left| \frac{v_1 - \alpha}{v_1 + \alpha} \right| = C_2 e^{- 2 \frac{k}{m} \alpha \cdot t_0}
$$

- if $v_1 - \alpha > 0$ so $v_0 > V$

$$
v_1 = \alpha \cdot \frac{1 + C_2 z_0}{1 - C_2 z_0}
$$

- if $v_1 - \alpha < 0$ so $v_0 < V$

$$
v_1 = \alpha \cdot \frac{1 - C_2 z_0}{1 + C_2 z_0}
$$

The direction of the velocity is consistent with the initial direction.

### Speed is opposite to thrust or speed and thrust are in the same direction(but thrust is less than sliding friction).

The car will slow down to 0.
If speed is opposite to thrust, the combined force of thrust and sliding friction $B = |F| + |f_k| > 0$
If speed and thrust are in the same direction and thrust is less than sliding friction,
the combined force of thrust and sliding friction $B = - (|F| - |f_k|) > 0$

$$
m \frac{dv}{dt} = - ( B + k v^2 )
$$

1. Variable separation

$$
\frac{m}{B + kv^2} dv = - dt
$$

2. Integrate both sides of the equation

$$
\int \frac{m}{B + kv^2} dv = - \int dt
$$

3. Constant separation

$$
\int \frac{m}{B + kv^2} dv = \frac{m}{k} \int \frac{1}{\frac{B}{k} + v^2} dv = \frac{m}{\sqrt{Bk}} \int \frac{\sqrt{\frac{k}{B}}}{1 + (\frac{v\sqrt{k}}{\sqrt{B}})^2} dv = - \int dt
$$

4. The left-hand side integral

$$
\int \frac{1}{1+x^2} dx = \arctan(x) + C
$$

$$
x = \frac{\sqrt{k}}{\sqrt{B}} \cdot v
\Longrightarrow
v = \frac{\sqrt{B}}{\sqrt{k}} \cdot x
\Longrightarrow
dv = \frac{\sqrt{B}}{\sqrt{k}} dx
$$

$$
\frac{m}{\sqrt{Bk}} \int \frac{1}{1 + x^2} dx = - \int dt
$$

5. Integral

$$
\frac{m}{\sqrt{B k}} \arctan(x) = -t + C_1
$$

$$
\frac{m}{\sqrt{B k}} \arctan{\left( \sqrt{\frac{k}{B}} \cdot v \right)} = -t + C_1
$$

$$
v(t) = \sqrt{\frac{B}{k}} \cdot \tan{\left(\sqrt{\frac{Bk}{m^2}}(-t + C_1)\right)}
$$

6. $v(0) = v_0$

$v_0$ is the absolute value of the initial velocity

$$
v(0) = \sqrt{\frac{B}{k}} \tan{\left(\sqrt{\frac{Bk}{m^2}} \cdot C_1\right)} = v_0
$$

7. $v(t_0) = 0$

$$
v(t_0) = \sqrt{\frac{B}{k}} \cdot \tan{\left(\sqrt{\frac{Bk}{m^2}}(-t_0 + C_1)\right)} = 0
$$

$$
-t_0 + C_1 = 0
$$

$$
t_0 = C_1 = \frac{m}{\sqrt{Bk}} \arctan{\left(\sqrt{\frac{k}{B}} \cdot v_0 \right)}
$$

8. Compare duration with $t_0$ to determine whether the first speed 0 point has been passed.

- If not passed, substitute duration.

$$
v(t_1) = \sqrt{\frac{B}{k}} \tan{\left(\sqrt{\frac{Bk}{m^2}}(-t_1 + t_0)\right)}
$$

The direction of the velocity is consistent with the initial direction.

- If passed, the change in velocity direction causes a sudden change in friction.
  Discuss again after the speed reaches 0.
