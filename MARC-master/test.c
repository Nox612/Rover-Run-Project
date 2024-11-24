#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "tree.h"
#include "map.h"

void createPathTree(int currentLayer, int maxLayer, t_map*  map, t_move* moves, int nbMoves, t_localisation* loc, char* usedMove, t_localisation* bestNode, char* bestMoves)
{
    //check this base case first
    if (map->costs[loc->pos.y][loc->pos.x] == 10000)
       return;

    // Create a tree with the current position as root
    t_node* root;
    root = CreateNode(map->costs[loc->pos.y][loc->pos.x]);

    //Check others base case
    if (currentLayer >= maxLayer)
    {
        if (map->costs[loc->pos.y][loc->pos.x] < map->costs[bestNode->pos.y][bestNode->pos.x])
        {
            bestMoves = usedMove;
            bestNode = root;
        }
        return;
    }

    if (map->costs[loc->pos.y][loc->pos.x] == 0)
    {
        bestMoves = usedMove;
        bestNode = root;
        return; 
    }

    // Check all cases of possible moves
    t_localisation newLoc = *loc;

    for (int i = 0; i < nbMoves; i++)
    {
        if (usedMove[i] != 0)
            continue;

        t_move currentMove = moves[nbMoves - 1];
        usedMove[i] = currentLayer + 1;
        nbMoves--;
        if (currentMove == F_10)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, F_10);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
        }

        else if (moves[i] == F_20)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, F_20);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
            else
                move(*loc, F_10);
        }

        else if (moves[i] == F_30)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, F_30);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
            else
                move(*loc, F_20);
        }
        else if (moves[i] == B_10)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, B_10); 
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
        }
        else if (moves[i] == T_LEFT)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, T_LEFT);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
        }
        else if (moves[i] == T_RIGHT)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, T_RIGHT);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
        }
        else if (moves[i] == U_TURN)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, U_TURN);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
            else
            {   
                newLoc = move(*loc, T_RIGHT);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
                newLoc = move(*loc, U_TURN);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMove, bestNode, bestMoves);
            }
        }
        usedMove[i] = 0;
    }
}

