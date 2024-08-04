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

2. Constant separation

$$
\frac{m}{A} \cdot \frac{1}{1 - \frac{k}{A} \cdot v^2} dv = dt
$$

3. Integrate both sides of the equation

$$
\frac{m}{A} \cdot \int \frac{1}{1 - \frac{k}{A} \cdot v^2} dv = \int dt
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

$t = \text{duration}$
Now the speed is consistent with the thrust direction.

### Speed and thrust are in the same direction, and speed is greater than sliding friction.

The car will tend to a certain speed, and the direction of the speed will not change.

$$
\lim_{t \to \infty} |v| = \sqrt{\frac{F-f}{k}}
$$

The combined force of thrust and sliding friction $A = |F| - |f_k| > 0$

$$
m \frac{dv}{dt} = A - k v^2
$$

Refer to [ ### Speed 0 and thrust greater than the static friction ]

$$
v(t) = \sqrt{\frac{A}{k}} \tan{\left(\sqrt{\frac{Ak}{m^2}}(t + C_1)\right)}
$$

1. $v(0) = v_0$

$$
v(0) = \sqrt{\frac{A}{k}} \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot C_1\right)} = v_0
$$

2. $v(t_0) = v_1$

$$
v_1 = v(t_0) = \sqrt{\frac{A}{k}} \tan{\left(\sqrt{\frac{Ak}{m^2}}(t_0 + C_1)\right)}
$$

$$
\tan{\left( \alpha + \beta \right)} =
\frac{\sin{\left( \alpha + \beta \right)}}{\cos{\left( \alpha + \beta \right)}} =
\frac{\sin{\alpha} \cdot \cos{\beta} + \cos{\alpha} \cdot \sin{\beta}}
     {\cos{\alpha} \cdot \cos{\beta} - \sin{\alpha} \cdot \sin{\beta}}
$$

Divide the numerator and denominator by $\cos{\alpha} \cdot \cos{\beta}$

$$
\tan{\left( \alpha + \beta \right)} =
\frac{\tan{\alpha} + \tan{\beta}}{1 - \tan{\alpha} \cdot \tan{\beta}}
$$

$$
v_1 = \sqrt{\frac{A}{k}} \cdot \frac{ \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot t_0 \right)} +
                                      \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot C_1 \right)}}
                                    { 1 - \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot t_0 \right)} \cdot
                                          \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot C_1 \right)}}
$$

$$
\begin{cases}
v_1 = \frac{ \sqrt{\frac{A}{k}} \cdot z + v_0}
           { 1 - \sqrt{\frac{k}{A}} \cdot z \cdot v_0}
\\
z = \tan{\left(\sqrt{\frac{Ak}{m^2}} \cdot t_0 \right)}
\end{cases}
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
