#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "objects.h"
#include "shaders.h"
#include "colors.h"
#include "cube.h"
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
#elif defined(_WIN32)
    #include <glad/glad.h>
    #include <sfd.h>
#elif defined(__linux__)
    #include <glad/glad.h>
    #include <sfd.h>
#else
    #error "unsupported platform!"
#endif

#define GLT_IMPLEMENTATION
#include <gltext.h>

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

typedef enum {RIGHT, LEFT, TOP} cubeSide;

typedef struct {
    int index;
    color sideColor;
} IndexAndSide;

Button buttons[20];

Cube testCube;
Cube flatCube;

FILE* inputSteps;
action stepsFromFile[1000];
int actionsInFile;
int currentStep;

char currentStepText[20];

int isCubeFilledFromFile = 0;

int currentFlatCubeIndex = -1;

// void replaceBackslashes(char str[]) {
//     for (int i = 0; i < strlen(str); i++) {
//         if (str[i] == '\\') {
//             str[i] = '/';
//         }
//     }
// }

sfd_Options openInputOpt = {
  .title        = "Open Steps File",
  .filter_name  = "Text File",
  .filter       = "*.txt",
};

void initData() {
    for (int i = 0; i < 17; i++) {
        buttons[i].width = 0.15f;
        buttons[i].height = 0.15f;
    }

    buttons[0].xPos = -0.95f;
    buttons[0].yPos = 0.95f;
    buttons[0].color = WHITE;
    buttons[0].function = REVERT;

    buttons[1].xPos = -0.75f;
    buttons[1].yPos = 0.95f;
    buttons[1].color = GREEN;
    buttons[1].function = ROTATE_SIDE;

    buttons[2].xPos = -0.95f;
    buttons[2].yPos = 0.75f;
    buttons[2].color = YELLOW;
    buttons[2].function = ROTATE_SIDE;

    buttons[3].xPos = -0.75f;
    buttons[3].yPos = 0.75f;
    buttons[3].color = RED;
    buttons[3].function = ROTATE_SIDE;

    buttons[4].xPos = -0.55f;
    buttons[4].yPos = 0.75f;
    buttons[4].color = WHITE;
    buttons[4].function = ROTATE_SIDE;

    buttons[5].xPos = -0.35f;
    buttons[5].yPos = 0.75f;
    buttons[5].color = ORANGE;
    buttons[5].function = ROTATE_SIDE;

    buttons[6].xPos = -0.75f;
    buttons[6].yPos = 0.55f;
    buttons[6].color = BLUE;
    buttons[6].function = ROTATE_SIDE;

    buttons[7].xPos = 0.8f;
    buttons[7].yPos = 0.95f;
    buttons[7].color = WHITE;
    buttons[7].function = NEXTSTEP;

    buttons[8].xPos = 0.8f;
    buttons[8].yPos = 0.75f;
    buttons[8].color = WHITE;
    buttons[8].function = FILLCUBE;

    buttons[9].xPos = 0.6f;
    buttons[9].yPos = 0.95f;
    buttons[9].color = WHITE;
    buttons[9].function = OPENSTEPSFILE;

    buttons[10].xPos = 0.6f;
    buttons[10].yPos = -0.4f;
    buttons[10].color = WHITE;
    buttons[10].function = SETCOLOR;

    buttons[11].xPos = 0.8f;
    buttons[11].yPos = -0.4f;
    buttons[11].color = GREEN;
    buttons[11].function = SETCOLOR;

    buttons[12].xPos = 0.6f;
    buttons[12].yPos = -0.6f;
    buttons[12].color = RED;
    buttons[12].function = SETCOLOR;

    buttons[13].xPos = 0.8f;
    buttons[13].yPos = -0.6f;
    buttons[13].color = BLUE;
    buttons[13].function = SETCOLOR;

    buttons[14].xPos = 0.6f;
    buttons[14].yPos = -0.8f;
    buttons[14].color = ORANGE;
    buttons[14].function = SETCOLOR;

    buttons[15].xPos = 0.8f;
    buttons[15].yPos = -0.8f;
    buttons[15].color = YELLOW;
    buttons[15].function = SETCOLOR;

    buttons[16].xPos = -0.95f;
    buttons[16].yPos = -0.8f;
    buttons[16].color = WHITE;
    buttons[16].function = GETFILECUBE;

    initCube(&testCube);
}

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
    for (int i = 0; i < 10; i++) {
        drawButton(buttons[i].xPos, buttons[i].yPos, buttons[i].width, buttons[i].height, buttons[i].color);
    }
}

