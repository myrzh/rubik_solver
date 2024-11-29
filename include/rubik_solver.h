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

typedef struct {
    GLuint VBO_button;
    GLuint VAO_button;
    GLuint VBO_stroke;
    GLuint VAO_stroke;

    // flat square or 3D square, depending on the window
    GLuint VBO_square;
    GLuint VAO_square;
} windowData;

#include <algo.h>
#include <cube.h>
#include <stdio.h>

extern windowType currentWindow;

extern windowData mainWndData;
extern windowData flatWndData;

extern Button mainButtons[20];
extern Button flatButtons[20];

extern LinearCube Cube2D;
extern LinearCube flatCube;
extern Cube Cube3D;
extern Cube tempCube3D;

extern FILE *inputSteps;
extern action stepsFromFile[1000];
extern int actionsInFile;
extern int currentStep;

extern char currentStepText[20];

extern int isCubeFilled;
extern int currentFlatCubeIndex;

unsigned int compileShader(unsigned int type, const char *source);

unsigned int createShaderProgram(const char *vertexSource,
                                 const char *fragmentSource);

void fillStepsFromFile(char filename[]);

void executeStep();

void fillCubeFromFile(char filename[]);

void updateFlatCube(color currentColor, int isFirstCall);

void fillCubeFromUserInput(GLFWwindow *window);

#endif
