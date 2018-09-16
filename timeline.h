#include "Mesh.h"
#include "basiclibs.h"
#include "gate.h"

#ifndef timeline_h
#define timeline_h

class TIMELINE {
public:
  FlightList FlightsOfLine;
  int delayFlightNum;
  set<FlyType> arrive_DI_type;
  set<FlyType> leave_DI_type;
  bool validFlag= false;
  TIMELINE(const FlightList FlightsOfLine_init);
  bool isValid();
  bool getDelayNum();
  bool getDIType();
};

#endif