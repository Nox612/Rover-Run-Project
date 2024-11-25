#include "map.h"
#include "moves.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void GetBestMoves(int maxMoves, t_map* map, t_move* moves, int nbMoves, t_localisation* loc, char* bestMoves);

int createPathTree(int currentLayer, int maxLayer, t_map* map, t_move* moves, int nbMoves, t_localisation* loc,
                   char* usedMoves, char* bestMoves, int* bestScores);

void printArray(char* array, int size);
