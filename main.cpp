
#include "Mesh.h"
#include "Graph.h"

int main()
{	
	shared_ptr<Mesh> mesh(new Mesh());
	printf("Start main\n");
	mesh->addFlights("../data/pucks.csv");
    mesh->addGates("../data/gates.csv");
	FlightList flight_nii;
	for(int i=0;i<mesh->flightListAll.size();i++){
		if(mesh->flightListAll[i]->plane_size==N  &&
		mesh->flightListAll[i]->type_arrive==I  &&
		mesh->flightListAll[i]->type_go==I){
			flight_nii.push_back(mesh->flightListAll[i]);
		}//end if
	}//end for
	cout<<"n_i_i:"<<flight_nii.size()<<endl;
	shared_ptr<Graph> graph(new Graph(flight_nii));
	graph->solve();
	for(int i=0;i<graph->path_list.size();i++){
		for(int j=0;j<graph->path_list[i].size();j++){
			cout<<graph->path_list[i][j]->time_go<<" ";
		}
		cout<<endl;
	}





	return EXIT_SUCCESS;
}
