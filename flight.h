#include "basiclibs.h"
#include "gate.h"
#ifndef flight_h
#define flight_h

static string wide_size_names[6] = {"332", "333", "33E", "33H", "33L", "773"};
class FLIGHT {

public:
  int id;
  int time_arrive;
  int time_go;
  Size plane_size;     //
  FlyType type_arrive; //
  FlyType type_go;
  string flight_arrive_number;
  string flight_leave_number;

  FLIGHT() {}
  int timeDiff(int time1, int time2);
  Size getTypeSize(string type);
};
typedef std::vector<shared_ptr<FLIGHT>> FlightList;

class FLIGHT_GATE : public FLIGHT{
public:
    GATE gate;
//    TIMELINE_GATE(const FlightList FlightsOfLine_init);
    FLIGHT_GATE(const GATE gate_init);
    bool isValid();

};


#endif