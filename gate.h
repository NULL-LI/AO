#include "basiclibs.h"

#ifndef gate_h
#define gate_h

class GATE {
public:
    GATE(int id_init, Building gate_building_init, int gate_num_init,
       Size gate_size_init, Direction gate_direction_init,
       string gate_arrive_type_init, string gate_leave_type_init);
  int id;
  Building gate_building;
  int gate_num;
  Direction gate_direction;
  Size gate_size;
    string gate_arrive_type_string;
    string gate_leave_type_string;
  set<FlyType> gate_arrive_type;
  set<FlyType> gate_leave_type;

  void getFlyType(const string gate_DI_type_string,set<FlyType>&gate_DI_type);
};

int gateShortestTime(GATE gate1,GATE gate2);

typedef std::vector<shared_ptr<GATE >> GateList;

class GATEINFO{
public:
    GATEINFO();

    int gateNum_Total;

    int gateNum_Narrow_I_I;
    int gateNum_Narrow_D_D;
    int gateNum_Narrow_I_DI;
    int gateNum_Narrow_DI_I;
    int gateNum_Narrow_D_DI;
    int gateNum_Narrow_DI_D;
    int gateNum_Narrow_DI_DI;

    int gateNum_Wide_I_I;
    int gateNum_Wide_D_D;
    int gateNum_Wide_I_DI;
    int gateNum_Wide_DI_I;
    int gateNum_Wide_D_DI;
    int gateNum_Wide_DI_D;
    int gateNum_Wide_DI_DI;

    void printGateInfo();
};
#endif