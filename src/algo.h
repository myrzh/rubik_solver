#ifndef ALGO_H
#define ALGO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HORIZONTALUP 1
#define VERTICALUP 3
#define HORIZONTALDOWN -1
#define VERTICALDOWN -3
#define LASTOP -1
#define LENARR 500
#define TABLESIZE 16777216
#define SMALLSTEPSCOUNT 19

typedef struct Cube {
    char front[3][3];
    char back[3][3];
    char left[3][3];
    char right[3][3];
    char up[3][3];
    char down[3][3];
    char operation;
    struct Cube* previousState;
} Cube;

typedef struct {
    int shift;
    char* line;
} CubeLine;

typedef struct {
    int openCubes;
    int closedCubes;
    int size;
    Cube* cubes;
} SolutionTable;

typedef enum
{
    FRONTROTATE, BACKROTATE, UPROTATE, DOWNROTATE, LEFTROTATE, RIGHTROTATE
} rotationType;

typedef struct {
    char op;
    char count;
} OperationPrint;

enum
{
    FIRSTSTEP1, FIRSTSTEP2, SECONDSTEP, THIRDSTEP, FOURTHSTEP, FIFTHSTEP, SIXTHSTEP, SEVENTHSTEP
};

void initCube(Cube* thisCube)
{
    memset(thisCube->front, 'w', sizeof(thisCube->front));
    memset(thisCube->back, 'y', sizeof(thisCube->back));
    memset(thisCube->up, 'b', sizeof(thisCube->left));
    memset(thisCube->down, 'g', sizeof(thisCube->right));
    memset(thisCube->left, 'o', sizeof(thisCube->up));
    memset(thisCube->right, 'r', sizeof(thisCube->down));
}

void rotateSideBy90(char panel[3][3])
{
    char tempPanel[3][3] = { '\0' };
    memcpy(tempPanel, panel, sizeof(tempPanel));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            panel[i][j] = tempPanel[3 - j - 1][i];
        }
    }
}

void rotateOtherSides(CubeLine sides[5])
{
    int destinantionIndex = 0;
    int sourceIndex = 0;
    int destinationShift = 0;
    int sourceShift = 0;
    char* destinationBuf = NULL;
    char* sourceBuf = NULL;
    
    for (int i = 0; i < 5; i++)
    {
        destinantionIndex = i;
        sourceIndex = i + 1;
        if (sourceIndex >= 5)
        {
            sourceIndex = 0;
        }

        destinationBuf = sides[destinantionIndex].line;
        sourceBuf = sides[sourceIndex].line;

        destinationShift = sides[destinantionIndex].shift;
        sourceShift = sides[sourceIndex].shift;

        for (int j = 0; j < 3; j++)
        {
            *destinationBuf = *sourceBuf;
            destinationBuf += destinationShift;
            sourceBuf += sourceShift;
        }
    }
}

void cubeFrontRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->left[0][2]);
    sides[2].shift = HORIZONTALUP;
    sides[2].line = &(thisCube->down[0][0]);
    sides[3].shift = VERTICALDOWN;
    sides[3].line = &(thisCube->right[2][0]);
    sides[4].shift = HORIZONTALDOWN;
    sides[4].line = &(thisCube->up[2][2]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->front);
};

void cubeBackRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->right[0][2]);
    sides[2].shift = HORIZONTALDOWN;
    sides[2].line = &(thisCube->down[2][2]);
    sides[3].shift = VERTICALDOWN;
    sides[3].line = &(thisCube->left[2][0]);
    sides[4].shift = HORIZONTALUP;
    sides[4].line = &(thisCube->up[0][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->back);
};

void cubeUpRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = HORIZONTALUP;
    sides[1].line = &(thisCube->left[0][0]);
    sides[2].shift = HORIZONTALUP;
    sides[2].line = &(thisCube->front[0][0]);
    sides[3].shift = HORIZONTALUP;
    sides[3].line = &(thisCube->right[0][0]);
    sides[4].shift = HORIZONTALUP;
    sides[4].line = &(thisCube->back[0][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->up);
};

void cubeDownRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = HORIZONTALUP;
    sides[1].line = &(thisCube->back[2][0]);
    sides[2].shift = HORIZONTALUP;
    sides[2].line = &(thisCube->right[2][0]);
    sides[3].shift = HORIZONTALUP;
    sides[3].line = &(thisCube->front[2][0]);
    sides[4].shift = HORIZONTALUP;
    sides[4].line = &(thisCube->left[2][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->down);
};

void cubeLeftRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->down[0][0]);
    sides[2].shift = VERTICALUP;
    sides[2].line = &(thisCube->front[0][0]);
    sides[3].shift = VERTICALUP;
    sides[3].line = &(thisCube->up[0][0]);
    sides[4].shift = VERTICALDOWN;
    sides[4].line = &(thisCube->back[2][2]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->left);
};

void cubeRightRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->up[0][2]);
    sides[2].shift = VERTICALUP;
    sides[2].line = &(thisCube->front[0][2]);
    sides[3].shift = VERTICALUP;
    sides[3].line = &(thisCube->down[0][2]);
    sides[4].shift = VERTICALDOWN;
    sides[4].line = &(thisCube->back[2][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->right);
};

void cubeDoOp(Cube* thisCube, int op)
{
    switch (op)
    {
    case FRONTROTATE: 
        cubeFrontRotate(thisCube);
        break;
    case BACKROTATE:
        cubeBackRotate(thisCube);
        break;
    case LEFTROTATE:
        cubeLeftRotate(thisCube);
        break;
    case RIGHTROTATE:
        cubeRightRotate(thisCube);
        break;
    case UPROTATE:
        cubeUpRotate(thisCube);
        break;
    case DOWNROTATE:
        cubeDownRotate(thisCube);
        break;
    default:
        break;
    }
}

void randCube(Cube* thisCube, int n)
{
    while (n > 0)
    {
        cubeDoOp(thisCube, rand() % 6);
        n--;
    }
}

int checkIfCrossFront(Cube* thisCube)
{
    int count = 0;
    if (thisCube->front[1][1] == thisCube->front[0][1])
    {
        count++;
    }
    if (thisCube->front[1][1] == thisCube->front[1][0])
    {
        count++;
    }
    if (thisCube->front[1][1] == thisCube->front[1][2])
    {
        count++;
    }
    if (thisCube->front[1][1] == thisCube->front[2][1])
    {
        count++;
    }

    return count;
}

int checkIfCrossSides(Cube* thisCube)
{
    int count = 0;
    if (thisCube->left[1][1] == thisCube->left[1][2])
    {
        count++;
    }
    if (thisCube->up[1][1] == thisCube->up[2][1])
    {
        count++;
    }
    if (thisCube->right[1][1] == thisCube->right[1][0])
    {
        count++;
    }
    if (thisCube->down[1][1] == thisCube->down[0][1])
    {
        count++;
    }

    return count;
}

