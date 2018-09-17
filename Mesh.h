
#include "basiclibs.h"
#include "gate.h"
using namespace std;

#ifndef mesh_h
#define mesh_h

static string wide_size_names[6] = {"332", "333", "33E", "33H", "33L", "773"};

struct GATEINFO{
    int gateNum_Total;

    int gateNum_Narrow_I_I;
    int gateNum_Narrow_D_D;
    int gateNum_Narrow_I_DI;
    int gateNum_Narrow_DI_I;
    int gateNum_Narrow_D_DI;
    int gateNum_Narrow_DI_D;
    int gateNum_Narrow_DI_DI;

    int gateNum_Wide_I_I;
    int gateNum_Wide_D_D;
    int gateNum_Wide_I_DI;
    int gateNum_Wide_DI_I;
    int gateNum_Wide_D_DI;
    int gateNum_Wide_DI_D;
    int gateNum_Wide_DI_DI;
};

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