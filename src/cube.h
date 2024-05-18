#include "colors.h"

#define CORNERFACE 1
#define CORNERWHITE 2
#define CORNERPREV 3

typedef enum { R, _R, G, _G, B, _B, W, _W, O, _O, Y, _Y } action;

void swap(color* x, color* y) {
    color t;
    t = (*x);
    (*x) = (*y);
    (*y) = t;
}

typedef struct {
    color whiteSide[9];
    color yellowSide[9];
    color redSide[9];
    color blueSide[9];
    color greenSide[9];
    color orangeSide[9];
} Cube;

void initCube(Cube* thisCube) {
    for (int index = 0; index < 9; index++) {
        thisCube->whiteSide[index] = WHITE;
        thisCube->yellowSide[index] = YELLOW;
        thisCube->redSide[index] = RED;
        thisCube->blueSide[index] = BLUE;
        thisCube->greenSide[index] = GREEN;
        thisCube->orangeSide[index] = ORANGE;
    }
}

void fillSideFromArray(color* cubeSide, char sideColors[]) {
    for (int index = 0; index < 9; index++) {
        switch (sideColors[index]) {
        case 'w':
            cubeSide[index] = WHITE;
            break;
        case 'y':
            cubeSide[index] = YELLOW;
            break;
        case 'r':
            cubeSide[index] = RED;
            break;
        case 'b':
            cubeSide[index] = BLUE;
            break;
        case 'g':
            cubeSide[index] = GREEN;
            break;
        case 'o':
            cubeSide[index] = ORANGE;
            break;
        default:
            break;
        }
    }
}

