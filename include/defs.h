/**
 * @file defs.h
 * @author Radu-D. Chira (github.com/RaduCh04)
 * @brief 
 * @version 0.1
 * @date 2025-05-04
 * 
 */

/**
 * @brief Predefined basic colors
 *
 */
typedef enum Color
{
    BLACK = 0x000000FF,
    WHITE = 0xFFFFFFFF,
    RED = 0xFF0000FF,
    GREEN = 0x00FF00FF,
    BLUE = 0x0000FFFF,
} Color;

/**
 * @brief Important constants, which can be changed for personal use
 *
 */
enum CONST
{
    WIDTH = 800,
    HEIGHT = 600,
    RES = (WIDTH * HEIGHT),
};