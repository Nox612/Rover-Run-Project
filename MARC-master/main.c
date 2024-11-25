#include "CreatePathTree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// move rover here

int main()
{
  // srand(time(NULL));
  srand(0);
  t_map map = createMapFromFile("./maps/example1.map");
  displayMap(map);
  int x = rand() % map.x_max;
  int y = rand() % map.y_max;
  t_localisation loc = loc_init(x, y, NORTH);
  while (map.costs[loc.pos.y][loc.pos.x] != 0)
  {
    printf("> Start loop\n");
    t_move* moves = getRandomMoves(9);
    printArray(moves, 9);
    char bestMoves[5];
    for (int i = 0; i < 9; i++)
    {
      bestMoves[i] = 0;
    }
    t_localisation bestNode = loc;
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
    GetBestMoves(maxLayer, &map, moves, 5, &loc, bestMoves);
    printf("created tree\n");
    printArray(bestMoves, maxLayer);
    int i = 0;
    while (bestMoves[i] <= 5 && i < maxLayer)
    {
      loc = move(loc, bestMoves[i]);
      printf("Move is : %s, cost : %d\n", getMoveAsString(bestMoves[i]), map.costs[loc.pos.y][loc.pos.x]);
      i++;
    }
    printf("> End loop\n");
    free(moves);
  }
  printf("program ended\n");
  // Free map
  for (int i = 0; i < map.y_max; i++)
  {
    free(map.costs[i]);
    free(map.soils[i]);
  }
  free(map.costs);
  free(map.soils);
  printf("program freed\n");
  return 0;
}
