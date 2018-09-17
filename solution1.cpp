#include "solution1.h"

void Solution1::getInitialPath(){
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
            } 
            else 
            {
                flight_wid.push_back(mesh->flightListAll[i]);
            }
            } else 
            {
            if (mesh->flightListAll[i]->type_go == I) {
                flight_wdi.push_back(mesh->flightListAll[i]);
            } else {
                flight_wdd.push_back(mesh->flightListAll[i]);
            }
        }
    } // end if w
    }   // end for
    flight_groups.push_back(flight_nii);
    flight_groups.push_back(flight_ndd);
    flight_groups.push_back(flight_nid);
    flight_groups.push_back(flight_ndi);
    flight_groups.push_back(flight_wii);
    flight_groups.push_back(flight_wdd);
    flight_groups.push_back(flight_wid);
    flight_groups.push_back(flight_wdi);
    char type_name[8][4]={"nii","ndd","nid","ndi","wii","wdd","wid","wdi"};
    for(int i=0;i<flight_groups.size();i++){
		graph.reset(new Graph(flight_groups[i]));
		graph->solve();
        int path_num=graph->path_list.size();
		printf("%4s pairs:%4d path:%4d size:%4d\n",type_name[i],graph->path_num,path_num,(int)flight_groups[i].size());

		if(i==1){
            shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
            flight_group->flight_paths.assign(graph->path_list.begin(),graph->path_list.end());
            flight_group->gate_type=(enum GateType)1;
            flight_group_list.push_back(flight_group);
            cout<<"node size:"<<graph->nodeList.size();
            cout<<"  initial:"<<flight_groups[1].size();
            cout<<"  graph:"<<getPathListSize(graph->path_list);
            cout<<" group:"<<getPathListSize(flight_group_list.back()->flight_paths)<<endl;

        }
        if(i==4){
            shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
            flight_group->flight_paths.assign(graph->path_list.begin(),graph->path_list.end());
            flight_group->gate_type=(enum GateType)7;
            flight_group_list.push_back(flight_group);
        }

    }

}

void Solution1::getWideCombine(){
    FlightList flight_wdi_wid;
    for(int i=0;i<flight_groups[6].size();i++){
        flight_wdi_wid.push_back(flight_groups[6][i]);
    }
    for(int i=0;i<flight_groups[7].size();i++){
        flight_wdi_wid.push_back(flight_groups[7][i]);
    }
    graph.reset(new Graph(flight_wdi_wid));
	graph->solve();
    cout<<"combine: wdi+wid"<<endl;
    int path_num=graph->path_list.size();
	printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_wdi_wid.size());

    shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
    flight_group->flight_paths.assign(graph->path_list.begin(),graph->path_list.end());
    flight_group->gate_type=(enum GateType)13;
    flight_group_list.push_back(flight_group);
}

void Solution1::getNarrowCombine(){
    FlightList flight_di_id_ii;
	for(int i=0;i<flight_groups[0].size();i++){
		flight_di_id_ii.push_back(flight_groups[0][i]);
	}
	for(int i=0;i<flight_groups[2].size();i++){
		flight_di_id_ii.push_back(flight_groups[2][i]);
	}
	for(int i=0;i<flight_groups[3].size();i++){
		flight_di_id_ii.push_back(flight_groups[3][i]);
	}

    graph.reset(new Graph(flight_di_id_ii));
	graph->solve();
	cout<<"combine: nii+ndi+nid"<<endl;

    int path_num=graph->path_list.size();
	printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_di_id_ii.size());

    vector<FlightList> path_max2;
	int max_num=0;
    int max_pos=0;
	for(int i=0;i<graph->path_list.size();i++){
        if(max_num<graph->path_list[i].size()){
            max_num=graph->path_list[i].size();
            max_pos=i;
        }
	}
    //max path
    path_max2.push_back(graph->path_list[max_pos]);
    graph->path_list.erase(graph->path_list.begin()+max_pos);

    max_num=0;
    max_pos=0;
	for(int i=0;i<graph->path_list.size();i++){
        if(max_num<graph->path_list[i].size()){
            max_num=graph->path_list[i].size();
            max_pos=i;
        }
	}
    //max path
    path_max2.push_back(graph->path_list[max_pos]);
    shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
    flight_group->flight_paths.assign(path_max2.begin(),path_max2.end());
    flight_group->gate_type=(enum GateType)6;
    flight_group_list.push_back(flight_group);

    //nii
    for(int i=0;i<flight_groups[0].size();i++){
        if(flightInGroup(flight_groups[0][i],path_max2)){
            flight_groups[0].erase(flight_groups[0].begin()+i);
        }
    }
    for(int i=0;i<flight_groups[2].size();i++){
		 if(flightInGroup(flight_groups[2][i],path_max2)){
            flight_groups[2].erase(flight_groups[2].begin()+i);
        }
    }
	for(int i=0;i<flight_groups[3].size();i++){
		 if(flightInGroup(flight_groups[3][i],path_max2)){
            flight_groups[3].erase(flight_groups[3].begin()+i);
        }
	}

    //0
    graph.reset(new Graph(flight_groups[0]));
	graph->solve();
    cout<<"combine: nii"<<endl;
    path_num=graph->path_list.size();
	printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_groups[0].size());
    vector<FlightList> path_max_group0;
    for(int i=0;i<4;i++){
        int max_pos=maxPath(graph->path_list);
        path_max_group0.push_back(graph->path_list[max_pos]);
        graph->path_list.erase(graph->path_list.begin()+max_pos);
    }
    for(int i=0;i<flight_groups[0].size();i++){
        if(!flightInGroup(flight_groups[0][i],path_max_group0)){
            flight_group_list[0]->flight_paths[0].push_back(flight_groups[0][i]);
        }
    }


    shared_ptr<struct FlightGroupStruct > flight_group0(new struct FlightGroupStruct);
    flight_group0->flight_paths.assign(path_max_group0.begin(),path_max_group0.end());
    flight_group0->gate_type=(enum GateType)0;
    flight_group_list.push_back(flight_group0);
