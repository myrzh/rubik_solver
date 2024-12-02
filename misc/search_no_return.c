Cube *search(SolutionTable *table, Cube *startCube, int state, char *operlist,
             int opernum, int cutvalue) {
    Cube *newcube = NULL;
    Cube *currcube = NULL;
    int newstate = 0;
    int newvalue = 0;

    startCube->previousState = NULL;
    startCube->operation = LASTOP;

    if (checkAllCube(startCube, 0) >= state) {
        return startCube;
    }

    table->openCubes = 0;
    table->closedCubes = 0;

    table->cubes[table->openCubes] = *startCube;
    table->openCubes++;

    while (table->closedCubes < table->openCubes) {
        if (table->openCubes + 6 >= table->size - 1) {
            // all memory was used
            break;
        }

        currcube = &(table->cubes[table->closedCubes++]);

        for (int i = 0; i < opernum; i++) {
            newcube = &(table->cubes[table->openCubes]);
            memcpy(newcube, currcube, sizeof(Cube));
            cubeDoOp(newcube, operlist[i]);

            newcube->operation = operlist[i];
            newcube->previousState = currcube;

            newstate = checkAllCube(newcube, 0);
            newvalue = checkAllCube(newcube, state);
            if (newstate >= state) {
                table->openCubes = -1; // Mark as found
                break;
            }
            if (cutTheWay(newvalue, cutvalue) || checkIfSameOps(newcube)) {
                continue;
            }
            table->openCubes++;
        }

        if (table->openCubes == -1) {
            break;
        }
    }

    if (table->openCubes == -1) {
        return newcube;
    }
    return NULL;
}
