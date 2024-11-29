#include <draw.h>

void initBuffers(GLuint* VAO, GLuint* VBO) {
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawStrokeLine(windowData* wndData, GLfloat x1, GLfloat y1, GLfloat x2,
                    GLfloat y2) {
    GLfloat vertices[] = {x1, y1, 0.0f, 0.0f, 0.0f, 0.0f,
                          x2, y2, 0.0f, 0.0f, 0.0f, 0.0f};

    glBindVertexArray(wndData->VAO_stroke);
    glBindBuffer(GL_ARRAY_BUFFER, wndData->VBO_stroke);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawStroke(GLfloat x, GLfloat y, cubeSide sideToDraw) {
    switch (sideToDraw) {
        case RIGHT:
            drawStrokeLine(&mainWndData, x, y, x + 0.173f, y + 0.1f);
            drawStrokeLine(&mainWndData, x + 0.173f, y + 0.1f, x + 0.173f, y - 0.1f);
            drawStrokeLine(&mainWndData, x + 0.173f, y - 0.1f, x, y - 0.2f);
            drawStrokeLine(&mainWndData, x, y - 0.2f, x, y);
            break;
        case LEFT:
            drawStrokeLine(&mainWndData, x, y, x - 0.173f, y + 0.1f);
            drawStrokeLine(&mainWndData, x - 0.173f, y + 0.1f, x - 0.173f, y - 0.1f);
            drawStrokeLine(&mainWndData, x - 0.173f, y - 0.1f, x, y - 0.2f);
            drawStrokeLine(&mainWndData, x, y - 0.2f, x, y);
            break;
        case TOP:
            drawStrokeLine(&mainWndData, x, y, x - 0.173f, y + 0.1f);
            drawStrokeLine(&mainWndData, x - 0.173f, y + 0.1f, x, y + 0.2f);
            drawStrokeLine(&mainWndData, x, y + 0.2f, x + 0.173f, y + 0.1f);
            drawStrokeLine(&mainWndData, x + 0.173f, y + 0.1f, x, y);
            break;
        default:
            break;
    }
}

void drawSquare(windowData* wndData, GLfloat x, GLfloat y, GLfloat r, GLfloat g,
                GLfloat b, cubeSide sideToDraw) {
    GLfloat vertices[24];
    if (sideToDraw == RIGHT) {
        GLfloat verticesTemp[] = {x,          y,        0.0f, r, g, b,
                                  x + 0.173f, y + 0.1f, 0.0f, r, g, b,
                                  x + 0.173f, y - 0.1f, 0.0f, r, g, b,
                                  x,          y - 0.2f, 0.0f, r, g, b};
        memcpy(vertices, verticesTemp, sizeof(vertices));
    } else if (sideToDraw == LEFT) {
        GLfloat verticesTemp[] = {x,          y,        0.0f, r, g, b,
                                  x - 0.173f, y + 0.1f, 0.0f, r, g, b,
                                  x - 0.173f, y - 0.1f, 0.0f, r, g, b,
                                  x,          y - 0.2f, 0.0f, r, g, b};
        memcpy(vertices, verticesTemp, sizeof(vertices));
    } else if (sideToDraw == TOP) {
        GLfloat verticesTemp[] = {
            x, y,        0.0f, r, g, b, x - 0.173f, y + 0.1f, 0.0f, r, g, b,
            x, y + 0.2f, 0.0f, r, g, b, x + 0.173f, y + 0.1f, 0.0f, r, g, b};
        memcpy(vertices, verticesTemp, sizeof(vertices));
    }

    glBindVertexArray(wndData->VAO_square);
    glBindBuffer(GL_ARRAY_BUFFER, wndData->VBO_square);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    drawStroke(x, y, sideToDraw);
}

void drawSide(cubeSide sideToDraw, color sideColors[]) {
    float currentColor[3];
    switch (sideToDraw) {
        case RIGHT:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[rightSideOrder[i]]],
                       sizeof(colors[sideColors[rightSideOrder[i]]]));
                drawSquare(&mainWndData, rightCoords[i][0], rightCoords[i][1],
                           currentColor[RED], currentColor[GREEN],
                           currentColor[BLUE], sideToDraw);
            }
            break;
        case LEFT:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[leftSideOrder[i]]],
                       sizeof(colors[sideColors[leftSideOrder[i]]]));
                drawSquare(&mainWndData, leftCoords[i][0], leftCoords[i][1],
                           currentColor[RED], currentColor[GREEN],
                           currentColor[BLUE], sideToDraw);
            }
            break;
        case TOP:
            for (int i = 0; i < 9; i++) {
                memcpy(currentColor, colors[sideColors[topSideOrder[i]]],
                       sizeof(colors[sideColors[topSideOrder[i]]]));
                drawSquare(&mainWndData, topCoords[i][0], topCoords[i][1],
                           currentColor[RED], currentColor[GREEN],
                           currentColor[BLUE], sideToDraw);
            }
            break;
        default:
            break;
    }
}

