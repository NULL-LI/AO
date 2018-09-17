#include "gate.h"

GATE::GATE(int id_init, Building gate_building_init, int gate_num_init,
           Size gate_size_init, Direction gate_direction_init,
           string gate_arrive_type_init, string gate_leave_type_init) {
  id = id_init;
  gate_size = gate_size_init;
  gate_building = gate_building_init;
  gate_num = gate_num_init;
  gate_direction = gate_direction_init;
  gate_arrive_type_string = gate_arrive_type_init;
  gate_leave_type_string = gate_leave_type_init;
  //    cout<<gate_arrive_type_init<<endl;
  getFlyType(gate_arrive_type_string, gate_arrive_type);
  getFlyType(gate_leave_type_string, gate_leave_type);
};
void GATE::getFlyType(const string gate_DI_type_string,
                      set<FlyType> &gate_DI_type) {
  if (strcmp(gate_DI_type_string.data(), "\"D; I\"") == 0) {
    gate_DI_type = {D, I};
  } else if (strcmp(gate_DI_type_string.data(), "D") == 0) {
    gate_DI_type = {D};
  } else if (strcmp(gate_DI_type_string.data(), "I") == 0) {
    gate_DI_type = {I};
  }
  //    for(auto it = gate_DI_type.begin(); it != gate_DI_type.end(); it++)
  //    {
  //        cout<<*it<<" ";
  //    }
  //    cout<<endl;
}
void GATEINFO::printGateInfo() {
  printf("gateNum_Narrow_I_I %d\n", gateNum_Narrow_I_I);

  printf("gateNum_Narrow_D_D %d\n", gateNum_Narrow_D_D);
  printf("gateNum_Narrow_I_DI %d\n", gateNum_Narrow_I_DI);
  printf("gateNum_Narrow_DI_I %d\n", gateNum_Narrow_DI_I);

  printf("gateNum_Narrow_D_DI %d\n", gateNum_Narrow_D_DI);

  printf("gateNum_Narrow_DI_D %d\n", gateNum_Narrow_DI_D);

  printf("gateNum_Narrow_DI_DI %d\n", gateNum_Narrow_DI_DI);

  printf("gateNum_Wide_I_I %d\n", gateNum_Wide_I_I);

  printf("gateNum_Wide_D_D %d\n", gateNum_Wide_D_D);

  printf("gateNum_Wide_I_DI %d\n", gateNum_Wide_I_DI);

  printf("gateNum_Wide_DI_I %d\n", gateNum_Wide_DI_I);

  printf("gateNum_Wide_D_DI %d\n", gateNum_Wide_D_DI);

  printf("gateNum_Wide_DI_D %d\n", gateNum_Wide_DI_D);

  printf("gateNum_Wide_DI_DI %d\n", gateNum_Wide_DI_DI);
}

int gateShortestTime(GATE gate1, GATE gate2) {
  int timeTableGate[7][7] = {
      {10, 15, 20, 25, 20, 25, 25}, {15, 10, 15, 20, 15, 20, 20},
      {20, 15, 10, 25, 20, 25, 25}, {25, 20, 25, 10, 15, 20, 20},
      {20, 15, 20, 15, 10, 15, 15}, {25, 20, 25, 20, 15, 10, 20},
      {25, 20, 25, 20, 15, 20, 10},
  };
  int timeGateIdx1, timeGateIdx2;

  if (gate1.gate_building == T) {
    switch (gate1.gate_direction) {
    case North:
      timeGateIdx1 = 0;
      break;
    case Center:
      timeGateIdx1 = 1;
      break;
    case South:
      timeGateIdx1 = 2;
      break;
    default:
      perror("get timeGateIdx error\n");
    }
  } else if (gate1.gate_building == S) {
    switch (gate1.gate_direction) {
    case North:
      timeGateIdx1 = 3;
      break;
    case Center:
      timeGateIdx1 = 4;
      break;
    case South:
      timeGateIdx1 = 5;
      break;
    case East:
      timeGateIdx1 = 6;
      break;
    default:
      perror("get timeGateIdx error\n");
    }
  }
  if (gate2.gate_building == T) {
    switch (gate2.gate_direction) {
    case North:
      timeGateIdx2 = 0;
      break;
    case Center:
      timeGateIdx2 = 1;
      break;
    case South:
      timeGateIdx2 = 2;
      break;
    default:
      perror("get timeGateIdx error\n");
    }
  } else if (gate2.gate_building == S) {
    switch (gate2.gate_direction) {
    case North:
      timeGateIdx2 = 3;
      break;
    case Center:
      timeGateIdx2 = 4;
      break;
    case South:
      timeGateIdx2 = 5;
      break;
    case East:
      timeGateIdx2 = 6;
      break;
    default:
      perror("get timeGateIdx error\n");
    }
  }

  return timeTableGate[timeGateIdx1][timeGateIdx2];
}

GATEINFO::GATEINFO() {
  gateNum_Narrow_I_I = 0;
  gateNum_Narrow_D_D = 0;
  gateNum_Narrow_I_DI = 0;
  gateNum_Narrow_DI_I = 0;
  gateNum_Narrow_D_DI = 0;
  gateNum_Narrow_DI_D = 0;
  gateNum_Narrow_DI_DI = 0;

  gateNum_Wide_I_I = 0;
  gateNum_Wide_D_D = 0;
  gateNum_Wide_I_DI = 0;
  gateNum_Wide_DI_I = 0;
  gateNum_Wide_D_DI = 0;
  gateNum_Wide_DI_D = 0;
  gateNum_Wide_DI_DI = 0;
}