//2
    graph.reset(new Graph(flight_groups[2]));
	graph->solve();
    cout<<"combine: nid"<<endl;
    path_num=graph->path_list.size();
	printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_groups[2].size());

    vector<FlightList> path_max_group2;
    for(int i=0;i<2;i++){
        int max_pos=maxPath(graph->path_list);
        path_max_group2.push_back(graph->path_list[max_pos]);
        graph->path_list.erase(graph->path_list.begin()+max_pos);
    }
    for(int i=0;i<flight_groups[2].size();i++){
        if(!flightInGroup(flight_groups[2][i],path_max_group2)){
            flight_group_list[0]->flight_paths[0].push_back(flight_groups[2][i]);
        }
    }

    shared_ptr<struct FlightGroupStruct > flight_group2(new struct FlightGroupStruct);
    flight_group2->flight_paths.assign(path_max_group2.begin(),path_max_group2.end());
    flight_group2->gate_type=(enum GateType)5;
    flight_group_list.push_back(flight_group2);

    //3
    graph.reset(new Graph(flight_groups[3]));
	graph->solve();
    cout<<"combine: ndi"<<endl;
    path_num=graph->path_list.size();
	printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_groups[3].size());

    vector<FlightList> path_max_group3;
    for(int i=0;i<2;i++){
        int max_pos=maxPath(graph->path_list);
        path_max_group3.push_back(graph->path_list[max_pos]);
        graph->path_list.erase(graph->path_list.begin()+max_pos);
    }
    for(int i=0;i<flight_groups[3].size();i++){
        if(!flightInGroup(flight_groups[3][i],path_max_group3)){
            flight_group_list[0]->flight_paths[0].push_back(flight_groups[3][i]);
        }
    }
    shared_ptr<struct FlightGroupStruct > flight_group3(new struct FlightGroupStruct);
    flight_group3->flight_paths.assign(path_max_group3.begin(),path_max_group3.end());
    flight_group3->gate_type=(enum GateType)4;
    flight_group_list.push_back(flight_group3);

}

bool Solution1::flightInGroup(shared_ptr<FLIGHT> flight,vector<FlightList> path_list){
    for(int i=0;i<path_list.size();i++){
        for(int j=0;j<path_list[i].size();j++){
            if(flight->id==path_list[i][j]->id)
                return true;
        }
    }
    return false;
}
int Solution1::maxPath(vector<FlightList> flight_path){
    int max_num=0;
    int max_pos=0;
	for(int i=0;i<flight_path.size();i++){
        if(max_num<flight_path[i].size()){
            max_num=flight_path[i].size();
            max_pos=i;
        }
	}
    return max_pos;
}
void Solution1::storeFrontPath(vector<FlightList> flight_path,int num){

}
int Solution1::getPathListSize(vector<FlightList> flight_path){
    int num=0;
    for(int i=0;i<flight_path.size();i++){
        num +=flight_path[i].size();
    }
    return num;
}
    