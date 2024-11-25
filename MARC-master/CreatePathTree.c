#include "CreatePathTree.h"
#include "loc.h"
#include <string.h>

void GetBestMoves(int maxMoves, t_map* map, t_move* moves, int nbMoves, t_localisation* loc, char* bestMoves)
{
  char usedMoves[9];
  int bestScores[maxMoves];

  memset(usedMoves, 0, sizeof(usedMoves));
  memset(bestScores, -1, sizeof(bestScores));
  // for (int i = 0; i < maxMoves; i++)
  //{
  //   usedMoves[i] = 0;
  //   bestScores[i] = -1;
  // }

  createPathTree(0, maxMoves, map, moves, nbMoves, loc, usedMoves, bestMoves, bestScores);
  printf("Best scores: ");
  for (int i = 0; i < maxMoves; i++)
  {
    printf("%d ", bestScores[i]);
  }
  printf("\n");
}

int createPathTree(int currentLayer, int maxLayer, t_map* map, t_move* moves, int nbMoves, t_localisation* loc,
                   char* usedMoves, char* bestMoves, int* bestScores)
{
  // printf("Current layer : %d\n", currentLayer);
  // printf("(%d, %d)\n", loc->pos.x, loc->pos.y);
  //  check this base case first
  if (isValidLocalisation(loc->pos, map->x_max, map->y_max) == 0)
  {
    // printf("Invalid localisation %d, %d\n", loc->pos.x, loc->pos.y);
    return -1;
  }

  if (map->costs[loc->pos.y][loc->pos.x] >= 10000)
  {
    //    printf("Crevasse\n");
    return -1;
  }

  if (map->costs[loc->pos.y][loc->pos.x] == 0)
  {
    //   printf("Best result found\n");
    return 0; // End found
  }

  // Check others base case
  if (currentLayer >= maxLayer)
  {
    //   printf("End of the tree\n");
    return map->costs[loc->pos.y][loc->pos.x];
  }

  // Check all cases of possible moves
  t_localisation newLoc = *loc;

  bestMoves[currentLayer] = nbMoves + 1; // Represents uninitialized

  for (int i = 0; i < nbMoves; i++)
  {
    //  printf("move is %d\n", moves[i]);
    //  printf("i = %d\n", i);
    //  printf("usedMoves : ");
    //  printArray(usedMoves, 9);
    if (usedMoves[i] != 0)
    {
      //    printf("Move already used\n");
      continue;
    }

    // Set move as used
    usedMoves[i] = currentLayer + 1;

    // Do move
    if (moves[i] == F_10)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, F_10);
      }
    }

    else if (moves[i] == F_20)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, F_20);
      }
      else
        move(*loc, F_10);
    }

    else if (moves[i] == F_30)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, F_30);
      }
      else
        move(*loc, F_20);
    }
    else if (moves[i] == B_10)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, B_10);
      }
    }
    else if (moves[i] == T_LEFT)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, T_LEFT);
      }
    }
    else if (moves[i] == T_RIGHT)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, T_RIGHT);
      }
    }
    else if (moves[i] == U_TURN)
    {
      if (!(map->soils[loc->pos.y][loc->pos.x] == ERG))
      {
        newLoc = move(*loc, U_TURN);
      }
      else
      {
        continue;
        // TODO: Deal with mess once again
        newLoc = move(*loc, T_RIGHT);
        // Disgusting copy paste but works
        // int score = createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestMoves);
        // Found end, finish search
        // if (score == 0)
        //{
        //  bestMoves[currentLayer] = T_RIGHT;
        //  return 0;
        //}
        // Score is better (lesser) or bestScore is uninitialized
        // if ((score > 0 && score < bestScore) || bestScore < 0)
        //{
        //  // bestScore = score;
        //  bestMoves[currentLayer] = moves[i];
        //}

        newLoc = move(*loc, T_LEFT);
      }
    }

    int score =
      createPathTree(currentLayer + 1, maxLayer, map, moves, nbMoves, &newLoc, usedMoves, bestMoves, bestScores);
    // Found end, finish search
    if (score == 0)
    {
      bestMoves[currentLayer] = moves[i];
      return 0;
    }
    // Score is better (lesser) or bestScore is uninitialized
    if ((score > 0 && score < bestScores[currentLayer]) || bestScores[currentLayer] < 0)
    {
      bestScores[currentLayer] = score;
      bestMoves[currentLayer] = moves[i];
    }

    // Reset
    usedMoves[i] = 0;
  }
  return bestScores[currentLayer];
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
