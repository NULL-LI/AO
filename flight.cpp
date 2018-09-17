#include "flight.h"
Size FLIGHT::getTypeSize(string type) {
    for (int i = 0; i < 6; i++) {
        if (type == wide_size_names[i]) //
            return W;
    }
    return N;
}


int FLIGHT::timeDiff(int time1, int time2) { return time2 - time1; }


FLIGHT_GATE::FLIGHT_GATE(const GATE gate_init):gate(gate_init){}