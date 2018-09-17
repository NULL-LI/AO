#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Mesh.h"

#define CLR(x) memset(x,-1,sizeof(x))
typedef std::vector<Node*> NodeList;
typedef std::vector<vector< int>> Map;
class Node;
class Graph;

struct Node{
    Flight *flight;
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

    Graph(NodeList nodes):nodeList(nodes){}
    ~Graph();
    void constructMap();
    void constructBinaryGraph();//
    bool dfs(Node *);
    void findPair();
    void findPath();
};