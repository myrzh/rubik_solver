#ifndef ALGO_H
#define ALGO_H
#define HORIZONTALUP 1
#define VERTICALUP 3
#define HORIZONTALDOWN -1
#define VERTICALDOWN -3
#define LASTOP -1
#define LENARR 500
#define TABLESIZE 16777216
#define SMALLSTEPSCOUNT 19
typedef struct Cube {
char front[3][3];
char back[3][3];
char left[3][3];
char right[3][3];
char up[3][3];
char down[3][3];
char operation;
struct Cube* previousState;
} Cube;
typedef struct {
int shift;
char* line;
} CubeLine;
typedef struct {
int openCubes;
int closedCubes;
int size;
Cube* cubes;
} SolutionTable;
typedef enum
{
FRONTROTATE, BACKROTATE, UPROTATE, DOWNROTATE, LEFTROTATE, RIGHTROTATE
} rotationType;
typedef struct {
char op;
char count;
} OperationPrint;
enum
{
FIRSTSTEP1, FIRSTSTEP2, SECONDSTEP, THIRDSTEP, FOURTHSTEP, FIFTHSTEP, SIXTHSTEP, SEVENTHSTEP
};
void initCube(Cube* thisCube);
void rotateSideBy90(char panel[3][3]);
void rotateOtherSides(CubeLine sides[5]);
void cubeFrontRotate(Cube* thisCube);
void cubeBackRotate(Cube* thisCube);
void cubeUpRotate(Cube* thisCube);
void cubeDownRotate(Cube* thisCube);
void cubeLeftRotate(Cube* thisCube);
void cubeRightRotate(Cube* thisCube);
void cubeDoOp(Cube* thisCube, int op);
void randCube(Cube* thisCube, int n);
int checkIfCrossFront(Cube* thisCube);
int checkIfCrossSides(Cube* thisCube);
int checkIfCornersFront(Cube* thisCube);
int checkIfMiddleRow(Cube* thisCube);
int checkIfBackCross(Cube* thiscube);
int checkIfBackSide(Cube* thisCube);
int checkIfBackCorners(Cube* thisCube);
int checkIfBackRow(Cube* thisCube);
int doCheck(Cube* thisCube, int op);
int checkAllCube(Cube* thisCube, int flag);
void createTable(SolutionTable* table, int size);
void deleteTable(SolutionTable* table);
int checkIfSameOps(Cube* thisCube);
int cutTheWay(int newvalue, int cutvalue);
Cube* search(SolutionTable* table, Cube* startCube, int state, char* operlist, int opernum, int cutvalue);
void setOpToChar(OperationPrint* ops, int countops, char lastop);
void setCountToChar(OperationPrint* ops, int countops, char rotatecounts);
void printOpToFile(Cube* thisCube, FILE* foutput);
void cubeSolve(Cube* thisCube, FILE* foutput, char filename[]);
void testInit(Cube* c);
#endif