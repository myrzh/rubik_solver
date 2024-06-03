#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "objects.h"
#include "shaders.h"
#include "colors.h"
#include "cube.h"
#include "algo.h"
#include "interface.h"
// #include "text_rendering.h"

// #include <ft2build.h>
// #include FT_FREETYPE_H

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <glad/glad.h>
    #include <sfd.h>
#endif

#define GLT_IMPLEMENTATION
#include <gltext.h>

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

typedef enum { MAINWND, FLATWND, AUTHORSWND } windowType;

typedef enum {RIGHT, LEFT, TOP} cubeSide;

typedef struct {
    int index;
    color sideColor;
} IndexAndSide;

windowType currentWindow;

Button mainButtons[20];
Button flatButtons[20];

LinearCube testCube;
LinearCube flatCube;
Cube Cube3D;

FILE* inputSteps;
action stepsFromFile[1000];
int actionsInFile;
int currentStep;

char currentStepText[20];

int isCubeFilled = 0;

int currentFlatCubeIndex = -1;

#ifndef __APPLE__
    sfd_Options openInputOpt = {
        .title        = "Open Steps File",
        .filter_name  = "Text Files (*.txt)",
        .filter       = "*.txt",
    };

    sfd_Options saveInputOpt = {
        .title        = "Save Steps File",
        .filter_name  = "Text Files (*.txt)",
        .filter       = "*.txt",
    };

    sfd_Options openCubeOpt = {
        .title        = "Open LinearCube File",
        .filter_name  = "Text Files (*.txt)",
        .filter       = "*.txt",
    };
#endif

void drawStrokeLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    GLfloat vertices[] = {
        x1, y1, 0.0f, 0.0f, 0.0f, 0.0f,
        x2, y2, 0.0f, 0.0f, 0.0f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void drawStroke(GLfloat x, GLfloat y, cubeSide sideToDraw) {
    switch (sideToDraw) {
        case RIGHT:
            drawStrokeLine(x, y, x + 0.173f, y + 0.1f);
            drawStrokeLine(x + 0.173f, y + 0.1f, x + 0.173f, y - 0.1f);
            drawStrokeLine(x + 0.173f, y - 0.1f, x, y - 0.2f);
            drawStrokeLine(x, y - 0.2f, x, y);
            break;
        case LEFT:
            drawStrokeLine(x, y, x - 0.173f, y + 0.1f);
            drawStrokeLine(x - 0.173f, y + 0.1f, x - 0.173f, y - 0.1f);
            drawStrokeLine(x - 0.173f, y - 0.1f, x, y - 0.2f);
            drawStrokeLine(x, y - 0.2f, x, y);
            break;
        case TOP:
            drawStrokeLine(x, y, x - 0.173f, y + 0.1f);
            drawStrokeLine(x - 0.173f, y + 0.1f, x, y + 0.2f);
            drawStrokeLine(x, y + 0.2f, x + 0.173f, y + 0.1f);
            drawStrokeLine(x + 0.173f, y + 0.1f, x, y);
            break;
        default:
            break;
    }
}

void drawSquare(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, cubeSide sideToDraw) {
    GLfloat vertices[24];
    if (sideToDraw == RIGHT) {
        GLfloat verticesTemp[] = {
            x, y, 0.0f, r, g, b,
            x + 0.173f, y + 0.1f, 0.0f, r, g, b,
            x + 0.173f, y - 0.1f, 0.0f, r, g, b,
            x, y - 0.2f, 0.0f, r, g, b
        };
        memcpy(vertices, verticesTemp, sizeof(vertices));
    } else if (sideToDraw == LEFT) {
        GLfloat verticesTemp[] = {
            x, y, 0.0f, r, g, b,
            x - 0.173f, y + 0.1f, 0.0f, r, g, b,
            x - 0.173f, y - 0.1f, 0.0f, r, g, b,
            x, y - 0.2f, 0.0f, r, g, b
        };
        memcpy(vertices, verticesTemp, sizeof(vertices));
    } else if (sideToDraw == TOP) {
        GLfloat verticesTemp[] = {
            x, y, 0.0f, r, g, b,
            x - 0.173f, y + 0.1f, 0.0f, r, g, b,
            x, y + 0.2f, 0.0f, r, g, b,
            x + 0.173f, y + 0.1f, 0.0f, r, g, b
        };
        memcpy(vertices, verticesTemp, sizeof(vertices));
    }

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    drawStroke(x, y, sideToDraw);
}

void drawSide(cubeSide sideToDraw, color sideColors[]) {
    float currentColor[3];
    switch (sideToDraw) {
        case RIGHT:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[rightSideOrder[i]]], sizeof(colors[sideColors[rightSideOrder[i]]]));
                drawSquare(rightCoords[i][0], rightCoords[i][1], currentColor[RED], currentColor[GREEN], currentColor[BLUE], sideToDraw);
            }
            break;
        case LEFT:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[leftSideOrder[i]]], sizeof(colors[sideColors[leftSideOrder[i]]]));
                drawSquare(leftCoords[i][0], leftCoords[i][1], currentColor[RED], currentColor[GREEN], currentColor[BLUE], sideToDraw);
            }
            break;
        case TOP:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[topSideOrder[i]]], sizeof(colors[sideColors[topSideOrder[i]]]));
                drawSquare(topCoords[i][0], topCoords[i][1], currentColor[RED], currentColor[GREEN], currentColor[BLUE], sideToDraw);
            }
            break;
        default:
            break;
    }
}