int checkIfCornersFront(Cube* thisCube)
{
    int count = 0;
    int ifcorrect = 0;

    if (thisCube->front[1][1] == thisCube->front[0][0])
    {
        ifcorrect++;
    }
    if(thisCube->left[1][1] == thisCube->left[0][2])
    {
        ifcorrect++;
    }
    if (thisCube->up[1][1] == thisCube->up[2][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->front[1][1] == thisCube->front[0][2])
    {
        ifcorrect++;
    }
    if (thisCube->up[1][1] == thisCube->up[2][2])
    {
        ifcorrect++;
    }
    if (thisCube->right[1][1] == thisCube->right[0][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->front[1][1] == thisCube->front[2][0])
    {
        ifcorrect++;
    }
    if (thisCube->left[1][1] == thisCube->left[2][2])
    {
        ifcorrect++;
    }
    if (thisCube->down[1][1] == thisCube->down[0][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->front[1][1] == thisCube->front[2][2])
    {
        ifcorrect++;
    }
    if (thisCube->right[1][1] == thisCube->right[2][0])
    {
        ifcorrect++;
    }
    if (thisCube->down[1][1] == thisCube->down[0][2])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }

    return count;
}

int checkIfFrontRow(Cube* thisCube)
{
    int count = 0;
    int ifcorrect = 0;

    if (thisCube->left[1][1] == thisCube->left[0][1])
    {
        ifcorrect++;
    }
    if (thisCube->up[1][1] == thisCube->up[1][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->up[1][1] == thisCube->up[1][2])
    {
        ifcorrect++;
    }
    if (thisCube->right[1][1] == thisCube->right[0][1])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->left[1][1] == thisCube->left[2][1])
    {
        ifcorrect++;
    }
    if (thisCube->down[1][1] == thisCube->down[1][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->right[1][1] == thisCube->right[2][1])
    {
        ifcorrect++;
    }
    if (thisCube->down[1][1] == thisCube->down[1][2])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }

    return count;
}

int checkIfBackCross(Cube* thiscube)
{
    int count = 0;

    if (thiscube->back[1][1] == thiscube->back[0][1] && thiscube->back[1][1] == thiscube->back[2][1])
    {
        count+=2;
    }

    if (thiscube->back[1][1] == thiscube->back[1][0] && thiscube->back[1][1] == thiscube->back[1][2])
    {
        count+=2;
    }
    return count;
}

int checkIfBackSide(Cube* thisCube)
{
    int count = 0;

    if (thisCube->back[1][1] == thisCube->back[0][0])
    {
        count++;
    }
    if (thisCube->back[1][1] == thisCube->back[0][2])
    {
        count++;
    }
    if (thisCube->back[1][1] == thisCube->back[2][0])
    {
        count++;
    }
    if (thisCube->back[1][1] == thisCube->back[2][2])
    {
        count++;
    }

    if (count == 2)
    {
        return 0;
    }

    return count;
}

int checkIfBackCorners(Cube* thisCube)
{
    int count = 0;
    int ifcorrect = 0;
    char flag = 0;
    int corners[4] = { 1, 1, 1, 1};

    if (thisCube->back[1][1] == thisCube->back[0][2])
    {
        ifcorrect++;
    }
    if (thisCube->left[1][1] == thisCube->left[0][0])
    {
        ifcorrect++;
    }
    if (thisCube->up[1][1] == thisCube->up[0][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }
    else 
    {
        corners[0] = 0;
    }

    ifcorrect = 0;
    if (thisCube->back[1][1] == thisCube->back[0][0])
    {
        ifcorrect++;
    }
    if (thisCube->up[1][1] == thisCube->up[0][2])
    {
        ifcorrect++;
    }
    if (thisCube->right[1][1] == thisCube->right[0][2])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }
    else
    {
        corners[1] = 0;
    }

    ifcorrect = 0;
    if (thisCube->back[1][1] == thisCube->back[2][0])
    {
        ifcorrect++;
    }
    if (thisCube->right[1][1] == thisCube->right[2][2])
    {
        ifcorrect++;
    }
    if (thisCube->down[1][1] == thisCube->down[2][2])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }
    else
    {
        corners[2] = 0;
    }

    ifcorrect = 0;
    if (thisCube->back[1][1] == thisCube->back[2][2])
    {
        ifcorrect++;
    }
    if (thisCube->left[1][1] == thisCube->left[2][0])
    {
        ifcorrect++;
    }
    if (thisCube->down[1][1] == thisCube->down[2][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 3)
    {
        count++;
    }
    else
    {
        corners[3] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        if (corners[i] && corners[(i + 1) % 4])
        {
            flag = 1;
        }
    }

    if (flag)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

int checkIfBackRow(Cube* thisCube)
{
    int count = 0;
    int ifcorrect = 0;

    if (thisCube->up[1][1] == thisCube->up[0][1])
    {
        ifcorrect++;
    }
    if (thisCube->back[1][1] == thisCube->back[0][1])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }

    ifcorrect = 0;
    if (thisCube->down[1][1] == thisCube->down[2][1])
    {
        ifcorrect++;
    }
    if (thisCube->back[1][1] == thisCube->back[2][1])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }
 
    ifcorrect = 0;
    if (thisCube->left[1][1] == thisCube->left[1][0])
    {
        ifcorrect++;
    }
    if (thisCube->back[1][1] == thisCube->back[1][2])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }
 
    ifcorrect = 0;
    if (thisCube->right[1][1] == thisCube->right[1][2])
    {
        ifcorrect++;
    }
    if (thisCube->back[1][1] == thisCube->back[1][0])
    {
        ifcorrect++;
    }
    if (ifcorrect == 2)
    {
        count++;
    }

    return count;
}

