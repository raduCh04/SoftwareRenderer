# Line Drawing Algorithms

## Overview

In computer graphics, drawing a line is one of the fundamental tasks. There are several algorithms for drawing lines between two points. The most basic equation for drawing a line in a 2D space is derived from the **linear equation**:

### General Line Equation

The general form of the line equation is given by:

$$
y = mx + b
$$

Where:
- $y$ is the y-coordinate of any point on the line.
- $x$ is the x-coordinate of the point.
- $m$ is the **slope** of the line, defined as:

$$
m = \frac{y_1 - y_0}{x_1 - x_0}
$$

- \( b \) is the **y-intercept**, calculated as:

$$
b = y_0 - m \cdot x_0
$$

Here, \( (x_0, y_0) \) and \( (x_1, y_1) \) are the two endpoints of the line.

## Line Drawing Algorithms

There are different ways to compute the points on the line between \( (x_0, y_0) \) and \( (x_1, y_1) \). Let's look at a few common methods.

### 1. **Naive Line Drawing (Mathematical Equation)**

The simplest way to draw a line is by using the mathematical formula above to calculate the y-value for each x-coordinate between \( x_0 \) and \( x_1 \). This method is **not optimal** for performance as it involves **floating-point operations** and **rounding errors**.

1. **Step 1**: Calculate the slope \( m \) and the y-intercept \( b \).
2. **Step 2**: For each integer value of \( x \) between \( x_0 \) and \( x_1 \), calculate the corresponding \( y \)-value using the equation:

$$
y = mx + b
$$

3. **Step 3**: Draw the point \( (x, y) \) for each calculated \( x \)-value.

### 2. **DDA Line Drawing Algorithm

Coming Soon