void drawButton(GLfloat x, GLfloat y, GLfloat width, GLfloat height, color colorName) {
    float currentColor[3];
    memcpy(currentColor, colors[colorName], sizeof(colors[colorName]));
    GLfloat vertices[] = {
        x, y, 0.0f, currentColor[RED], currentColor[GREEN], currentColor[BLUE],
        x + width, y, 0.0f, currentColor[RED], currentColor[GREEN], currentColor[BLUE],
        x + width, y - height, 0.0f, currentColor[RED], currentColor[GREEN], currentColor[BLUE],
        x, y - height, 0.0f, currentColor[RED], currentColor[GREEN], currentColor[BLUE]
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void drawUI() {
    for (int i = 0; i < sizeof(mainButtons) / sizeof(mainButtons[0]); i++) {
        drawButton(mainButtons[i].xPos, mainButtons[i].yPos, mainButtons[i].width, mainButtons[i].height, mainButtons[i].color);
    }
}

void drawFlatWindowUI() {
    for (int i = 0; i < sizeof(flatButtons) / sizeof(flatButtons[0]); i++) {
        drawButton(flatButtons[i].xPos, flatButtons[i].yPos, flatButtons[i].width, flatButtons[i].height, flatButtons[i].color);
    }
}

void fillStepsFromFile(char filename[]) {
    // replaceBackslashes(filename);
    inputSteps = fopen(filename, "r");
    // printf("'%s\n'", filename);
    if (inputSteps == NULL) {
        printf("can't open steps file!\n");
        return;
    }
    currentStep = 0;
    printf("steps file opened!\n");

    char line[256];

    memset(stepsFromFile, 0, sizeof(stepsFromFile));
    actionsInFile = 0;

    int actionIndex;
    int isReverse;
    action currentAction;
    int currentActionCount;

    while (fgets(line, sizeof(line), inputSteps) != NULL) {
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
        // rotateLinearSideBy90(&testCube, (color)(currentAction / 2), STRAIGHT);
    } else {
        sideColorToRotate = (color)((currentAction - 1) / 2);
        n += 2;
        // rotateLinearSideBy90(&testCube, (color)((currentAction - 1) / 2), BACK);
    }

    for (int i = 0; i < n; i++) {
        cubeDoOp(&Cube3D, getRotationFromColor(sideColorToRotate));
        matrixToLinearCube(&testCube, &Cube3D);
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

    while (fgets(line, sizeof(line), inputCube) != NULL) {
        for (int i = 0; i < 9; i++) {
            currentColor = getColorFromChar(line[i]);
            // printf("%c", line[i]);
            switch (currentLineNumber) {
                case 1:
                    testCube.blueSide[flatBlueSideOrder[i]] = currentColor;
                    break;
                case 2:
                    testCube.orangeSide[flatOrangeSideOrder[i]] = currentColor;
                    break;
                case 3:
                    testCube.whiteSide[flatWhiteSideOrder[i]] = currentColor;
                    break;
                case 4:
                    testCube.redSide[flatRedSideOrder[i]] = currentColor;
                    break;
                case 5:
                    testCube.yellowSide[flatYellowSideOrder[i]] = currentColor;
                    break;
                case 6:
                    testCube.greenSide[flatGreenSideOrder[i]] = currentColor;
                    break;
                default:
                    break;
            }
        }
        currentLineNumber++;
    }
    fclose(inputCube);

    linearToMatrixCube(&Cube3D, &testCube);

    isCubeFilled = 1;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    int minSize = (width < height) ? width : height;
    glfwSetWindowSize(window, minSize, minSize);
    glViewport(0, 0, minSize, minSize);
}

void drawFlatSquare(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) {
    GLfloat vertices[] = {
        x, y, 0.0f, r, g, b,
        x + 0.15f, y, 0.0f, r, g, b,
        x + 0.15f, y - 0.15f, 0.0f, r, g, b,
        x, y - 0.15f, 0.0f, r, g, b
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    // drawStroke(x, y, sideToDraw);
}

void drawFlatSide(GLfloat x, GLfloat y, color sideToDraw, color sideColors[]) {
    int squareCount = 0;
    float currentColor[3];
    for (float j = y; j > (y - 0.35f); j -= 0.15f) {
        for (float i = x; i < (x + 0.35f); i += 0.15f) {
            switch (sideToDraw) {
                case BLUE:
                    memcpy(currentColor, colors[sideColors[flatBlueSideOrder[squareCount]]], sizeof(colors[sideColors[flatBlueSideOrder[squareCount]]]));
                    break;
                case ORANGE:
                    memcpy(currentColor, colors[sideColors[flatOrangeSideOrder[squareCount]]], sizeof(colors[sideColors[flatOrangeSideOrder[squareCount]]]));
                    break;
                case WHITE:
                    memcpy(currentColor, colors[sideColors[flatWhiteSideOrder[squareCount]]], sizeof(colors[sideColors[flatWhiteSideOrder[squareCount]]]));
                    break;
                case RED:
                    memcpy(currentColor, colors[sideColors[flatRedSideOrder[squareCount]]], sizeof(colors[sideColors[flatRedSideOrder[squareCount]]]));
                    break;
                case YELLOW:
                    memcpy(currentColor, colors[sideColors[flatYellowSideOrder[squareCount]]], sizeof(colors[sideColors[flatYellowSideOrder[squareCount]]]));
                    break;
                case GREEN:
                    memcpy(currentColor, colors[sideColors[flatGreenSideOrder[squareCount]]], sizeof(colors[sideColors[flatGreenSideOrder[squareCount]]]));
                    break;
                default:
                    break;
            }
            drawFlatSquare(i, j, currentColor[RED], currentColor[GREEN], currentColor[BLUE]);
            squareCount++;
        }
    }
}

IndexAndSide getIndexAndSideFromNumber(int absoluteIndex) {
    color sideColor;
    int relativeIndex;

    if (absoluteIndex >= 0 && absoluteIndex <= 8) {
        sideColor = BLUE;
        relativeIndex = flatBlueSideOrder[absoluteIndex - 9 * 0];
    } else if (absoluteIndex >= 9 && absoluteIndex <= 17) {
        sideColor = ORANGE;
        relativeIndex = flatOrangeSideOrder[absoluteIndex - 9 * 1];
    } else if (absoluteIndex >= 18 && absoluteIndex <= 26) {
        sideColor = WHITE;
        relativeIndex = flatWhiteSideOrder[absoluteIndex - 9 * 2];
    } else if (absoluteIndex >= 27 && absoluteIndex <= 35) {
        sideColor = RED;
        relativeIndex = flatRedSideOrder[absoluteIndex - 9 * 3];
    } else if (absoluteIndex >= 36 && absoluteIndex <= 44) {
        sideColor = YELLOW;
        relativeIndex = flatYellowSideOrder[absoluteIndex - 9 * 4];
    } else if (absoluteIndex >= 45 && absoluteIndex <= 53) {
        sideColor = GREEN;
        relativeIndex = flatGreenSideOrder[absoluteIndex - 9 * 5];
    }

    IndexAndSide result;
    result.index = relativeIndex;
    result.sideColor = sideColor;
    return result;
}

void updateFlatCube(color currentColor, int isFirstCall) {
    currentFlatCubeIndex++;
    int needToJump = 0;

    IndexAndSide iterationSquare = getIndexAndSideFromNumber(currentFlatCubeIndex);
    if (currentFlatCubeIndex <= 53) {
        if (iterationSquare.index == 8) {
            iterationSquare = getIndexAndSideFromNumber(currentFlatCubeIndex + 1);
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
        IndexAndSide prevIterationSquare = getIndexAndSideFromNumber(currentFlatCubeIndex - 1);
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
        memcpy(&testCube, &flatCube, sizeof(flatCube));
        linearToMatrixCube(&Cube3D, &testCube);
        isCubeFilled = 1;
    }
    // IndexAndSide nextIterationSquare = getIndexAndSideFromNumber(currentFlatCubeIndex + 1);
    // if (nextIterationSquare.index == 8) {
    //     currentFlatCubeIndex++;
    // }
}

void fillCubeFromUserInput(GLFWwindow* window) {
    GLFWwindow* flatCubeWindow = glfwCreateWindow(500, 500, "User Input", NULL, NULL);
    if (!flatCubeWindow) {
        fprintf(stderr, "failed to create flat cube window!\n");
        return;
    }
    glfwMakeContextCurrent(flatCubeWindow);
    glfwSetFramebufferSizeCallback(flatCubeWindow, framebufferSizeCallback);
    glfwSetMouseButtonCallback(flatCubeWindow, mouseButtonCallback);

    GLuint shaderProgram = createShaderProgram(vertexShaderInstanceSource, fragmentShaderInstanceSource);

    initFlatCube(&flatCube);
    updateFlatCube(WHITE, 1);

    currentWindow = FLATWND;

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

        glfwSwapBuffers(flatCubeWindow);
        glfwPollEvents();
    }

    currentWindow = MAINWND;

    currentFlatCubeIndex = -1;
    glfwDestroyWindow(flatCubeWindow);
    glfwMakeContextCurrent(window);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        GLFWwindow* authorsWindow = glfwCreateWindow(500, 200, "Authors", NULL, NULL);
        if (!authorsWindow) {
            fprintf(stderr, "failed to create secondary window!\n");
            return;
        }
        glfwMakeContextCurrent(authorsWindow);

        // glfwSetWindowAspectRatio(authorsWindow, 1, 1);

        // const char* authors[] = { "Shtarev I.A.", "Plotnikov D.A." };
        // const char* authors[] = { "Shtarev I.A.\nPlotnikov D.A." };
        // for (int i = 0; i < 2; ++i) {
        //     const char* name = authors[i];
        //     printf("%s\n", name);
        // }

        const char* authorsText =
            "RubikSolver (c)\n"
            "\n"
            "Made by:\n"
            "Plotnikov D.A.\n"
            "Shtarev I.A.\n"
            "2024\n"
            "\n"
            "Peter the Great St.Petersburg Polytechnic University\n"
            "Institute of Cybersecurity and Computer Science\n"
            "Higher School of Cybersecurity\n";

        gltInit();

        GLTtext *text = gltCreateText();
        gltSetText(text, authorsText);
        int width, height;
        GLfloat xpos, ypos;

        currentWindow = AUTHORSWND;

        while (!glfwWindowShouldClose(authorsWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwGetWindowSize(authorsWindow, &width, &height);

            xpos = (width * 0.0f + width) / 2.0f;
            ypos = (height - height * 0.0f) / 2.0f;
            // printf("%f %f\n", xpos, ypos);

            gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            // gltDrawText2D(text, xpos, ypos, 1.0f);
            gltDrawText2DAligned(text, xpos, ypos, 1.0f, GLT_CENTER, GLT_CENTER);
            gltEndDraw();

            // renderText(currentTextData, "Hello World", 0.5f, 0.5f, 25.0f, colors[3]);

            glfwSwapBuffers(authorsWindow);
            glfwPollEvents();
        }

        currentWindow = MAINWND;

        gltDeleteText(text);
        gltTerminate();
        // glDeleteProgram(currentTextData.shaderData);
        glfwDestroyWindow(authorsWindow);
        glfwMakeContextCurrent(window);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        double normalizedX = -1.0 + 2.0 * xpos / width;
        double normalizedY =  1.0 - 2.0 * ypos / height;

        // printf("%f %f -> %f %f\n", xpos, ypos, normalizedX, normalizedY);

        // char inputFilename[50] = "input.txt";
        // char inputFilename[50];
        // char cubeFilename[50] = "cube1.txt";
        // char cubeFilename[50];
        char filename[256];

        switch (currentWindow) {
            case MAINWND:
                for (int i = 0; i < sizeof(mainButtons) / sizeof(mainButtons[0]); i++) {
                    if (normalizedX >= mainButtons[i].xPos && normalizedX <= mainButtons[i].xPos + mainButtons[i].width &&
                    normalizedY <= mainButtons[i].yPos && normalizedY >= mainButtons[i].yPos - mainButtons[i].height) {
                        switch (mainButtons[i].function) {
                            case REVERT:
                                initLinearCube(&testCube);
                                linearToMatrixCube(&Cube3D, &testCube);
                                break;
                            case ROTATE_SIDE:
                                switch (button) {
                                    case GLFW_MOUSE_BUTTON_LEFT:
                                        cubeDoOp(&Cube3D, getRotationFromColor(mainButtons[i].color));
                                        matrixToLinearCube(&testCube, &Cube3D);
                                        // renderMatrixCube(&Cube3D);
                                        // rotateLinearSideBy90(&testCube, mainButtons[i].color, STRAIGHT);
                                        break;
                                    case GLFW_MOUSE_BUTTON_RIGHT:
                                        for (int count = 0; count < 3; count++) {
                                            cubeDoOp(&Cube3D, getRotationFromColor(mainButtons[i].color));
                                            matrixToLinearCube(&testCube, &Cube3D);
                                        }
                                        // rotateLinearSideBy90(&testCube, mainButtons[i].color, BACK);
                                    default:
                                        break;
                                }
                                break;
                            case NEXTSTEP:
                                executeStep();
                                break;
                            case FILLCUBE:
                                fillCubeFromUserInput(window);
                                break;
                            case OPENSTEPSFILE:
                                #ifdef __APPLE__
                                    printf("enter steps filename: ");
                                    fgets(filename, sizeof(filename), stdin);
                                    filename[strcspn(filename, "\n")] = '\0';
                                    if (strlen(filename) != 0) {
                                        printf("got steps file: '%s'\n", filename);
                                    }
                                    fillStepsFromFile(filename);
                                #else
                                    const char *filenamePointer = sfd_open_dialog(&openInputOpt);
                                    if (filenamePointer) {
                                        printf("got steps file: '%s'\n", filenamePointer);
                                    }
                                    fillStepsFromFile(filenamePointer);
                                    // free(filenamePointer);
                                #endif
                                break;
                            case SOLVECUBE:
                                // SAVE SOLUTION STEPS TO FILE AND LOAD IT TO PROGRAM
                                break;
                            default:
                                break;
                        }
                    }
                }
                break;
            case FLATWND:
                for (int i = 0; i < sizeof(flatButtons) / sizeof(flatButtons[0]); i++) {
                    if (normalizedX >= flatButtons[i].xPos && normalizedX <= flatButtons[i].xPos + flatButtons[i].width &&
                    normalizedY <= flatButtons[i].yPos && normalizedY >= flatButtons[i].yPos - flatButtons[i].height) {
                        switch (flatButtons[i].function) {
                            case SETCOLOR:
                                updateFlatCube(flatButtons[i].color, 0);
                                break;
                            case GETFILECUBE:
                                #ifdef __APPLE__
                                    printf("enter cube filename: ");
                                    fgets(filename, sizeof(filename), stdin);
                                    filename[strcspn(filename, "\n")] = '\0';
                                    if (strlen(filename) != 0) {
                                        printf("got cube file: '%s'\n", filename);
                                    }
                                    fillCubeFromFile(filename);
                                #else
                                    const char *filenamePointer = sfd_open_dialog(&openCubeOpt);;
                                    if (filenamePointer) {
                                        printf("got cube file: '%s'\n", filenamePointer);
                                    }
                                    fillCubeFromFile(filenamePointer);
                                    // free(filenamePointer);
                                #endif
                                break;
                            default:
                                break;
                        }
                    }
                }
                break;
            case AUTHORSWND:
                break;
        }
    }
}


int main(int argc, char *argv[]) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize GLFW!\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 8); // anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL major version to be 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor set to 3, which makes the version 3.3
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC OS only
    #endif
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE); //avoid using old OpenGL

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

    GLuint shaderProgram = createShaderProgram(vertexShaderInstanceSource, fragmentShaderInstanceSource);

    // printf("%s\n", glGetString(GL_VERSION));

    initButtons(mainButtons, flatButtons);
    initLinearCube(&testCube);
    initCube(&Cube3D);

    gltInit();

    GLTtext *stepText = gltCreateText();
    GLTtext *revertText = gltCreateText();
    GLTtext *openText = gltCreateText();
    GLTtext *nextText = gltCreateText();
    GLTtext *cubeText = gltCreateText();
    GLTtext *solveText = gltCreateText();
    gltSetText(revertText, "R");
    gltSetText(openText, "O");
    gltSetText(nextText, "N");
    gltSetText(cubeText, "C");
    gltSetText(solveText, "S");

    int width, height;

    currentWindow = MAINWND;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        drawSide(RIGHT, testCube.redSide);
        drawSide(LEFT, testCube.whiteSide);
        drawSide(TOP, testCube.blueSide);
        drawUI();
        gltSetText(stepText, currentStepText);

        glfwGetWindowSize(window, &width, &height);
        // printf("%f %f\n", xpos, ypos);
        gltBeginDraw();
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        // gltDrawText2D(text, xpos, ypos, 1.0f);
        gltDrawText2DAligned(stepText, NDCToPixels(0.0f, width, 'x'), NDCToPixels(0.875f, height, 'y'), 2.0f, GLT_CENTER, GLT_CENTER);
        gltColor(1.0f, 0.0f, 0.0f, 1.0f);
        gltDrawText2DAligned(revertText,
                                 NDCToPixels(mainButtons[0].xPos + 0.075f, width, 'x'),
                                 NDCToPixels(mainButtons[0].yPos - 0.075f, height, 'y'),
                             2.0f, GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(openText,
                                 NDCToPixels(mainButtons[9].xPos + 0.075f, width, 'x'),
                                 NDCToPixels(mainButtons[9].yPos - 0.075f, height, 'y'),
                             2.0f, GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(nextText,
                                 NDCToPixels(mainButtons[7].xPos + 0.075f, width, 'x'),
                                 NDCToPixels(mainButtons[7].yPos - 0.075f, height, 'y'),
                             2.0f, GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(cubeText,
                                 NDCToPixels(mainButtons[8].xPos + 0.075f, width, 'x'),
                                 NDCToPixels(mainButtons[8].yPos - 0.075f, height, 'y'),
                             2.0f, GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(solveText,
                                 NDCToPixels(mainButtons[10].xPos + 0.075f, width, 'x'),
                                 NDCToPixels(mainButtons[10].yPos - 0.075f, height, 'y'),
                             2.0f, GLT_CENTER, GLT_CENTER);
        gltEndDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free(stepText);
    free(revertText);
    free(openText);
    free(nextText);
    free(cubeText);
    free(solveText);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
