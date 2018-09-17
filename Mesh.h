
#include "basiclibs.h"
#include "gate.h"
#include "flight.h"
using namespace std;

#ifndef mesh_h
#define mesh_h



//class Flight {
//
//};

typedef std::vector<shared_ptr<FLIGHT>> FlightList;
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