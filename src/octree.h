#ifndef MYOCTREE_OCTREE_H_
#define MYOCTREE_OCTREE_H_
#include <stdio.h>
//#include <string.h>
#include <list>
#include "block.h"


namespace myoctree {


int block_counter;
int level;
class octree;
std::list<octree*> nodes;



//octree class
class octree {

	public:
	//default constructor
	octree() {

		for(int i=0; i<2; i++) { 
			for(int j=0; j<2; j++) { 
				for(int k=0; k<2; k++)  
					children[i][j][k] = NULL;	
			}
		}

		if(level==0)
			parent = NULL;

		//creating block to assign it to the data
		block new_block;
		block_data = &new_block;		

		//make current pointer point to the current object
		current = this;	
		nodes.push_back(current);
	}
	
	//parametrized constructor
	octree( double x1, double x2, double y1, double y2, double z1, double z2 ) : x_min(x1), x_max(x2), y_min(y1), y_max(y2), z_min(z1), z_max(z2)   {

		for(int i=0; i<2; i++) { 
			for(int j=0; j<2; j++) { 
				for(int k=0; k<2; k++)  
					children[i][j][k] = NULL;	
			}
		}

		if(level==0)
			parent = NULL;


		x_centre = (x_min + x_max ) / 2.0;
		y_centre = (y_min + y_max ) / 2.0;
		z_centre = (z_min + z_max ) / 2.0;
		

		//creating block to assign it to the data
		block new_block(x_min, x_max, y_min, y_max, z_min, z_max);
		block_data = &new_block;		


		//make current pointer point to the current object
		current = this;	
		nodes.push_back(current);
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
	
		//assign dimensions to newly created children	
		for(k=0; k<2; k++) { 
			for(j=0; j<2; j++) { 
				for(i=0; i<2; i++) {

					if(i==0) { 
						children[i][j][k]->block_data->x_min = this->x_min; 	
						children[i][j][k]->block_data->x_max = this->x_centre; 	
					}
					else {
						children[i][j][k]->block_data->x_min = this->x_centre; 	
						children[i][j][k]->block_data->x_max = this->x_max; 	
					} 
				
					if(j==0) {	
						children[i][j][k]->block_data->y_min = this->y_min;	
						children[i][j][k]->block_data->y_max = this->y_centre;	
					}
					else {
						children[i][j][k]->block_data->y_min = this->y_centre;	
						children[i][j][k]->block_data->y_max = this->y_max;	
					}
					
					if(k==0) {
						children[i][j][k]->block_data->z_min = this->z_min;	
						children[i][j][k]->block_data->z_max = this->z_centre;	
					}
					else {
						children[i][j][k]->block_data->z_min = this->z_centre;	
						children[i][j][k]->block_data->z_max = this->z_max;	
					}
				

					children[i][j][k]->block_data->calculate_grid_size();
					children[i][j][k]->block_data->calculate_centre();

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
	block *block_data;

	//pointer to the parent
	octree *parent;

	//pointer to the current node
	octree *current;

	//level in the tree
	int level;

	//siblings
	octree *siblings[7];

	//node's block dimensions - temporary variables
	double x_centre, y_centre, z_centre;
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;

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
