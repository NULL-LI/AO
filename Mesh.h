#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#ifndef mesh_h
#define mesh_h

string wide_size_names[6] = {"332", "333", "33E", "33H", "33L", "773"};

enum Size { WIDE, SLIM };
enum FlyType { D, I };
class Flight {
private:
public:
  int id;
  int time_arrive;
  int time_go;
  Size type_size;      //
  FlyType type_arrive; //
  FlyType type_go;
  string flight_arrive;
  string flight_go;

  Flight() {}
  int timeDiff(int time1, int time2);
  Size getTypeSize(string type);
};

typedef std::vector<Flight *> FlightList;

class Mesh {
public:
  FlightList flightList;
  Mesh() {}
  ~Mesh() { clear(); }
  void addFlights(string flights_name);
  void clear();
  string Trim(string &str);
};

#endif