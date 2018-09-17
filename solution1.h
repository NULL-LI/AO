#include "Graph.h"
#include "Mesh.h"
#include "basiclibs.h"

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
    shared_ptr<Mesh> mesh;
    shared_ptr<Graph> graph;
    FlightGroupList flight_group_list;
    vector<FlightList> flight_groups;
    Solution1(shared_ptr<Mesh> mesh_ptr):mesh(mesh_ptr){
        shared_ptr<struct FlightGroupStruct > flight_group(new struct FlightGroupStruct);
        flight_group->gate_type=NoneType;
        flight_group_list.push_back(flight_group);

    }
    void getInitialPath();
    void getWideCombine();
    void getNarrowCombine();
    bool flightInGroup(shared_ptr<FLIGHT> flight,vector<FlightList> path_list);
    


};
#endif