void rotateSideBy90(Cube* thisCube, color sideToRotate) {
    switch (sideToRotate) {
    case WHITE:
        printf("ROTATE WHITE\n");
        swap(&thisCube->whiteSide[7], &thisCube->whiteSide[3]);
        swap(&thisCube->whiteSide[6], &thisCube->whiteSide[4]);
        swap(&thisCube->whiteSide[0], &thisCube->whiteSide[2]);
        swap(&thisCube->whiteSide[7], &thisCube->whiteSide[5]);
        swap(&thisCube->whiteSide[0], &thisCube->whiteSide[4]);
        swap(&thisCube->whiteSide[1], &thisCube->whiteSide[3]);

        swap(&thisCube->blueSide[0], &thisCube->orangeSide[0]);
        swap(&thisCube->blueSide[7], &thisCube->orangeSide[7]);
        swap(&thisCube->blueSide[6], &thisCube->orangeSide[6]);

        swap(&thisCube->orangeSide[6], &thisCube->greenSide[6]);
        swap(&thisCube->orangeSide[7], &thisCube->greenSide[7]);
        swap(&thisCube->orangeSide[0], &thisCube->greenSide[0]);

        swap(&thisCube->greenSide[6], &thisCube->redSide[6]);
        swap(&thisCube->greenSide[7], &thisCube->redSide[7]);
        swap(&thisCube->greenSide[0], &thisCube->redSide[0]);
        break;
    case YELLOW:
        printf("ROTATE YELLOW\n");
        swap(&thisCube->yellowSide[7], &thisCube->yellowSide[3]);
        swap(&thisCube->yellowSide[6], &thisCube->yellowSide[4]);
        swap(&thisCube->yellowSide[0], &thisCube->yellowSide[2]);
        swap(&thisCube->yellowSide[7], &thisCube->yellowSide[5]);
        swap(&thisCube->yellowSide[0], &thisCube->yellowSide[4]);
        swap(&thisCube->yellowSide[1], &thisCube->yellowSide[3]);

        swap(&thisCube->blueSide[4], &thisCube->redSide[4]);
        swap(&thisCube->blueSide[3], &thisCube->redSide[3]);
        swap(&thisCube->blueSide[2], &thisCube->redSide[2]);

        swap(&thisCube->redSide[2], &thisCube->greenSide[2]);
        swap(&thisCube->redSide[3], &thisCube->greenSide[3]);
        swap(&thisCube->redSide[4], &thisCube->greenSide[4]);

        swap(&thisCube->greenSide[4], &thisCube->orangeSide[4]);
        swap(&thisCube->greenSide[3], &thisCube->orangeSide[3]);
        swap(&thisCube->greenSide[2], &thisCube->orangeSide[2]);
        break;
    case RED:
        printf("ROTATE RED\n");
        swap(&thisCube->redSide[0], &thisCube->redSide[4]);
        swap(&thisCube->redSide[7], &thisCube->redSide[5]);
        swap(&thisCube->redSide[1], &thisCube->redSide[3]);
        swap(&thisCube->redSide[0], &thisCube->redSide[6]);
        swap(&thisCube->redSide[1], &thisCube->redSide[5]);
        swap(&thisCube->redSide[2], &thisCube->redSide[4]);

        swap(&thisCube->blueSide[6], &thisCube->whiteSide[3]);
        swap(&thisCube->blueSide[5], &thisCube->whiteSide[2]);
        swap(&thisCube->blueSide[4], &thisCube->whiteSide[1]);

        swap(&thisCube->whiteSide[1], &thisCube->greenSide[0]);
        swap(&thisCube->whiteSide[2], &thisCube->greenSide[1]);
        swap(&thisCube->whiteSide[3], &thisCube->greenSide[2]);

        swap(&thisCube->greenSide[0], &thisCube->yellowSide[3]);
        swap(&thisCube->greenSide[1], &thisCube->yellowSide[2]);
        swap(&thisCube->greenSide[2], &thisCube->yellowSide[1]);
        break;
    case BLUE:
        printf("ROTATE BLUE\n");
        swap(&thisCube->blueSide[1], &thisCube->blueSide[7]);
        swap(&thisCube->blueSide[2], &thisCube->blueSide[6]);
        swap(&thisCube->blueSide[5], &thisCube->blueSide[3]);
        swap(&thisCube->blueSide[2], &thisCube->blueSide[0]);
        swap(&thisCube->blueSide[7], &thisCube->blueSide[3]);
        swap(&thisCube->blueSide[6], &thisCube->blueSide[4]);

        swap(&thisCube->yellowSide[1], &thisCube->orangeSide[4]);
        swap(&thisCube->yellowSide[0], &thisCube->orangeSide[5]);
        swap(&thisCube->yellowSide[7], &thisCube->orangeSide[6]);

        swap(&thisCube->whiteSide[7], &thisCube->orangeSide[4]);
        swap(&thisCube->whiteSide[0], &thisCube->orangeSide[5]);
        swap(&thisCube->whiteSide[1], &thisCube->orangeSide[6]);

        swap(&thisCube->whiteSide[7], &thisCube->redSide[0]);
        swap(&thisCube->whiteSide[0], &thisCube->redSide[1]);
        swap(&thisCube->whiteSide[1], &thisCube->redSide[2]);
        break;
    case GREEN:
        printf("ROTATE GREEN\n");
        swap(&thisCube->greenSide[6], &thisCube->greenSide[2]);
        swap(&thisCube->greenSide[5], &thisCube->greenSide[3]);
        swap(&thisCube->greenSide[7], &thisCube->greenSide[1]);
        swap(&thisCube->greenSide[4], &thisCube->greenSide[6]);
        swap(&thisCube->greenSide[7], &thisCube->greenSide[3]);
        swap(&thisCube->greenSide[0], &thisCube->greenSide[2]);

        swap(&thisCube->whiteSide[5], &thisCube->orangeSide[2]);
        swap(&thisCube->whiteSide[4], &thisCube->orangeSide[1]);
        swap(&thisCube->whiteSide[3], &thisCube->orangeSide[0]);

        swap(&thisCube->yellowSide[3], &thisCube->orangeSide[2]);
        swap(&thisCube->yellowSide[4], &thisCube->orangeSide[1]);
        swap(&thisCube->yellowSide[5], &thisCube->orangeSide[0]);

        swap(&thisCube->yellowSide[3], &thisCube->redSide[6]);
        swap(&thisCube->yellowSide[4], &thisCube->redSide[5]);
        swap(&thisCube->yellowSide[5], &thisCube->redSide[4]);
        break;
    case ORANGE:
        printf("ROTATE ORANGE\n");
        swap(&thisCube->orangeSide[4], &thisCube->orangeSide[0]);
        swap(&thisCube->orangeSide[3], &thisCube->orangeSide[1]);
        swap(&thisCube->orangeSide[5], &thisCube->orangeSide[7]);
        swap(&thisCube->orangeSide[4], &thisCube->orangeSide[2]);
        swap(&thisCube->orangeSide[5], &thisCube->orangeSide[1]);
        swap(&thisCube->orangeSide[6], &thisCube->orangeSide[0]);

        swap(&thisCube->blueSide[2], &thisCube->yellowSide[5]);
        swap(&thisCube->blueSide[1], &thisCube->yellowSide[6]);
        swap(&thisCube->blueSide[0], &thisCube->yellowSide[7]);

        swap(&thisCube->yellowSide[5], &thisCube->greenSide[6]);
        swap(&thisCube->yellowSide[6], &thisCube->greenSide[5]);
        swap(&thisCube->yellowSide[7], &thisCube->greenSide[4]);

        swap(&thisCube->greenSide[6], &thisCube->whiteSide[7]);
        swap(&thisCube->greenSide[5], &thisCube->whiteSide[6]);
        swap(&thisCube->greenSide[4], &thisCube->whiteSide[5]);
        break;
    default:
        break;
    }
}

