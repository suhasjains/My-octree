#include "octree.h"
#include <stdio.h>

namespace myoctree {

//void write_vtk(std::list<octree*>& nodes) {
void write_vtk(std::vector<octree*>& nodes) {


	int Npx = NX_BLOCK + 1;
	int Npy = NY_BLOCK + 1;
	int Npz = NZ_BLOCK + 1;
	

	char filename[30];
        sprintf(filename, "output.vtk");
        FILE *fp = fopen(filename, "w");

        fprintf(fp,"# vtk DataFile Version 3.0\n");
        fprintf(fp,"particle point data\n");
        fprintf(fp,"ASCII\n");
        fprintf(fp,"DATASET STRUCTURED_GRID\n");
        fprintf(fp,"DIMENSIONS %d %d %d\n",Npx, Npy, Npz);
        fprintf(fp,"POINTS %d double\n", Npx * Npy * Npz);

	//for (std::list<octree*>::iterator iterator = nodes.begin(), end = nodes.end(); iterator != end; ++iterator) {
	for (int n = 0; n< nodes.size(); n++) {
    	
		//Block* block_data = (*iterator)->get_block_data();
		//printf("hi\n");
		Block* block_data = nodes[n]->block_data;
		//printf("hi\n");
		int N = nodes[n]->block_data->mesh->N;
		//printf("hi\n");
		double dx = block_data->dx;
		double dy = block_data->dy;
		double dz = block_data->dz;
		double x_min = block_data->x_min;		
		double y_min = block_data->y_min;		
		double z_min = block_data->z_min;		

		printf("dx=%g dy=%g, dz=%g N =%d\n", dx, dy, dz, N);

	        for(int k = 0; k<Npz; k++) {
	                for(int j = 0; j<Npy; j++) {
	                        for(int i = 0; i<Npx ; i++) {
	                                fprintf(fp,"%2.8lf %2.8lf %2.8lf\n",x_min + i*dx, y_min + j*dy, z_min + k*dz);
	                        }
	                }
	        }


	}
//	fclose(fp);
}

}
