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
  Size sizeNW;
  bool validFlag= false;
  GateType gate_type;
  TIMELINE(const FlightList FlightsOfLine_init);
  bool isValid();
  bool getDelayNum();
  bool getDIType();
  bool getSize();
};


class TIMELINE_GATE : public TIMELINE{
public:
    GATE gate;
//    TIMELINE_GATE(const FlightList FlightsOfLine_init);
    TIMELINE_GATE(const FlightList FlightsOfLine_init,const GATE gate_init);
    bool isValid();

};
bool gateCompatible(const set<FlyType > DI_Flight,const set<FlyType > DI_Gate);

#endif