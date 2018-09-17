#include "timeline.h"

TIMELINE::TIMELINE(const FlightList FlightsOfLine_init) {
  FlightsOfLine = FlightsOfLine_init;
  isValid();
}

bool TIMELINE::isValid() {
  if (getDelayNum() == true && getDIType() == true && getSize() == true) {
    validFlag = true;
  } else {
    validFlag = false;
    cout << "TIMELINE invalid" << endl;
  }

  return validFlag;
}
bool TIMELINE::getDelayNum() {
  this->delayFlightNum = 0;
  for (int i = 0; i < FlightsOfLine.size() - 1; i++) {
    if (FlightsOfLine[i]->time_go + 45 > FlightsOfLine[i + 1]->time_go) {
      return false;
    } else if (FlightsOfLine[i]->time_go + 45 >
               FlightsOfLine[i + 1]->time_arrive) {
      delayFlightNum += 1;
    }
  }

  return true;
}
bool TIMELINE::getDIType() {
  this->arrive_DI_type = {};
  this->leave_DI_type = {};
  for (int i = 0; i < FlightsOfLine.size(); i++) {
    set<FlyType>::iterator iter;
    iter = arrive_DI_type.find(FlightsOfLine[i]->type_arrive);
    if (iter == arrive_DI_type.end()) { // found
      arrive_DI_type.insert(FlightsOfLine[i]->type_arrive);
    }
    iter = leave_DI_type.find(FlightsOfLine[i]->type_go);
    if (iter == leave_DI_type.end()) { // found
      leave_DI_type.insert(FlightsOfLine[i]->type_go);
    }
  }
  return true;
}

bool TIMELINE::getSize() {
  sizeNW = FlightsOfLine[0]->plane_size;
  for (int i = 0; i < FlightsOfLine.size(); i++) {
    if (FlightsOfLine[0]->plane_size != sizeNW) {
      return false;
    }
  }
  return true;
}
// TIMELINE_GATE::TIMELINE_GATE(const FlightList
// FlightsOfLine_init):TIMELINE(FlightsOfLine_init){
//    ;
//}
TIMELINE_GATE::TIMELINE_GATE(const FlightList FlightsOfLine_init,
                             const GATE gate_init)
    : TIMELINE(FlightsOfLine_init), gate(gate_init) {
  isValid();
  //    TIMELINE::;
}

bool TIMELINE_GATE::isValid() {
  if (getDelayNum() == true && getDIType() == true && getSize() == true) {
    validFlag = true;
  } else {
    validFlag = false;
    cout << "TIMELINE invalid" << endl;
  }
  if (sizeNW != gate.gate_size) {
    validFlag = false;
    cout << "GateType not match" << endl;
  }

  return validFlag;
}

bool gateCompatible(const set<FlyType > DI_Flight,const set<FlyType > DI_Gate){
  set<FlyType>::iterator iter;
  for (auto iter_flight=DI_Flight.begin();iter_flight!=DI_Flight.end();iter_flight++)
  {
  iter = DI_Gate.find(*iter_flight);
  if (iter == DI_Gate.end()) { //not found
    return false;
  }
  }
    return true;

}