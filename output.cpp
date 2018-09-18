#include "basiclibs.h"


string Trim(string &str) {

  str.erase(0, str.find_first_not_of(" \t\r\n"));
  str.erase(str.find_last_not_of(" \t\r\n") + 1);
  return str;
}
int main(){
    string solution_file_name[2]={"../data/solution2.txt","../data/solution3.txt"};
    string read_file_name="../data/pucks_v1.csv";
    string write_file_name="../data/pucks_v2.csv";

    ifstream read_file(read_file_name);
    vector<string> fin_content;
    string line;
    while (getline(read_file,line )){
        fin_content.push_back(Trim(line));
    }
    for(int i=0;i<2;i++){
        ifstream solution_file(solution_file_name[i]);
        string line;
        while (getline(solution_file, line)){
            istringstream sin(line);
            vector<string> fields;
            string field;
            while (getline(sin, field, ' ')) //
            {
                fields.push_back(Trim(field));
            }
            //find which line we needed
            if(!fields.empty() && fields[0]=="flight_id"){
                if(fields[3]=="s")
                    fields[3]="S";
                fin_content[stoi(fields[1])-1] +=(","+fields[3]+fields[5]);
            }
        }//end while
        solution_file.close();

    }

    ofstream write_file(write_file_name);
    for(int i=0;i<fin_content.size();i++){
        write_file<<fin_content[i]<<endl;
    }
    write_file.close();

    return 0;
}