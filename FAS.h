#ifndef FAS_H
#define FAS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

void ArrayAdd(
  UniformGrid solution,
  UniformGrid array1,
  UniformGrid array2
);

void ArraySubtract(
  UniformGrid solution,
  UniformGrid array1,
  UniformGrid array2
);
/*
Performs a spezialized Newton's Method for the FAS with FV as base discretization. Calls the Finite Volume Method as part of the procedure
*/
void NewtonFAS(
  UniformGrid grid,
  float tolerance,
  int max_iterations 
);
/*
Calculates the saturation function required in newtons method.
*/
double SaturationFunction(
  UniformGrid grid,
  UniformGrid old_grid,
  int x,
  int y,
  int z
);

double SaturationFlux(
  UniformGrid grid,
  int position_i,
  int x,
  int y,
  int z,
  int x_direction,
  int y_direction,
  int z_direction
);

double Transmissibility(
  UniformGrid grid, 
  int position_i, 
  int position_j, 
  int x_direction, 
  int y_direction
);

double HarmonicMean(
  double value_1, 
  double value_2
);

double Mobility(
  UniformGrid grid,
  int position_i,
  int position_j,
  int flow_direction
);

double JacobianMobility(
  UniformGrid grid,
  int position_i,
  int position_j,
  double flow_direction 
);

#endif 
