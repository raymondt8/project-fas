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
  int grid_step_size; 
  int x_steps, y_steps, z_steps;

  double x_step_size, y_step_size, z_step_size;
  double time_step;

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
  double volume;
}UniformGrid_t;

typedef UniformGrid_t* UnifromGrid

UniformGrid CreateUniformGrid(double time_step,int x_steps, int y_steps, int x_steps, double permeability, Fluid Wetting, Fluid NonWetting){
  UniformGrid result = (UniformGrid)calloc(step_sizeof(UniformGrid));
  result->grid_step_size = 1.0/(x_steps*y_steps*z_steps);

  result->saturation = (UniformGrid)malloc(step_sizeof(double)result.grid_step_size);
  result->pressure = (UniformGrid)malloc(step_sizeof(double)result.grid_step_size);

  result->x_steps = x_steps;
  result->y_steps = y_steps;
  result->z_steps = z_steps;
  result->x_step_size = 1.0/x_steps;
  result->y_step_size = 1.0/y_steps;
  result->z_step_size = 1.0/z_steps;

  result->x_face = y_steps*z_steps;
  result->y_face = x_steps*z_steps;
  result->z_face = x_steps*y_steps;

  result->permeability = permeability;

  result->oil.fluid.viscosity = NonWetting.viscosity;
  result->oil.fluid.density = NonWetting.density;
  result->oil.fluid.relative_permeability = NonWetting.relative_permeability;
  result->water.fluid.viscosity = Wetting.viscosity;
  result->water.fluid.density = Wetting.density;
  result->water.fluid.relative_permeability = Wetting.relative_permeability;
  result->saturation_denominator = 1 - result->water.fluid.relative_permeability - result->oil.fluid.relative_permeability;
  result->volume = porosity * result->x_step_size * result->y_step_size * result->z_step_size;
  result->time_step = time_step;
  return result;
}

