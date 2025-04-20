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

- $b$ is the **y-intercept**, calculated as:

$$
b = y_0 - m \cdot x_0
$$

Here, $(x_0, y_0)$ and $(x_1, y_1)$ are the two endpoints of the line.

## Line Drawing Algorithms

There are different ways to compute the points on the line between $(x_0, y_0)$ and $(x_1, y_1)$. Let's look at a few common methods.

### 1. **Naive Line Drawing (Mathematical Equation)**

The simplest way to draw a line is by using the mathematical formula above to calculate the y-value for each x-coordinate between $x_0$ and $x_1$. 

#### Steps
1. Calculate the slope $m$ and the y-intercept $b$.
2. For each integer value of $x$ between $x_0$ and $x_1$, calculate the corresponding $y$-value using the equation:

$$
y = mx + b
$$

3. Draw the point $(x, y)$ for each calculated $x$-value.

#### Performance Considerations

- This approach is inefficient due to its reliance on floating-point arithmetic and rounding functions.

- It lacks precision for lines with very steep or very shallow slopes, which can result in visible artifacts.

- Rounding operations may introduce gaps or jagged edges in the rendered line.

- While not suitable for performance-critical applications, it is simple to implement and useful for educational purposes or prototyping.

### 2. DDA Line Drawing Algorithm

The **Digital Differential Analyzer** is a line drawing algorithm based on the incremental difference between the x and y coordinates in the two endpoints.

#### Steps
1. Calculate the differenece $(dx, dy)$ between the $x$ and $y$ coordinates of the endpoints.
2. Choose the number of $steps$ needed to plot the line by choosing the greater difference $max(|dx|, |dy|)$.
3. Calculate the steps for incrementing the x and y coordinates.
$$
x_{\text{step}}= \frac{dx}{steps} \quad y_{\text{step}} = \frac{dy}{steps}
$$
4. Starting from the initial point $(x_0,y_0)$, add $x_{\text{step}}$​ and $y_{\text{step}}$ at each iteration and plot the point until the final point $(x_1,y_1)$ is reached.

#### Performance Considerations

- The DDA algorithm provides more consistent results than the naive method, especially across different slopes.

- It still involves floating-point division and repeated additions, which may be computationally expensive on certain platforms.

- It is well-suited for applications requiring uniform and predictable stepping between points.

- The algorithm produces smoother and more uniform lines than the naive approach, particularly on low-resolution displays or long segments.

### 3. Bresenham Line Drawing Algorithm
Comming Soon