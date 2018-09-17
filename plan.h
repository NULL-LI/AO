#include "basiclibs.h"
#include "timeline.h"

#ifndef plan_h
#define plan_h

class PLAN{
public:
    vector<shared_ptr<TIMELINE>>schedule;

    PLAN(vector<shared_ptr<TIMELINE>> timelines);

    double passengerTotalTime;
    double passengerTotalTension;

    void getpassengerTotalTime();
    void getpassengerTotalTension();

    void switchGates();



};


#endif