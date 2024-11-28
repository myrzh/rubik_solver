#ifndef RUBIK_SOLVER_H
#define RUBIK_SOLVER_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#include <sfd.h>
#endif

#define GLT_IMPLEMENTATION
#include <gltext.h>

typedef enum { MAINWND, FLATWND, AUTHORSWND } windowType;

typedef enum { RIGHT, LEFT, TOP } cubeSide;

#include <stdio.h>
#include <cube.h>
#include <algo.h>

windowType currentWindow;

Button mainButtons[20];
Button flatButtons[20];

LinearCube Cube2D;
LinearCube flatCube;
Cube Cube3D;
Cube tempCube3D;

FILE *inputSteps;
action stepsFromFile[1000];
int actionsInFile;
int currentStep;

char currentStepText[20];

int isCubeFilled;
int currentFlatCubeIndex;

unsigned int compileShader(unsigned int type, const char *source);

unsigned int createShaderProgram(const char *vertexSource,
                                 const char *fragmentSource);

void fillStepsFromFile(char filename[]);

void executeStep();

void fillCubeFromFile(char filename[]);

void updateFlatCube(color currentColor, int isFirstCall);

void fillCubeFromUserInput(GLFWwindow *window);

#endif