void rotateSideBy90Back(Cube* thisCube, color sideToRotate)
{
    rotateSideBy90(thisCube, sideToRotate);
    rotateSideBy90(thisCube, sideToRotate);
    rotateSideBy90(thisCube, sideToRotate);
}

color getPrevPanel(color facePanel)
{
    color prev = 0;
    switch (facePanel)
    {
    case(RED):
    {
        prev = GREEN;
    }
    case(GREEN):
    {
        prev = ORANGE;
    }
    case(ORANGE):
    {
        prev = BLUE;
    }
    case(BLUE):
    {
        prev = RED;
    }
    default:
        break;
    }

    return prev;
}

color getNextPanel(color facePanel)
{
    color next = 0;
    switch (facePanel)
    {
    case(RED):
    {
        next = BLUE;
    }
    case(GREEN):
    {
        next = RED;
    }
    case(ORANGE):
    {
        next = GREEN;
    }
    case(BLUE):
    {
        next = ORANGE;
    }
    default:
        break;
    }

    return next;
}

char checkIfFirstStep(Cube* thisCube)
{
    char countPoses[4] = { 0 };

    if (thisCube->whiteSide[6] == WHITE && thisCube->orangeSide[7] == ORANGE)
    {
        countPoses[0] = 1;
    }
    if (thisCube->whiteSide[4] == WHITE && thisCube->greenSide[7] == GREEN)
    {
        countPoses[1] = 1;
    }
    if (thisCube->whiteSide[0] == WHITE && thisCube->blueSide[7] == BLUE)
    {
        countPoses[2] = 1;
    }
    if (thisCube->whiteSide[2] == WHITE && thisCube->redSide[7] == RED)
    {
        countPoses[3] = 1;
    }

    char count = 0;

    for (int i = 0; i < 4; i++)
    {
        if (countPoses[i] == 1)
        {
            count++;
        }
    }

    if (count == 4)
    {
        return 1;
    }
    return 0;
}

char checkIfSecondStep(Cube* thisCube)
{
    char countPoses[4] = { 0 };

    if (thisCube->blueSide[6] == BLUE && thisCube->redSide[0] == RED && thisCube->whiteSide[1] == WHITE)
    {
        countPoses[0] = 1;
    }
    if (thisCube->orangeSide[6] == ORANGE && thisCube->blueSide[0] == BLUE && thisCube->whiteSide[7] == WHITE)
    {
        countPoses[1] = 1;
    }
    if (thisCube->greenSide[6] == GREEN && thisCube->orangeSide[0] == ORANGE && thisCube->whiteSide[5] == WHITE)
    {
        countPoses[2] = 1;
    }
    if (thisCube->redSide[6] == RED && thisCube->greenSide[0] == GREEN && thisCube->whiteSide[3] == WHITE)
    {
        countPoses[3] = 1;
    }

    char count = 0;

    for (int i = 0; i < 4; i++)
    {
        if (countPoses[i] == 1)
        {
            count++;
        }
    }

    if (count == 4)
    {
        return 1;
    }
    return 0;
}

char checkIfThirdStep(Cube* thisCube)
{
    char countPoses[4] = { 0 };

    if (thisCube->blueSide[5] == BLUE && thisCube->redSide[1] == RED)
    {
        countPoses[0] = 1;
    }
    if (thisCube->orangeSide[5] == ORANGE && thisCube->blueSide[1] == BLUE)
    {
        countPoses[1] = 1;
    }
    if (thisCube->greenSide[5] == GREEN && thisCube->orangeSide[1] == ORANGE)
    {
        countPoses[2] = 1;
    }
    if (thisCube->redSide[5] == RED && thisCube->greenSide[1] == GREEN)
    {
        countPoses[3] = 1;
    }

    char count = 0;

    for (int i = 0; i < 4; i++)
    {
        if (countPoses[i] == 1)
        {
            count++;
        }
    }

    if (count == 4)
    {
        return 1;
    }
    return 0;
}

