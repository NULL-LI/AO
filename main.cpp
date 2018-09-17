
#include "Graph.h"
#include "Mesh.h"

int main() {
  shared_ptr<Mesh> mesh(new Mesh());
  printf("Start main\n");
  mesh->addFlights("../data/pucks.csv");
  mesh->addGates("../data/gates.csv");
  mesh->addPassengerGroups("../data/tickets.csv");

  FlightList flight_nii, flight_ndd, flight_nid, flight_ndi;
  FlightList flight_wii, flight_wdd, flight_wid, flight_wdi;
  for (int i = 0; i < mesh->flightListAll.size(); i++) {
    if (mesh->flightListAll[i]->plane_size == N) {
      if (mesh->flightListAll[i]->type_arrive == I) {
        if (mesh->flightListAll[i]->type_go == I) {
          flight_nii.push_back(mesh->flightListAll[i]);
        } else {
          flight_nid.push_back(mesh->flightListAll[i]);
        }
      } else {
        if (mesh->flightListAll[i]->type_go == I) {
          flight_ndi.push_back(mesh->flightListAll[i]);
        } else {
          flight_ndd.push_back(mesh->flightListAll[i]);
        }
      }
    } // end if n
    else {
      if (mesh->flightListAll[i]->type_arrive == I) {
        if (mesh->flightListAll[i]->type_go == I) {
          flight_wii.push_back(mesh->flightListAll[i]);
        } else {
          flight_wid.push_back(mesh->flightListAll[i]);
        }
      } else {
        if (mesh->flightListAll[i]->type_go == I) {
          flight_wdi.push_back(mesh->flightListAll[i]);
        } else {
          flight_wdd.push_back(mesh->flightListAll[i]);
        }
      }
    } // end if w
  }   // end for

  vector<FlightList> flight_groups;
  flight_groups.push_back(flight_nii);
  flight_groups.push_back(flight_ndd);
  flight_groups.push_back(flight_nid);
  flight_groups.push_back(flight_ndi);
  flight_groups.push_back(flight_wii);
  flight_groups.push_back(flight_wdd);
  flight_groups.push_back(flight_wid);
  flight_groups.push_back(flight_wdi);
  cout << "wdd:" << flight_wdd.size() << endl;


	int side_stop=0;
	//
	ofstream outFile;
	outFile.open("../data/result.csv",ios::out);

	shared_ptr<Graph> graph;
	printf("%4s%4s%4s%4s%4s%4s%4s%4s\n","nii","ndd","nid","ndi","wii","wdd","wid","wdi");
	for(int i=0;i<flight_groups.size();i++){
		graph.reset(new Graph(flight_groups[i]));
		graph->solve();
		int path_num=graph->path_list.size();
		printf("%4d",path_num);
		printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,flight_groups[i].size());
		//
		for(int j=0;j<graph->path_list.size();j++){
			if(j==0 || j==2 || j==3){
			for(int k=0;k<graph->path_list[j].size()-1;k++){
				if((graph->path_list[j][k+1]->time_arrive-graph->path_list[j][k]->time_go)<45){
					side_stop++;

				}
			}	
			}
		}

		outFile<<i<<endl;
		for(int j=0;j<graph->path_list.size();j++){
			for(int k=0;k<graph->path_list[j].size();k++){
				outFile<<graph->path_list[j][k]->id<<" "<<graph->path_list[j][k]->time_arrive<<"  "<<graph->path_list[j][k]->time_go<<"  ";
			}
			outFile<<endl;
		}
		outFile<<endl;
	}
	outFile.close();
	cout<<endl;
	cout<<"side:"<<side_stop<<endl;
	//mesh->getGateInfo();
	//cout<<"n i i:"<<mesh->gateInfoAll.gateNum_Narrow_I_I<<endl;
	//combine wdi-wid
	for(int i=0;i<flight_wdi.size();i++)
		flight_wid.push_back(flight_wdi[i]);
	graph.reset(new Graph(flight_wid));
	graph->solve();
	cout<<"combine: wdi+wid"<<endl;
	int path_num=graph->path_list.size();
	printf("%4d",path_num);
	printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,flight_wid.size());






	return EXIT_SUCCESS;
}
