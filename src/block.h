#include <string.h>

namespace myoctree {

#define PAD 2
#define NX_BLOCK 10
#define NY_BLOCK 10
#define NZ_BLOCK 10



//Field class
class Field {

        public:
        //Members
        int Nx,Ny,Nz;              //size
        int N;                  //size
        double ***val;            //values

        //Constructors
        //allocates memory to the field variables equal to the number of cells in the domain
        Field( int N_x, int N_y, int N_z ) : Nx(N_x), Ny(N_y), Nz(N_z) {

                N = N_x*N_y*N_z;
                val = new double** [Nx];
                for(int i=0;i<Nx;i++) {
                        val[i] = new double* [Ny];
                        for(int j=0;j<Ny;j++) {
                                val[i][j] = new double [Nz];
                        }
                }
        }

        Field() {

                Nx = 0;
                Ny = 0;
                Nz = 0;
                N = Nx*Ny*Nz;
                val = new double** [Nx];
                for(int i=0;i<Nx;i++) {
                        val[i] = new double* [Ny];
                        for(int j=0;j<Ny;j++) {
                                val[i][j] = new double [Nz];
                        }
                }
        }
 	
 	//Copy constructor
        Field(const Field &obj) {


                Nx = obj.Nx;
                Ny = obj.Ny;
                Nz = obj.Nz;
                N = obj.N;
                memcpy(val,obj.val,sizeof(double**)*Nx);
                for(int i=0;i<Nx;i++) {
                        memcpy(val[i],obj.val[i],sizeof(double*)*Ny);
                        for(int j=0;j<Ny;j++) {
                                memcpy(val[i][j],obj.val[i][j],sizeof(double)*Nz);
                        }
                }
        }
	

        //Destructor
        ~Field() {

                for (int i = 0; i < Nx; ++i) {
                        for (int j = 0; j < Ny; ++j)
                                delete [] val[i][j];

                        delete [] val[i];
                        }

                delete [] val;
        }

        private:
        protected:
	
};



//Block class
class block {

	public:

	Field *mesh;

	double x_centre, y_centre, z_centre;	
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;
	static int iNx;
	static int iNy;
	static int iNz;
	double dx, dy, dz;


	//parametrized constructor
	block( double x1, double x2, double y1, double y2, double z1, double z2 ) : x_min(x1), x_max(x2), y_min(y1), y_max(y2), z_min(z1), z_max(z2) {
		
		//dx = ( x_max - x_min ) / iNx; 
		//dy = ( y_max - y_min ) / iNy; 
		//dz = ( z_max - z_min ) / iNz; 

		dx = 1.0;
		dy = 2.0;
		dz = 3.0;
		
		printf("dx=%g, dy=%g, dz=%g \n", dx, dy, dz);
		

		x_centre = (x_min + x_max ) / 2.0;
                y_centre = (y_min + y_max ) / 2.0;
                z_centre = (z_min + z_max ) / 2.0;
		

		Field mesh_field(iNx+2*PAD,iNy+2*PAD,iNz+2*PAD);
		mesh = &mesh_field;

	}

	//default constructor
	block() {
	
		Field mesh_field(iNx+2*PAD,iNy+2*PAD,iNz+2*PAD);
		mesh = &mesh_field;	
	}

	//~block() {
		
		

	//}	
		
	//member function
	void calculate_grid_size() {

		this->dx = ( this->x_max - this->x_min ) / this->iNx; 
		this->dy = ( this->y_max - this->y_min ) / this->iNy; 
		this->dz = ( this->z_max - this->z_min ) / this->iNz; 
	}

	//member function
	void calculate_centre() {
		this->x_centre = (this->x_min + this->x_max ) / 2.0;
                this->y_centre = (this->y_min + this->y_max ) / 2.0;
                this->z_centre = (this->z_min + this->z_max ) / 2.0;
	}
};

//extern int block::iNx = NX_BLOCK;
//extern int block::iNy = NY_BLOCK;
//extern int block::iNz = NZ_BLOCK; 


}
