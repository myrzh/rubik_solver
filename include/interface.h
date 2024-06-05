#ifndef INTERFACE_H
#define INTERFACE_H
#include <algo.h>
#include <cube.h>
rotationType getRotationFromColor(color clr);
void linearToMatrixCube(Cube *dst, LinearCube *src);
void matrixToLinearCube(LinearCube *dst, Cube *src);
#endif