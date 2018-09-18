#ifndef basiclibs_h
#define basiclibs_h

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <string.h>
#include <algorithm>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cmath>
using namespace std;

enum Size { W, N };
enum FlyType { D, I };
enum Building { T, S };
enum Direction {North,South,East,West,Center};
enum GateType{
    Narrow_I_I=0,
    Narrow_D_D=1,
    Narrow_I_DI=2,
    Narrow_DI_I=3,
    Narrow_D_DI=4,
    Narrow_DI_D=5,
    Narrow_DI_DI=6,

    Wide_I_I=7,
    Wide_D_D=8,
    Wide_I_DI=9,
    Wide_DI_I=10,
    Wide_D_DI=11,
    Wide_DI_D=12,
    Wide_DI_DI=13,
    NoneType=14
};
#define random(x)(rand()%x)




#endif