#include "colors.h"

const float rightCoords[][2] = {
    { 0.0f, 0.0f },
    { 0.173f, 0.1f },
    { 0.346f, 0.2f },

    { 0.0f, -0.2f },
    { 0.173f, -0.1f },
    { 0.346f, 0.0f },

    { 0.0f, -0.4f },
    { 0.173f, -0.3f },
    { 0.346f, -0.2f }
};

const float leftCoords[][2] = {
    { 0.0f, 0.0f },
    { -0.173f, 0.1f },
    { -0.346f, 0.2f },

    { 0.0f, -0.2f },
    { -0.173f, -0.1f },
    { -0.346f, 0.0f },

    { 0.0f, -0.4f },
    { -0.173f, -0.3f },
    { -0.346f, -0.2f }
};

const float topCoords[][2] = {
    { 0.0f, 0.0f },
    { -0.173f, 0.1f },
    { -0.346f, 0.2f },

    { 0.173f, 0.1f },
    { 0.0f, 0.2f },
    { -0.173f, 0.3f },

    { 0.346f, 0.2f },
    { 0.173f, 0.3f },
    { 0.0f, 0.4f }
};

const int rightSideOrder[] = { 1, 2, 3, 0, 8, 4, 7, 6, 5 };
const int leftSideOrder[] = { 6, 5, 4, 7, 8, 3, 0, 1, 2 };
const int topSideOrder[] = { 0, 1, 2, 7, 8, 3, 6, 5, 4 };

typedef enum { REVERT, ROTATE_SIDE, NEXTSTEP } buttonFunction;

typedef struct {
    float xPos;
    float yPos;
    float width;
    float height;
    color color;
    buttonFunction function;

} Button;
