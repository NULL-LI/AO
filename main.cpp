
#include "Mesh.h"

int main()
{	
	Mesh *mesh=new Mesh();
	printf("Start main\n");
	mesh->addFlights("../../../pucks.csv");
	return EXIT_SUCCESS;
}
