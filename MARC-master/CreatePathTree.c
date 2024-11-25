#include "CreatePathTree.h"

void createPathTree(int currentLayer, int maxLayer, t_map*  map, t_move* moves, int nbMoves, t_localisation* loc, char* usedMoves, t_localisation* bestNode, char* bestMoves)
{
    printf("Current layer : %d\n", currentLayer);
    printf("(%d, %d)\n", loc->pos.x, loc->pos.y);
    //check this base case first
    if (isValidLocalisation(loc->pos, map->x_max, map->y_max) == 0)
    {
        printf("Invalid localisation %d, %d\n", loc->pos.x, loc->pos.y);
        return;
    }

    if (map->costs[loc->pos.y][loc->pos.x] >= 10000)
    {
        printf("Crevasse\n");
        return;
    }


    //Check others base case
    if (currentLayer >= maxLayer)
    {
        if (map->costs[loc->pos.y][loc->pos.x] < map->costs[bestNode->pos.y][bestNode->pos.x])
        {
            bestMoves = usedMoves;
            bestNode = loc;
        }
        printf("End of the tree\n");
        return;
    }

    if (map->costs[loc->pos.y][loc->pos.x] == 0 || map->costs[bestNode->pos.y][bestNode->pos.x] == 0)
    {
        bestMoves = usedMoves;
        bestNode = loc;
        printf("Best result found\n");
        return; 
    }

    // Check all cases of possible moves
    t_localisation newLoc = *loc;

    for (int i = 0; i < nbMoves; i++)
    {
        printf("move is %d\n", moves[i]);
        printf("i = %d\n", i);
        printArray(usedMoves, 9);
        if (usedMoves[i] != 0)
        { 
            printf("Move already used\n");
            continue;
        }
        usedMoves[i] = currentLayer + 1;

        if (moves[i] == F_10)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, F_10);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
        }

        else if (moves[i] == F_20)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, F_20);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
            else
                move(*loc, F_10);
        }

        else if (moves[i] == F_30)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, F_30);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
            else
                move(*loc, F_20);
        }
        else if (moves[i] == B_10)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, B_10); 
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
        }
        else if (moves[i] == T_LEFT)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, T_LEFT);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
        }
        else if (moves[i] == T_RIGHT)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, T_RIGHT);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
        }
        else if (moves[i] == U_TURN)
        {
            if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
            {
                newLoc = move(*loc, U_TURN);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
            else
            {   
                newLoc = move(*loc, T_RIGHT);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
                newLoc = move(*loc, U_TURN);
                createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestNode, bestMoves);
            }
        }
        usedMoves[i] = 0;
    }
}

void printArray(char* array, int size)
{
    printf("your array is : ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}