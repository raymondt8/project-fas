#include <stdlib.h>
#include <stdio.h>
typedef struct{
    float density;
    float
}phase_t;

typedef struct{
    float permeability;
    float pressure;
    float density;
    float saturation;
    float source = 0.0;
    float arealXDir;
    float arealYDir;
}gridCell_t;

typedef struct{
    float xSize;
    float ySize;
    gridCell_t *mesh;
    float hight;
    float width;
}grid_t;
typedef grid_t *Grid;

Grid generateUniformGrid(int xSize, int ySize){
    Grid result = (Grid)malloc(sizeof(grid_t));
    result->xSize = xSize;
    result->ySize = ySize;
    result->mesh = (gridCell_t)malloc(sizeof(gridCell_t)*xSize*ySize);
    result->hight = 1.0/ySize;
    result->width = 1.0/xsize;
}

float cellPermeability{

}

float transmissibility{

}

float phaseMobility{

}

void finiteVolume(Grid grid){
    float flow
}
