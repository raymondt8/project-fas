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
          position = GridPosition(coarse_grid,x,y,z);
          new_grid->saturation[position] = grid->saturation[GridPosition(coarse_grid,x,y,z)] - saturationFlux(grid,position)/SimpleJacobian(grid,position);
          saturation_error += pow(new_grid->saturation[position] - grid->saturation,2.0);
        }
      }
    }
    for(int z = 0; z < fine_grid->z_size, z++){
      for(int y = 0; y < fine_grid->y_size, y++){
        for(int x=0; x < fine_grid->x_size, x++){
          position = GridPosition(coarse_grid,x,y,z);
          new_grid->pressure[position] = grid->pressure[position] - PressureFlux/SimplePressureJacobian; 
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
        jacobian->data[GridPosition(jacobian,x,y,z)] =;  
      } 
    }
  }
}
double SaturationFlux(UniformGrid grid,int x,int y,int z int x_direction,int y_direction,int z_direction){
  double result = 0.0;
  if(x_direction != 0 && x+x_direction <0 && x+x_direction >)
  result = grid->x_face*permeability*
  
  if(x + x_dirextion >= 0 && x + x_direction <= grid->x_steps && y + y_direction <= 0 && y + y_direction <= grid->y_steps && z + z_direction >= 0 && z =< grid->z_steps){
    position = GridPosition(grid,x,y,z);
    result = 
  }else{
    return 0.0;
  }
}

double Transmissibility(grid, int position_i int position_j, double flow_direction){

}

double Mobility(UniformGrid grid, int position_i, int position_j, double flow_direction){
  if(flow_direction < 0){
    return( (pow(grid->saturation[position_j],2.0) - 2*grid->saturation[position_j]*grid->water.fluid.relative_permeability)/pow(grid->saturation_denominator,2.0)*grid->water.fluid.viscosity );
  }else{
    return( (pow(grid->saturation[position_i],2.0) - 2*grid->saturation[position_i]*grid->water.fluid.relative_permeability)/pow(grid->saturation_denominator,2.0)*grid->water.fluid.viscosity );
  } 
}

double JacobianMobility(UniformGrid, int position_i, int position_j, double flow_direction){
  if(flow_direction<0){    
    return ((2*grid->saturation[position_j])/(pow(grid->saturation_denominator,2.0)*grid->water.fluid.viscosity));
  }else{
    return ((2*grid->saturation[position_i])/(pow(grid->saturation_denominator,2.0)*grid->water.fluid.viscosity));
  
  }
}
