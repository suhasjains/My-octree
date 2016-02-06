#include "octree.h"

namespace myoctree {

//std::list<octree*> nodes;
std::vector<octree*> nodes;
int Block::iNx = NX_BLOCK;
int Block::iNy = NY_BLOCK;
int Block::iNz = NZ_BLOCK;

}


using namespace myoctree;

int main(int argc, char **argv) {

	octree root1(0.0,1.0,0.0,1.0,0.0,1.0,0);

	//root1.refine();

	printf("level=%d\n",nodes[0]->level);

	write_vtk(nodes);

}

