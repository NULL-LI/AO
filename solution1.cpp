#include "solution1.h"
bool maxFirst(FlightList &f1,FlightList &f2);
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
    ofstream outFile;
    outFile.open("../data/result.csv",ios::out);
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
        }
        if(i==4){
            shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
            flight_group->flight_paths.assign(graph->path_list.begin(),graph->path_list.end());
            flight_group->gate_type=(enum GateType)7;
            flight_group_list.push_back(flight_group);
        }
        // cout<<"node size:"<<graph->nodeList.size();
        // cout<<"  initial:"<<flight_groups[i].size();
        // cout<<"  graph:"<<getPathListSize(graph->path_list);
        // cout<<" group:"<<getPathListSize(flight_group_list.back()->flight_paths)<<endl;

        

        outFile<<i<<endl;
        for(int j=0;j<graph->path_list.size();j++){
            for(int k=0;k<graph->path_list[j].size();k++){
                outFile<<graph->path_list[j][k]->id<<", "<<graph->path_list[j][k]->time_arrive<<",  "<<graph->path_list[j][k]->time_go<<",  ";
            }
            outFile<<endl;
        }
        outFile<<endl;
       

    }
     
    outFile.close();

}

void Solution1::getWideCombine(){
    vector<FlightList> path_wdi_wid,path_wdi,path_wid;
    graph.reset(new Graph(flight_groups[6]));//wid
	graph->solve();
    path_wid.assign(graph->path_list.begin(),graph->path_list.end());
    path_wdi_wid.push_back(path_wid.back());
    path_wid.erase(path_wid.begin()+1);

    graph.reset(new Graph(flight_groups[7]));//wid
	graph->solve();
    path_wdi.assign(graph->path_list.begin(),graph->path_list.end());
    path_wdi_wid.push_back(path_wdi.back());
    path_wdi.erase(path_wdi.begin()+1);

    shared_ptr<struct FlightGroupStruct > flight_group_wdi_wid(new struct FlightGroupStruct);
    flight_group_wdi_wid->flight_paths.assign(path_wdi_wid.begin(),path_wdi_wid.end());
    flight_group_wdi_wid->gate_type=(enum GateType)13;
    flight_group_list.push_back(flight_group_wdi_wid);

    shared_ptr<struct FlightGroupStruct > flight_group_wid(new struct FlightGroupStruct);
    flight_group_wid->flight_paths.assign(path_wid.begin(),path_wid.end());
    flight_group_wid->gate_type=(enum GateType)9;
    flight_group_list.push_back(flight_group_wid);

    shared_ptr<struct FlightGroupStruct > flight_group_wdi(new struct FlightGroupStruct);
    flight_group_wdi->flight_paths.assign(path_wdi.begin(),path_wdi.end());
    flight_group_wdi->gate_type=(enum GateType)10;
    flight_group_list.push_back(flight_group_wdi);




    // FlightList flight_wdi_wid;
    // for(int i=0;i<flight_groups[6].size();i++){
    //     flight_wdi_wid.push_back(flight_groups[6][i]);
    // }
    // for(int i=0;i<flight_groups[7].size();i++){
    //     flight_wdi_wid.push_back(flight_groups[7][i]);
    // }
    // graph.reset(new Graph(flight_wdi_wid));
	// graph->solve();
    // cout<<"combine: wdi+wid"<<endl;
    // int path_num=graph->path_list.size();
	// printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_wdi_wid.size());

    // shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
    // flight_group->flight_paths.assign(graph->path_list.begin(),graph->path_list.end());
    // flight_group->gate_type=(enum GateType)13;
    // flight_group_list.push_back(flight_group);
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
    //cout<<"di_id_ii:"<<flight_di_id_ii.size()<<endl;//109

    graph.reset(new Graph(flight_di_id_ii));
	graph->solve();
	//cout<<"combine: nii+ndi+nid"<<endl;

    int path_num=graph->path_list.size();
	//printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_di_id_ii.size());

    vector<FlightList> path_max2;
    for(int i=0;i<2;i++){
        int max_pos=maxPath(graph->path_list);
        path_max2.push_back(graph->path_list[max_pos]);
        graph->path_list.erase(graph->path_list.begin()+max_pos);
    }

    shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
    flight_group->flight_paths.assign(path_max2.begin(),path_max2.end());
    flight_group->gate_type=(enum GateType)6;
    flight_group_list.push_back(flight_group);
   // cout<<"path-max:"<<getPathListSize(path_max2)<<" rest:"<<getPathListSize(graph->path_list)<<endl;

    //nii
    int rest_in=0;
    FlightList flight_group00,flight_group22,flight_group33;
    for(int i=0;i<flight_groups[0].size();i++){
        if(!flightInGroup(flight_groups[0][i],path_max2)){
            flight_group00.push_back(flight_groups[0][i]);
        }
        else{
            //flight_groups[0].erase(flight_groups[0].begin()+i);
            rest_in++;
        }
    }
    //cout<<"group_0:"<<rest_in<<" "<<flight_group00.size()<<endl;
    rest_in=0;
    for(int i=0;i<flight_groups[2].size();i++){
		 if(!flightInGroup(flight_groups[2][i],path_max2)){
             flight_group22.push_back(flight_groups[2][i]);
         }
        else{
             rest_in++;
        }
    }
    //cout<<"  group_0:"<<rest_in<<" "<<flight_group22.size()<<endl;
    rest_in=0;
	for(int i=0;i<flight_groups[3].size();i++){
		 if(!flightInGroup(flight_groups[3][i],path_max2)){
             flight_group33.push_back(flight_groups[3][i]);
         }
        else{
            rest_in++;
        }
	}
    //cout<<" group_0:"<<rest_in<<" "<<flight_group33.size()<<endl;
    rest_in=0;

    //0
    graph.reset(new Graph(flight_group00));
	graph->solve();
    //cout<<"combine: nii"<<endl;
    path_num=graph->path_list.size();
	//printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_group00.size());
    vector<FlightList> path_max_group0;
    sort(graph->path_list.begin(),graph->path_list.end(),maxFirst);
    for(int i=0;i<4;i++){
        path_max_group0.push_back(graph->path_list[i]);
        // int max_pos=maxPath(graph->path_list);
        // path_max_group0.push_back(graph->path_list[max_pos]);
        // graph->path_list.erase(graph->path_list.begin()+max_pos);
    }
    for(int i=4;i<graph->path_list.size();i++){
        for(int j=0;j<graph->path_list[i].size();j++){
            flight_group_list[0]->flight_paths[0].push_back(graph->path_list[i][j]);
        }
    }
    // for(int i=0;i<flight_group00.size();i++){
    //     if(!flightInGroup(flight_group00[i],path_max_group0)){
    //         flight_group_list[0]->flight_paths[0].push_back(flight_group00[i]);
    //     }
    // }


    shared_ptr<struct FlightGroupStruct > flight_group0(new struct FlightGroupStruct);
    flight_group0->flight_paths.assign(path_max_group0.begin(),path_max_group0.end());
    flight_group0->gate_type=(enum GateType)0;
    flight_group_list.push_back(flight_group0);
//2
    graph.reset(new Graph(flight_group22));
	graph->solve();
    //cout<<"combine: nid"<<endl;
    path_num=graph->path_list.size();
	//printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_group22.size());

    vector<FlightList> path_max_group2;
    sort(graph->path_list.begin(),graph->path_list.end(),maxFirst);
    for(int i=0;i<2;i++){
        path_max_group2.push_back(graph->path_list[i]);
        }
    // for(int i=0;i<2;i++){
    //     int max_pos=maxPath(graph->path_list);
    //     path_max_group2.push_back(graph->path_list[max_pos]);
    //     graph->path_list.erase(graph->path_list.begin()+max_pos);
    // }
    for(int i=2;i<graph->path_list.size();i++){
        for(int j=0;j<graph->path_list[i].size();j++){
            flight_group_list[0]->flight_paths[0].push_back(graph->path_list[i][j]);
        }
    }
    // for(int i=0;i<flight_groups[2].size();i++){
    //     if(!flightInGroup(flight_group22[i],path_max_group2)){
    //         flight_group_list[0]->flight_paths[0].push_back(flight_group22[i]);
    //     }
    // }

    shared_ptr<struct FlightGroupStruct > flight_group2(new struct FlightGroupStruct);
    flight_group2->flight_paths.assign(path_max_group2.begin(),path_max_group2.end());
    flight_group2->gate_type=(enum GateType)5;
    flight_group_list.push_back(flight_group2);

    //3
    graph.reset(new Graph(flight_group33));
	graph->solve();
    //cout<<"combine: ndi"<<endl;
    path_num=graph->path_list.size();
	//printf("pairs:%4d path:%4d size:%4d\n",graph->path_num,path_num,(int)flight_group33.size());

    vector<FlightList> path_max_group3;
    sort(graph->path_list.begin(),graph->path_list.end(),maxFirst);
    for(int i=0;i<2;i++){
        path_max_group3.push_back(graph->path_list[i]);
        }
    // for(int i=0;i<2;i++){
    //     int max_pos=maxPath(graph->path_list);
    //     path_max_group3.push_back(graph->path_list[max_pos]);
    //     graph->path_list.erase(graph->path_list.begin()+max_pos);
    // }
    for(int i=2;i<graph->path_list.size();i++){
        for(int j=0;j<graph->path_list[i].size();j++){
            flight_group_list[0]->flight_paths[0].push_back(graph->path_list[i][j]);
        }
    }
    // for(int i=0;i<flight_group33.size();i++){
    //     if(!flightInGroup(flight_group33[i],path_max_group3)){
    //         flight_group_list[0]->flight_paths[0].push_back(flight_group33[i]);
    //     }
    // }
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
void Solution1::constructTimeline(){
    for(int i=1;i<flight_group_list.size();i++){
	  if(flight_group_list[i]->flight_paths.size()>mesh->gateInfoAll.gate_group[(int)(flight_group_list[i]->gate_type)]->gate_same_type.size()){
          cout<<"too many timelines in one gate"<<endl;
          return;
      }
      for(int j=0;j<flight_group_list[i]->flight_paths.size();j++){
        GATE gate=*(mesh->gateInfoAll.gate_group[(int)(flight_group_list[i]->gate_type)]->gate_same_type[j]);
        shared_ptr<TIMELINE_GATE> one_timeline(new  TIMELINE_GATE(flight_group_list[i]->flight_paths[j],gate));
        timelines.push_back(one_timeline);
      }//end for
  }//end for
  plan.reset(new PLAN(timelines,mesh->passengerGroupListAll));

}
void Solution1::saveResult(){
    string result1_file_name="../data/result1.csv";
    ofstream outFile;
    outFile.open(result1_file_name,ios::out);
    outFile<<"all flights,"<<mesh->flightListAll.size()<<",";
    outFile<<"success flights,"<<mesh->flightListAll.size()-flight_group_list[0]->flight_paths[0].size()<<",";
    outFile<<"failed flights,"<<flight_group_list[0]->flight_paths[0].size()<<endl;
    int narrow_flights=0;
    int wide_flights=0;
    int gate_num=0;
    int gate_narrow=0;
    int gate_wide=0;
    int s_gate=0;
    int t_gate=0;
    int time_duration_t=0; 
    int time_duration_s=0;
    for(int i=0;i<plan->schedule.size();i++){
		for(int j=0;j<plan->schedule[i]->FlightsOfLine.size();j++){
			if(plan->schedule[i]->FlightsOfLine[j]->plane_size==N)
                narrow_flights++;
            else
                wide_flights++;
            if(plan->schedule[i]->gate.gate_building==T)
                time_duration_t +=plan->schedule[i]->FlightsOfLine[j]->time_go-plan->schedule[i]->FlightsOfLine[j]->time_arrive;
            else
                time_duration_s +=plan->schedule[i]->FlightsOfLine[j]->time_go-plan->schedule[i]->FlightsOfLine[j]->time_arrive;
		}
        if(plan->schedule[i]->gate.gate_building==T)
            t_gate++;
        else
            s_gate++;
        if(plan->schedule[i]->gate.gate_size==N)
            gate_narrow++;
        else
            gate_wide++;
		gate_num++;
		cout<<endl;
	}
    int narrow_flights_all=0;
    int wide_flights_all=0;
    for(int i=0;i<mesh->flightListAll.size();i++){
        if(mesh->flightListAll[i]->plane_size==N){
            narrow_flights_all ++;
        }else{
            wide_flights_all++;
        }
    }
    outFile<<"wide flights,"<<wide_flights<<",all wide flights,"<<wide_flights_all<<",narrow flights,"<<narrow_flights<<",all narrow flights,"<<narrow_flights_all<<endl;
    outFile<<"gate used,"<<gate_num<<",narrow gate,"<<gate_narrow<<",wide gate,"<<gate_wide<<",t gate,"<<t_gate<<",s gate,"<<s_gate<<endl;
    outFile<<"time duration in t,"<<time_duration_t<<",time duration s,"<<time_duration_s<<endl;

    outFile.close();

}

bool maxFirst(FlightList &f1,FlightList &f2){
    return f1.size()>f2.size();
}
    