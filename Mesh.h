
#include "basiclibs.h"
#include "gate.h"
using namespace std;

#ifndef mesh_h
#define mesh_h

static string wide_size_names[6] = {"332", "333", "33E", "33H", "33L", "773"};

class Flight {
private:
public:
  int id;
  int time_arrive;
  int time_go;
  Size plane_size;      //
  FlyType type_arrive; //
  FlyType type_go;
  string flight_arrive;
  string flight_go;

  Flight() {}
  int timeDiff(int time1, int time2);
  Size getTypeSize(string type);
};

typedef std::vector<Flight *> FlightList;
typedef std::vector<GATE *> GateList;

class Mesh {
public:
  FlightList flightListAll;
  GateList gateListAll;
  Mesh() {}
  ~Mesh() { clear(); }
  void addFlights(string flights_source_file_name);
  void addGates(string gates_src_name) ;
  void clear();
  string Trim(string &str);
};

#endif