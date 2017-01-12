#include <stdlib>
/*
Holds the system information. Grid holds information on water saturation for each grid cell
*/
typedef struct{
  int x_step, x_size;
  int y_step, y_size;
  int z_step, z_size;
  int grid_size;

  float permeability;
  float porosity;

  float* data;   
}UniformGrid_t;

typedef UniformGrid_t* UnifromGrid

typedef struct{
  float viscosity;
  float density;
}Fluid_t;

typedef Fluid_t Oil;
typedef fluid_t Water;

UniformGrid CreateUniformGrid(int x_step, int y_step, int x_step, float permeability){
  UniformGrid result = (UniformGrid)calloc(sizeof(UniformGrid));
  result->grid_size = 1.0/(x_step*y_step*z_step);

  result->data = (UniformGrid)malloc(sizeof(float)result.grid_size);

  result->x_step = x_step;
  result->y_step = y_step;
  result->z_step = z_step;
  result->x_size = 1.0/x_step;
  result->y_size = 1.0/y_step;
  result->z_size = 1.0/z_step;

  result->permeability = permeability;
  return result;
}

