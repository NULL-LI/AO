#include "basiclibs.h"
#include "flight.h"
#ifndef passenger_h
#define passenger_h

class PASSENGERGROUP {
public:
  int id;
  int peopleNum;

  int date_arrive;
  int date_leave;

  string flight_arrive_number;
  string flight_leave_number;
  shared_ptr<FLIGHT_GATE> flight_with_gate_arrive_ptr;
  shared_ptr<FLIGHT_GATE> flight_with_gate_leave_ptr;
  bool inBuilding();
  bool ifSuccessQ2();
  bool ifSuccessQ3();
  double PassWalkingTime() {
    return (double)gateWalkingTime(flight_with_gate_arrive_ptr->gate,
                                   flight_with_gate_leave_ptr->gate);
  }

  double PassFormalityTime() {
    return (double)formalityTime(flight_with_gate_arrive_ptr,
                                 flight_with_gate_leave_ptr);
  }
  double PassMetroTime() {
    return (double)metroTime(flight_with_gate_arrive_ptr,
                             flight_with_gate_leave_ptr);
  }
  double flight_connect_time() {
    return (double)flight_with_gate_leave_ptr->time_go -
           (double)flight_with_gate_arrive_ptr->time_arrive;
  }

    double passengerTimeQ2();
    double passengerTimeQ3();

    double passengerTensionQ2();
    double passengerTensionQ3();
};
typedef std::vector<shared_ptr<PASSENGERGROUP>> PassengerGroupList;
#endif
