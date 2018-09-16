#include "timeline.h"

TIMELINE::TIMELINE(const FlightList FlightsOfLine_init) {
  FlightsOfLine = FlightsOfLine_init;
  isValid();
}

bool TIMELINE::isValid() {
  if (getDelayNum() == true && getDIType() == true) {
      validFlag= true;
  } else {
      validFlag= true;
  }

    return validFlag;
}
bool TIMELINE::getDelayNum() { return true; }
bool TIMELINE::getDIType() { return true; }
