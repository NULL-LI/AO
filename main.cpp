#include "Mesh.h"

int main()
{	
	Mesh *mesh=new Mesh();
	mesh->addFlights("../../../pucks.csv");
	return EXIT_SUCCESS;
}
