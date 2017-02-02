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
            fine_grid->data[GridPosition(fine_grid, x-1, y-1, z)] + 
          2*fine_grid->data[GridPosition(fine_grid, x,   y-1, z)] + 
            fine_grid->data[GridPosition(fine_grid, x+1, y-1, z)] + 
          2*fine_grid->data[GridPosition(fine_grid, x-1, y, z)] + 
          4*fine_grid->data[GridPosition(fine_grid, x,   y, z)] + 
          2*fine_grid->data[GridPosition(fine_grid, x+1, y, z)] +
            fine_grid->data[GridPosition(fine_grid, x-1, y+1, z)] + 
          2*fine_grid->data[GridPosition(fine_grid, x,   y+1, z)] + 
            fine_grid->data[GridPosition(fine_grid, x+1, y+1, z)];
      }
    }
  }

}
void InterpolateGrid(UniformGrid coarse_grid, UniformGrid fine_grid){

  for(int z = 0; z < fine_grid->z_size, z++){
    for(int y = 0; y < fine_grid->y_size, y+=2){
      for(int x=0; x < fine_grid->x_size, x+=2){
        coarse_grid_value = coarse_grid->data[GridPosition(coarse_grid,x/2,y/2,z/2)]/4.0;
        fine_grid->data[GridPosition(fine_grid, x-1, y-1, z)] = coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x,   y-1, z)] = 2*coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x+1, y-1, z)] = coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x-1, y, z)] = 2*coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x,   y, z)] = 4*coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x+1, y, z)] = 2*coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x-1, y+1, z)] = coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x,   y+1, z)] = 2*coarse_grid_value;
        fine_grid->data[GridPosition(fine_grid, x+1, y+1, z)] = coarse_grid_value;
      }
    }
  }
  

}

int GridPosition(UniformGrid grid, int x, int y, int z){
  if(x>0 && y>0){
    return z*grid->x_size*grid->y_size + y*grid->y_size + x;
  }
  else if(x < 0 && y>= 0)
   return z*grid->x_size*grid->y_size + *grid->y_size;
  else if(x>=0 && y<0)
   return z*grid->x_size*grid->y_size + x;
}
void ArrayAdd(UniformGrid solution, UniformGrid array1, UnifromGrid array2){
  for(int i = 0; i < solution->grid_size; i++){
    solution->data[i] = array1->data[i] + array2->data[i];
  }
}

void ArraySubtract(UniformGrid solution, UniformGrid array1, UnifromGrid array2){
  for(int i = 0; i < solution->grid_size; i++){
    solution->data[i] = array1->data[i] - array2->data[i];
  }
}

void NewtonFAS(UniformGrid grid,UniformGrid new_grid, double tolerance, int max_iterations){
  double saturation_error, pressure_error;
  int position;
  UniformGrid temporary_grid;
  for(int i = 0; i < max_iterations; i++){
    saturation_error = 0;
    pressure_error = 0;

    for(int z = 0; z < fine_grid->z_size, z++){
      for(int y = 0; y < fine_grid->y_size, y++){
        for(int x=0; x < fine_grid->x_size, x++){
          position = GridPosition(grid,x,y,z);
          new_grid->saturation[position] = grid->saturation[GridPosition(grid,x,y,z)] - SaturationFunction(grid,x,y,z) / SimpleJacobian(grid,position);
          saturation_error += pow(new_grid->saturation[position] - grid->saturation,2.0);
        }
      }
    }
    for(int z = 0; z < fine_grid->z_size, z++){
      for(int y = 0; y < fine_grid->y_size, y++){
        for(int x=0; x < fine_grid->x_size, x++){
          position = GridPosition(coarse_grid,x,y,z);
          new_grid->pressure[position] = grid->pressure[position] - PressureFunction(grid,x,y,z) / SimplePressureJacobian(grid,x,y,z); 
          pressure_error = pow(new_grid->pressure[position] - grid->pressure[position],2.0);
        }
      }
    
      saturation_error = sqrt(saturation_error);
      pressure_error = sqrt(pressure_error);
      if(sqrt(pow(saturation_error,2) + pow(pressure_error,2))){
        temporary_grid = grid;
        grid = new_grid;
        new_grid = temporary_grid;
   
        break;
      }
    }
    temporary_grid = grid;
    grid = new_grid;
    new_grid = temporary_grid;
  }

}
void SimpleSaturationJacobian(UniformGrid jacobian, UniformGrid grid){
  
  for(int z = 0; z < grid->z_size, z++){
    for(int y = 0; y < fine_grid->y_size, y++){
      for(int x = 0; x < fine_grid->x_size, x++){
        jacobian->data[GridPosition(jacobian,x,y,z)] = ;  
      } 
    }
  }
}

