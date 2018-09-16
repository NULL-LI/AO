#include "basiclibs.h"

#ifndef gate_h
#define gate_h


class gate{
public:
    gate(int id_init,Size gate_size_init,Building gate_building_init,int gate_num_init) ;
    int id;
    Size gate_size;
    Building gate_building;
    int gate_num;
};


#endif