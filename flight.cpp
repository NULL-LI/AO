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
    if(laterFlight->time_arrive-time_go>=45)
        return true;
    else
        return false;
}


int formalityTime(FLIGHT_GATE flightGateArrive,FLIGHT_GATE flightGateLeave){
    int formalityTimeTable[4][4] = {
            {15,20,35,40},
            {20,15,40,35},
            {35,40,20,30},
            {40,45,30,20},
    };


    int formalityTimeArriveIdx, formalityTimeLeaveIdx;
    if (flightGateArrive.type_arrive == D) {
        switch (flightGateArrive.gate.gate_building) {
            case T:
                formalityTimeArriveIdx = 0;
                break;
            case S:
                formalityTimeArriveIdx = 1;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    } else if (flightGateArrive.type_arrive == I) {
        switch (flightGateArrive.gate.gate_building) {
            case T:
                formalityTimeArriveIdx = 2;
                break;
            case S:
                formalityTimeArriveIdx = 3;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    }
    if (flightGateLeave.type_go == D) {
        switch (flightGateLeave.gate.gate_building) {
            case T:
                formalityTimeLeaveIdx = 0;
                break;
            case S:
                formalityTimeLeaveIdx = 1;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    } else if (flightGateLeave.type_go == I) {
        switch (flightGateLeave.gate.gate_building) {
            case T:
                formalityTimeLeaveIdx = 2;
                break;
            case S:
                formalityTimeLeaveIdx = 3;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    }
    return formalityTimeTable[formalityTimeArriveIdx][formalityTimeLeaveIdx];
}


int metroTimes(FLIGHT_GATE flightGateArrive,FLIGHT_GATE flightGateLeave){
    int formalityTimeTable[4][4] = {
            {0,1,0,1},
            {1,0,1,0},
            {0,1,0,1},
            {1,2,1,0},
    };


    int formalityTimeArriveIdx, formalityTimeLeaveIdx;
    if (flightGateArrive.type_arrive == D) {
        switch (flightGateArrive.gate.gate_building) {
            case T:
                formalityTimeArriveIdx = 0;
                break;
            case S:
                formalityTimeArriveIdx = 1;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    } else if (flightGateArrive.type_arrive == I) {
        switch (flightGateArrive.gate.gate_building) {
            case T:
                formalityTimeArriveIdx = 2;
                break;
            case S:
                formalityTimeArriveIdx = 3;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    }
    if (flightGateLeave.type_go == D) {
        switch (flightGateLeave.gate.gate_building) {
            case T:
                formalityTimeLeaveIdx = 0;
                break;
            case S:
                formalityTimeLeaveIdx = 1;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    } else if (flightGateLeave.type_go == I) {
        switch (flightGateLeave.gate.gate_building) {
            case T:
                formalityTimeLeaveIdx = 2;
                break;
            case S:
                formalityTimeLeaveIdx = 3;
                break;
            default:
                perror("get timeGateIdx error\n");
        }
    }
    return formalityTimeTable[formalityTimeArriveIdx][formalityTimeLeaveIdx];
}
