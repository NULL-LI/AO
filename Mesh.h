
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
  string flight_arrive_number;
  string flight_leave_number;

  Flight() {}
  int timeDiff(int time1, int time2);
  Size getTypeSize(string type);
};

typedef std::vector<shared_ptr<Flight>> FlightList;
typedef std::vector<shared_ptr<GATE >> GateList;

class Mesh {
public:
  FlightList flightListAll;
  GateList gateListAll;
  GATEINFO gateInfoAll;
  Mesh() {}
  ~Mesh() { clear(); }
  bool addFlights(string flights_source_file_name);
  bool addGates(string gates_src_name) ;
  bool getGateInfo();
  void clear();
  string Trim(string &str);
};

#endif