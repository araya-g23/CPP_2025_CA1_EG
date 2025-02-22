#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
#include <sstream>

using namespace std;
void readCSV();

struct FootballPlayer{
    string playername;
    string team;
    int age;
    int goals;
    float rating;

};
void readCSV(const string& filename, vector<FootballPlayer>& players) {
    ifstream fin(filename);
    string line;
    bool firstrow = true;
    while (getline(fin, line)) {
        if (firstrow) {
            firstrow = false;
            continue;
        }
        istringstream iss(line);
        FootballPlayer player;
        string ageStr, goalsStr, ratingStr;

        getline(iss, player.playername, ',');
        getline(iss, player.team, ',');
        getline(iss,ageStr, ',');
        getline(iss, goalsStr, ',');
        getline(iss, ratingStr, ',');

        player.age = stoi(ageStr);
        player.goals = stoi(goalsStr);
        player.rating = stof(ratingStr);

        players.push_back(player);
    }
    fin.close();
}

void display(const vector<FootballPlayer>& players) {
   for (int i = 0; i < players.size(); i++) {
       cout<< left<<setw(20)<<players[i].playername;
       cout<<setw(20)<<players[i].team;
       cout<<setw(20)<<players[i].age;
       cout<<setw(20)<<players[i].goals;
       cout<<setw(20)<<players[i].rating<<endl;


   }


}
int main() {
    string filename = "football.csv";
    vector<FootballPlayer> players;
    readCSV(filename, players);
    display(players);
    return 0;

}
// void readCSV() {
//     ifstream fin("football.csv");
//     string line;
//     vector<vector<string>> data;
//     while (getline(fin, line)) {
//         istringstream iss(line);
//         vector<string> row;
//         string cell;
//         while (getline(iss, cell, ',')) {
//             row.push_back(cell);
//         }
//         data.push_back(row);
//     }
//     fin.close();
//
//     for (size_t i = 0; i < data.size(); i++) {
//         cout<<left<<setw(20)<<data[i][0]
//         <<setw(15)<<data[i][1]
//         <<setw(5)<<data[i][2]
//         <<setw(8)<<data[i][3]
//         <<setw(20)<<data[i][4]<<endl;
//
//
//     }
//
//
// }