char checkIfFourthStep(Cube* thisCube)
{
    char countPoses[4] = { 0 };

    if (thisCube->blueSide[5] == BLUE && thisCube->redSide[1] == RED)
    {
        countPoses[0] = 1;
    }
    if (thisCube->orangeSide[5] == ORANGE && thisCube->blueSide[1] == BLUE)
    {
        countPoses[1] = 1;
    }
    if (thisCube->greenSide[5] == GREEN && thisCube->orangeSide[1] == ORANGE)
    {
        countPoses[2] = 1;
    }
    if (thisCube->redSide[5] == RED && thisCube->greenSide[1] == GREEN)
    {
        countPoses[3] = 1;
    }

    char count = 0;

    for (int i = 0; i < 4; i++)
    {
        if (countPoses[i] == 1)
        {
            count++;
        }
    }

    if (count == 4)
    {
        return 1;
    }
    return 0;
}

// char checkIfFifthhStep(Cube* thisCube)
// {

// }

// char checkIfSixthStep(Cube* thisCube)
// {

// }

void makeCross(Cube* thisCube, int* countPoses)
{
    color facePanel = ORANGE;
    if (countPoses[0] == 0)
    {
        if (thisCube->orangeSide[3] == ORANGE && thisCube->yellowSide[2] == WHITE)
        {
            rotateSideBy90(thisCube, ORANGE);
            rotateSideBy90(thisCube, ORANGE);
            countPoses[0]++;
        }
        else if (thisCube->orangeSide[3] == WHITE && thisCube->yellowSide[2] == ORANGE)
        {
            rotateSideBy90(thisCube, YELLOW);
            rotateSideBy90(thisCube, GREEN);
            rotateSideBy90(thisCube, ORANGE);
            rotateSideBy90Back(thisCube, GREEN);
        }
    }
    facePanel = BLUE;

    if (countPoses[1] == 0)
    {
        if (thisCube->blueSide[3] == BLUE && thisCube->yellowSide[2] == WHITE)
        {
            rotateSideBy90(thisCube, BLUE);
            rotateSideBy90(thisCube, BLUE);
            countPoses[1] = 1;
        }
        else if (thisCube->blueSide[3] == WHITE && thisCube->yellowSide[4] == BLUE)
        {
            rotateSideBy90(thisCube, YELLOW);
            rotateSideBy90(thisCube, ORANGE);
            rotateSideBy90(thisCube, BLUE);
            rotateSideBy90Back(thisCube, ORANGE);//Поворот в обратную сторону, поэтому 3 раза
            countPoses[1] = 1;
        }
    }
    facePanel = GREEN;

    if (countPoses[2] == 0)
    {
        if (thisCube->greenSide[3] == GREEN && thisCube->yellowSide[0] == WHITE)
        {
            rotateSideBy90(thisCube, GREEN);
            rotateSideBy90(thisCube, GREEN);
            countPoses[2] = 1;
        }
        else if (thisCube->greenSide[3] == WHITE && thisCube->yellowSide[0] == GREEN)
        {
            rotateSideBy90(thisCube, YELLOW);
            rotateSideBy90(thisCube, RED);
            rotateSideBy90(thisCube, GREEN);
            rotateSideBy90Back(thisCube, RED);//Поворот в обратную сторону, поэтому 3 раза
            countPoses[2] = 1;
        }
    }
    facePanel = RED;

    if (countPoses[3] == 0)
    {
        if (thisCube->redSide[3] == RED && thisCube->yellowSide[2] == WHITE)
        {
            rotateSideBy90(thisCube, RED);
            rotateSideBy90(thisCube, RED);
            countPoses[3] = 1;
            facePanel = ORANGE;
        }
        else if (thisCube->redSide[3] == WHITE && thisCube->yellowSide[6] == RED)
        {
            rotateSideBy90(thisCube, YELLOW);
            rotateSideBy90(thisCube, BLUE);
            rotateSideBy90(thisCube, RED);
            rotateSideBy90Back(thisCube, BLUE);//Поворот в обратную сторону, поэтому 3 раза
            countPoses[3] = 1;
            facePanel = ORANGE;
        }
    }
}

