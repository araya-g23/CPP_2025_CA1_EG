#include <algorithm>
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


    cout<<fixed<<setprecision(2);

    cout<<"**************************************************************************************"<<endl;

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
    cin.ignore();
    string searchname;
    getline(cin, searchname);
    int index=findplayername(players,searchname);
    if (index!=-1) {
        cout<<"player found at index "<<index<<endl;
        cout<<left<<setw(20)<<"Player Name"
        <<setw(20)<<"Team"
        <<setw(20)<<"Age"
        <<setw(20)<<"Goals"
        <<setw(20)<<"Rating"<<endl;


        cout<<fixed<<setprecision(2);

        cout<<"**************************************************************************************"<<endl;

        cout<<left<<setw(20)<<players[index].playername
        <<setw(20)<<players[index].team
        <<setw(20)<<players[index].age
        <<setw(20)<<players[index].goals
        <<setw(20)<<players[index].rating<<endl;

        cout<<"**************************************************************************************"<<endl;

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
    cout<<left<<setw(20)<<"Team"
    <<setw(20)<<"Count"<<endl;
    for (const auto& count: teamCounts) {
        cout<<left<<setw(20)<<count.first
        <<setw(20)<<count.second<<endl;
    }

}

void filterByTame(vector<FootballPlayer>& players) {
    cout<<"enter a team name: ";
    cin.ignore();
    string teamname;
    bool found = false;
    getline(cin, teamname);
    cout<<left<<setw(20)<<"Player Name"
        <<setw(20)<<"Team"
        <<setw(20)<<"Age"
        <<setw(20)<<"Goals"
        <<setw(20)<<"Rating"<<endl;


    cout<<fixed<<setprecision(2);

    cout<<"**************************************************************************************"<<endl;

    for (const auto& player: players) {
        if (player.team == teamname) {
            found = true;
            cout<<left<<setw(20)<<player.playername
            <<setw(20)<<player.team
            <<setw(20)<<player.age
            <<setw(20)<<player.goals
            <<setw(20)<<player.rating<<endl;
            cout<<"**************************************************************************************"<<endl;

        }

    }
    if (!found) {
        cout<<"team not found"<<endl;
    }

}
int calculateGoalStats(const vector<FootballPlayer>& players, FootballPlayer& highest, FootballPlayer& lowest) {
//https://stackoverflow.com/questions/32447086/finding-the-highest-and-lowest-number
    int totalGoals = 0;
    highest=lowest=players[0];

    for (int i = 1; i < players.size(); i++) {
        if (players[i].goals > highest.goals) {
            highest=players[i];
        }
        if (players[i].goals < lowest.goals) {
            lowest=players[i];
        }
        totalGoals += players[i].goals;
    }
    return totalGoals/players.size();

}
void displayGoalStats(const vector<FootballPlayer>& players) {
    FootballPlayer highest, lowest;
    int averageGoals = calculateGoalStats(players, highest, lowest);

    cout<<"higehest goal Scorer: "<<highest.playername<<" ( "<<highest.goals<<" )"<<endl;
    cout<<"Lowest goal Scorer: "<<lowest.playername<<" ( "<<lowest.goals<<" )"<<endl;
    cout << "Average Goal Scored: "<<averageGoals<<endl;
}

void sortByRating(vector<FootballPlayer>& players) {
    auto func=[](const FootballPlayer& a, const FootballPlayer& b) {
        return a.rating >   b.rating;
    };
    sort(players.begin(), players.end(), func);
}

vector<FootballPlayer>searchPlayers(const vector<FootballPlayer>& players, const string& name) {
    vector<FootballPlayer> playerName;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].playername.find(name) != string::npos) {
            playerName.push_back(players[i]);
        }
    }
    return playerName;

}
void displaySearchPlayers(const vector<FootballPlayer>& players) {
    cout<<"enter a player name: ";
    cin.ignore();
    string search;
    getline(cin, search);
    vector<FootballPlayer> results=searchPlayers(players, search);

    if (!results.empty()) {
        cout<<"players found: \n";
        display(results);
    }
    else {
        cout<<"player not found\n"<<endl;
    }
}
void menu(vector<FootballPlayer>& players) {
    int option;
    do {
        cout<<"enter option: \n"
        <<"[1]. Display all players\n"
        <<"[2]. Search for a player by name\n"
        << "[3]. Count players by team\n"
        << "[4]. Filter players by team\n"
        << "[5]. Show goal statistics\n"
        << "[6]. Sort players by rating( descending )\n"
        << "[7]. Search players by partial name\n"
        << "[8]. Exit\n";
        cin>>option;
        switch (option) {
            case 1:
                display(players);
            break;
            case 2:
                displayfindplayername(players);
            break;
            case 3:
                //map<string,int> teamCounts = countplayersByTeam(players);
                dispalyTeamCounts(countplayersByTeam(players));
            break;
            case 4:
                filterByTame(players);
            break;
            case 5:
                displayGoalStats(players);
            break;
            case 6:
                cout<<"Before Sorting by Rating: \n";
                display(players);
                sortByRating(players);

                cout<<"After Sorting by Rating: \n";
                display(players);
            break;
            case 7:
                displaySearchPlayers(players);
            break;
            case 8:
                cout<<"Exit\n";
            break;
            default:
                cout<<"Invalid option\n";

        }

    }
    while(option!=8);
}

int main() {
    string filename = "football.csv";
    vector<FootballPlayer> players;
    readCSV(filename, players);
    menu(players);


    return 0;

}


