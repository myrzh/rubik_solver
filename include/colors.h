#ifndef COLORS_H
#define COLORS_H
typedef enum { RED, GREEN, BLUE, WHITE, ORANGE, YELLOW, CYAN, PURPLE } color;
extern float colors[][3];
color getColorFromChar(char letter);
char getCharFromColor(color clr);
#endif