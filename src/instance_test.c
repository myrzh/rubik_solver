#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#include "shaders.h"
#include "colors.h"
#include "cube.h"

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#elif defined(_WIN32)
    #include <glad/glad.h>
#else
    #error "unsupported platform!"
#endif

typedef enum {RIGHT, LEFT, TOP} cubeSide;

void printMessage() {
    printf("MESSAGE\n");
}

Button buttons[10];

Cube testCube;

void initData() {
    for (int i = 0; i < 7; i++) {
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

    initCube(&testCube);
}

GLuint getShaderProgram() {
    // GLuint shaderID;
    // Compile and link shaders
    GLuint vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderInstanceSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderInstanceSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    char log[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        printf("Vertex shader didn't compile properly. GL Log:\n%s\n", log);
    };

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        printf("Fragment shader didn't compile properly. GL Log:\n%s\n", log);
    };

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        printf("Linking didn't work. GL Log:\n%s\n", log);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
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
                drawSquare(rightCoords[i][0], rightCoords[i][1], currentColor[R], currentColor[G], currentColor[B], sideToDraw);
            }
            break;
        case LEFT:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[leftSideOrder[i]]], sizeof(colors[sideColors[leftSideOrder[i]]]));
                drawSquare(leftCoords[i][0], leftCoords[i][1], currentColor[R], currentColor[G], currentColor[B], sideToDraw);
            }
            break;
        case TOP:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[topSideOrder[i]]], sizeof(colors[sideColors[topSideOrder[i]]]));
                drawSquare(topCoords[i][0], topCoords[i][1], currentColor[R], currentColor[G], currentColor[B], sideToDraw);
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
        x, y, 0.0f, currentColor[R], currentColor[G], currentColor[B],
        x + width, y, 0.0f, currentColor[R], currentColor[G], currentColor[B],
        x + width, y - height, 0.0f, currentColor[R], currentColor[G], currentColor[B],
        x, y - height, 0.0f, currentColor[R], currentColor[G], currentColor[B]
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
    for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        drawButton(buttons[i].xPos, buttons[i].yPos, buttons[i].width, buttons[i].height, buttons[i].color);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    int minSize = (width < height) ? width : height;
    glfwSetWindowSize(window, minSize, minSize);
    glViewport(0, 0, minSize, minSize);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void randomizeSides() {
    // int randColor;
    // for (int i = 0; i < 8; i++) {
    //     randColor = rand() % 6;
    //     rightSide[i] = randColor;
    // }
    // for (int i = 0; i < 8; i++) {
    //     randColor = rand() % 6;
    //     leftSide[i] = randColor;
    // }
    // for (int i = 0; i < 8; i++) {
    //     randColor = rand() % 6;
    //     topSide[i] = randColor;
    // }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        double normalizedX = -1.0 + 2.0 * xpos / width; 
        double normalizedY = 1.0 - 2.0 * ypos / height; 

        // printf("%f %f -> %f %f\n", xpos, ypos, normalizedX, normalizedY);

        for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
            if (normalizedX >= buttons[i].xPos && normalizedX <= buttons[i].xPos + buttons[i].width &&
                normalizedY <= buttons[i].yPos && normalizedY >= buttons[i].yPos - buttons[i].height) {
                switch (buttons[i].function) {
                    case REVERT:
                        // initCube(&testCube);
                        firstStep(&testCube);
                        break;
                    case ROTATE_SIDE:
                        switch (button) {
                            case GLFW_MOUSE_BUTTON_LEFT:
                                rotateSideBy90(&testCube, buttons[i].color);
                                break;
                            case GLFW_MOUSE_BUTTON_RIGHT:
                                rotateSideBy90Back(&testCube, buttons[i].color);
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main (int argc, char *argv[]) {

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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC OS only
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE); //avoid using old openGL

    window = glfwCreateWindow(600, 600, "RubikSolver", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    #ifdef _WIN32
        gladLoadGL();
    #endif

    GLuint shaderProgram = getShaderProgram();

    // printf("%s\n", glGetString(GL_VERSION));

    initData();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        drawSide(RIGHT, testCube.whiteSide);
        drawSide(LEFT, testCube.blueSide);
        drawSide(TOP, testCube.redSide);
        drawUI();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
