
#include "Mesh.h"

int main()
{	
	Mesh *mesh=new Mesh();
	printf("Start main\n");
//	mesh->addFlights("../data/pucks.csv");

    mesh->addGates("../data/gates.csv");
	return EXIT_SUCCESS;
}
