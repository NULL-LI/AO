#include "plan.h"
PLAN::PLAN(vector<shared_ptr<TIMELINE>> timelines) {}

bool PLAN::getpassengerTotalTime() { return true; }
bool PLAN::getpassengerTotalTension() { return true; }

bool PLAN::switchGatesRandom() { return true; }
bool PLAN::switchGatesBack() { return true; }

bool PLAN::isValid() { return true; }

bool PLAN::updateFlightGate(){ return true;}

bool PLAN::optimizeTotalTime(int iter){
    return true;
}
bool PLAN::optimizeTotalTension(int iter){
    return true;
}