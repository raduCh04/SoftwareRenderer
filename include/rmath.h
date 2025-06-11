/**
 * @file rmath.h
 * @author Radu-Dumitru Chira (github.com/RaduCh04)
 * @version 0.1
 * @date 2025-04-12
 */

#include <math.h>
#include <stdint.h>

#ifndef M_PI
    #define M_PI 3.141592653589793f
#endif

typedef struct Point
{
    uint32_t x, y;
} Point;
typedef Point Vec2;