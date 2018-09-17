#include "basiclibs.h"
#include "timeline.h"

#ifndef plan_h
#define plan_h

class PLAN {
public:
  vector<shared_ptr<TIMELINE>> schedule;

  FlightGateList FlightGateListOfPlan;

  PLAN(vector<shared_ptr<TIMELINE>> timelines);


  double passengerTotalTime;
  double passengerTotalTension;

  bool getpassengerTotalTime();
  bool getpassengerTotalTension();

  bool switchGatesRandom();
  bool switchGatesBack();

  bool isValid();

  bool updateFlightGate();

};

#endif