void firstStep(Cube* thisCube)
{
    int countPoses[4] = { 0 }; //Счетчик сколько по итогу стоит на месте, 0 - orange, 1 - green, 2 - blue, 3 - red
    if (thisCube->whiteSide[6] == WHITE && thisCube->orangeSide[7] == ORANGE)
    {
        countPoses[0]=1;
    }
    if (thisCube->whiteSide[4] == WHITE && thisCube->greenSide[7] == GREEN)
    {
        countPoses[1]=1;
    }
    if (thisCube->whiteSide[0] == WHITE && thisCube->blueSide[7] == BLUE)
    {
        countPoses[2]=1;
    }
    if (thisCube->whiteSide[2] == WHITE && thisCube->redSide[7] == RED)
    {
        countPoses[3]=1;
    }
    
    makeCross(thisCube, countPoses);
    if (countPoses[0] == 0 || countPoses[1] == 0 || countPoses[2] == 0 || countPoses[3] == 0)
    {
        rotateSideBy90(thisCube, YELLOW);
        makeCross(thisCube, countPoses);
        if (countPoses[0] == 0 || countPoses[1] == 0 || countPoses[2] == 0 || countPoses[3] == 0)
        {
            rotateSideBy90(thisCube, YELLOW);
            makeCross(thisCube, countPoses);
            if (countPoses[0] == 0 || countPoses[1] == 0 || countPoses[2] == 0 || countPoses[3] == 0)
            {
                rotateSideBy90(thisCube, YELLOW);
                makeCross(thisCube, countPoses);
                if (countPoses[0] == 0 || countPoses[1] == 0 || countPoses[2] == 0 || countPoses[3] == 0)
                {
                    rotateSideBy90(thisCube, YELLOW);
                    makeCross(thisCube, countPoses);
                }
            }
        }
    }
    //Тут должна быть рекурсия
    //Обычно поиск по повороту facePanel

    //3 поворота по 90 заменить визуально на 1 по -90
    //Проверка на то где находится 
}

char ifCorner(Cube* thisCube, color facePanel)
{
    switch (facePanel)
    {
    case RED:
        if (thisCube->redSide[4] == RED && thisCube->yellowSide[3] == GREEN && thisCube->greenSide[2] == WHITE)
        {
            return CORNERFACE;
        }
        else if (thisCube->redSide[4] == WHITE && thisCube->yellowSide[3] == RED && thisCube->greenSide[2] == GREEN)
        {
            return CORNERWHITE;
        }
        else if (thisCube->redSide[4] == GREEN && thisCube->yellowSide[3] == WHITE && thisCube->greenSide[2] == RED)
        {
            return CORNERPREV;
        }
        return 0;
        break;
    case BLUE:
        if (thisCube->blueSide[4] == BLUE && thisCube->yellowSide[1] == RED && thisCube->redSide[2] == WHITE)
        {
            return CORNERFACE;
        }
        else if (thisCube->blueSide[4] == WHITE && thisCube->yellowSide[1] == BLUE && thisCube->redSide[2] == RED)
        {
            return CORNERWHITE;
        }
        else if (thisCube->blueSide[4] == RED && thisCube->yellowSide[1] == WHITE && thisCube->redSide[2] == BLUE)
        {
            return CORNERPREV;
        }
        return 0;
        break;
    case ORANGE:
        if (thisCube->orangeSide[4] == ORANGE && thisCube->yellowSide[7] == BLUE && thisCube->blueSide[2] == WHITE)
        {
            return CORNERFACE;
        }
        else if (thisCube->orangeSide[4] == WHITE && thisCube->yellowSide[7] == ORANGE && thisCube->blueSide[2] == BLUE)
        {
            return CORNERWHITE;
        }
        else if (thisCube->orangeSide[4] == BLUE && thisCube->yellowSide[7] == WHITE && thisCube->blueSide[2] == ORANGE)
        {
            return CORNERPREV;
        }
        return 0;
        break;
    case GREEN:
        if (thisCube->greenSide[4] == GREEN && thisCube->yellowSide[5] == ORANGE && thisCube->blueSide[2] == WHITE)
        {
            return CORNERFACE;
        }
        else if (thisCube->greenSide[4] == WHITE && thisCube->yellowSide[5] == GREEN && thisCube->blueSide[2] == ORANGE)
        {
            return CORNERWHITE;
        }
        else if (thisCube->greenSide[4] == ORANGE && thisCube->yellowSide[5] == WHITE && thisCube->blueSide[2] == GREEN)
        {
            return CORNERPREV;
        }
        return 0;
        break;
    default:
        break;
    }
    return 0;
}

