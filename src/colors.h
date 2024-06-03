#ifndef COLORS_H
#define COLORS_H

typedef enum { RED, GREEN, BLUE, WHITE, ORANGE, YELLOW, CYAN, PURPLE } color;

float colors[][3] = {
        { 1.0f, 0.0f, 0.0f }, // Red
        { 0.0f, 1.0f, 0.0f }, // Green
        { 0.0f, 0.0f, 1.0f }, // Blue
        { 1.0f, 1.0f, 1.0f }, // White
        { 1.0f, 0.65f, 0.0f }, // Orange
        { 1.0f, 1.0f, 0.0f },  // Yellow
        { 0.0f, 1.0f, 1.0f },  // Cyan
        { 1.0f, 0.0f, 1.0f },  // Purple
    };

color getColorFromChar(char letter) {
    switch (letter) {
        case 'R':
        case 'r':
            return RED;
        case 'G':
        case 'g':
            return GREEN;
        case 'B':
        case 'b':
            return BLUE;
        case 'W':
        case 'w':
            return WHITE;
        case 'O':
        case 'o':
            return ORANGE;
        case 'Y':
        case 'y':
            return YELLOW;
        default:
            return 0;
            break;
    }
}

#endif
