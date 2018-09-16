#include "basiclibs.h"

#ifndef gate_h
#define gate_h

class gate {
public:
  gate(int id_init, Building gate_building_init, int gate_num_init,
       Size gate_size_init, Direction gate_direction_init,
       set<FlyType> gate_arrive_type_init, set<FlyType> gate_leave_type_init);
  int id;
  Building gate_building;
  int gate_num;
  Direction gate_direction;
  Size gate_size;
  set<FlyType> gate_arrive_type;
  set<FlyType> gate_leave_type;
};

#endif