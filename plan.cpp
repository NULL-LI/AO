#include "plan.h"
PLAN::PLAN(vector<shared_ptr<TIMELINE_GATE>> timelines, PassengerGroupList pl)
    : schedule(timelines), passengerGroupListAll(pl), passengerTotalTension(0) {
  srand((unsigned)time(0));
  switchedScheduleIdx1 = 0;
  switchedScheduleIdx2 = 0;
  passengerInBuildingNumber = 0;
}

bool PLAN::getpassengerTotalTime() {
  passengerTotalTime = 0;
  for (int iter = 0; iter < passengerGroupListAll.size(); iter++) {
    if (passengerGroupListAll[iter]->inBuilding()) {
      int temp_time = formalityTime(
          passengerGroupListAll[iter]->flight_with_gate_arrive_ptr,
          passengerGroupListAll[iter]->flight_with_gate_leave_ptr);
      passengerTotalTime +=
          temp_time * (passengerGroupListAll[iter]->peopleNum);
    }
  }
  return true;
}

bool PLAN::getpassengerTotalTension() {
  passengerTotalTension = 0;
  for (int i = 0; i < passengerGroupListAll.size(); i++) {
    if (passengerGroupListAll[i]->inBuilding()) {
      double passengerTotalChangeTime = 0;
      passengerTotalChangeTime += (double)gateWalkingTime(
          passengerGroupListAll[i]->flight_with_gate_arrive_ptr->gate,
          passengerGroupListAll[i]->flight_with_gate_leave_ptr->gate);
      passengerTotalChangeTime += (double)formalityTime(
          passengerGroupListAll[i]->flight_with_gate_arrive_ptr,
          passengerGroupListAll[i]->flight_with_gate_leave_ptr);
      passengerTotalChangeTime +=
          (double)metroTime(
              passengerGroupListAll[i]->flight_with_gate_arrive_ptr,
              passengerGroupListAll[i]->flight_with_gate_leave_ptr) *
          8.0;

      double flight_connect_time = 0;
      flight_connect_time = (double)passengerGroupListAll[i]
                                ->flight_with_gate_leave_ptr->time_go -
                            (double)passengerGroupListAll[i]
                                ->flight_with_gate_arrive_ptr->time_arrive;

      passengerTotalTension += (double)passengerGroupListAll[i]->peopleNum *
                               (passengerTotalChangeTime / flight_connect_time);
    }
  }
  return true;
}

