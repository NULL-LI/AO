#include "basiclibs.h"


string Trim(string &str) {

  str.erase(0, str.find_first_not_of(" \t\r\n"));
  str.erase(str.find_last_not_of(" \t\r\n") + 1);
  return str;
}
bool stringFirst(vector<string> &s1,vector<string> s2){
    return s1[0]<s2[0];
}
void gatesPucks();
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

    gatesPucks();

    return 0;
}
void gatesPucks(){
    string solution_file_name[2]={"../data/solution2.txt","../data/solution3.txt"};
    string write_file_name[2]={"../data/gates_pucks_v2.csv","../data/gates_pucks_v3.csv"};
    
    
    for(int i=0;i<2;i++){
        ifstream solution_file(solution_file_name[i]);
        ofstream write_gate(write_file_name[i]);
        vector<vector<string>> contents;
        vector<string> gate_ts;
        
        string last_string="k";
        string current_string;
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
                current_string=fields[3]+fields[5];
                if(current_string==last_string){
                    gate_ts.push_back("PK"+fields[1]);
                }else{
                    if(!gate_ts.empty()){
                        contents.push_back(gate_ts);
                        gate_ts.clear();
                    }
                    gate_ts.push_back(current_string);
                    last_string=current_string;
                    gate_ts.push_back("PK"+fields[1]);
                }
            }
            else if(!gate_ts.empty()){
                contents.push_back(gate_ts);
                gate_ts.clear();
                last_string="k";
            }
        }//end while
        solution_file.close();
        sort(contents.begin(),contents.end(),stringFirst);
        for(int i=0;i<contents.size();i++){
            for(int j=0;j<contents[i].size();j++){
                write_gate<<contents[i][j]+",";
            }
            write_gate<<endl;   
        }
    
        write_gate.close();

    }
    


}