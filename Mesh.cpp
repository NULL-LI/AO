#include "Mesh.h"

void Mesh::addFlights(string flights_name) {
  ifstream fin(flights_name);
  string line;
  int page = 0;
  while (getline(fin, line)) { // for (int i = 0; i < 700; i++) {
    page++;

    // getline(fin, line);   //
    istringstream sin(line);
    vector<string> fields; //
    string field;
    while (getline(sin, field, ',')) //
    {
      fields.push_back(Trim(field)); //
                                     // cout << Trim(field) << endl;
    }
    int date_arrive, date_go;
    // cout << fields[1] << endl;
    date_arrive = stoi(fields[1].substr(0, 2));
    date_go = stoi(fields[6].substr(0, 2));
    // cout << "arrive" << date_arrive << " go" << date_go << endl;
    if (date_arrive == 20 || date_go == 20) {
      cout << "arrive" << date_arrive << " go" << date_go << endl;
      cout << "pages:" << page << endl;
      shared_ptr<Flight>flight;
      flight.reset(new Flight());
      flight->id = stoi(fields[0].substr(2, 3));
      int hour, minute;
      // char * date_time = fields[2].data();
      sscanf(fields[2].data(), "%d:%d", &hour, &minute);
      if (date_arrive != 20) {
        flight->time_arrive = 24 * 60 + hour * 60 + minute;
      } else {
        flight->time_arrive = hour * 60 + minute;
      }
      sscanf(fields[7].data(), "%d:%d", &hour, &minute);
      flight->time_go = hour * 60 + minute; // stoi(fields[7].substr(0, 2)) * 60
                                            // + stoi(fields[7].substr(3, 2));
                                            //      cout << fields[4] << endl;
      flight->type_arrive = (fields[4] == "D" ? D : I);
      //      cout << fields[9] << endl;
      flight->type_go = (fields[9] == "D" ? D : I);
      flight->plane_size = flight->getTypeSize(fields[5]);
      flight->flight_arrive = fields[3];
      flight->flight_go = fields[8];
      flightListAll.push_back(flight);
    } // if

  } // for
  for (int i = 0; i < flightListAll.size(); i++) {
    cout << "id:" << flightListAll[i]->id
         << " flight arrive:" << flightListAll[i]->flight_arrive
         << "type arrive:" << flightListAll[i]->type_arrive << endl;
  }
  // cout << "pages:" << page << endl;
}

void Mesh::addGates(string gates_src_name) {
  ifstream fin(gates_src_name);
  string line;
  int gates_cnt = 0;
  while (getline(fin, line)) {
    istringstream sin(line);

    //      cout<<line<<endl;
    vector<string> fields; //
    string field;
    while (getline(sin, field, ',')) //
    {
      fields.push_back(Trim(field)); //
                                     //          cout<<field<<endl;
    }
    //      cout<<fields.size()<<endl;
    int id = gates_cnt++;
    Building gate_building = (fields[1] == "T" ? T : S);
    int gate_num;
    char tmp[2];
    sscanf(fields[0].data(), "%s%d", tmp, &gate_num);
    Direction gate_direction;
    //      string direction;
    if (strcmp(fields[2].data(), "North") == 0) {
      gate_direction = North;
    } else if (strcmp(fields[2].data(), "South") == 0) {
      gate_direction = South;
    } else if (strcmp(fields[2].data(), "East") == 0) {
      gate_direction = East;
    } else if (strcmp(fields[2].data(), "West") == 0) {
      gate_direction = West;
    } else // if(strcmp(fields[2].data(),"Center")==0 )
    {
      gate_direction = Center;
    }
    Size gate_size = (fields[5] == "W" ? W : N);
    shared_ptr<GATE>gate_tmp;
    gate_tmp.reset( new GATE(id, gate_building, gate_num, gate_size,
                          gate_direction, fields[3], fields[4]));
    gateListAll.push_back(gate_tmp);
  }
}

void Mesh::clear() {
  size_t i;
  for (i = 0; i < flightListAll.size(); i++) {
    if (flightListAll[i] != NULL){
      
    }
//      delete flightListAll[i];
  }
}

string Mesh::Trim(string &str) {

  str.erase(0, str.find_first_not_of(" \t\r\n"));
  str.erase(str.find_last_not_of(" \t\r\n") + 1);
  return str;
}

int Flight::timeDiff(int time1, int time2) { return time2 - time1; }

Size Flight::getTypeSize(string type) {
  for (int i = 0; i < 6; i++) {
    if (type == wide_size_names[i]) //
      return W;
  }
  return N;
}
