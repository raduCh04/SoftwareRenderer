# Circle Drawing Algorithms

## Overview

Drawing circles is a fundamental operation in computer graphics. There are several algorithms for rendering circles, with the most popular ones based on the **implicit equation of a circle** or optimized algorithms like **Bresenham's Circle Algorithm**.

### Circle Equation

The general equation for a circle with center \( (h, k) \) and radius \( r \) is derived from the **implicit equation** of a circle:

$$
(x - h)^2 + (y - k)^2 = r^2
$$

Where:
- \( (h, k) \) is the center of the circle.
- \( r \) is the radius of the circle.
- \( (x, y) \) are the coordinates of any point on the circle.

## Circle Drawing Algorithms

There are various methods for drawing a circle, including the **Mathematical Method**, **Midpoint Circle Drawing**, and **Bresenham's Circle Algorithm**.

### 1. **Mathematical Equation Method**

This approach uses the parametric equation of a circle:

$$
x(t) = h + r \cdot \cos(t)
$$
$$
y(t) = k + r \cdot \sin(t)
$$

Where:
- \( t \) $\in  [0, 2\pi]$, representing the angle around the circle.
- The parameter \( t \) is incremented in small steps (e.g., \( 0.01 \)) to approximate the points on the circle.

#### Steps:
1. Start with the center \( (h, k) \) and radius \( r \).
2. For each value of \( t \), compute the corresponding \( x(t) \) and \( y(t) \) using the parametric equations.
3. Round the calculated coordinates to the nearest integer values.
4. Plot the points \( (x(t), y(t)) \) for \( t \) from \( 0 \) to \( 2\pi \).

##### Performance Consideration:
This method is computationally expensive because of frequent **floating-point operations** (sine and cosine calculations) and **rounding**. It is not optimal for real-time applications.

### 2. **Optimized Equation Method**
This approach uses the same equation as the **Mathematical Equation Method**, however it is based on the symmetry of a circle, since a circle can be divided in **eight equal octants** with the same **45°** angle. This means we can mirror the coordinates of one octant, to create a full circle. For a given point (\(x, y\)), the following points are also on the circle:
$$
(h + x, k + y),(h - x, k + y),(h + x, k - y),(h -x, k - y) \\
(h + y, k + x),(h - y, k + x),(h + y, k - x),(h -y, k - x)
$$

Where:
- \(t\) $\in [2/\pi, 4/\pi]$

- $(h,k)$ is the center of the circle.

- $r$ is the radius of the circle.

- $x$ and $y$ are the coordinates of a point on the circle in one octant.

#### Steps:
1. Start with the center \( (h, k) \) and radius \( r \).
2. For each value of \( t \), compute the corresponding \( x(t) \) and \( y(t) \) using the parametric equations.
3. Round the calculated coordinates to the nearest integer values.
4. Mirror the calculated coordinates to the other seven points on the circle.
4. Plot the points \( (x(t), y(t)) \) for all evaluated coordinates for the range $2/\pi$ to $4/\pi$.
