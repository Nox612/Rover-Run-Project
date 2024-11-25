#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "CreatePathTree.h"
#include "moves.h"
#include "map.h"
#include "loc.h"
#include <stdlib.h>
#include <time.h>


/// move rover here

int main() {    
    srand(time(NULL));
    t_map map = createMapFromFile("./maps/example1.map");
    displayMap(map);
    int x = rand() % map.x_max;
    int y = rand() % map.y_max;
    t_localisation loc = loc_init(x, y, NORTH);
    t_move* moves = getRandomMoves(9); 
    char* usedMoves = (char*)malloc(9*sizeof(char));
    char* bestMoves = (char*)malloc(9*sizeof(char));
    for (int i = 0; i < 9; i++)
    {
        usedMoves[i] = 0;
        bestMoves[i] = 0;
    }
    t_localisation bestNode;
    if (map.soils[loc.pos.y][loc.pos.x] == CREVASSE)
    {
        printf("The robot is in a crevasse, it can't move\n");
        return 0;
    }
    int maxLayer = 5;
    if (map.soils[loc.pos.y][loc.pos.x] == REG)
    {
        maxLayer = 4;
    }
    createPathTree(0, maxLayer, &map, moves, 9, &loc, usedMoves, &bestNode, bestMoves);
    printArray(bestMoves, 9);
    return 0;
}
