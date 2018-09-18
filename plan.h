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

  int switchedScheduleIdx1, switchedScheduleIdx2;

  PLAN(vector<shared_ptr<TIMELINE_GATE>> timelines, PassengerGroupList pl);

  double passengerTotalTime;
  double passengerTotalTension;
  int passengerInBuildingNumber;

  bool getpassengerTotalTime();
  bool getpassengerTotalTension();
  bool getpassengerTotalNumber();

  //  bool getPassengerGate(PASSENGERGROUP &passengerGroup);

  bool switchGatesRandom();
  bool switchGatesBack();

  bool updatePassengerFlightGate();

  bool isValid(GATEINFO gateinfo);

  bool updateFlightGate();
  bool initFlightGate();
  bool fillInEmptyTimeline();

  bool optimizeTotalTime();
  bool optimizeTotalTension();

  bool printAllocation();

    bool printPassengerTimeInfoQ2();
    bool printPassengerTimeInfoQ3();

  int passengerQ3FailNum();
  int passengerQ2FailNum();

};
bool switchable(const TIMELINE_GATE time_gate_1,
                const TIMELINE_GATE time_gate_2);
#endif