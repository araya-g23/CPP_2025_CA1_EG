#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
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

    cout<<left<<setw(20)<<"Player Name"
    <<setw(20)<<"Team"
    <<setw(20)<<"Age"
    <<setw(20)<<"Goals"
    <<setw(20)<<"Rating"<<endl;

   for (int i = 0; i < players.size(); i++) {
       cout<< left<<setw(20)<<players[i].playername;
       cout<<setw(20)<<players[i].team;
       cout<<setw(20)<<players[i].age;
       cout<<setw(20)<<players[i].goals;
       cout<<setw(20)<<players[i].rating<<endl;


   }


}
int findplayername(const vector<FootballPlayer>& players,const string& name) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].playername == name) {
            return i;
        }
    }
    return -1;

}
void displayfindplayername(const vector<FootballPlayer>& players) {
    cout<<"enter a player name to search: ";
    string searchname;
    getline(cin, searchname);
    int index=findplayername(players,searchname);
    if (index!=-1) {
        cout<<"player found at index "<<index<<endl;
        cout<<left<<setw(20)<<players[index].playername
        <<setw(20)<<players[index].team
        <<setw(20)<<players[index].age
        <<setw(20)<<players[index].goals
        <<setw(20)<<players[index].rating<<endl;
    }
    else {
        cout<<"player not found"<<endl;
    }

}

map<string,int> countplayersByTeam(const vector<FootballPlayer>& players) {
    map<string,int> teamCounts;
    for (int i = 0; i < players.size(); i++) {
        teamCounts[players[i].team]++;
    }
    return teamCounts;

}

void dispalyTeamCounts(const map<string,int>& teamCounts) {
    for (const auto& count: teamCounts) {
        cout<<left<<setw(20)<<count.first
        <<setw(20)<<count.second<<endl;
    }

}

int main() {
    string filename = "football.csv";
    vector<FootballPlayer> players;
    readCSV(filename, players);
    display(players);
    displayfindplayername(players);

    map<string,int> teamCounts = countplayersByTeam(players);
    dispalyTeamCounts(teamCounts);
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

