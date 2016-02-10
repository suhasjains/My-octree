#include "octree.h"
#include "output.h"

namespace myOctree {

std::list<Octree*> nodes;
int Block::iNx = NX_BLOCK;
int Block::iNy = NY_BLOCK;
int Block::iNz = NZ_BLOCK;

}


using namespace myOctree;

int main(int argc, char **argv) {

	Octree root1(0.0,1.0,0.0,1.0,0.0,1.0,0);
	Octree root2(1.0,2.0,0.0,1.0,0.0,1.0,0);
	Octree root3(1.0,2.0,1.0,2.0,0.0,1.0,0);
	
	root2.refine();

	write_vtk(nodes);

}