void drawFlatWindowUI() {
    for (int i = 10; i < 17; i++) {
        drawButton(buttons[i].xPos, buttons[i].yPos, buttons[i].width, buttons[i].height, buttons[i].color);
    }
}

void fillStepsFromFile(const char filename[]) {
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
        // printf("%s", line);
        actionIndex = 0;
        isReverse = 0;
        currentActionCount = 0;
        if (line[0] == '_') {
            actionIndex = 1;
            isReverse = 1;
        }

        currentAction = getActionFromChar(line[actionIndex]);

        if (isReverse) {
            currentAction++;
        }

        currentActionCount = line[actionIndex + 1] - '0';

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

    if (currentAction % 2 == 0) {
        rotateSideBy90(&testCube, (color)(currentAction / 2), STRAIGHT);
    } else {
        rotateSideBy90(&testCube, (color)((currentAction - 1) / 2), BACK);
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
                    testCube.whiteSide[flatLevelOneSideOrder[i]] = currentColor;
                    break;
                case 2:
                    testCube.greenSide[flatLevelTwoSideOrder[i]] = currentColor;
                    break;
                case 3:
                    testCube.redSide[flatLevelTwoSideOrder[i]] = currentColor;
                    break;
                case 4:
                    testCube.blueSide[flatLevelTwoSideOrder[i]] = currentColor;
                    break;
                case 5:
                    testCube.orangeSide[flatLevelTwoSideOrder[i]] = currentColor;
                    break;
                case 6:
                    testCube.yellowSide[flatLevelThreeSideOrder[i]] = currentColor;
                    break;
                default:
                    break;
            }
        }
        currentLineNumber++;
    }
    fclose(inputCube);

    isCubeFilledFromFile = 1;
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