int doCheck(Cube* thisCube, int op)
{
    switch (op)
    {
    case FIRSTSTEP1:
        return checkIfCrossFront(thisCube);
        break;
    case FIRSTSTEP2:
        return checkIfCrossSides(thisCube);
        break;
    case SECONDSTEP:
        return checkIfCornersFront(thisCube);
        break;
    case THIRDSTEP:
        return checkIfFrontRow(thisCube);
        break;
    case FOURTHSTEP:
        return checkIfBackCross(thisCube);
        break;
    case FIFTHSTEP:
        return checkIfBackSide(thisCube);
        break;
    case SIXTHSTEP:
        return checkIfBackCorners(thisCube);
        break;
    case SEVENTHSTEP:
        return checkIfBackRow(thisCube);
        break;
    default:
        return -1;
        break;
    }
}

int checkAllCube(Cube* thisCube, int flag)
{
    int checksum = 0;
    int cursum = 0;

    for (int i = 0; i<8; i++)
    {
        if (flag)
        {
            checksum += doCheck(thisCube, i);
            cursum += 4;
            if (cursum >= flag)
            {
                break;
            }
        }
        else
        {
            cursum = doCheck(thisCube, i);
            checksum += cursum;
            if (cursum != 4)
            {
                break;
            }
        }
    }
    return checksum;
}

void createTable(SolutionTable* table, int size)
{
    table->size = size;
    table->cubes = (Cube*)malloc(size * sizeof(Cube));
    if (table->cubes == NULL)
    {
        exit(1);
    }
}

// void deleteTable(SolutionTable* table)
// {
//     free(table->cubes);
//     table->cubes = NULL;
// }

void deleteTable(SolutionTable* table)
{
    for (int i = 0; i < table->size; i++)
    {
        free(table->cubes[i].previousState);
        table->cubes[i].previousState = NULL;
    }

    free(table->cubes);
    table->cubes = NULL;
}

int checkIfSameOps(Cube* thisCube)
{
    int curop = thisCube->operation;
    int count = 0;

    while (thisCube != NULL)
    {
        if (thisCube->operation == curop)
        {
            count++;
            if (count == 4)
            {
                return 1;
            }
            thisCube = thisCube->previousState;
        }
        else
        {
            break;
        }
    }
    return 0;
}

