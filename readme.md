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

