#include "Graph.h"
#include "Mesh.h"
#include "basiclibs.h"
#include "plan.h"

#ifndef solution1_h
#define solution1_h
class Solution1;

struct FlightGroupStruct{
    vector<FlightList> flight_paths;
    GateType gate_type;
};
typedef std::vector<shared_ptr<struct FlightGroupStruct >> FlightGroupList; 

class Solution1{
public:
    shared_ptr<PLAN> plan;
    shared_ptr<Mesh> mesh;
    shared_ptr<Graph> graph;
    FlightGroupList flight_group_list;
    vector<FlightList> flight_groups;
    vector<shared_ptr<TIMELINE_GATE>> timelines;
    Solution1(shared_ptr<Mesh> mesh_ptr):mesh(mesh_ptr){
        shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
        flight_group->gate_type=NoneType;
        FlightList path;
        flight_group->flight_paths.push_back(path);
        flight_group_list.push_back(flight_group);

    }
    void getInitialPath();
    void getWideCombine();
    void getNarrowCombine();
    bool flightInGroup(shared_ptr<FLIGHT> flight,vector<FlightList> path_list);
    int maxPath(vector<FlightList> flight_path);
    void storeFrontPath(vector<FlightList> flight_path,int num);
    int getPathListSize(vector<FlightList> flight_path);
    void constructTimeline();
   // bool maxFirst(FlightList &f1,FlightList &f2);
    void solve(){
        getInitialPath();
        getWideCombine();
        getNarrowCombine();
        constructTimeline();
    }


};
#endif