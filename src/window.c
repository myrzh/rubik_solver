#include <time.h>
#include <window.h>

#ifndef __APPLE__
sfd_Options openInputOpt = {
    .title = "Open Steps File",
    .filter_name = "Text Files (*.txt)",
    .filter = "*.txt",
};

sfd_Options saveInputOpt = {
    .title = "Save Steps File",
    .filter_name = "Text Files (*.txt)",
    .filter = "*.txt",
};

sfd_Options openCubeOpt = {
    .title = "Open LinearCube File",
    .filter_name = "Text Files (*.txt)",
    .filter = "*.txt",
};
#endif

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    int minSize = (width < height) ? width : height;
    glfwSetWindowSize(window, minSize, minSize);
    glViewport(0, 0, minSize, minSize);
}

void keyCallbackEscapeOnly(GLFWwindow* window, int key, int scancode,
                           int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        GLFWwindow* authorsWindow =
            glfwCreateWindow(700, 450, "Authors", NULL, NULL);
        if (!authorsWindow) {
            fprintf(stderr, "failed to create secondary window!\n");
            return;
        }
        glfwMakeContextCurrent(authorsWindow);
        glfwSetKeyCallback(authorsWindow, keyCallbackEscapeOnly);

        // glfwSetWindowAspectRatio(authorsWindow, 1, 1);

        GLTtext* text = gltCreateText();
        gltSetText(text, authorsText);
        int width, height;
        GLfloat xpos, ypos;

        currentWindow = AUTHORSWND;

        while (!glfwWindowShouldClose(authorsWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            gltInit();

            glfwGetWindowSize(authorsWindow, &width, &height);

            xpos = (width * 0.0f + width) / 2.0f;
            ypos = (height - height * 0.0f) / 2.0f;
            // printf("%f %f\n", xpos, ypos);

            gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            // gltDrawText2D(text, xpos, ypos, 1.0f);
            gltDrawText2DAligned(text, xpos, ypos, 1.0f, GLT_CENTER,
                                 GLT_CENTER);
            gltEndDraw();

            gltTerminate();

            // renderText(currentTextData, "Hello World", 0.5f, 0.5f, 25.0f,
            // colors[3]);

            glfwSwapBuffers(authorsWindow);
            glfwPollEvents();
        }

        currentWindow = MAINWND;

        gltDeleteText(text);
        // gltTerminate();
        // glDeleteProgram(currentTextData.shaderData);
        glfwDestroyWindow(authorsWindow);
        glfwMakeContextCurrent(window);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        printTime = 1;
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        double normalizedX = -1.0 + 2.0 * xpos / width;
        double normalizedY = 1.0 - 2.0 * ypos / height;

// printf("%f %f -> %f %f\n", xpos, ypos, normalizedX, normalizedY);

// char inputFilename[50] = "input.txt";
// char inputFilename[50];
// char cubeFilename[50] = "cube1.txt";
// char cubeFilename[50];
#ifdef __APPLE__
        char filename[256];
#else
        char* filenamePointer;
#endif

        switch (currentWindow) {
            case MAINWND:
                for (int i = 0;
                     i < sizeof(mainButtons) / sizeof(mainButtons[0]); i++) {
                    if (normalizedX >= mainButtons[i].xPos &&
                        normalizedX <=
                            mainButtons[i].xPos + mainButtons[i].width &&
                        normalizedY <= mainButtons[i].yPos &&
                        normalizedY >=
                            mainButtons[i].yPos - mainButtons[i].height) {
                        switch (mainButtons[i].function) {
                            case REVERT:
                                initLinearCube(&Cube2D);
                                linearToMatrixCube(&Cube3D, &Cube2D);
                                break;
                            case ROTATE_SIDE:
                                switch (button) {
                                    case GLFW_MOUSE_BUTTON_LEFT:
                                        cubeDoOp(&Cube3D,
                                                 getRotationFromColor(
                                                     mainButtons[i].color));
                                        matrixToLinearCube(&Cube2D, &Cube3D);
                                        // renderMatrixCube(&Cube3D);
                                        // rotateLinearSideBy90(&Cube2D,
                                        // mainButtons[i].color, STRAIGHT);
                                        break;
                                    case GLFW_MOUSE_BUTTON_RIGHT:
                                        for (int count = 0; count < 3;
                                             count++) {
                                            cubeDoOp(&Cube3D,
                                                     getRotationFromColor(
                                                         mainButtons[i].color));
                                            matrixToLinearCube(&Cube2D,
                                                               &Cube3D);
                                        }
                                        // rotateLinearSideBy90(&Cube2D,
                                        // mainButtons[i].color, BACK);
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
                                filenamePointer =
                                    sfd_open_dialog(&openInputOpt);
                                if (filenamePointer) {
                                    printf("got steps file: '%s'\n",
                                           filenamePointer);
                                }
                                fillStepsFromFile(filenamePointer);
                                // free(filenamePointer);
#endif
                                break;
                            case SOLVECUBE:
                                strcpy(currentStepText, "PLEASE WAIT");
#ifdef __APPLE__
                                printf("enter steps filename: ");
                                fgets(filename, sizeof(filename), stdin);
                                filename[strcspn(filename, "\n")] = '\0';
                                if (strlen(filename) != 0) {
                                    printf("got steps file: '%s'\n", filename);
                                }
                                tempCube3D = Cube3D;
                                FILE* foutput = fopen(filename, "w");
                                if (foutput == NULL) {
                                    printf("can't open output file!\n");
                                    strcpy(currentStepText, "");
                                    break;
                                }
                                cubeSolve(&tempCube3D, foutput, filename);
                                fclose(foutput);
                                fillStepsFromFile(filename);
#else
                                filenamePointer =
                                    sfd_save_dialog(&saveInputOpt);
                                if (filenamePointer) {
                                    printf("got steps file: '%s'\n",
                                           filenamePointer);
                                }
                                tempCube3D = Cube3D;
                                FILE* foutput = fopen(filenamePointer, "w");
                                if (foutput == NULL) {
                                    printf("can't open output file!\n");
                                    strcpy(currentStepText, "");
                                    break;
                                }
                                clock_t start =
                                    clock();  // start measuring time
                                cubeSolve(&tempCube3D, foutput,
                                          filenamePointer);
                                clock_t end = clock();  // end measuring time
                                printf("cubesolve took %0.f ms to execute\n",
                                       ((double)(end - start)) /
                                           (CLOCKS_PER_SEC / 1000));
                                fprintf(logFile,
                                        "cubesolve took %0.f ms to execute\n",
                                        ((double)(end - start)) /
                                            (CLOCKS_PER_SEC / 1000));
                                fclose(foutput);
                                fillStepsFromFile(filenamePointer);
#endif
                                break;
                            case SHUFFLE:
                                randCube(&Cube3D, 52);
                                matrixToLinearCube(&Cube2D, &Cube3D);
                                break;
                            default:
                                break;
                        }
                    }
                }
                break;
            case FLATWND:
                for (int i = 0;
                     i < sizeof(flatButtons) / sizeof(flatButtons[0]); i++) {
                    if (normalizedX >= flatButtons[i].xPos &&
                        normalizedX <=
                            flatButtons[i].xPos + flatButtons[i].width &&
                        normalizedY <= flatButtons[i].yPos &&
                        normalizedY >=
                            flatButtons[i].yPos - flatButtons[i].height) {
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
                                filenamePointer = sfd_open_dialog(&openCubeOpt);
                                ;
                                if (filenamePointer) {
                                    printf("got cube file: '%s'\n",
                                           filenamePointer);
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
