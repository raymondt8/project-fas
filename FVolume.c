#include <stdlib.h>
#include <stdio.h>


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
    float *mesh;
    float hight;
    float width;
}grid_t;

float cellPermeability{

}

float transmissibility{

}

float phaseMobility{

}