void solveCorner(Cube* thisCube, color facePanel, char type)
{
    color prev = getPrevPanel(facePanel);
    color next = getNextPanel(facePanel);
    
    switch (type)
    {
    case(CORNERFACE):
    {
        rotateSideBy90(thisCube, prev);
        rotateSideBy90(thisCube, YELLOW);
        rotateSideBy90Back(thisCube, prev);
    }
    case(CORNERPREV):
    {
        rotateSideBy90Back(thisCube, facePanel);
        rotateSideBy90Back(thisCube, next);
        rotateSideBy90(thisCube, YELLOW);
        rotateSideBy90(thisCube, YELLOW);
        rotateSideBy90(thisCube, next);
        rotateSideBy90(thisCube, facePanel);
    }
    case(CORNERWHITE):
    {
        rotateSideBy90Back(thisCube, facePanel);
        rotateSideBy90(thisCube, YELLOW);
        rotateSideBy90(thisCube, facePanel);
    }
    default:
        break;
    }
}

void searchForCorner(Cube* thisCube, char* corner1, char* corner2, char* corner3, char* corner4, color panel1, color panel2, color panel3, color panel4)
{
    if (!((*corner1) && (*corner2) && (*corner3) && (*corner4)))
    {
        rotateSideBy90(thisCube, YELLOW);
        (*corner1) = ifCorner(thisCube, panel1);
        (*corner2) = ifCorner(thisCube, panel2);
        (*corner3) = ifCorner(thisCube, panel3);
        (*corner4) = ifCorner(thisCube, panel4);
        if (!((*corner1) && (*corner2) && (*corner3) && (*corner4)))
        {
            rotateSideBy90(thisCube, YELLOW);
            (*corner1) = ifCorner(thisCube, panel1);
            (*corner2) = ifCorner(thisCube, panel2);
            (*corner3) = ifCorner(thisCube, panel3);
            (*corner4) = ifCorner(thisCube, panel4);
            if (!((*corner1) && (*corner2) && (*corner3) && (*corner4)))
            {
                rotateSideBy90(thisCube, YELLOW);
                (*corner1) = ifCorner(thisCube, panel1);
                (*corner2) = ifCorner(thisCube, panel2);
                (*corner3) = ifCorner(thisCube, panel3);
                (*corner4) = ifCorner(thisCube, panel4);
            }
        }
    }
}

void searchForCorner2(Cube* thisCube, char* corner1, char* corner2, char* corner3, color panel1, color panel2, color panel3)
{
    if (!((*corner1) && (*corner2) && (*corner3)))
    {
        rotateSideBy90(thisCube, YELLOW);
        (*corner1) = ifCorner(thisCube, panel1);
        (*corner2) = ifCorner(thisCube, panel2);
        (*corner3) = ifCorner(thisCube, panel3);
        if (!((*corner1) && (*corner2) && (*corner3)))
        {
            rotateSideBy90(thisCube, YELLOW);
            (*corner1) = ifCorner(thisCube, panel1);
            (*corner2) = ifCorner(thisCube, panel2);
            (*corner3) = ifCorner(thisCube, panel3);
            if (!((*corner1) && (*corner2) && (*corner3)))
            {
                rotateSideBy90(thisCube, YELLOW);
                (*corner1) = ifCorner(thisCube, panel1);
                (*corner2) = ifCorner(thisCube, panel2);
                (*corner3) = ifCorner(thisCube, panel3);
            }
        }
    }
}

void searchForCorner3(Cube* thisCube, char* corner1, char* corner2, color panel1, color panel2)
{
    if (!((*corner1) && (*corner2)))
    {
        rotateSideBy90(thisCube, YELLOW);
        (*corner1) = ifCorner(thisCube, panel1);
        (*corner2) = ifCorner(thisCube, panel2);
        if (!((*corner1) && (*corner2)))
        {
            rotateSideBy90(thisCube, YELLOW);
            (*corner1) = ifCorner(thisCube, panel1);
            (*corner2) = ifCorner(thisCube, panel2);
            if (!((*corner1) && (*corner2) ))
            {
                rotateSideBy90(thisCube, YELLOW);
                (*corner1) = ifCorner(thisCube, panel1);
                (*corner2) = ifCorner(thisCube, panel2);
            }
        }
    }
}

