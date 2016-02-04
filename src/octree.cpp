#include "octree.h"

namespace myoctree {

int block_counter;
int level;
//std::list<octree*> nodes;
std::vector<octree*> nodes;
int block::iNx = NX_BLOCK;
int block::iNy = NY_BLOCK;
int block::iNz = NZ_BLOCK;

}


using namespace myoctree;

int main(int argc, char **argv) {


	octree root1(0.0,1.0,0.0,1.0,0.0,1.0);


	write_vtk(nodes);

	printf("hi");
}

