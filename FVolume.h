#ifndef FVOLUME_H
#define FVOLUME_H

#include <stdlib.h>
#include <stdio.h>
typedef struct{
    float xDir;
    float yDir;
}phaseFlow_t;

typedef struct{
    float dencity;
    float viscosity;
}phase_t;

typedef struct{
    float permeability;
    float pressure;
    phase_t density;
    float saturation;
    float source = 0.0;
    float arealXDir;
    float arealYDir;
    phaseFlow_t waterFlow, oilFlow;
}cell_t;

typedef struct{
    float xSize;
    float ySize;
    gridCell_t mesh[2];
    float height;
    float width;
    float delatZ = 1.0
    phase_t water, oil;
    float gravity = 9.819;//TODO: Update gravity constant
}grid_t;
typedef grid_t *Grid;

typedef struct{
    float *permeability; //Three dimentions
    float rnSaturation;
    float rwSaturation;
    float porosity;
}sediment_t;

Grid generateUniformGrid(int xSize, int ySize);
/*Allocates the grid. 
//TODO: change name to allocateUniformGrid ?
Input:
	xSize: size of mesh in x - direction
	ySize: size of mesh in y - direction
Output:
	result: final grid

*/

#endif
