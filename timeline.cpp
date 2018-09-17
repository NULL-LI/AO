#include "timeline.h"

TIMELINE::TIMELINE(const FlightList FlightsOfLine_init) {
  FlightsOfLine = FlightsOfLine_init;
  isValid();
}

bool TIMELINE::isValid() {
  if (getDelayNum() == true && getDIType() == true) {
      validFlag= true;
  } else {
      validFlag= false;
      cout<<"TIMELINE invalid"<<endl;
  }

    return validFlag;
}
bool TIMELINE::getDelayNum() { return true; }
bool TIMELINE::getDIType() { return true; }


//TIMELINE_GATE::TIMELINE_GATE(const FlightList FlightsOfLine_init):TIMELINE(FlightsOfLine_init){
//    ;
//}
TIMELINE_GATE::TIMELINE_GATE(const FlightList FlightsOfLine_init,const GATE gate_init):TIMELINE(FlightsOfLine_init),gate(gate_init){

//    TIMELINE::;
}

bool TIMELINE_GATE::isValid() {
    if (getDelayNum() == true && getDIType() == true) {
        validFlag= true;
    } else {
        validFlag= false;
        cout<<"TIMELINE invalid"<<endl;
    }

    return validFlag;
}