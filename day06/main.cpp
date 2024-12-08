#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "guard.cpp"
using namespace std;

int main(){
    string line;
    int line_count{0};
    ifstream inputFile("input.txt");
    Guard guard;
    vector<string> lab_map;
    bool in_bounds{true};
    int distinct_positions{0};
    string map_after;
    int start_x{0}, start_y{0};

    
    //initial position and direction
    //filling vector with playing field
    while(getline(inputFile, line)){
        if(line.find('^') < line.size()){
            start_x = line.find('^');
            start_y = line_count;
            guard.set_positions(start_x, line_count);
            guard.set_direction('^');

        }

        lab_map.push_back(line);
        line_count++;
    }
    inputFile.close();

    vector<string> lab_map_2 (lab_map);
    Guard guard_2(guard);

    //moving guard by rules
    while(in_bounds){
        //cout << guard.display_guard() << endl;
        in_bounds = guard.move_guard(lab_map,1);
    }


    cout << "The map after the guard left:\n\n";

    //counting the number of distint positions
    for(string line: lab_map){

        map_after += line + "\n";

        for(char c: line){
            if(c=='X'){
                distinct_positions++;
            }
        }
    }
    
    cout << map_after << endl;

    ofstream outputFile("output.txt");
    outputFile << map_after;
    outputFile.close();

    cout << "\n\n\nThe number of distinct positions is: \e[1m" + to_string(distinct_positions) + "\e[0m"<< endl;

   

    int loop_option{0};
    long count{0};
    line = "";

    for(int j = 0; j<lab_map_2.size(); j++){
        line = lab_map_2[j];
        for(int i=0; i<line.size(); i++){
            count++;
            if(line[i]!='#'&&line[i]!='^'){
                lab_map_2[j].replace(i,1,1,'O');
                in_bounds = true;
                while(in_bounds){
                    in_bounds = guard_2.move_guard(lab_map_2,2);
                    
                    if(guard_2.get_x() == start_x && guard_2.get_y()==start_y && guard_2.get_direction() == '^'){
                        loop_option++;
                        break;
                    }
                }
                lab_map_2[j].replace(i,1,1,'.');
                guard_2.set_positions(start_x, start_y);
                guard_2.set_direction('^');
            }
        }
    }
    cout << count <<endl;

    cout << "\n\n\nThe number of different options with obstruction is: \e[1m" + to_string(loop_option) + "\e[0m"<< endl;

    cout<<"Press Enter to exit..."; cin.get();
}
