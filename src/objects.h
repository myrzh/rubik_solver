#ifndef OBJECTS_H
#define OBJECTS_H

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
const int leftSideOrder[] =  { 6, 5, 4, 7, 8, 3, 0, 1, 2 };
const int topSideOrder[] =   { 0, 1, 2, 7, 8, 3, 6, 5, 4 };

const int flatLevelOneSideOrder[] =   { 5, 6, 7, 4, 8, 0, 3, 2, 1 };
const int flatLevelTwoSideOrder[] =   { 6, 7, 0, 5, 8, 1, 4, 3, 2 };
const int flatLevelThreeSideOrder[] = { 3, 2, 1, 4, 8, 0, 5, 6, 7 };

// const int flatLevelOneSideOrder[] =   { 5, 4, 3, 6, 8, 2, 7, 0, 1 };
// const int flatLevelTwoSideOrder[] =   { 6, 5, 4, 7, 8, 3, 0, 1, 2 };
// const int flatLevelThreeSideOrder[] = { 3, 4, 5, 2, 8, 6, 1, 0, 7 };

typedef enum { REVERT, ROTATE_SIDE, NEXTSTEP, FILLCUBE, SETCOLOR, GETFILECUBE, OPENSTEPSFILE, SOLVECUBE } buttonFunction;

typedef struct {
    float xPos;
    float yPos;
    float width;
    float height;
    color color;
    buttonFunction function;

} Button;

float NDCToPixels(float coord, int dimension, char mode) {
    switch (mode) {
        case 'x':
            return (dimension * coord + dimension) / 2.0f;
            break;
        case 'y':
            return (dimension - dimension * coord) / 2.0f;
            break;
        default:
            return 0;
            break;
    }
}

void initButtons(Button mainButtons[], Button flatButtons[]) {
    for (int i = 0; i < 11; i++) {
        mainButtons[i].width = 0.15f;
        mainButtons[i].height = 0.15f;
    }
    for (int i = 0; i < 7; i++) {
        flatButtons[i].width = 0.15f;
        flatButtons[i].height = 0.15f;
    }

    mainButtons[0].xPos = -0.95f;
    mainButtons[0].yPos = 0.95f;
    mainButtons[0].color = WHITE;
    mainButtons[0].function = REVERT;

    mainButtons[1].xPos = -0.75f;
    mainButtons[1].yPos = 0.95f;
    mainButtons[1].color = GREEN;
    mainButtons[1].function = ROTATE_SIDE;

    mainButtons[2].xPos = -0.95f;
    mainButtons[2].yPos = 0.75f;
    mainButtons[2].color = YELLOW;
    mainButtons[2].function = ROTATE_SIDE;

    mainButtons[3].xPos = -0.75f;
    mainButtons[3].yPos = 0.75f;
    mainButtons[3].color = RED;
    mainButtons[3].function = ROTATE_SIDE;

    mainButtons[4].xPos = -0.55f;
    mainButtons[4].yPos = 0.75f;
    mainButtons[4].color = WHITE;
    mainButtons[4].function = ROTATE_SIDE;

    mainButtons[5].xPos = -0.35f;
    mainButtons[5].yPos = 0.75f;
    mainButtons[5].color = ORANGE;
    mainButtons[5].function = ROTATE_SIDE;

    mainButtons[6].xPos = -0.75f;
    mainButtons[6].yPos = 0.55f;
    mainButtons[6].color = BLUE;
    mainButtons[6].function = ROTATE_SIDE;

    mainButtons[7].xPos = 0.8f;
    mainButtons[7].yPos = 0.95f;
    mainButtons[7].color = WHITE;
    mainButtons[7].function = NEXTSTEP;

    mainButtons[8].xPos = 0.8f;
    mainButtons[8].yPos = 0.75f;
    mainButtons[8].color = WHITE;
    mainButtons[8].function = FILLCUBE;

    mainButtons[9].xPos = 0.6f;
    mainButtons[9].yPos = 0.95f;
    mainButtons[9].color = WHITE;
    mainButtons[9].function = OPENSTEPSFILE;

    mainButtons[10].xPos = -0.075f;
    mainButtons[10].yPos = -0.8f;
    mainButtons[10].color = WHITE;
    mainButtons[10].function = SOLVECUBE;

    flatButtons[0].xPos = 0.6f;
    flatButtons[0].yPos = -0.4f;
    flatButtons[0].color = WHITE;
    flatButtons[0].function = SETCOLOR;

    flatButtons[1].xPos = 0.8f;
    flatButtons[1].yPos = -0.4f;
    flatButtons[1].color = GREEN;
    flatButtons[1].function = SETCOLOR;

    flatButtons[2].xPos = 0.6f;
    flatButtons[2].yPos = -0.6f;
    flatButtons[2].color = RED;
    flatButtons[2].function = SETCOLOR;

    flatButtons[3].xPos = 0.8f;
    flatButtons[3].yPos = -0.6f;
    flatButtons[3].color = BLUE;
    flatButtons[3].function = SETCOLOR;

    flatButtons[4].xPos = 0.6f;
    flatButtons[4].yPos = -0.8f;
    flatButtons[4].color = ORANGE;
    flatButtons[4].function = SETCOLOR;

    flatButtons[5].xPos = 0.8f;
    flatButtons[5].yPos = -0.8f;
    flatButtons[5].color = YELLOW;
    flatButtons[5].function = SETCOLOR;

    flatButtons[6].xPos = -0.95f;
    flatButtons[6].yPos = -0.8f;
    flatButtons[6].color = WHITE;
    flatButtons[6].function = GETFILECUBE;
}

#endif
