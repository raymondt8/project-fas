#include <stdlib>
/*
Holds the system information. Grid holds information on water saturation for each grid cell
*/

typedef struct{
  double viscosity;
  double density;
  double relative_permeability;
}Fluid_t;

typedef Fluid_t Fluid;



typedef struct{
  int x_step, x_size;
  int y_step, y_size;
  int z_step, z_size;
  int grid_size;

  double x_face;
  double y_face;
  double z_face;  

  double* saturation;
  double* pressure;
  //double* wells, reservoir;   

  union{
  struct Fluid_t fluid;
  }oil, water;

  double permeability;
  double porosity;
  double saturation_denominator;

}UniformGrid_t;

typedef UniformGrid_t* UnifromGrid

UniformGrid CreateUniformGrid(int x_step, int y_step, int x_step, double permeability, Fluid Wetting, Fluid NonWetting){
  UniformGrid result = (UniformGrid)calloc(sizeof(UniformGrid));
  result->grid_size = 1.0/(x_step*y_step*z_step);

  result->saturation = (UniformGrid)malloc(sizeof(double)result.grid_size);
  result->pressure = (UniformGrid)malloc(sizeof(double)result.grid_size);

  result->x_step = x_step;
  result->y_step = y_step;
  result->z_step = z_step;
  result->x_size = 1.0/x_step;
  result->y_size = 1.0/y_step;
  result->z_size = 1.0/z_step;

  result->x_face = y_step*z_step;
  result->y_face = x_step*z_step;
  result->z_face = x_step*y_step;

  result->permeability = permeability;

  result->oil.fluid.viscosity = NonWetting.viscosity;
  result->oil.fluid.density = NonWetting.density;
  result->oil.fluid.relative_permeability = NonWetting.relative_permeability;
  result->water.fluid.viscosity = Wetting.viscosity;
  result->water.fluid.density = Wetting.density;
  result->water.fluid.relative_permeability = Wetting.relative_permeability;
  result->saturation_denominator = 1 - result->water.fluid.relative_permeability - result->oil.fluid.relative_permeability;


  return result;
}

