#include "passenger.h"

bool PASSENGERGROUP::inBuilding(){
    if(flight_with_gate_arrive_ptr!=NULL&&flight_with_gate_leave_ptr!=NULL)
    {
        return true;
    } else{
        return false;
    }
}


bool PASSENGERGROUP::ifFailQ2(){
//if()
}

bool PASSENGERGROUP::ifFailQ3(){

}
