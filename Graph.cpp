#include "Graph.h"

Graph::Graph(FlightList flightGroup){
    for(int i=0;i<flightGroup.size();i++){
        shared_ptr<Node> node(new Node());
        node->flight=flightGroup[i];
        //node->vis=false;
        nodeList.push_back(node);
    }
}
Graph::~Graph(){
    size_t i;
    for (i = 0; i < nodeList.size(); i++) {
        if (nodeList[i] != NULL){}
//            delete nodeList[i];
    }
}
void Graph::constructDirecMap(){
    for(int i=0;i<nodeList.size();i++){
        vector<int> adjacent;
        for(int j=0;j<nodeList.size();j++){
            
            if(j!=i){
                //if((nodeList[j]->flight->time_arrive-nodeList[i]->flight->time_go)>=45){
                if((nodeList[j]->flight->time_go-nodeList[i]->flight->time_go)>=45){

                    adjacent.push_back(j);
                    //cout<<"time go:"<<nodeList[i]->flight->time_go<<"  time arrive"<<nodeList[j]->flight->time_arrive<<endl;
                }
            }//end if
        }//end for
        map.push_back(adjacent);
    }//end for
}

//construct binary graph
void Graph::constructBinaryGraph(){
    //two nodes,x-parent/y-child
    //in child nodes, FLight* is NULL
    int initial_size=nodeList.size();
    //augment map size
    for(int i=0;i<initial_size;i++){
        vector<int> adjacent;
        map.push_back(adjacent);
    }
    //update nodeList
    for(int i=0;i<initial_size;i++){
        shared_ptr<Node> node;
        node.reset(new  Node());
        nodeList.push_back(node);
        //update map
        for(int j=0;j<map[i].size();j++){
            map[i][j]+=initial_size;
            map[map[i][j]].push_back(i);
        }

    }
    //update link
    link=new int[nodeList.size()];
    //CLR(link);
    for(int i=0;i<nodeList.size();i++){
        link[i]=-1;
    }
}
//dfs propagration
bool Graph::dfs(int index){
    for(int i=0;i<map[index].size();i++){
        int index_child=map[index][i];
        shared_ptr<Node> node=nodeList[index_child];
        if(!node->vis){
            node->vis=true;
            if(link[index_child]<0 || dfs(link[index_child])){
                link[index_child]=index;
                link[index]=index_child;
                return true;
            }
        }
    }
    return false;
}
//
void Graph::findPair(){
    //update link
    for(int i=0;i<nodeList.size();i++){
        if(link[i] <0 && dfs(i))//self is not in the pair
            path_num++;
    }
}

//according to the pairs store in links
//find the feasible path
void Graph::findPath(){
    Map map2;
    int map_size=map.size();
    if(map_size%2!=0){
        cout<<"map size is not even number."<<endl;
        return;
    }
    int initial_node_size=map_size/2;
    for(int i=0;i<map_size;i++){
        nodeList[i]->vis=false;
        vector<int> adjacent;
        //connect the binary node
        adjacent.push_back((i<initial_node_size)?(initial_node_size+i):(i-initial_node_size));
        //connect the pair node
        if(link[i]>=0){
            adjacent.push_back(link[i]);
        }
        //cout<<adjacent[0]<<endl;
        map2.push_back(adjacent);
    }
    //path will be found in map2
    int path_found=0;
    for(int i=0;i<initial_node_size;i++){
        //if not visited and only be connected to one link
        //and flight is not NULL
        //then this is a start node
        if(!(nodeList[i]->vis)&& nodeList[i]->flight && map2[i].size()==1){
            path_found++;
            nodeList[i]->vis=true;
            FlightList one_path;
            one_path.push_back(nodeList[i]->flight);
            int sig=i;
            //cout<<map2[map2[sig][0]][0]<<"  "<<map2[map2[sig][0]][1]<<endl;
            while(map2[map2[sig][0]].size()==2){
                //cout<<"2"<<endl;
                sig=map2[map2[sig][0]][1];
                nodeList[sig]->vis=false;
                one_path.insert(one_path.begin(),nodeList[sig]->flight);
            }
            path_list.push_back(one_path);   
        }//end if
    }//end for
   // cout<<"path num:"<<path_num<<endl;
   // cout<<"path found:"<<path_found<<endl;
}

void Graph::solve(){
    constructDirecMap();
    constructBinaryGraph();
    findPair();
    findPath();
}