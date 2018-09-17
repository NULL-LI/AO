#include "plan.h"
PLAN::PLAN(vector<shared_ptr<TIMELINE_GATE>> timelines, PassengerGroupList pl)
    : schedule(timelines), passengerGroupListAll(pl) {}

bool PLAN::getpassengerTotalTime() { return true; }
bool PLAN::getpassengerTotalTension() { return true; }
bool PLAN::getPassengerGate(PASSENGERGROUP &passengerGroup){

}
bool switchable(TIMELINE_GATE time_gate_1, TIMELINE_GATE time_gate_2) {
  if (time_gate_1.sizeNW != time_gate_2.sizeNW) {
    return false;
  }
  if (!gateCompatible(time_gate_1.arrive_DI_type,
                      time_gate_2.gate.gate_arrive_type)) {
    return false;
  }
  if (!gateCompatible(time_gate_1.leave_DI_type,
                      time_gate_2.gate.gate_leave_type)) {
    return false;
  }
  if (!gateCompatible(time_gate_2.arrive_DI_type,
                      time_gate_1.gate.gate_arrive_type)) {
    return false;
  }
  if (!gateCompatible(time_gate_2.leave_DI_type,
                      time_gate_1.gate.gate_leave_type)) {
    return false;
  }
  return true;
}

bool PLAN::switchGatesRandom() {
  int scheduleNum = schedule.size();
  int switchIdx1 = rand() % (scheduleNum + 1);
  int switchIdx2 = rand() % (scheduleNum + 1);
  do {
    switchIdx1 = rand() % (scheduleNum + 1);
    switchIdx2 = rand() % (scheduleNum + 1);
  } while (!switchable(*schedule[switchIdx1], *schedule[switchIdx2]));

  GATE temp_gate = schedule[switchIdx1]->gate;
  schedule[switchIdx1]->gate = schedule[switchIdx2]->gate;
  schedule[switchIdx2]->gate = temp_gate;

  switchedScheduleIdx1 = switchIdx1;
  switchedScheduleIdx2 = switchIdx2;

  return true;
}
bool PLAN::switchGatesBack() {
  if (switchable(*schedule[switchedScheduleIdx1],
                 *schedule[switchedScheduleIdx2])) {
    GATE temp_gate = schedule[switchedScheduleIdx1]->gate;
    schedule[switchedScheduleIdx1]->gate = schedule[switchedScheduleIdx2]->gate;
    schedule[switchedScheduleIdx2]->gate = temp_gate;
    return true;
  } else {
    return false;
  }
}

bool PLAN::isValid(GATEINFO gateinfo) {
  if (gateListAll.empty() == true) {
    cout << "Gate list empty, error!" << endl;
    return false;
  }

  GATEINFO gateInfoUsed;
  set<FlyType> FlyType_DI = {D, I};
  set<FlyType> FlyType_I = {I};
  set<FlyType> FlyType_D = {D};
  for (int ite_sche = 0; ite_sche < schedule.size(); ite_sche++) {
    if (schedule[ite_sche]->gate.gate_size == N) {
      if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_I &&
          schedule[ite_sche]->gate.gate_leave_type == FlyType_I) {
        gateInfoUsed.gateNum_Narrow_I_I += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_D &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_D) {
        gateInfoUsed.gateNum_Narrow_D_D += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_I &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_DI) {
        gateInfoUsed.gateNum_Narrow_I_DI += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_DI &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_I) {
        gateInfoUsed.gateNum_Narrow_DI_I += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_D &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_DI) {
        gateInfoUsed.gateNum_Narrow_D_DI += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_DI &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_D) {
        gateInfoUsed.gateNum_Narrow_DI_D += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_DI &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_DI) {
        gateInfoUsed.gateNum_Narrow_DI_DI += 1;
      } else {
        perror("gate DI type error\n");
      }
    } else if (schedule[ite_sche]->gate.gate_size == W) {
      if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_I &&
          schedule[ite_sche]->gate.gate_leave_type == FlyType_I) {
        gateInfoUsed.gateNum_Wide_I_I += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_D &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_D) {
        gateInfoUsed.gateNum_Wide_D_D += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_I &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_DI) {
        gateInfoUsed.gateNum_Wide_I_DI += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_DI &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_I) {
        gateInfoUsed.gateNum_Wide_DI_I += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_D &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_DI) {
        gateInfoUsed.gateNum_Wide_D_DI += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_DI &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_D) {
        gateInfoUsed.gateNum_Wide_DI_D += 1;
      } else if (schedule[ite_sche]->gate.gate_arrive_type == FlyType_DI &&
                 schedule[ite_sche]->gate.gate_leave_type == FlyType_DI) {
        gateInfoUsed.gateNum_Wide_DI_DI += 1;
      } else {
        perror("gate DI type error\n");
      }
    } else {
      perror("gate WN type error\n");
    }
  }

  if ((gateinfo.gateNum_Narrow_DI_DI < gateInfoUsed.gateNum_Narrow_DI_DI) ||
      (gateinfo.gateNum_Narrow_DI_D < gateInfoUsed.gateNum_Narrow_DI_D) ||
      (gateinfo.gateNum_Narrow_D_D < gateInfoUsed.gateNum_Narrow_D_D) ||
      (gateinfo.gateNum_Narrow_D_DI < gateInfoUsed.gateNum_Narrow_D_DI) ||
      (gateinfo.gateNum_Narrow_DI_I < gateInfoUsed.gateNum_Narrow_DI_I) ||
      (gateinfo.gateNum_Narrow_I_DI < gateInfoUsed.gateNum_Narrow_I_DI) ||
      (gateinfo.gateNum_Narrow_I_I < gateInfoUsed.gateNum_Narrow_I_I) ||
      (gateinfo.gateNum_Wide_D_D < gateInfoUsed.gateNum_Wide_D_D) ||
      (gateinfo.gateNum_Wide_D_DI < gateInfoUsed.gateNum_Wide_D_DI) ||
      (gateinfo.gateNum_Wide_DI_D < gateInfoUsed.gateNum_Wide_DI_D) ||
      (gateinfo.gateNum_Wide_DI_DI < gateInfoUsed.gateNum_Wide_DI_DI) ||
      (gateinfo.gateNum_Wide_DI_I < gateInfoUsed.gateNum_Wide_DI_I) ||
      (gateinfo.gateNum_Wide_I_I < gateInfoUsed.gateNum_Wide_I_I) ||
      (gateinfo.gateNum_Narrow_I_DI < gateInfoUsed.gateNum_Narrow_I_DI)) {
    return false;
  }

  return true;
}

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
        ite_gate -= 1;
      }
    }
  }
  for (int ite_gate = 0; ite_gate < tempGateList.size(); ite_gate++) {
    shared_ptr<TIMELINE_GATE> timeline_gate_ptr_temp;
    FlightList Flights_temp;
    Flights_temp.clear();
    TIMELINE timeline_temp(Flights_temp);
    timeline_gate_ptr_temp.reset(
        new TIMELINE_GATE(Flights_temp, *tempGateList[ite_gate]));

    schedule.push_back(timeline_gate_ptr_temp);
  }
  if (schedule.size() != gateListAll.size()) {
    perror("Fill in empty timeline error\n");
    return false;
  }
  return true;
}

bool PLAN::optimizeTotalTime(int iter) { return true; }
bool PLAN::optimizeTotalTension(int iter) { return true; }