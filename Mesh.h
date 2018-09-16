#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class Flight;
class Mesh;
string wide_size_names[6] = { "332","333","33E","33H","33L","773" };
typedef std::vector<Flight*> FlightList;
enum Size {
	WIDE,
	SLIM
};
enum FlyType {
	D,
	I
};
class Flight
{
private:
	
public:

	int id;
	int time_arrive;
	int time_go;
	Size type_size;//宽窄型
	FlyType type_arrive;//到达类型/出发类型
	FlyType type_go;
	string flight_arrive;
	string flight_go;

	Flight(){}
	int timeDiff(int time1, int time2) {
		return time2 - time1;
	}
	Size getTypeSize(string type) {
		for (int i = 0; i < 6; i++) {
			if (type == wide_size_names[i])//
				return WIDE;
		}
		return SLIM;
	}
};
class Mesh {
public:
	FlightList flightList;
	Mesh(){}
	~Mesh() { clear(); }
	void addFlights(string flights_name) {
		ifstream fin(flights_name); //打开文件流操作
		string line;
		int page=0;
		while (getline(fin, line)){//for (int i = 0; i < 700; i++) {
			page++;
			
			//getline(fin, line);   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
			//cout << "原始字符串：" << line << endl; //整行输出
			istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
			vector<string> fields; //声明一个字符串向量
			string field;
			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			{
				fields.push_back(Trim(field)); //将刚刚读取的字符串添加到向量fields中
				//cout << Trim(field) << endl;
			}
			int date_arrive, date_go;
			//cout << fields[1] << endl;
			date_arrive = stoi(fields[1].substr(0, 2));
			date_go=stoi(fields[6].substr(0, 2));
			//cout << "arrive" << date_arrive << " go" << date_go << endl;
			if (date_arrive == 20 || date_go == 20) {
				cout << "arrive" << date_arrive << " go" << date_go << endl;
				cout << "pages:" << page << endl;
				Flight *flight = new Flight();
				flight->id = stoi(fields[0].substr(2,3));
				int hour, minute;
				//char * date_time = fields[2].data();
				sscanf_s(fields[2].data(),"%d:%d",&hour,&minute);
				if (date_arrive != 20) {
					flight->time_arrive = 24* 60 + hour * 60 + minute;
				}
				else {
					flight->time_arrive = hour * 60 + minute;
				}
				sscanf_s(fields[7].data(), "%d:%d", &hour, &minute);
				flight->time_go= hour * 60 + minute; //stoi(fields[7].substr(0, 2)) * 60 + stoi(fields[7].substr(3, 2));
				cout << fields[4] << endl;
				flight->type_arrive = (fields[4] == "D" ? D : I);
				cout << fields[9] << endl;
				flight->type_go= (fields[9] == "D" ? D : I);
				flight->type_size = flight->getTypeSize(fields[5]);
				flight->flight_arrive = fields[3];
				flight->flight_go = fields[8];
				flightList.push_back(flight);
			}//if
			
		}//for
		for (int i = 0; i < flightList.size(); i++) {
			cout << "id:" << flightList[i]->id << " flight arrive:" << flightList[i]->flight_arrive <<"type arrive:"<<flightList[i]->type_arrive << endl;
		}
		//cout << "pages:" << page << endl;
	}
	void clear() {
		size_t i;
		for (i = 0; i < flightList.size(); i++) {
			if (flightList[i] != NULL)
				delete flightList[i];
		}
	}
	string Trim(string& str)
	{
		//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
		str.erase(0, str.find_first_not_of(" \t\r\n"));
		str.erase(str.find_last_not_of(" \t\r\n") + 1);
		return str;
	}
};