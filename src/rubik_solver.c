#include <algo.h>
#include <colors.h>
#include <ctype.h>
#include <cube.h>
#include <draw.h>
#include <interface.h>
#include <math.h>
#include <objects.h>
#include <rubik_solver.h>
#include <shaders.h>
#include <stdlib.h>
#include <string.h>
#include <window.h>

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

unsigned int compileShader(unsigned int type, const char *source) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // Error handling
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }

    return id;
}

unsigned int createShaderProgram(const char *vertexSource,
                                 const char *fragmentSource) {
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Error handling
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void fillStepsFromFile(char filename[]) {
    inputSteps = fopen(filename, "r");
    // printf("'%s\n'", filename);
    if (inputSteps == NULL) {
        printf("can't open steps file!\n");
        return;
    }
    currentStep = 0;
    printf("steps file opened!\n");
    strcpy(currentStepText, "STEPS LOADED");

    char line[256];

    memset(stepsFromFile, 0, sizeof(stepsFromFile));
    actionsInFile = 0;

    int actionIndex;
    int isReverse;
    action currentAction;
    int currentActionCount;

    while (fgets(line, sizeof(line), inputSteps) != NULL) {
        if (line[0] == '_') {
            strcpy(currentStepText, "UNSOLVEABLE");
            break;
        }
        isReverse = 0;
        currentActionCount = 1;
        if (line[1] == '\'') {
            isReverse = 1;
        }

        currentAction = getActionFromChar(line[0]);

        if (isReverse) {
            currentAction++;
        }
        if (isdigit(line[1])) {
            currentActionCount = line[1] - '0';
        }

        for (int i = 0; i < currentActionCount; i++) {
            stepsFromFile[actionsInFile++] = currentAction;
        }
    }

    fclose(inputSteps);

    // for (int i = 0; i < actionsInFile; i++) {
    //     printf("%d\n", stepsFromFile[i]);
    // }
}

void executeStep() {
    if (currentStep + 1 > actionsInFile) {
        // printf("no steps to execute!\n");
        strcpy(currentStepText, "FILE IS OVER");
        return;
    }
    action currentAction = stepsFromFile[currentStep++];

    getTextFromAction(currentStepText, currentAction);

    int n = 1;
    color sideColorToRotate;

    if (currentAction % 2 == 0) {
        sideColorToRotate = (color)(currentAction / 2);
        // rotateLinearSideBy90(&Cube2D, (color)(currentAction / 2), STRAIGHT);
    } else {
        sideColorToRotate = (color)((currentAction - 1) / 2);
        n += 2;
        // rotateLinearSideBy90(&Cube2D, (color)((currentAction - 1) / 2),
        // BACK);
    }

    for (int i = 0; i < n; i++) {
        cubeDoOp(&Cube3D, getRotationFromColor(sideColorToRotate));
        matrixToLinearCube(&Cube2D, &Cube3D);
    }
}

void fillCubeFromFile(char filename[]) {
    FILE *inputCube = fopen(filename, "r");
    if (inputCube == NULL) {
        printf("can't open cube file!\n");
        return;
    }
    printf("cube file opened!\n");

    char line[256];

    int currentLineNumber = 1;

    color currentColor;

    LinearCube tempCube2D;

    while (fgets(line, sizeof(line), inputCube) != NULL) {
        for (int i = 0; i < 9; i++) {
            currentColor = getColorFromChar(line[i]);
            // printf("%c", line[i]);
            switch (currentLineNumber) {
                case 1:
                    tempCube2D.blueSide[flatBlueSideOrder[i]] = currentColor;
                    break;
                case 2:
                    tempCube2D.orangeSide[flatOrangeSideOrder[i]] =
                        currentColor;
                    break;
                case 3:
                    tempCube2D.whiteSide[flatWhiteSideOrder[i]] = currentColor;
                    break;
                case 4:
                    tempCube2D.redSide[flatRedSideOrder[i]] = currentColor;
                    break;
                case 5:
                    tempCube2D.yellowSide[flatYellowSideOrder[i]] =
                        currentColor;
                    break;
                case 6:
                    tempCube2D.greenSide[flatGreenSideOrder[i]] = currentColor;
                    break;
                default:
                    break;
            }
        }
        currentLineNumber++;
    }
    fclose(inputCube);

    if (isLinearCubeCorrect(&tempCube2D) == 1) {
        Cube2D = tempCube2D;
        linearToMatrixCube(&Cube3D, &Cube2D);
        isCubeFilled = 1;
        strcpy(currentStepText, "CUBE LOADED");
    }
}

void updateFlatCube(color currentColor, int isFirstCall) {
    currentFlatCubeIndex++;
    int needToJump = 0;

    IndexAndSide iterationSquare =
        getIndexAndSideFromNumber(currentFlatCubeIndex);
    if (currentFlatCubeIndex <= 53) {
        if (iterationSquare.index == 8) {
            iterationSquare =
                getIndexAndSideFromNumber(currentFlatCubeIndex + 1);
            needToJump = 1;
        }
        switch (iterationSquare.sideColor) {
            case WHITE:
                flatCube.whiteSide[iterationSquare.index] = PURPLE;
                break;
            case GREEN:
                flatCube.greenSide[iterationSquare.index] = PURPLE;
                break;
            case RED:
                flatCube.redSide[iterationSquare.index] = PURPLE;
                break;
            case BLUE:
                flatCube.blueSide[iterationSquare.index] = PURPLE;
                break;
            case ORANGE:
                flatCube.orangeSide[iterationSquare.index] = PURPLE;
                break;
            case YELLOW:
                flatCube.yellowSide[iterationSquare.index] = PURPLE;
                break;
            default:
                break;
        }
    }
    if (!isFirstCall) {
        IndexAndSide prevIterationSquare =
            getIndexAndSideFromNumber(currentFlatCubeIndex - 1);
        switch (prevIterationSquare.sideColor) {
            case WHITE:
                flatCube.whiteSide[prevIterationSquare.index] = currentColor;
                break;
            case GREEN:
                flatCube.greenSide[prevIterationSquare.index] = currentColor;
                break;
            case RED:
                flatCube.redSide[prevIterationSquare.index] = currentColor;
                break;
            case BLUE:
                flatCube.blueSide[prevIterationSquare.index] = currentColor;
                break;
            case ORANGE:
                flatCube.orangeSide[prevIterationSquare.index] = currentColor;
                break;
            case YELLOW:
                flatCube.yellowSide[prevIterationSquare.index] = currentColor;
                break;
            default:
                break;
        }
    }
    if (needToJump == 1) {
        currentFlatCubeIndex++;
    }
    if (currentFlatCubeIndex > 53) {
        if (isLinearCubeCorrect(&flatCube) == 1) {
            memcpy(&Cube2D, &flatCube, sizeof(flatCube));
            linearToMatrixCube(&Cube3D, &Cube2D);
            isCubeFilled = 1;
            strcpy(currentStepText, "CUBE LOADED");
        } else {
            currentFlatCubeIndex = -1;
            initFlatCube(&flatCube);
            updateFlatCube(WHITE, 1);
        }
    }
    // IndexAndSide nextIterationSquare =
    // getIndexAndSideFromNumber(currentFlatCubeIndex + 1); if
    // (nextIterationSquare.index == 8) {
    //     currentFlatCubeIndex++;
    // }
}

void fillCubeFromUserInput(GLFWwindow *window) {
    GLFWwindow *flatCubeWindow =
        glfwCreateWindow(500, 500, "User Input", NULL, NULL);
    if (!flatCubeWindow) {
        fprintf(stderr, "failed to create flat cube window!\n");
        return;
    }
    glfwMakeContextCurrent(flatCubeWindow);
    glfwSetFramebufferSizeCallback(flatCubeWindow, framebufferSizeCallback);
    glfwSetMouseButtonCallback(flatCubeWindow, mouseButtonCallback);
    glfwSetKeyCallback(flatCubeWindow, keyCallbackEscapeOnly);

    GLuint shaderProgram = createShaderProgram(vertexShaderInstanceSource,
                                               fragmentShaderInstanceSource);

    initFlatCube(&flatCube);
    updateFlatCube(WHITE, 1);

    currentWindow = FLATWND;

    gltInit();
    GLTtext *fileText = gltCreateText();
    gltSetText(fileText, "F");
    int width, height;

    while (!glfwWindowShouldClose(flatCubeWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        if (isCubeFilled) {
            isCubeFilled = 0;
            break;
        }

        drawFlatSide(-0.5f, 0.95f, BLUE, flatCube.blueSide);
        drawFlatSide(-0.95f, 0.5f, ORANGE, flatCube.orangeSide);
        drawFlatSide(-0.5f, 0.5f, WHITE, flatCube.whiteSide);
        drawFlatSide(-0.05f, 0.5f, RED, flatCube.redSide);
        drawFlatSide(0.4f, 0.5f, YELLOW, flatCube.yellowSide);
        drawFlatSide(-0.5f, 0.05f, GREEN, flatCube.greenSide);
        drawFlatWindowUI();

        gltInit();
        glfwGetWindowSize(flatCubeWindow, &width, &height);
        gltBeginDraw();
        gltColor(1.0f, 0.0f, 0.0f, 1.0f);
        gltDrawText2DAligned(
            fileText, NDCToPixels(flatButtons[6].xPos + 0.075f, width, 'x'),
            NDCToPixels(flatButtons[6].yPos - 0.075f, height, 'y'), 1.75f,
            GLT_CENTER, GLT_CENTER);
        gltEndDraw();
        gltTerminate();

        glfwSwapBuffers(flatCubeWindow);
        glfwPollEvents();
    }

    currentWindow = MAINWND;
    gltDeleteText(fileText);

    currentFlatCubeIndex = -1;
    glfwDestroyWindow(flatCubeWindow);
    glfwMakeContextCurrent(window);
}

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) {
#else
int main(int argc, char **argv) {
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;

    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize GLFW!\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 8);  // anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                   3);  // openGL major version to be 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                   3);  // minor set to 3, which makes the version 3.3
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for MAC OS only
#endif
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);  // avoid using old OpenGL

    window = glfwCreateWindow(600, 600, "RubikSolver", NULL, NULL);
    if (!window) {
        fprintf(stderr, "failed to create GLFW window!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // glfwSetWindowAspectRatio(window, 1, 1);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

#ifndef __APPLE__
    gladLoadGL();
#endif

    GLuint shaderProgram = createShaderProgram(vertexShaderInstanceSource,
                                               fragmentShaderInstanceSource);

    // printf("%s\n", glGetString(GL_VERSION));

    isCubeFilled = 0;
    currentFlatCubeIndex = -1;

    initButtons(mainButtons, flatButtons);
    initLinearCube(&Cube2D);
    initCube(&Cube3D);

    GLTtext *stepText = gltCreateText();
    GLTtext *revertText = gltCreateText();
    GLTtext *openText = gltCreateText();
    GLTtext *nextText = gltCreateText();
    GLTtext *cubeText = gltCreateText();
    GLTtext *solveText = gltCreateText();
    GLTtext *shuffleText = gltCreateText();
    gltSetText(revertText, "I");
    gltSetText(openText, "O");
    gltSetText(nextText, "N");
    gltSetText(cubeText, "C");
    gltSetText(solveText, "S");
    gltSetText(shuffleText, "R");

    int width, height;

    currentWindow = MAINWND;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        drawSide(RIGHT, Cube2D.redSide);
        drawSide(LEFT, Cube2D.whiteSide);
        drawSide(TOP, Cube2D.blueSide);
        drawUI();
        gltSetText(stepText, currentStepText);

        gltInit();
        glfwGetWindowSize(window, &width, &height);
        // printf("%f %f\n", xpos, ypos);
        gltBeginDraw();
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        // gltDrawText2D(text, xpos, ypos, 1.0f);
        gltDrawText2DAligned(stepText, NDCToPixels(0.0f, width, 'x'),
                             NDCToPixels(0.875f, height, 'y'), 2.0f, GLT_CENTER,
                             GLT_CENTER);
        gltColor(1.0f, 0.0f, 0.0f, 1.0f);
        gltDrawText2DAligned(
            revertText, NDCToPixels(mainButtons[0].xPos + 0.075f, width, 'x'),
            NDCToPixels(mainButtons[0].yPos - 0.075f, height, 'y'), 2.0f,
            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(
            openText, NDCToPixels(mainButtons[9].xPos + 0.075f, width, 'x'),
            NDCToPixels(mainButtons[9].yPos - 0.075f, height, 'y'), 2.0f,
            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(
            nextText, NDCToPixels(mainButtons[7].xPos + 0.075f, width, 'x'),
            NDCToPixels(mainButtons[7].yPos - 0.075f, height, 'y'), 2.0f,
            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(
            cubeText, NDCToPixels(mainButtons[8].xPos + 0.075f, width, 'x'),
            NDCToPixels(mainButtons[8].yPos - 0.075f, height, 'y'), 2.0f,
            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(
            solveText, NDCToPixels(mainButtons[10].xPos + 0.075f, width, 'x'),
            NDCToPixels(mainButtons[10].yPos - 0.075f, height, 'y'), 2.0f,
            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(
            shuffleText, NDCToPixels(mainButtons[11].xPos + 0.075f, width, 'x'),
            NDCToPixels(mainButtons[11].yPos - 0.075f, height, 'y'), 2.0f,
            GLT_CENTER, GLT_CENTER);
        gltEndDraw();
        gltTerminate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gltDeleteText(stepText);
    gltDeleteText(revertText);
    gltDeleteText(openText);
    gltDeleteText(nextText);
    gltDeleteText(cubeText);
    gltDeleteText(solveText);
    gltDeleteText(shuffleText);
    gltTerminate();
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
