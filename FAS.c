#include "FAS.h"

/*
NB! Current version only supports odd number of grid cells
*/

void RestrictGrid(UniformGrid coarse_Grid, UniformGrid fine_grid){
  coarse_grid = CreateUniformGrid(fine_grid->x_step/2.0, fine_grid->y_step/2.0, fine_grid->z_step, fine_grid->permeability);

  for(int z = 0; z < fine_grid->z_size, z++){
    for(int y = 0; y < fine_grid->y_size, y+=2){
      for(int x=0; x < fine_grid->x_size, x+=2){
        coarse_mesh->grid[GridPosition(coarse_grid, x/2, y/2, z)] = 1.0/16*(
            fine_mesh->grid[GridPosition(fine_grid, x-1, y-1, z)] + 
          2*fine_mesh->grid[GridPosition(fine_grid, x,   y-1, z)] + 
            fine_mesh->grid[GridPosition(fine_grid, x+1, y-1, z)] + 
          2*fine_mesh->grid[GridPosition(fine_grid, x-1, y, z)] + 
          4*fine_mesh->grid[GridPosition(fine_grid, x,   y, z)] + 
          2*fine_mesh->grid[GridPosition(fine_grid, x+1, y, z)] +
            fine_mesh->grid[GridPosition(fine_grid, x-1, y+1, z)] + 
          2*fine_mesh->grid[GridPosition(fine_grid, x,   y+1, z)] + 
            fine_mesh->grid[GridPosition(fine_grid, x+1, y+1, z)];
      }
    }
  }

}
void InterpolateGrid(UniformGrid coarse_grid, UniformGrid fine_grid){
  

}

int GridPosition(UniformGrid grid, int x, int y, int z){
  return z*grid->x_size*grid->y_size + y*grid->y_size + x;
}

