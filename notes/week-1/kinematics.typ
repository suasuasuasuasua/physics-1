= Week 1 - Kinematics

== Goals

- Describe geometric motion of an object in 1D and 2D
- Discuss why an object's motion changes when a force is applied

== Definitions

- Kinematics
  - *How* does an object move?
  - What does the geometry of motion look like?
  - Described using $m arrow(a)$ from Newton's Second Law of Motion
- Dynamics
  - *Why* does an object move?
  - What are the causes of motion?
  - Described using $arrow(F)$ from Newton's Second Law of Motion
- Coordinate Systems
  - Defined with the following properties
    - Origin $(0, 0)$
    - An axis should be logically chosen w.r.t the problem
    - Define unit vector(s) for each point in the coordinate space
- Distance
  - The length of the path travelled by an object between two objects in space
  - Distance is a *scalar* quantity
- Displacement
  - Describes a change in position after some time $Delta t$

== Equations

- The *position* function is described as $arrow(r)(t) = x(t) hat(i)$
  - Note that it is a vector function
  - We can also define it in terms of an initial time plus some offset:
    $arrow(r)(t + Delta t) = x(t + Delta t) hat(i)$
- The *displacement* vector is $Delta hat(r) = hat(r)(t + Delta t) - arrow(t)$
  or $(x(t + Delta t) - x(t)) hat(i)$
  - This is the difference between the new position an old position
  - $Delta x$ is called the component of the displacement vector
- Average velocity depends on A) the time interval $[t, t + Delta t]$ and
  the change in position
  $
    arrow(V)_("ave") equiv
    (Delta arrow(r)) / (Delta t) = (Delta x) / (Delta t) hat(i)
  $
  - $frac(Delta x, Delta t)$ is called the component of the average velocity
- The instantaneous velocity (at some specific time $t_i$ is defined as the
  derivative at the position function $arrow(r)$ at time $t_i$
  $
    arrow(v)(t) = dif / (dif t) arrow(r)(t)
  $
  - graphically, this is the slope of the tangent line at $t_i$

== Reference

Here is a list of useful derivatives. Hints are 1) power rule, 2) product rule,
and 3) quotient rule

1. Polynomial function
  $
    "if" x(t) = A t^n arrow dif / (dif t) x = n A t^(n-1)
  $
  - the derivative of $t^n$ is $n t^(n-1)$
2. Exponential function
  $
    "if" x(t) = A e^(b t) arrow dif / (dif t) x = A b e^(b t)
  $
  - the derivative of $e^x$ is $e^x$
3. Logarithmic function
  $
    "if" x(t) = A ln(b + c t) arrow dif / (dif t) x = (A c) / (b + c t)
  $
  - the derivative of $ln(t)$ is $1 / t$
4. Sine function
  $
    "if" x(t) = A sin(b + c t) arrow dif / (dif t) x = A c cos(b + c t)
  $
  - the derivative of $sin(t)$ is $cos(t)$
5. Cosine function
  $
    "if" x(t) = A cos(b + c t) arrow dif / (dif t) x = -A c sin(b + c t)
  $
  - the derivative of $cos(t)$ is $-sin(t)$
