class Flight:
- int id;
- int time_arrive;
- int time_go;
- Size type_size;
- FlyType type_arrive;
- FlyType type_go;
- string flight_arrive;
- string flight_go;

class Gates:
- (enum) StationType station_type;
- (enum) Direction direction;
- Size type_size; //wide or slim
- FlyType type_arrive;
- FlyType type_go;

class Nodes:
- 
