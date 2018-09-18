
#include "basiclibs.h"
#include "gate.h"
#include "flight.h"
#include "passenger.h"
using namespace std;

#ifndef mesh_h
#define mesh_h


class Mesh {
public:
  FlightList flightListAll;
  GateList gateListAll;
  PassengerGroupList passengerGroupListAll;
  GATEINFO gateInfoAll;
  Mesh() {}
  ~Mesh() { clear(); }
  bool addFlights(string flights_source_file_name);
  bool addGates(string gates_src_name) ;
  bool addPassengerGroups(string ticket_src_name) ;
  bool getGateInfo();
  void clear();
  void constructGateInfo();//yee
  string Trim(string &str);
};

#endif