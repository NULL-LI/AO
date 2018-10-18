AO

## class Flight:
- int id;
- int time_arrive;
- int time_go;
- Size type_size;
- FlyType type_arrive;
- FlyType type_go;
- string flight_arrive;
- string flight_go;

## class Gates:

- (enum) StationType station_type;
- (enum) Direction direction;
- Size type_size; //wide or slim
- FlyType type_arrive;
- FlyType type_go;

## class Graph

```c++
Graph::Graph(FlightList flightGroup);//receive a FlightList when constructing
Graph::solve();//do all the needed calculation and the results stored in attribute path_list;
GraphPtr->path_list; //access the results
```

result1:

各个班次分别考虑

```
nii ndd nid ndi wii wdd wid wdi
   8pairs:  20 path:   8 size:  28
  30pairs: 115 path:  30 size: 145
   9pairs:  27 path:   9 size:  36
  14pairs:  31 path:  14 size:  45
  15pairs:  24 path:  15 size:  39
   0pairs:   0 path:   0 size:   0
   2pairs:   3 path:   2 size:   5
   1pairs:   4 path:   1 size:   5

   combine: wdi+wid
   3pairs:   7 path:   3 size:  10
```

