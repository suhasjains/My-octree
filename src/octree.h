#ifndef MYOCTREE_OCTREE_H_
#define MYOCTREE_OCTREE_H_
#include <stdio.h>
#include <string.h>
#include <list>

namespace myoctree {


int block_counter;
int level;
class octree;
class block;
class Field;
std::list<octree> blocks;


//Block class
class block {

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
                        **val = new double [Nx];
                        for(int i=0;i<Nx;i++) {
                                *val[i] = new double [Ny];
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
                        **val = new double [Nx];
                        for(int i=0;i<Nx;i++) {
                                *val[i] = new double [Ny];
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
                        memcpy(**val,**(obj.val),sizeof(double)*Nx);
                        for(int i=0;i<Nx;i++) {
                                memcpy(*val[i],*(obj.val)[i],sizeof(double)*Ny);
                                for(int j=0;j<Ny;j++) {
                                        memcpy(val[i][j],(obj.val)[i][j],sizeof(double)*Nz);
                                }
                        }
          	}
   		
   		
   		//Destructor
               ~Field() {

                       for (int i = 0; i < Nx; ++i) {
                               for (int j = 0; j < Ny; ++j)
                                       delete [] val[i][j];

                               delete [] *val[i];
                               }

                       delete [] **val;
               }

               private:
               protected:

       };

};


//octree class
class octree {

	public:
	//constructors
	octree() {

		for(int i=0; i<2; i++) { 
			for(int j=0; j<2; j++) { 
				for(int k=0; k<2; k++)  
					children[i][j][k] = NULL;	
			}
		}

		if(level==0)
			parent = NULL;

		block new_block;
	//	blocks.push_back(new_block);
		data = &new_block;		
	

		current = this;	

	}

	//member functions	
	void refine() {

		int i, j, k;
		
		//define new octree nodes	
		octree node[8];
	
		//assign newly created nodes to children 
		int local_node_count = 0;	
		for(k=0; k<2; k++) { 
			for(j=0; j<2; j++) { 
				for(i=0; i<2; i++) { 
					this->children[i][j][k] = &node[local_node_count];
					local_node_count++;	
				}
			}
		}

		//assigning each child its siblings
		int local_sibling_count;
		for(i=0; i<8; i++) {
			local_sibling_count = 0;
			for(j=0; j<8; j++) {
				if(i==j) continue;
				node[i].siblings[local_sibling_count] = &node[j]; 
				local_sibling_count++;
			}
		}

		//increment children level by 1 and parent to current node pointer
		for(i=0; i<8; i++) {
			node[i].level = level+1;
			node[i].parent = this;
		}
	
	}

	void coarsen() {

		//moving to its parent
		this->current = this->parent;

		//deleting all children
		for(int i=0; i<2; i++) { 
			for(int j=0; j<2; j++) { 
				for(int k=0; k<2; k++)  
					this->current->children[i][j][k] = NULL;	
			}
		}
		
		delete this;		
		
	}

	private:
	//each node has upto 8 children (2^3 for 3 dimensions) 
	octree *children[2][2][2];
	
	//each node stores a block of grid cells
	block *data;

	//pointer to the parent
	octree *parent;

	//pointer to the current node
	octree *current;

	//level in the tree
	int level;

	//siblings
	octree *siblings[7];

	//function to test if leaf node
	bool isLeafNode() {

		return children[0][0][0] == NULL;
	} 

	//function to test if root node
	bool isRootNode() {

		return parent == NULL;
	} 
			
	protected:	

};



}
#endif