void secondStep(Cube* thisCube)
{
    char redcorner = ifCorner(thisCube, RED);
    char bluecorner = ifCorner(thisCube, BLUE);
    char orangecorner = ifCorner(thisCube, ORANGE);
    char greencorner = ifCorner(thisCube, GREEN);

    searchForCorner(thisCube, &redcorner, &bluecorner, &greencorner, &orangecorner, RED, BLUE, ORANGE, GREEN);
    
    if (redcorner)
    {
        solveCorner(thisCube, RED, redcorner);

        char bluecorner = ifCorner(thisCube, BLUE);
        char orangecorner = ifCorner(thisCube, ORANGE);
        char greencorner = ifCorner(thisCube, GREEN);
        searchForCorner2(thisCube, &bluecorner, &greencorner, &orangecorner, BLUE, GREEN, ORANGE);

        if (bluecorner)
        {
            solveCorner(thisCube, BLUE, bluecorner);

            char orangecorner = ifCorner(thisCube, ORANGE);
            char greencorner = ifCorner(thisCube, GREEN);
            searchForCorner3(thisCube, &orangecorner, &greencorner, ORANGE, GREEN);

            if (orangecorner)
            {
                solveCorner(thisCube, ORANGE, orangecorner);
                solveCorner(thisCube, GREEN, greencorner);
            }
            else if (greencorner)
            {
                solveCorner(thisCube, GREEN, greencorner);
                solveCorner(thisCube, ORANGE, orangecorner);
            }
        }
        else if (orangecorner)
        {
            solveCorner(thisCube, ORANGE, orangecorner);

            char bluecorner = ifCorner(thisCube, BLUE);
            char greencorner = ifCorner(thisCube, GREEN);
            searchForCorner3(thisCube, &bluecorner, &greencorner, BLUE, GREEN);

            if (bluecorner)
            {
                solveCorner(thisCube, BLUE, bluecorner);
                solveCorner(thisCube, GREEN, greencorner);
            }
            else if (greencorner)
            {
                solveCorner(thisCube, GREEN, greencorner);
                solveCorner(thisCube, BLUE, bluecorner);
            }
        }
        else if (greencorner)
        {
            solveCorner(thisCube, GREEN, greencorner);

            char bluecorner = ifCorner(thisCube, BLUE);
            char orangecorner = ifCorner(thisCube, ORANGE);
            searchForCorner3(thisCube, &orangecorner, &bluecorner, ORANGE, BLUE);

            if (orangecorner)
            {
                solveCorner(thisCube, ORANGE, orangecorner);
                solveCorner(thisCube, BLUE, bluecorner);
            }
            else if (bluecorner)
            {
                solveCorner(thisCube, BLUE, bluecorner);;
                solveCorner(thisCube, ORANGE, orangecorner);
            }
        }
    }
    else if (bluecorner)
    {
        char redcorner = ifCorner(thisCube, RED);
        char orangecorner = ifCorner(thisCube, ORANGE);
        char greencorner = ifCorner(thisCube, GREEN);
        searchForCorner2(thisCube, &redcorner, &greencorner, &orangecorner, RED, GREEN, ORANGE);

        if (redcorner)
        {
            solveCorner(thisCube, RED, redcorner);

            char orangecorner = ifCorner(thisCube, ORANGE);
            char greencorner = ifCorner(thisCube, GREEN);
            searchForCorner3(thisCube, &orangecorner, &greencorner, ORANGE, GREEN);

            if (orangecorner)
            {
                solveCorner(thisCube, ORANGE, orangecorner);
                solveCorner(thisCube, GREEN, greencorner);
            }
            else if (greencorner)
            {
                solveCorner(thisCube, GREEN, greencorner);
                solveCorner(thisCube, ORANGE, orangecorner);
            }
        }
        else if (orangecorner)
        {
            solveCorner(thisCube, ORANGE, orangecorner);

            char redcorner = ifCorner(thisCube, RED);
            char greencorner = ifCorner(thisCube, GREEN);
            searchForCorner3(thisCube, &redcorner, &greencorner, RED, GREEN);

            if (bluecorner)
            {
                solveCorner(thisCube, RED, redcorner);
                solveCorner(thisCube, GREEN, greencorner);
            }
            else if (greencorner)
            {
                solveCorner(thisCube, GREEN, greencorner);
                solveCorner(thisCube, RED, redcorner);
            }
        }
        else if (greencorner)
        {
            solveCorner(thisCube, GREEN, greencorner);

            char redcorner = ifCorner(thisCube, RED);
            char orangecorner = ifCorner(thisCube, ORANGE);
            searchForCorner3(thisCube, &redcorner, &orangecorner, RED, ORANGE);

            if (orangecorner)
            {
                solveCorner(thisCube, ORANGE, orangecorner);
                solveCorner(thisCube, RED, redcorner);
            }
            else if (redcorner)
            {
                solveCorner(thisCube, RED, redcorner);
                solveCorner(thisCube, ORANGE, orangecorner);
            }
        }
    }
    else if (orangecorner)
    {
        solveCorner(thisCube, ORANGE, orangecorner);

        char redcorner = ifCorner(thisCube, RED);
        char bluecorner = ifCorner(thisCube, BLUE);
        char greencorner = ifCorner(thisCube, GREEN);
        searchForCorner2(thisCube, &redcorner, &bluecorner, &greencorner, RED, BLUE, GREEN);

        if (bluecorner)
        {
            solveCorner(thisCube, BLUE, bluecorner);

            char redcorner = ifCorner(thisCube, RED);
            char greencorner = ifCorner(thisCube, GREEN);
            searchForCorner3(thisCube, &redcorner, &greencorner, RED, GREEN);

            if (redcorner)
            {
                solveCorner(thisCube, RED, redcorner);
                solveCorner(thisCube, GREEN, greencorner);
            }
            else if (greencorner)
            {
                solveCorner(thisCube, GREEN, greencorner);
                solveCorner(thisCube, RED, redcorner);
            }
        }
        else if (redcorner)
        {
            solveCorner(thisCube, RED, redcorner);

            char bluecorner = ifCorner(thisCube, BLUE);
            char greencorner = ifCorner(thisCube, GREEN);
            searchForCorner3(thisCube, &bluecorner, &greencorner, BLUE, GREEN);

            if (bluecorner)
            {
                solveCorner(thisCube, BLUE, bluecorner);
                solveCorner(thisCube, GREEN, greencorner);
            }
            else if (greencorner)
            {
                solveCorner(thisCube, GREEN, greencorner);
                solveCorner(thisCube, BLUE, bluecorner);
            }
        }
        else if (greencorner)
        {
            solveCorner(thisCube, GREEN, greencorner);

            char bluecorner = ifCorner(thisCube, BLUE);
            char redcorner = ifCorner(thisCube, RED);
            searchForCorner3(thisCube, &bluecorner, &redcorner, BLUE, RED);

            if (redcorner)
            {
                solveCorner(thisCube, RED, redcorner);
                solveCorner(thisCube, BLUE, bluecorner);
            }
            else if (bluecorner)
            {
                solveCorner(thisCube, BLUE, bluecorner);
                solveCorner(thisCube, RED, redcorner);
            }
        }
    }
    else if (greencorner)
    {
        solveCorner(thisCube, GREEN, greencorner);

        char redcorner = ifCorner(thisCube, RED);
        char bluecorner = ifCorner(thisCube, BLUE);
        char orangecorner = ifCorner(thisCube, ORANGE);
        searchForCorner2(thisCube, &redcorner, &bluecorner, &orangecorner, RED, BLUE, ORANGE);

        if (bluecorner)
        {
            solveCorner(thisCube, BLUE, bluecorner);

            char redcorner = ifCorner(thisCube, RED);
            char orangecorner = ifCorner(thisCube, ORANGE);
            searchForCorner3(thisCube, &orangecorner, &redcorner, ORANGE, RED);

            if (redcorner)
            {
                solveCorner(thisCube, RED, redcorner);
                solveCorner(thisCube, ORANGE, orangecorner);
            }
            else if (orangecorner)
            {
                solveCorner(thisCube, ORANGE, orangecorner);
                solveCorner(thisCube, RED, redcorner);
            }
        }
        else if (redcorner)
        {
            solveCorner(thisCube, RED, redcorner);

            char bluecorner = ifCorner(thisCube, BLUE);
            char orangecorner = ifCorner(thisCube, ORANGE);
            searchForCorner3(thisCube, &orangecorner, &bluecorner, ORANGE, BLUE);

            if (bluecorner)
            {
                solveCorner(thisCube, BLUE, bluecorner);
                solveCorner(thisCube, ORANGE, orangecorner);
            }
            else if (redcorner)
            {
                solveCorner(thisCube, ORANGE, orangecorner);
                solveCorner(thisCube, BLUE, bluecorner);
            }
        }
        else if (orangecorner)
        {
            solveCorner(thisCube, ORANGE, orangecorner);

            char bluecorner = ifCorner(thisCube, BLUE);
            char redcorner = ifCorner(thisCube, RED);
            searchForCorner3(thisCube, &redcorner, &bluecorner, RED, BLUE);

            if (redcorner)
            {
                solveCorner(thisCube, RED, redcorner);
                solveCorner(thisCube, BLUE, bluecorner);
            }
            else if (bluecorner)
            {
                solveCorner(thisCube, BLUE, bluecorner);
                solveCorner(thisCube, RED, redcorner);
            }
        }
    }

    //добавить опускатель угла вниз
}

void thirdStep(Cube* thisCube)
{

}

void fourthStep(Cube* thisCube)
{

}

void fifthStep(Cube* thisCuve)
{

}
