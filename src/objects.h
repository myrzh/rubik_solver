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

// const int rightSideOrder[] = { 1, 2, 3, 0, 8, 4, 7, 6, 5 };
// const int leftSideOrder[] =  { 6, 5, 4, 7, 8, 3, 0, 1, 2 };
// const int topSideOrder[] =   { 0, 1, 2, 7, 8, 3, 6, 5, 4 };

const int rightSideOrder[] = { 0, 1, 2, 7, 8, 3, 6, 5, 4 };
const int leftSideOrder[] =  { 1, 0, 7, 2, 8, 6, 3, 4, 5 };
const int topSideOrder[] =   { 6, 7, 0, 5, 8, 1, 4, 3, 2 };

// const int flatLevelOneSideOrder[] =   { 5, 6, 7, 4, 8, 0, 3, 2, 1 };
// const int flatLevelTwoSideOrder[] =   { 6, 7, 0, 5, 8, 1, 4, 3, 2 };
// const int flatLevelThreeSideOrder[] = { 3, 2, 1, 4, 8, 0, 5, 6, 7 };

const int flatBlueSideOrder[] =   { 2, 3, 4, 1, 8, 5, 0, 7, 6 };
const int flatOrangeSideOrder[] = { 4, 5, 6, 3, 8, 7, 2, 1, 0 };
const int flatWhiteSideOrder[] =  { 7, 0, 1, 6, 8, 2, 5, 4, 3 };
const int flatRedSideOrder[] =    { 0, 1, 2, 7, 8, 3, 6, 5, 4 };
const int flatYellowSideOrder[] = { 1, 0, 7, 2, 8, 6, 3, 4, 5 };
const int flatGreenSideOrder[] =  { 6, 7, 0, 5, 8, 1, 4, 3, 2 };

typedef enum { REVERT, ROTATE_SIDE, NEXTSTEP, FILLCUBE, SETCOLOR, GETFILECUBE, OPENSTEPSFILE, SOLVECUBE, SHUFFLE } buttonFunction;

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
    for (int i = 0; i < 12; i++) {
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
    mainButtons[1].color = BLUE;
    mainButtons[1].function = ROTATE_SIDE;

    mainButtons[2].xPos = -0.95f;
    mainButtons[2].yPos = 0.75f;
    mainButtons[2].color = ORANGE;
    mainButtons[2].function = ROTATE_SIDE;

    mainButtons[3].xPos = -0.75f;
    mainButtons[3].yPos = 0.75f;
    mainButtons[3].color = WHITE;
    mainButtons[3].function = ROTATE_SIDE;

    mainButtons[4].xPos = -0.55f;
    mainButtons[4].yPos = 0.75f;
    mainButtons[4].color = RED;
    mainButtons[4].function = ROTATE_SIDE;

    mainButtons[5].xPos = -0.35f;
    mainButtons[5].yPos = 0.75f;
    mainButtons[5].color = YELLOW;
    mainButtons[5].function = ROTATE_SIDE;

    mainButtons[6].xPos = -0.75f;
    mainButtons[6].yPos = 0.55f;
    mainButtons[6].color = GREEN;
    mainButtons[6].function = ROTATE_SIDE;

    mainButtons[7].xPos = 0.8f;
    mainButtons[7].yPos = 0.95f;
    mainButtons[7].color = WHITE;
    mainButtons[7].function = NEXTSTEP;

    mainButtons[8].xPos = 0.8f;
    mainButtons[8].yPos = 0.55f;
    mainButtons[8].color = WHITE;
    mainButtons[8].function = FILLCUBE;

    mainButtons[9].xPos = 0.8f;
    mainButtons[9].yPos = 0.75f;
    mainButtons[9].color = WHITE;
    mainButtons[9].function = OPENSTEPSFILE;

    mainButtons[10].xPos = -0.075f;
    mainButtons[10].yPos = -0.8f;
    mainButtons[10].color = WHITE;
    mainButtons[10].function = SOLVECUBE;

    mainButtons[11].xPos = -0.95f;
    mainButtons[11].yPos = 0.55f;
    mainButtons[11].color = WHITE;
    mainButtons[11].function = SHUFFLE;

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

const char* authorsText =
            "RubikSolver (c)\n"
            "\n"
            "Made by:\n"
            "Plotnikov D.A.\n"
            "Shtarev I.A.\n"
            "Group 5151003/30002\n"
            "2024\n"
            "\n"
            "Peter the Great St.Petersburg Polytechnic University\n"
            "Institute of Cybersecurity and Computer Science\n"
            "Higher School of Cybersecurity\n"
            "\n"
            "Main window usage:\n"
            "Colored buttons -- rotate correspoding side (right-click for counterclockwise)\n"
            "I -- initialize cube (restore original state)\n"
            "R -- randomize cube\n"
            "N -- execute next step (if steps file is opened)\n"
            "O -- open steps file (*.txt)\n"
            "C -- open cube definition window\n"
            "S -- solve cube and load solution to steps file\n"
            "\n"
            "Cube definition window usage:\n"
            "Colored buttons -- define purple square (central squares are being skipped)\n"
            "Down left button -- open cube from file (*.txt)\n";

#endif