int cutTheWay(int newvalue, int cutvalue)
{
    if (newvalue < cutvalue)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Cube* search(SolutionTable* table, Cube* startCube, int state, char* operlist, int opernum, int cutvalue)
{
    Cube* newcube = NULL;
    Cube* currcube = NULL;
    int newstate = 0;
    int newvalue = 0;
    
    startCube->previousState = NULL;
    startCube->operation = LASTOP;

    if (checkAllCube(startCube, 0) >= state)
    {
        return startCube;
    }

    table->openCubes = 0;
    table->closedCubes = 0;

    table->cubes[table->openCubes] = *startCube;
    table->openCubes++;

    while (table->closedCubes < table->openCubes)
    {
        if (table->openCubes + 6 >= table->size - 1)
        {
            //all memory was used
            break;
        }

        currcube = &(table->cubes[table->closedCubes++]);

        for (int i = 0; i < opernum; i++)
        {
            newcube = &(table->cubes[table->openCubes]);
            memcpy(newcube, currcube, sizeof(Cube));
            cubeDoOp(newcube, operlist[i]);

            newcube->operation = operlist[i];
            newcube->previousState = currcube;

            newstate = checkAllCube(newcube, 0);
            newvalue = checkAllCube(newcube, state);
            if (newstate >= state)
            {
                return newcube;
            }
            if (cutTheWay(newvalue, cutvalue) || checkIfSameOps(newcube))
            {
                continue;
            }
            table->openCubes++;
        }
    }
    return NULL;
}

void setOpToChar(OperationPrint* ops, int countops, char lastop)
{
    if (lastop == FRONTROTATE)
    {
        ops[countops].op = 'F';
    }
    else if (lastop == BACKROTATE)
    {
        ops[countops].op = 'B';
    }
    else if (lastop == UPROTATE)
    {
        ops[countops].op = 'U';
    }
    else if (lastop == DOWNROTATE)
    {
        ops[countops].op = 'D';
    }
    else if (lastop == LEFTROTATE)
    {
        ops[countops].op = 'L';
    }
    else if (lastop == RIGHTROTATE)
    {
        ops[countops].op = 'R';
    }
}

void setCountToChar(OperationPrint* ops, int countops, char rotatecounts)
{
    if (rotatecounts == 0)
    {
        ops[countops].count = '\0';
    }
    else if (rotatecounts == 1)
    {
        ops[countops].count = '2';
    }
    else if (rotatecounts == 2)
    {
        ops[countops].count = '\'';
    }
}

void printOpToFile(Cube* thisCube, FILE* foutput)
{
    OperationPrint ops[1000];

    int countops = 0;
    char lastop = LASTOP;
    char rotatecounts = 0;
    int j = 0;

    while (thisCube)
    {
        if (thisCube->operation >= 0)
        {
            if (lastop != thisCube->operation)
            {
                if (lastop != LASTOP)
                {
                    setOpToChar(&ops, countops, lastop);
                    setCountToChar(&ops, countops, rotatecounts);
                    countops++;
                }
                lastop = thisCube->operation;
                rotatecounts = 0;
            }
            else
            {
                rotatecounts++;
            }
        }
        else
        {
            if (lastop != LASTOP)
            {
                setOpToChar(&ops, countops, lastop);
                setCountToChar(&ops, countops, rotatecounts);
                countops++;
            }
        }
        thisCube = thisCube->previousState;
    }
    while (countops > 0)
    {
        countops--;
        fputc(ops[countops].op, foutput);
        if (ops[countops].count != 0)
        {
            fputc(ops[countops].count, foutput);
        }
        fputs("\n", foutput);
    }
}

void cubeSolve(Cube* thisCube, FILE* foutput, char filename[])
{
    if (foutput == NULL) {
        return;
    }
    SolutionTable table;

    createTable(&table, TABLESIZE);
    char operationsfirstseps[6] = { FRONTROTATE, UPROTATE, DOWNROTATE, LEFTROTATE, RIGHTROTATE };
    char operatoinssecondsteps[6] = { UPROTATE, DOWNROTATE, LEFTROTATE, RIGHTROTATE, BACKROTATE };
    char operationslastspets[4] = { BACKROTATE, RIGHTROTATE, UPROTATE };

    char* opeartionsarray[3] = { operationsfirstseps, operatoinssecondsteps, operationslastspets };

    int parametrs[][4] = {
        { 2 , 0, 5, 0 }, //начало белого креста1
        { 4 , 0, 5, 2 }, //конец белого креста1
        { 8 , 0, 5, 2 }, //начало и конец белого креста2
        { 9 , 0, 5, 3 }, //начало сборки верхнего слоя
        { 10, 0, 5, 4 }, //
        { 11, 0, 5, 5 }, //
        { 12, 0, 5, 5 }, //конец сборки верхнего слоя
        { 13, 1, 5, 6 }, //начало сборки среднего ряда
        { 14, 1, 5, 6 }, //
        { 15, 1, 5, 7 }, //
        { 16, 1, 5, 8 }, //конец сборки среднего ряда
        { 18, 1, 5, 10}, //начало сборки желтого креста
        { 20, 1, 5, 11}, //конец сборки желтого креста
        { 21, 1, 5, 11}, //начало сборки желтого креста
        { 24, 1, 5, 11}, //конец сборки желтого креста
        { 26, 2, 3, 12}, //начало сборки всей желтой стороны
        { 28, 2, 3, 12}, //конец сборки всей желтой стороны
        { 32, 2, 2, 12}, //начало и конец сборки нижнего слоя
        { 0 , 0, 0, 0 }
    };

    Cube* startCube = thisCube;
    Cube* find = NULL;

    for (int i = 0; i < SMALLSTEPSCOUNT; i++)
    {
        find = search(&table, startCube, parametrs[i][0], opeartionsarray[parametrs[i][1]], parametrs[i][2], parametrs[i][3]);
        if (find)
        {
            if (find != startCube)
            {
                startCube = find;
                *thisCube = *find;
                printOpToFile(find, foutput);
            }
        }
        else
        {
            // FILE* foutput = fopen("ops.txt", "w");
            freopen(filename, "w", foutput);
            fputc('_', foutput);
            //Couldn't find
            deleteTable(&table);
            // fclose(foutput);
            break;
        }
    }
}

void testInit(Cube* c)
{
    char str[256];

    //printf("please input F surface of cube:\n");
    (void)scanf(" %c %c %c %c %c %c %c %c %c",
        &(c->front[0][0]), &(c->front[0][1]), &(c->front[0][2]),
        &(c->front[1][0]), &(c->front[1][1]), &(c->front[1][2]),
        &(c->front[2][0]), &(c->front[2][1]), &(c->front[2][2]));
    fgets(str, sizeof(str), stdin);

    //printf("please input U surface of cube:\n");
    (void)scanf(" %c %c %c %c %c %c %c %c %c",
        &(c->up[0][0]), &(c->up[0][1]), &(c->up[0][2]),
        &(c->up[1][0]), &(c->up[1][1]), &(c->up[1][2]),
        &(c->up[2][0]), &(c->up[2][1]), &(c->up[2][2]));
    fgets(str, sizeof(str), stdin);

    //printf("please input D surface of cube:\n");
    (void)scanf(" %c %c %c %c %c %c %c %c %c",
        &(c->down[0][0]), &(c->down[0][1]), &(c->down[0][2]),
        &(c->down[1][0]), &(c->down[1][1]), &(c->down[1][2]),
        &(c->down[2][0]), &(c->down[2][1]), &(c->down[2][2]));
    fgets(str, sizeof(str), stdin);

    //printf("please input L surface of cube:\n");
    (void)scanf(" %c %c %c %c %c %c %c %c %c",
        &(c->left[0][0]), &(c->left[0][1]), &(c->left[0][2]),
        &(c->left[1][0]), &(c->left[1][1]), &(c->left[1][2]),
        &(c->left[2][0]), &(c->left[2][1]), &(c->left[2][2]));
    fgets(str, sizeof(str), stdin);

    //printf("please input R surface of cube:\n");
    (void)scanf(" %c %c %c %c %c %c %c %c %c",
        &(c->right[0][0]), &(c->right[0][1]), &(c->right[0][2]),
        &(c->right[1][0]), &(c->right[1][1]), &(c->right[1][2]),
        &(c->right[2][0]), &(c->right[2][1]), &(c->right[2][2]));
    fgets(str, sizeof(str), stdin);

    //printf("please input B surface of cube:\n");
    (void)scanf(" %c %c %c %c %c %c %c %c %c",
        &(c->back[0][0]), &(c->back[0][1]), &(c->back[0][2]),
        &(c->back[1][0]), &(c->back[1][1]), &(c->back[1][2]),
        &(c->back[2][0]), &(c->back[2][1]), &(c->back[2][2]));
    fgets(str, sizeof(str), stdin);
}

// int main()
// {
//     FILE* foutput = fopen("solution.txt", "w");
//     Cube c;
//     initCube(&c);
//     randCube(&c, 52);
//     cubeSolve(&c, foutput);

//     fclose(foutput);

//     return 0;
// }

#endif
