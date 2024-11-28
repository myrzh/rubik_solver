#ifndef DRAW_H
#define DRAW_H

#include <colors.h>
#include <objects.h>
#include <rubik_solver.h>
#include <stdio.h>
#include <string.h>

void drawStrokeLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

void drawStroke(GLfloat x, GLfloat y, cubeSide sideToDraw);

void drawSquare(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b,
                cubeSide sideToDraw);

void drawSide(cubeSide sideToDraw, color sideColors[]);

void drawButton(GLfloat x, GLfloat y, GLfloat width, GLfloat height,
                color colorName);

void drawUI();

void drawFlatWindowUI();

void drawFlatSquare(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);

void drawFlatSide(GLfloat x, GLfloat y, color sideToDraw, color sideColors[]);

#endif
