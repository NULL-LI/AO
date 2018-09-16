#ifndef Mesh_h
#define Mesh_h
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class Flight;
class Mesh;
string wide_size_names[6] = {"332", "333", "33E", "33H", "33L", "773"};
typedef std::vector<Flight *> FlightList;
enum Size { WIDE, SLIM };
enum FlyType { D, I };
class Flight {
private:
public:
  int id;
  int time_arrive;
  int time_go;
  Size type_size;      //��խ��
	FlyType
  ype_arrive;//������� �/��������
	FlyType type_go;
	string flight_arrive;
  string flight_go

	Flight(){}
	int tim
  iff(int time1, in

  ime2) ;
 	S
  e getTypeSize(string type) ;
};

ca
   gates{};

class Mesh {
publi:
	FlightList fli ghtList;
	Mesh(){}
	~Mesh
   { clear(); }
	void ad
  lights (s
  ing flights_name);

  id clear();
	string Trim(string& str)
  };

#endif