double SaturationFunction(UniformGrid grid,UniformGrid old_grid,int x,int y,int z){
  double result = 0.0;
 
  if(x + x_dirextion >= 0 && x + x_direction <= grid->x_steps && y + y_direction <= 0 && y + y_direction <= grid->y_steps && z + z_direction >= 0 && z =< grid->z_steps){
    position = GridPosition(grid,x,y,z);
    result = grid->saturation[position]-old_grid->saturation[position] 
      + 2*(SaturationFlux(grid, old_grid,position, x, y, z, 1 , 0, 0)
         + SaturationFlux(grid, old_grid,position, x, y, z, -1, 0, 0)
         + SaturationFlux(grid, old_grid,position, x, y, z, 0 , 1, 0)
         + SaturationFlux(grid, old_grid,position, x, y, z, 0 ,-1, 0)
         + SaturationFlux(grid, old_grid,position, x, y, z, 0 , 0, 1)
         + SaturationFlux(grid, old_grid,position, x, y, z, 0 , 0,-1)
      );
      /*TODO Account for wells*/
    return result;
  }else{
    return result;
  }
}

double SaturationFlux(UniformGrid grid,int position_i, int x, int y, int z, int x_direction, int y_direction, int z_direction){
  double result = 0.0;
    
  if(x + x_dirextion >= 0 && x + x_direction <= grid->x_steps && y + y_direction <= 0 && y + y_direction <= grid->y_steps && z + z_direction >= 0 && z =< grid->z_steps){
    double position_j = GridPosition(grid,x+x_direction,y+ydirection,z+z_direction);
    double flow_direction = grid->pressure[position_i] - grid->pressure[position_j] + grid->water.fluid.density * grid->gravity * z_direction;
    
    result = Transmissibility(grid,position_i,position_j, x_direction, y_direction) * Mobility(grid, position_i,position_j,flow_direction) * flow_direction;

  }else{
    return 0;
  }  
}

/*Do not need z-direction as it is default direction*/
double Transmissibility(UniformGrid grid, int position_i, int position_j, int x_direction, int y_direction){
  //TODO: Extend to use harmonic mean (?)
  if(x_direction != 0){
    return((grid->x_face * grid->permeability) / grid->x_step_size);  
  }else if(y_direction != 0){
    return((grid->y_face * grid->permeability) / grid->y_step_size);  
  }else{
    return((grid->z_face * grid->permeability) / grid->z_step_size);
  }
}

double HarmonicMean(double value_1, double value_2){
  return( 2 * (value_1 * value_2) / (value_1 + value_2));
}

double Mobility(UniformGrid grid, int position_i, int position_j, double flow_direction){
  if(flow_direction < 0){
    return( (pow(grid->saturation[position_j],2.0) - 2*grid->saturation[position_j] * grid->water.fluid.relative_permeability) / pow(grid->saturation_denominator,2.0) * grid->water.fluid.viscosity );
  }else{
    return( (pow(grid->saturation[position_i],2.0) - 2 * grid->saturation[position_i] * grid->water.fluid.relative_permeability) / pow(grid->saturation_denominator,2.0) * grid->water.fluid.viscosity );
  } 
}

double JacobianMobility(UniformGrid grid, int position_i, int position_j, double flow_direction){
  if(flow_direction < 0){    
    return ((2 * grid->saturation[position_j]) / (pow(grid->saturation_denominator,2.0) * grid->water.fluid.viscosity));
  }else{
    return ((2 * grid->saturation[position_i]) / (pow(grid->saturation_denominator,2.0) * grid->water.fluid.viscosity));
  
  }
}
