#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "tree.h"
#include "map.h"


void createPathTree(int currentLayer, int maxLayer, t_map*  map, t_move* moves, int nbMoves, t_localisation* loc, char* usedMoves, t_localisation* bestNode, char* bestMoves);

void printArray(char* array, int size);