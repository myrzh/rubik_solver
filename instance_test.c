#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cubecoords.h"
#include "shaders.h"

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

typedef enum {RIGHT, LEFT, TOP} cubeSide;

unsigned int getShaderProgram() {
    // Compile and link shaders
    unsigned int vertexShader, fragmentShader, shaderProgram;
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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void drawSquare(GLfloat x, GLfloat y, cubeSide sideToDraw) {
    float vertices[12];
    if (sideToDraw == RIGHT) {
        float verticesTemp[] = {
            x, y, 0.0f,
            x + 0.17f, y + 0.09f, 0.0f,
            x + 0.17f, y - 0.1f, 0.0f,
            x, y - 0.17f, 0.0f
        };
        memcpy(vertices, verticesTemp, sizeof(vertices));
    } else if (sideToDraw == LEFT) {
        float verticesTemp[] = {
            x, y, 0.0f,
            x - 0.17f, y + 0.09f, 0.0f,
            x - 0.17f, y - 0.1f, 0.0f,
            x, y - 0.17f, 0.0f
        };
        memcpy(vertices, verticesTemp, sizeof(vertices));
    } else if (sideToDraw == TOP) {
        float verticesTemp[] = {
            x, y, 0.0f,
            x - 0.17f, y + 0.09f, 0.0f,
            x, y + 0.17f, 0.0f,
            x + 0.17f, y + 0.1f, 0.0f
        };
        memcpy(vertices, verticesTemp, sizeof(vertices));
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void drawSide(cubeSide sideToDraw) {
    switch (sideToDraw) {
        case RIGHT:
            for (int i = 0; i < 9; i++) {
                drawSquare(rightCoords[i][0], rightCoords[i][1], sideToDraw);
            }
            break;
        case LEFT:
            for (int i = 0; i < 9; i++) {
                drawSquare(leftCoords[i][0], leftCoords[i][1], sideToDraw);
            }
            break;
        case TOP:
            for (int i = 0; i < 9; i++) {
                drawSquare(topCoords[i][0], topCoords[i][1], sideToDraw);
            }
            break;
        default:
            break;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(800, 600, "RubikSolver", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    unsigned int shaderProgram = getShaderProgram();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        drawSide(RIGHT);
        drawSide(LEFT);
        drawSide(TOP);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
