#include "gate.h"

gate::gate(int id_init, Building gate_building_init, int gate_num_init,
           Size gate_size_init, Direction gate_direction_init,
           set<FlyType> gate_arrive_type_init, set<FlyType> gate_leave_type_init) {
    id=id_init;
    gate_size=gate_size_init;
    gate_building=gate_building_init;
    gate_num=gate_num_init;
    gate_direction=gate_direction_init;
    gate_arrive_type=gate_arrive_type_init;
    gate_leave_type=gate_leave_type_init;
};
