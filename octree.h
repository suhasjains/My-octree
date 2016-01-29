#ifndef MYOCTREE_OCTREE_H_
#define MYOCTREE_OCTREE_H_

namespace myoctree {


	class octree {

		//octree has upto 8 children (2^3 for 3 dimensions) 
		octree *children[2][2][2];
		
		//each node stores a block of grid cells
		data *block;


}
#endif