bool PLAN::getpassengerTotalNumber() {
  passengerInBuildingNumber = 0;
  for (int iter = 0; iter < passengerGroupListAll.size(); iter++) {
    if (passengerGroupListAll[iter]->inBuilding()) {
      passengerInBuildingNumber += passengerGroupListAll[iter]->peopleNum;
    }
  }
  return true;
}
// bool PLAN::getPassengerGate(PASSENGERGROUP &passengerGroup){
//
//}
bool switchable(TIMELINE_GATE time_gate_1, TIMELINE_GATE time_gate_2) {
  if (time_gate_1.gate.gate_size != time_gate_2.gate.gate_size) {
    return false;
  }
  time_gate_1.getDIType();
  time_gate_2.getDIType();
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

bool PLAN::updatePassengerFlightGate() {
  for (int i = 0; i < passengerGroupListAll.size(); i++) {
    passengerGroupListAll[i]->flight_with_gate_arrive_ptr = NULL;
    passengerGroupListAll[i]->flight_with_gate_leave_ptr = NULL;

    for (int j = 0; j < FlightGateListOfPlan.size(); j++) {
      if (FlightGateListOfPlan[j]->flight_arrive_number ==
          passengerGroupListAll[i]->flight_arrive_number) {
        int passenger_arrive_time = passengerGroupListAll[i]->date_arrive - 19;
        int flight_arrive_time = FlightGateListOfPlan[j]->time_arrive;

        if ((passenger_arrive_time == 0 && flight_arrive_time > 0 &&
             flight_arrive_time < 1440) ||
            (passenger_arrive_time == 1 && flight_arrive_time >= 1440 &&
             flight_arrive_time < 2880)) {
          passengerGroupListAll[i]->flight_with_gate_arrive_ptr =
              FlightGateListOfPlan[j];
        }
      }
    }

    //    if (passengerGroupListAll[i]->flight_with_gate_arrive_ptr == NULL)
    //      continue;

    for (int j = 0; j < FlightGateListOfPlan.size(); j++) {
      if (FlightGateListOfPlan[j]->flight_leave_number ==
          passengerGroupListAll[i]->flight_leave_number) {
        int passenger_leave_time = passengerGroupListAll[i]->date_leave - 19;
        int flight_leave_time = FlightGateListOfPlan[j]->time_go;

        if ((passenger_leave_time == 2 && flight_leave_time > 2880) ||
            (passenger_leave_time == 1 && flight_leave_time >= 1440 &&
             flight_leave_time < 2880)) {
          passengerGroupListAll[i]->flight_with_gate_leave_ptr =
              FlightGateListOfPlan[j];
        }
      }
    }
  }
}

bool PLAN::switchGatesRandom() {
  int scheduleNum = schedule.size();
  int switchIdx1 = rand() % (scheduleNum);
  int switchIdx2 = rand() % (scheduleNum);
  do {
    switchIdx1 = rand() % (scheduleNum);
    switchIdx2 = rand() % (scheduleNum);
  } while (!switchable(*schedule[switchIdx1], *schedule[switchIdx2]) ||
           switchIdx1 == switchIdx2);

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

bool PLAN::initFlightGate() {
  FlightGateListOfPlan.clear();
  for (int ite_sche = 0; ite_sche < schedule.size(); ite_sche++) {
    if (schedule[ite_sche]->FlightsOfLine.empty()) {
      continue;
    } else {
      for (int ite_fli = 0; ite_fli < schedule[ite_sche]->FlightsOfLine.size();
           ite_fli++) {
        shared_ptr<FLIGHT_GATE> flight_gate;
        flight_gate.reset(
            new FLIGHT_GATE(*schedule[ite_sche]->FlightsOfLine[ite_fli],
                            schedule[ite_sche]->gate));
        FlightGateListOfPlan.push_back(flight_gate);
      }
    }
  }
  return true;
}

bool PLAN::updateFlightGate() {
  //  FlightGateListOfPlan.clear();
  for (int ite_sche = 0; ite_sche < schedule.size(); ite_sche++) {
    if (schedule[ite_sche]->FlightsOfLine.empty()) {
      continue;
    } else {
      for (int ite_fli = 0; ite_fli < schedule[ite_sche]->FlightsOfLine.size();
           ite_fli++) {
        for (int ite_fli_gate = 0; ite_fli_gate < FlightGateListOfPlan.size();
             ite_fli_gate++) {
          if (schedule[ite_sche]->FlightsOfLine[ite_fli]->id ==
              FlightGateListOfPlan[ite_fli_gate]->id) {
            FlightGateListOfPlan[ite_fli_gate]->gate = schedule[ite_sche]->gate;
            break;
          } else {
            continue;
          }
        }
      }
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
  printf("tempGateList.size(): %ld\n", tempGateList.size());
  printf("schedule.size(): %ld\n", schedule.size());
  printf("gateListAll.size(): %ld\n", gateListAll.size());

  for (int ite_gate = 0; ite_gate < tempGateList.size(); ite_gate++) {

    FlightList Flights_temp;
    Flights_temp.clear();
    TIMELINE timeline_temp(Flights_temp);
    shared_ptr<TIMELINE_GATE> timeline_gate_ptr_temp(
        new TIMELINE_GATE(Flights_temp, *tempGateList[ite_gate]));

    schedule.push_back(timeline_gate_ptr_temp);
  }
  if (schedule.size() != gateListAll.size()) {
    perror("Fill in empty timeline error\n");
    return false;
  }
  return true;
}

bool PLAN::optimizeTotalTime() {
  int iter_max = 40;
  const double T_k = 0.92;
  const double EPS = 1e-2;
  double T_now = 500;
  while (T_now > EPS) {
    for (int i = 0; i < iter_max; i++) {
      //    printf("i %d\n",i);
      int timeStore = passengerTotalTime;

      //    printf("size: %ld %ld %ld %ld
      //    ",schedule.size(),gateListAll.size(),FlightGateListOfPlan.size(),passengerGroupListAll.size());

      switchGatesRandom();
      updateFlightGate();
      updatePassengerFlightGate();
      getpassengerTotalTime();

      double dE = passengerTotalTime - timeStore;

      if (dE < 0) { // success accept
        continue;
      } else {
        double probabilityAccept = exp((-dE) / T_now);
        if (rand() / double(RAND_MAX) < probabilityAccept) {
          continue;
        } else {
          switchGatesBack();
          updateFlightGate();
          updatePassengerFlightGate();
          getpassengerTotalTime();
        }
      }

      printf("passengerTotalTime average %f T_now %f FailNum %d FailRate %f \n",
             passengerTotalTime / (double)passengerInBuildingNumber, T_now,
             passengerQ2FailNum(),
             passengerQ2FailNum() / (double)passengerInBuildingNumber);
    }
    T_now *= T_k;
  }
  return true;
}
bool PLAN::optimizeTotalTension() {
  int iter_max = 20;
  const double T_k = 0.9;
  const double EPS = 1e-5;
  double T_now = 10;
  while (T_now > EPS) {
    for (int i = 0; i < iter_max; i++) {
      double tensionStore = passengerTotalTension;
      switchGatesRandom();
      updateFlightGate();
      updatePassengerFlightGate();
      getpassengerTotalTension();

      double dE = passengerTotalTension - tensionStore;

      if (dE < 0) { // success accept
        continue;
      } else {
        double probabilityAccept = exp((-dE) / T_now);
        if (rand() / double(RAND_MAX) < probabilityAccept) {
          continue;
        } else {
          switchGatesBack();
          updateFlightGate();
          updatePassengerFlightGate();
          getpassengerTotalTension();
        }
      }

      printf("passengerTotalTension average %f T_now %f FailNum %d FailRate %f \n",
             passengerTotalTension / (double)passengerInBuildingNumber, T_now,
             passengerQ3FailNum(),
             passengerQ3FailNum() / (double)passengerInBuildingNumber);
    }
    T_now *= T_k;
  }
  return true;
}

bool PLAN::printAllocation() {
  printf("Plan statistics :\n");
  for (auto flight_gate_ptr : FlightGateListOfPlan) {
    printf("flight_id %d gate_building %s gate_num %d\n", flight_gate_ptr->id,
           flight_gate_ptr->gate.gate_building == T ? "T" : "s",
           flight_gate_ptr->gate.gate_num);
  }
}

int PLAN::passengerQ2FailNum() {
  int FailNum = 0;
  for (int iter = 0; iter < passengerGroupListAll.size(); iter++) {
    if (passengerGroupListAll[iter]->inBuilding()) {
      if (!passengerGroupListAll[iter]->ifSuccessQ2())
        FailNum += passengerGroupListAll[iter]->peopleNum;
    }
  }
  return FailNum;
}

int PLAN::passengerQ3FailNum() {
  int FailNum = 0;
  for (int iter = 0; iter < passengerGroupListAll.size(); iter++) {
    if (passengerGroupListAll[iter]->inBuilding()) {
      if (!passengerGroupListAll[iter]->ifSuccessQ3())
        FailNum += passengerGroupListAll[iter]->peopleNum;
    }
  }
  return FailNum;
}
