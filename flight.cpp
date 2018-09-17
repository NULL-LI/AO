#include "flight.h"
Size FLIGHT::getTypeSize(string type) {
    for (int i = 0; i < 6; i++) {
        if (type == wide_size_names[i]) //
            return W;
    }
    return N;
}


int FLIGHT::timeDiff(int time1, int time2) { return time2 - time1; }


FLIGHT_GATE::FLIGHT_GATE(const FLIGHT flight_init,const GATE gate_init):FLIGHT(flight_init),gate(gate_init){}

bool FLIGHT_GATE::isValid(){
    return true;
}
bool FLIGHT::validFlight(shared_ptr<FLIGHT> laterFlight){
    if(laterFlight->time_go-time_go>=45)
        return true;
    else
        return false;
}