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
};
typedef std::vector<shared_ptr<PASSENGERGROUP>> PassengerGroupList;
#endif