void drawButton(windowData* wndData, GLfloat x, GLfloat y, GLfloat width,
                GLfloat height, color colorName) {
    float currentColor[3];
    memcpy(currentColor, colors[colorName], sizeof(colors[colorName]));
    GLfloat vertices[] = {x,
                          y,
                          0.0f,
                          currentColor[RED],
                          currentColor[GREEN],
                          currentColor[BLUE],
                          x + width,
                          y,
                          0.0f,
                          currentColor[RED],
                          currentColor[GREEN],
                          currentColor[BLUE],
                          x + width,
                          y - height,
                          0.0f,
                          currentColor[RED],
                          currentColor[GREEN],
                          currentColor[BLUE],
                          x,
                          y - height,
                          0.0f,
                          currentColor[RED],
                          currentColor[GREEN],
                          currentColor[BLUE]};

    glBindVertexArray(wndData->VAO_button);
    glBindBuffer(GL_ARRAY_BUFFER, wndData->VBO_button);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawUI() {
    for (int i = 0; i < sizeof(mainButtons) / sizeof(mainButtons[0]); i++) {
        drawButton(&mainWndData, mainButtons[i].xPos, mainButtons[i].yPos,
                   mainButtons[i].width, mainButtons[i].height,
                   mainButtons[i].color);
    }
}

void drawFlatWindowUI() {
    for (int i = 0; i < sizeof(flatButtons) / sizeof(flatButtons[0]); i++) {
        drawButton(&flatWndData, flatButtons[i].xPos, flatButtons[i].yPos,
                   flatButtons[i].width, flatButtons[i].height,
                   flatButtons[i].color);
    }
}

void drawFlatSquare(windowData* wndData, GLfloat x, GLfloat y, GLfloat r,
                    GLfloat g, GLfloat b) {
    GLfloat vertices[] = {x,         y,         0.0f, r, g, b,
                          x + 0.15f, y,         0.0f, r, g, b,
                          x + 0.15f, y - 0.15f, 0.0f, r, g, b,
                          x,         y - 0.15f, 0.0f, r, g, b};

    glBindVertexArray(wndData->VAO_square);
    glBindBuffer(GL_ARRAY_BUFFER, wndData->VBO_square);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawFlatSide(GLfloat x, GLfloat y, color sideToDraw, color sideColors[]) {
    int squareCount = 0;
    float currentColor[3];
    for (float j = y; j > (y - 0.35f); j -= 0.15f) {
        for (float i = x; i < (x + 0.35f); i += 0.15f) {
            switch (sideToDraw) {
                case BLUE:
                    memcpy(
                        currentColor,
                        colors[sideColors[flatBlueSideOrder[squareCount]]],
                        sizeof(
                            colors
                                [sideColors[flatBlueSideOrder[squareCount]]]));
                    break;
                case ORANGE:
                    memcpy(
                        currentColor,
                        colors[sideColors[flatOrangeSideOrder[squareCount]]],
                        sizeof(colors[sideColors
                                          [flatOrangeSideOrder[squareCount]]]));
                    break;
                case WHITE:
                    memcpy(
                        currentColor,
                        colors[sideColors[flatWhiteSideOrder[squareCount]]],
                        sizeof(
                            colors
                                [sideColors[flatWhiteSideOrder[squareCount]]]));
                    break;
                case RED:
                    memcpy(
                        currentColor,
                        colors[sideColors[flatRedSideOrder[squareCount]]],
                        sizeof(
                            colors[sideColors[flatRedSideOrder[squareCount]]]));
                    break;
                case YELLOW:
                    memcpy(
                        currentColor,
                        colors[sideColors[flatYellowSideOrder[squareCount]]],
                        sizeof(colors[sideColors
                                          [flatYellowSideOrder[squareCount]]]));
                    break;
                case GREEN:
                    memcpy(
                        currentColor,
                        colors[sideColors[flatGreenSideOrder[squareCount]]],
                        sizeof(
                            colors
                                [sideColors[flatGreenSideOrder[squareCount]]]));
                    break;
                default:
                    break;
            }
            drawFlatSquare(&flatWndData, i, j, currentColor[RED],
                           currentColor[GREEN], currentColor[BLUE]);
            squareCount++;
        }
    }
}
