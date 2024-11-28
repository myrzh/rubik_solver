#ifndef WINDOW_H
#define WINDOW_H

#include <objects.h>
#include <rubik_solver.h>
#include <stdio.h>
#include <interface.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void keyCallbackEscapeOnly(GLFWwindow* window, int key, int scancode,
                           int action, int mods);

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods);

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

#endif
