#ifndef COLORS_HEADER
#define COLORS_HEADER

typedef enum { RED, GREEN, BLUE, WHITE, ORANGE, YELLOW, CYAN, PURPLE } color;

const float colors[][3] = {
        { 1.0f, 0.0f, 0.0f }, // Red
        { 0.0f, 1.0f, 0.0f }, // Green
        { 0.0f, 0.0f, 1.0f }, // Blue
        { 1.0f, 1.0f, 1.0f }, // White
        { 1.0f, 0.65f, 0.0f }, // Orange
        { 1.0f, 1.0f, 0.0f }  // Yellow
        { 0.0f, 1.0f, 0.0f }  // Cyan
        { 1.0f, 0.0f, 0.0f }  // Purple
    };

#endif
