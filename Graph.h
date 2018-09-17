#include "basiclibs.h"

#include "Mesh.h"

#define CLR(x) memset(x,0,sizeof(x))
#ifndef graph_h
#define graph_h

struct Node;
typedef std::vector<shared_ptr<Node>> NodeList;
typedef std::vector<vector< int>> Map;


struct Node{
    shared_ptr<Flight>flight;
    //vector<int> link_nodes;
    bool vis=false;
};

class Graph{
public:
    int path_num=0;
    NodeList nodeList;//
   // NodeList binaryNodes;
    Map map;//connections, will change during the graph construction
    int * link;//proper pair
    vector<FlightList> path_list;

    Graph(FlightList flightGroup);
    ~Graph();
    void constructDirecMap();
    void constructBinaryGraph();//
    bool dfs(int index);
    void findPair();
    void findPath();
    void solve();
};

#endif