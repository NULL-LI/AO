#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class Flight;
class Mesh;
string wide_size_names[6] = { "332","333","33E","33H","33L","773" };
typedef std::vector<Flight*> FlightList;
enum Size {
    WIDE,
    SLIM
};
enum FlyType {
    D,
    I
};
class Flight
{
private:

public:

    int id;
    int time_arrive;
    int time_go;
    Size type_size;//��խ��
    FlyType type_arrive;//��������/��������
    FlyType type_go;
    string flight_arrive;
    string flight_go;

    Flight(){}
    int timeDiff(int time1, int time2) ;
    Size getTypeSize(string type) ;
};
class Mesh {
public:
    FlightList flightList;
    Mesh(){}
    ~Mesh() { clear(); }
    void addFlights(string flights_name) ;
    void clear() ;
    string Trim(string& str);
};