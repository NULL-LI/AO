#include "plan.h"
PLAN::PLAN(vector<shared_ptr<TIMELINE_GATE>> timelines, PassengerGroupList pl)
    : schedule(timelines), passengerGroupListAll(pl) {}

bool PLAN::getpassengerTotalTime() { return true; }
bool PLAN::getpassengerTotalTension() { return true; }

bool PLAN::switchGatesRandom() { return true; }
bool PLAN::switchGatesBack() { return true; }

bool PLAN::isValid() { return true; }

bool PLAN::updateFlightGate() {
  for (int ite_sche = 0; ite_sche < schedule.size(); ite_sche++) {
    for (int ite_fli = 0; ite_fli < schedule[ite_sche]->FlightsOfLine.size();
         ite_fli++) {
      shared_ptr<FLIGHT_GATE> flight_gate;
      flight_gate.reset(
          new FLIGHT_GATE(*schedule[ite_sche]->FlightsOfLine[ite_fli],
                          schedule[ite_sche]->gate));
      FlightGateListOfPlan.push_back(flight_gate);
    }
  }
  return true;
}

bool PLAN::fillInEmptyTimeline() { // fill the open gates with empty schedule
  GateList tempGateList = gateListAll;

  for (int ite_sche = 0; ite_sche < schedule.size(); ite_sche++) {
    for (int ite_gate = 0; ite_gate < tempGateList.size(); ite_gate++) {
      if (schedule[ite_sche]->gate.id == tempGateList[ite_gate]->id) {
        tempGateList.erase(tempGateList.begin() + ite_gate);
        ite_gate-=1;
      }
    }
  }
    for (int ite_gate = 0; ite_gate < tempGateList.size(); ite_gate++){
        shared_ptr<TIMELINE_GATE> timeline_gate_ptr_temp;
        FlightList Flights_temp;
        Flights_temp.clear();
        TIMELINE timeline_temp(Flights_temp);
        timeline_gate_ptr_temp.reset(new TIMELINE_GATE(Flights_temp,*tempGateList[ite_gate]));

        schedule.push_back(timeline_gate_ptr_temp);
    }


  return true;
}

bool PLAN::optimizeTotalTime(int iter) { return true; }
bool PLAN::optimizeTotalTension(int iter) { return true; }