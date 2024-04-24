#include <stdio.h>
#include "shaders.h"

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
    // и приложение после этого закроется
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {	
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Инициализация GLFW
	glfwInit();
	// Настройка GLFW
	// Задается минимальная требуемая версия OpenGL. 
	// Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "RubikSolver", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);

    // SHADERS START
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // SHADERS END

    GLfloat vertices[] = {
         0.0f, 0.0f, 0.0f,
         0.17f, 0.09f, 0.0f,
         0.34f, 0.19f, 0.0f,
         0.5f, 0.28f, 0.0f,

         0.0f, -0.18f, 0.0f,
         0.17f, -0.1f, 0.0f,
         0.34f, 0.0f, 0.0f,
         0.5f, 0.09f, 0.0f,

         0.0f, -0.38f, 0.0f,
         0.17f, -0.3f, 0.0f,
         0.34f, -0.19f, 0.0f,
         0.5f, -0.1f, 0.0f,

         0.0f, -0.58f, 0.0f,
         0.17f, -0.48f, 0.0f,
         0.34f, -0.38f, 0.0f,
         0.5f, -0.28f, 0.0f
    };

    GLfloat vertices2[] = {
         0.0f, 0.0f, 0.0f,
         -0.17f, 0.09f, 0.0f,
         -0.34f, 0.19f, 0.0f,
         -0.5f, 0.28f, 0.0f,

         0.0f, -0.18f, 0.0f,
         -0.17f, -0.1f, 0.0f,
         -0.34f, 0.0f, 0.0f,
         -0.5f, 0.09f, 0.0f,

         0.0f, -0.38f, 0.0f,
         -0.17f, -0.3f, 0.0f,
         -0.34f, -0.19f, 0.0f,
         -0.5f, -0.1f, 0.0f,

         0.0f, -0.58f, 0.0f,
         -0.17f, -0.48f, 0.0f,
         -0.34f, -0.38f, 0.0f,
         -0.5f, -0.28f, 0.0f
    };    

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 4,
        1, 4, 5,

        1, 2, 5,
        2, 5, 6,

        2, 3, 6,
        3, 6, 7,

        4, 5, 8,
        5, 8, 9,

        5, 6, 9,
        6, 9, 10,

        6, 7, 10,
        7, 10, 11,

        8, 9, 12,
        9, 12, 13,

        9, 10, 13,
        10, 13, 14,

        10, 11, 14,
        11, 14, 15
    };
    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO


    // Uncommenting this call will result in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