void drawFlatSide(GLfloat x, GLfloat y, flatCubeLevel levelToDraw, color sideColors[]) {
    int squareCount = 0;
    float currentColor[3];
    for (float j = y; j > (y - 0.35f); j -= 0.15f) {
        for (float i = x; i < (x + 0.35f); i += 0.15f) {
            switch (levelToDraw) {
                case LEVEL_ONE:
                    memcpy(currentColor, colors[sideColors[flatLevelOneSideOrder[squareCount]]], sizeof(colors[sideColors[flatLevelOneSideOrder[squareCount]]]));
                    break;
                case LEVEL_TWO:
                    memcpy(currentColor, colors[sideColors[flatLevelTwoSideOrder[squareCount]]], sizeof(colors[sideColors[flatLevelTwoSideOrder[squareCount]]]));
                    break;
                case LEVEL_THREE:
                    memcpy(currentColor, colors[sideColors[flatLevelThreeSideOrder[squareCount]]], sizeof(colors[sideColors[flatLevelThreeSideOrder[squareCount]]]));
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
        sideColor = WHITE;
        relativeIndex = flatLevelOneSideOrder[absoluteIndex - 9 * 0];
    } else if (absoluteIndex >= 9 && absoluteIndex <= 17) {
        sideColor = GREEN;
        relativeIndex = flatLevelTwoSideOrder[absoluteIndex - 9 * 1];
    } else if (absoluteIndex >= 18 && absoluteIndex <= 26) {
        sideColor = RED;
        relativeIndex = flatLevelTwoSideOrder[absoluteIndex - 9 * 2];
    } else if (absoluteIndex >= 27 && absoluteIndex <= 35) {
        sideColor = BLUE;
        relativeIndex = flatLevelTwoSideOrder[absoluteIndex - 9 * 3];
    } else if (absoluteIndex >= 36 && absoluteIndex <= 44) {
        sideColor = ORANGE;
        relativeIndex = flatLevelTwoSideOrder[absoluteIndex - 9 * 4];
    } else if (absoluteIndex >= 45 && absoluteIndex <= 53) {
        sideColor = YELLOW;
        relativeIndex = flatLevelThreeSideOrder[absoluteIndex - 9 * 5];
    }

    IndexAndSide result;
    result.index = relativeIndex;
    result.sideColor = sideColor;
    return result;
}

void updateFlatCube(color currentColor, int isFirstCall) {
    currentFlatCubeIndex++;

    IndexAndSide iterationSquare = getIndexAndSideFromNumber(currentFlatCubeIndex);
    // if (iterationSquare.index == 8) {
    //     currentFlatCubeIndex++;
    // }
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

    while (!glfwWindowShouldClose(flatCubeWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        if (isCubeFilledFromFile) {
            isCubeFilledFromFile = 0;
            break;
        }

        drawFlatSide(-0.5f, 0.95f, LEVEL_ONE, flatCube.whiteSide); // WHITE SIDE
        drawFlatSide(-0.95f, 0.5f, LEVEL_TWO, flatCube.greenSide); // GREEN SIDE
        drawFlatSide(-0.5f, 0.5f, LEVEL_TWO, flatCube.redSide);  // RED SIDE
        drawFlatSide(-0.05f, 0.5f, LEVEL_TWO, flatCube.blueSide); // BLUE SIDE
        drawFlatSide(0.4f, 0.5f, LEVEL_TWO, flatCube.orangeSide);   // ORANGE SIDE
        drawFlatSide(-0.5f, 0.05f, LEVEL_THREE, flatCube.yellowSide); // YELLOW SIDE
        drawFlatWindowUI();

        glfwSwapBuffers(flatCubeWindow);
        glfwPollEvents();
    }

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
        char inputFilename[50];
        // char cubeFilename[50] = "input.txt";
        char cubeFilename[50];

        for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
            if (normalizedX >= buttons[i].xPos && normalizedX <= buttons[i].xPos + buttons[i].width &&
                normalizedY <= buttons[i].yPos && normalizedY >= buttons[i].yPos - buttons[i].height) {
                switch (buttons[i].function) {
                    case REVERT:
                        initCube(&testCube);
                        break;
                    case ROTATE_SIDE:
                        switch (button) {
                            case GLFW_MOUSE_BUTTON_LEFT:
                                rotateSideBy90(&testCube, buttons[i].color, STRAIGHT);
                                break;
                            case GLFW_MOUSE_BUTTON_RIGHT:
                                rotateSideBy90(&testCube, buttons[i].color, BACK);
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
                        // printf("enter steps filename: ");
                        // fgets(inputFilename, sizeof(inputFilename), stdin);
                        // inputFilename[strcspn(inputFilename, "\n")] = '\0';
                        const char *filename = sfd_open_dialog(&openInputOpt);
                        if (filename) {
                            printf("got steps file: '%s'\n", filename);
                        }
                        // else {
                        //     printf("can't open steps file!\n");
                        // }
                        // break;
                        fillStepsFromFile(filename);
                        break;
                    case SETCOLOR:
                        updateFlatCube(buttons[i].color, 0);
                        break;
                    case GETFILECUBE:
                        printf("enter cube filename: ");
                        fgets(cubeFilename, sizeof(cubeFilename), stdin);
                        cubeFilename[strcspn(cubeFilename, "\n")] = '\0';
                        fillCubeFromFile(cubeFilename);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 8); // anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL major version to be 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor set to 3, which makes the version 3.3
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC OS only
    #endif
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE); //avoid using old openGL

    window = glfwCreateWindow(600, 600, "RubikSolver", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // glfwSetWindowAspectRatio(window, 1, 1);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);


    #ifdef _WIN32
        gladLoadGL();
    #endif

    GLuint shaderProgram = createShaderProgram(vertexShaderInstanceSource, fragmentShaderInstanceSource);

    // printf("%s\n", glGetString(GL_VERSION));

    initData();

    gltInit();

    GLTtext *text = gltCreateText();
    int width, height;
    GLfloat xpos, ypos;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        drawSide(RIGHT, testCube.whiteSide);
        drawSide(LEFT, testCube.blueSide);
        drawSide(TOP, testCube.redSide);
        drawUI();
        gltSetText(text, currentStepText);

        glfwGetWindowSize(window, &width, &height);
        xpos = (width * 0.0f + width) / 2.0f;
        ypos = (height - height * 0.95f) / 2.0f;
        // printf("%f %f\n", xpos, ypos);
        gltBeginDraw();
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        // gltDrawText2D(text, xpos, ypos, 1.0f);
        gltDrawText2DAligned(text, xpos, ypos, 2.0f, GLT_CENTER, GLT_CENTER);
        gltEndDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
