#include "passenger.h"

bool PASSENGERGROUP::inBuilding() {
  if (flight_with_gate_arrive_ptr != NULL &&
      flight_with_gate_leave_ptr != NULL) {
    return true;
  } else {
    return false;
  }
}

bool PASSENGERGROUP::ifSuccessQ2() {
  double PassWalkingTime = (double)gateWalkingTime(
      flight_with_gate_arrive_ptr->gate, flight_with_gate_leave_ptr->gate);

  double PassFormalityTime = (double)formalityTime(flight_with_gate_arrive_ptr,
                                                   flight_with_gate_leave_ptr);
  double PassMetroTime = (double)metroTime(flight_with_gate_arrive_ptr,
                                           flight_with_gate_leave_ptr);
  double flight_connect_time = (double)flight_with_gate_leave_ptr->time_go -
                               (double)flight_with_gate_arrive_ptr->time_arrive;
  if (flight_connect_time < PassFormalityTime) {
    return false;
  } else {
    return true;
  }
}

bool PASSENGERGROUP::ifSuccessQ3() {
  double PassWalkingTime = (double)gateWalkingTime(
      flight_with_gate_arrive_ptr->gate, flight_with_gate_leave_ptr->gate);

  double PassFormalityTime = (double)formalityTime(flight_with_gate_arrive_ptr,
                                                   flight_with_gate_leave_ptr);
  double PassMetroTime = (double)metroTime(flight_with_gate_arrive_ptr,
                                           flight_with_gate_leave_ptr);
  double flight_connect_time = (double)flight_with_gate_leave_ptr->time_go -
                               (double)flight_with_gate_arrive_ptr->time_arrive;
//  if (flight_connect_time < 90) {
//    printf("flight_connect_time%f "
//           "(PassFormalityTime+PassWalkingTime+PassMetroTime) %f \n",
//           flight_connect_time,
//           (PassFormalityTime + PassWalkingTime + PassMetroTime));
//  }

  if (flight_connect_time <
      (PassFormalityTime + PassWalkingTime + PassMetroTime)) {
    return false;
  } else {
    return true;
  }
}

double PASSENGERGROUP::passengerTimeQ2()
{
  return PassFormalityTime();
}
double PASSENGERGROUP::passengerTimeQ3(){
  return PassFormalityTime()+PassWalkingTime()+PassMetroTime();
}

double PASSENGERGROUP::passengerTensionQ2(){
  return passengerTimeQ2()/flight_connect_time();
}
double PASSENGERGROUP::passengerTensionQ3(){
  return passengerTimeQ3()/flight_connect_time();
}