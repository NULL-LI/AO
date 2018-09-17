
#include "Graph.h"
#include "Mesh.h"
#include "solution1.h"

int main() {
  shared_ptr<Mesh> mesh(new Mesh());
  printf("Start main\n");
  mesh->addFlights("../data/pucks.csv");
  mesh->addGates("../data/gates.csv");
  mesh->addPassengerGroups("../data/tickets.csv");

  shared_ptr<Solution1 > solution1(new Solution1(mesh));


  




	//
	// ofstream outFile;
	// outFile.open("../data/result.csv",ios::out);

	// 	outFile<<i<<endl;
	// 	for(int j=0;j<graph->path_list.size();j++){
	// 		for(int k=0;k<graph->path_list[j].size();k++){
	// 			outFile<<graph->path_list[j][k]->id<<" "<<graph->path_list[j][k]->time_arrive<<"  "<<graph->path_list[j][k]->time_go<<"  ";
	// 		}
	// 		outFile<<endl;
	// 	}
	// 	outFile<<endl;
	// }
	// outFile.close();
	

	//all to di_id
	//then depart
	
	
	// path_num=graph->path_list.size();
	// printf("%4d",path_num);
	// printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,flight_wid.size());

	// vector<FlightList> path_max2;
	// int max_num=0;
	// for(int i=0;i<graph->path_list.size();i++){

	// }




	return EXIT_SUCCESS;
}
