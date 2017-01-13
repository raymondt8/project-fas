#ifndef FAS_H
#define FAS_H

#include <stdlib.h>
#include <stdio.h>

/*
Computes the right hand side.
Input: 
    float *right_hand_side - float pointer to array where output is stored
    float *approximation - float pointer to solution approximation
Out:
    'void' - Result is stored in input array
*/
void ComputeDefect(
  float *right_hand_side,
  float *approximation
);

/*
Restricts the input by coarsening the grid.
Allocates a new grid and restricts the existing grid into the new grid
Input:
    float *coarse_grid - single float pointer where the new coarsened grid is allocated and stored
    float *fine_grid - grid array to be coarsened
Output:
    'void' - Resulting restricted grid is stored at input pointer  
*/
void RestrictGrid(
  UniformGrid coarse_grid, 
  UniformGrid fine_grid
);

void InterpolateGrid(
  UniformGrid coarse_grid, 
  UniformGrid fine_grid

);
/*
Returns the calculated position in the grid array. If point is beyond the border, the border point is given
*/
int GridPosition(
  UniformGrid grid,
  int x,
  int y,
  int z
);
#endif 
