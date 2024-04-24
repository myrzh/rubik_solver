#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#include "shaders.h"
#include "colors.h"

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

btnCoordsStruct btn1;

int rightSide[] = { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE };
int leftSide[] = { BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE };
int topSide[] = { RED, RED, RED, RED, RED, RED, RED, RED, RED };

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

void drawSide(cubeSide sideToDraw, int sideColors[]) {
    float color[3];
    switch (sideToDraw) {
        case RIGHT:
            for (int i = 0; i < 9; i++) {
                memcpy(color, colors[sideColors[rightSideOrder[i]]], sizeof(colors[sideColors[rightSideOrder[i]]]));
                drawSquare(rightCoords[i][0], rightCoords[i][1], color[R], color[G], color[B], sideToDraw);
            }
            break;
        case LEFT:
            for (int i = 0; i < 9; i++) {
                memcpy(color, colors[sideColors[leftSideOrder[i]]], sizeof(colors[sideColors[leftSideOrder[i]]]));
                drawSquare(leftCoords[i][0], leftCoords[i][1], color[R], color[G], color[B], sideToDraw);
            }
            break;
        case TOP:
            for (int i = 0; i < 9; i++) {
                memcpy(color, colors[sideColors[topSideOrder[i]]], sizeof(colors[sideColors[topSideOrder[i]]]));
                drawSquare(topCoords[i][0], topCoords[i][1], color[R], color[G], color[B], sideToDraw);
            }
            break;
        default:
            break;
    }
}

void drawBtn1(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    GLfloat vertices[] = {
        x, y, 0.0f, 1.0f, 1.0f, 1.0f,
        x + width, y, 0.0f, 1.0f, 1.0f, 1.0f,
        x + width, y - height, 0.0f, 1.0f, 1.0f, 1.0f,
        x, y - height, 0.0f, 1.0f, 1.0f, 1.0f
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
    drawBtn1(btn1.xPos, btn1.yPos, btn1.width, btn1.height);
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
    int randColor;
    for (int i = 0; i < 8; i++) {
        randColor = rand() % 6;
        rightSide[i] = randColor;
    }
    for (int i = 0; i < 8; i++) {
        randColor = rand() % 6;
        leftSide[i] = randColor;
    }
    for (int i = 0; i < 8; i++) {
        randColor = rand() % 6;
        topSide[i] = randColor;
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        double normalizedX = -1.0 + 2.0 * xpos / width; 
        double normalizedY = 1.0 - 2.0 * ypos / height; 

        printf("%f %f -> %f %f\n", xpos, ypos, normalizedX, normalizedY);

        if (normalizedX >= btn1.xPos && normalizedX <= btn1.xPos + btn1.width &&
            normalizedY <= btn1.yPos && normalizedY >= btn1.yPos - btn1.height) {
            // printMessage();
            randomizeSides();
        }
    }
}

int main(void) {
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // DATA INIT
    btn1.xPos = -0.95f;
    btn1.yPos = 0.95f;
    btn1.width = 0.2f;
    btn1.height = 0.1f;
    // DATA INIT

    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 8); // anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL major version to be 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor set to 3, which makes the version 3.3
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC OS only
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

    // int testRightSide[] = { ORANGE, RED, GREEN, WHITE, ORANGE, BLUE, YELLOW, ORANGE, WHITE };
    // int testLeftSide[] = { WHITE, RED, GREEN, RED, YELLOW, YELLOW, BLUE, WHITE, BLUE };
    // int testTopSide[] = { YELLOW, GREEN, ORANGE, RED, WHITE, YELLOW, RED, WHITE, RED };
    // memcpy(rightSide, testRightSide, sizeof(testRightSide));
    // memcpy(leftSide, testLeftSide, sizeof(testLeftSide));
    // memcpy(topSide, testTopSide, sizeof(testTopSide));

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        drawSide(RIGHT, rightSide);
        drawSide(LEFT, leftSide);
        drawSide(TOP, topSide);
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
