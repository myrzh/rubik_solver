#ifndef OBJECTS_H
#define OBJECTS_H
#include <colors.h>
extern const float rightCoords[][2];
extern const float leftCoords[][2];
extern const float topCoords[][2];
// extern const int rightSideOrder[];
// extern const int leftSideOrder[];
// extern const int topSideOrder[];
extern const int rightSideOrder[];
extern const int leftSideOrder[];
extern const int topSideOrder[];
// extern const int flatLevelOneSideOrder[];
// extern const int flatLevelTwoSideOrder[];
// extern const int flatLevelThreeSideOrder[];
extern const int flatBlueSideOrder[];
extern const int flatOrangeSideOrder[];
extern const int flatWhiteSideOrder[];
extern const int flatRedSideOrder[];
extern const int flatYellowSideOrder[];
extern const int flatGreenSideOrder[];
typedef enum { REVERT, ROTATE_SIDE, NEXTSTEP, FILLCUBE, SETCOLOR, GETFILECUBE, OPENSTEPSFILE, SOLVECUBE, SHUFFLE } buttonFunction;
typedef struct {
float xPos;
float yPos;
float width;
float height;
color color;
buttonFunction function;
} Button;
float NDCToPixels(float coord, int dimension, char mode);
void initButtons(Button mainButtons[], Button flatButtons[]);
extern const char* authorsText;
#endif