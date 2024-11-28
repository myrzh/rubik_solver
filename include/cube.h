#ifndef CUBE_H
#define CUBE_H
#include <colors.h>
#include <stdio.h>

#define CORNERFACE 1
#define CORNERWHITE 2
#define CORNERPREV 3

typedef enum { R, _R, G, _G, B, _B, W, _W, O, _O, Y, _Y } action;

typedef enum { STRAIGHT, BACK } rotationMode;

typedef enum { LEVEL_ONE, LEVEL_TWO, LEVEL_THREE } flatCubeLevel;

typedef struct {
    int index;
    color sideColor;
} IndexAndSide;

typedef struct {
    color whiteSide[9];
    color yellowSide[9];
    color redSide[9];
    color blueSide[9];
    color greenSide[9];
    color orangeSide[9];
} LinearCube;

IndexAndSide getIndexAndSideFromNumber(int absoluteIndex);
action getActionFromChar(char letter);
void getTextFromAction(char text[], action act);
void swap(color *x, color *y);
void initLinearCube(LinearCube *thisCube);
void initFlatCube(LinearCube *thisCube);
int isLinearCubeCorrect(LinearCube *thisCube);
#endif
