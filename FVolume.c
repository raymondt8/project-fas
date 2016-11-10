#include <FVolume.h>

Grid generateUniformGrid(int xSize, int ySize){
    Grid result = (Grid)malloc(sizeof(grid_t));
    result->xSize = xSize;
    result->ySize = ySize;
    result->mesh[0] = (cell_t)malloc(sizeof(cell_t)*xSize*ySize)
    result->mesh[1] = (cell_t)malloc(sizeof(cell_t)*xSize*ySize)
    result->hight = 1.0/ySize;
    result->width = 1.0/xsize;

    return result;
}

enum direction {NORTH, SOUTH, EAST, WEST};
void cellPermeability(Grid grid){

}

float transmissibility(Grid grid,int row, int col, rowDir, colDir){

    if(colDir == 0){
(grid->mesh[0][row*grid->Size + col].arealXDir/grid->width)*(2*grid->mesh[0][row*grid->Size + col].permeability*grid->mesh[0][(row+rowDir)*grid->Size + (col + colDir)])/(grid->mesh[0][row*grid->Size + col].permeability + grid->mesh[0][(row+rowDir)*grid->Size + (col + colDir)])  ;
 
}
    return(grid->mesh(row) );
}

float phaseMobility(){

}

float cellfaceFlow(Grid grid, row, col, rowDir, colDir ){
    float flow = 0.0;
    float phaseMobilityWater, phaseMobilityOil, facePermeability, transmissibility, facePressure; 
    phaseMobilityWater = 
    facePressureWater =abs(grid->mesh[0][row*grid->Size + col].pressure-grid->mesh[0][(row+rowDir)*grid->Size + (col+colDir)].pressure) - grid->water.density * grid->gravity * grid->deltaZ;
    
    facePermeability = (2*grid->mesh[0][row*grid->Size + col].permeability*grid->mesh[0][(row+rowDir)*grid->Size + (col + colDir)])/(grid->mesh[0][row*grid->Size + col].permeability + grid->mesh[0][(row+rowDir)*grid->Size + (col + colDir)])  ;
  
    if(rowDir !=0){
        flow =  ((grid->mesh[0][row*grid->Size + col].arealXDir/grid->width)*facePermeability*  ;
    }else{
        
    }
    return flow;
}

void finiteVolume(Grid grid){
    for(row = 0; row < grid->ySize;row++){
	for(col = 0; col < grid->xSize; col++){
	    //TODO: Test how usage of enum affects performance: enum direction {NORTH,...}
	    grid->mesh[1][row*grid->xSize + col] = cellfaceFlow(grid,row,col,0,1) + cellfaceFlow(grid,row, col,0,-1) + cellfaceFlow(grid,row,col,1,0) + cellfaceFlow(grid,row, col,-1,0);
	}
    }
}
