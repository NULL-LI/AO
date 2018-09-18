
#include "Graph.h"
#include "Mesh.h"
#include "solution1.h"

int main() {
	//initialization
  shared_ptr<Mesh> mesh(new Mesh());
  printf("Start main\n");
  mesh->addFlights("../data/pucks.csv");
  mesh->addGates("../data/gates.csv");
  mesh->addPassengerGroups("../data/tickets.csv");
	//solution1
  shared_ptr<Solution1 > solution1(new Solution1(mesh));
  solution1->solve();
  int flight_num=0;
  for(int i=0;i<solution1->flight_group_list.size();i++){
	  cout<<"size:"<<solution1->flight_group_list[i]->flight_paths.size()<<" type:"<<solution1->flight_group_list[i]->gate_type;
	  for(int j=0;j<solution1->flight_group_list[i]->flight_paths.size();j++){
		  flight_num +=solution1->flight_group_list[i]->flight_paths[j].size();
	  }
	  cout<<"  flight num:"<<flight_num<<endl;
	  flight_num=0;
  }
	//print solution result
	shared_ptr<PLAN> plan;
	plan=solution1->plan;
	int gate_num=0;
	for(int i=0;i<plan->schedule.size();i++){
		cout<<"Gate id:"<<plan->schedule[i]->gate.id<<" ";
		for(int j=0;j<plan->schedule[i]->FlightsOfLine.size();j++){
			
			printf("%4d",plan->schedule[i]->FlightsOfLine[j]->id);
		}
		gate_num++;
		cout<<endl;

	}
	cout<<"gate used num:"<<gate_num<<endl;
	plan->gateListAll=mesh->gateListAll;
	plan->initFlightGate();
	plan->updateFlightGate();
	plan->updatePassengerFlightGate();
	plan->getpassengerTotalNumber();
	plan->fillInEmptyTimeline();
	plan->getpassengerTotalTime();
	plan->getpassengerTotalTension();

	bool bool_opti_time= plan->optimizeTotalTime(100);
printf("bool_opti_time : %s\n",bool_opti_time ?"true":"false");

  




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
