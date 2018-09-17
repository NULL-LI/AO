#include "basiclibs.h"
#include "timeline.h"

#ifndef plan_h
#define plan_h

class PLAN {
public:
  vector<shared_ptr<TIMELINE_GATE>> schedule;
  GateList gateListAll;
  FlightGateList FlightGateListOfPlan;
  PassengerGroupList passengerGroupListAll;

  int switchedScheduleIdx1,switchedScheduleIdx2;

  PLAN(vector<shared_ptr<TIMELINE_GATE>> timelines, PassengerGroupList pl);

  double passengerTotalTime;
  double passengerTotalTension;

  bool getpassengerTotalTime();
  bool getpassengerTotalTension();

  bool getPassengerGate(PASSENGERGROUP &passengerGroup);

  bool switchGatesRandom();
  bool switchGatesBack();

  bool isValid(GATEINFO gateinfo);

  bool updateFlightGate();

  bool fillInEmptyTimeline();

  bool optimizeTotalTime(int iter);
  bool optimizeTotalTension(int iter);
};

#endif