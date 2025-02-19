#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
#include <sstream>

using namespace std;
void readCSV();
int main() {
    readCSV();
    return 0;

}
void readCSV() {
    ifstream fin("football.csv");
    string line;
    vector<vector<string>> data;
    while (getline(fin, line)) {
        istringstream iss(line);
        vector<string> row;
        string cell;
        while (getline(iss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    fin.close();

    for (size_t i = 0; i < data.size(); i++) {
        cout<<left<<setw(20)<<data[i][0]
        <<setw(15)<<data[i][1]
        <<setw(5)<<data[i][2]
        <<setw(8)<<data[i][3]
        <<setw(20)<<data[i][4]<<endl;


    }


}

