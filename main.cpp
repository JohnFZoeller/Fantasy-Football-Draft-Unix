#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "team.h" 
#include "draft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <vector>
using namespace std;

void intro();                                                       //intro message
const bool contains(const vector<int>& v, const int& target);
void clearIn();                                                     //clear; ignore;

int main() {
    int numTeams, numUsers = 1, draftPosition, i, j;                //primitives
    string teamName;

    Team *teams;                                                      //abstracts
    NodeData *ptr = NULL;
    Draft draft;
    vector<NodeData*> players;                                        //all players
    vector<int> claimedDraftPositions;                                //taken Picks

    //----------------------------PART ONE--------------------------------
    intro();
    teams = new Team[numTeams = 10];
    draft.setNumTeams(numTeams);

    for(i = 0; i < numUsers; i++) {                                  //set user info
        cout << "Enter your name: ";
        getline(cin, teamName);
        cout << endl << endl;

        do {                                                         //set draft positions
            cout << "Enter draft position (1 - " << numTeams << ") : ";
            cin >> draftPosition;
            clearIn();
        } while(draftPosition < 1 || draftPosition > numTeams ||
        		 contains(claimedDraftPositions, draftPosition));

        teams[draftPosition - 1] = Team(teamName, draftPosition, true);
        claimedDraftPositions.push_back(draftPosition);
    }


    for(j = 0; j < numTeams; j++)                                   //fill autopicks
        if(teams[j].getUser() == false)                               //not a user?
            teams[j] = Team("auto", (j + 1), false);                  //make autopick

    //-------------------------------END PART ONE----------------------------
    //now read in player list into vector
    //----------------------------------PART TWO----------------------------
    cout << "\n\nRetreiving ESPN Player Data... \n";

    system("sh 2017.sh");
    ifstream in("players.txt");                                    //open file
    
    if(!in) {                                                       //file validity
        cout << "File could not be opened.\n";
        return 1;
    }

    while(!in.eof()) {
        Player playerObject;
        ptr = playerObject.makeFromStream(in);

        for(int i = 0; i < players.size(); i++)                    //search whole vector
            if(ptr == players[i])                                  //...for repeats
                delete ptr;                                        //...delete repeats

        if(ptr != NULL) players.push_back(ptr);                        //add player
    }

    cout << "Players Acquired \n\n\n";

    //---------------------------------END PART TWO----------------------------
    //--------------------------------PART THREE-----------------------------

    draft.pickTime();
    draft.makeBoard(teams, players, numTeams);
    return 0;
}

const bool contains(const vector<int>& v, const int& target) {
    return find(v.begin(), v.end(), target) != v.end();
}

void intro(){
	system("clear;");
    string line = "-------------------------------------------";
    cout << line + line << endl;
    cout << "                     FANTASY FOOTBALL DRAFT SIMULATOR - JOHN ZOELLER" << endl;
    cout << line + line << endl << endl << endl;
}

void clearIn() {
    cin.clear();
    cin.ignore(100, '\n');
}

//commmented out 

    // cout << "Welcome to The Draft Machine. "
    // << "Default teams consist of: " << endl 
    // << "1 Quarterback" << endl
    // << "2 Running backs" << endl
    // << "2 Wide Recievers " << endl
    // << "1 Flex" << endl
    // << "1 Tight End " << endl
    // << "1 Defense " << endl
    // << "1 Kicker" << endl
    // << "8 Bench spots" << endl << endl;
    // cout << "10 teams, 1 user " << endl;

    /*do{                                                             //get numTeams
        cout << "Choose between 4 and 12 teams: ";
        cin >> numTeams;
        cin.clear();
        cin.ignore(100, '\n');
    } while(numTeams < 4 || numTeams > 12);

    cout << endl << "Ok, there will be " << numTeams << " teams. " << endl << endl;*/
    // do{                                                             //get numUsers
    //     cout << "Choose between 0 and " << numTeams << " users: ";
    //     cin >> numUsers;
    //     cin.clear();
    //     cin.ignore(100, '\n');
    // } while(numUsers < 0 || numUsers > numTeams);

    // cout << "Ok, there will be " << numUsers << " user(s) and " 
    // << (numTeams - numUsers) << " autopicks" << endl;
        //cout << "Enter user " << i + 1 << "'s  name: ";

        // teams[i] = Team(teamName, draftPosition, true);               //new team object
        // teams[draftPosition - 1] = teams[i];                            //correct teamsay position
        // claimedDraftPositions.push_back(draftPosition);                           //pick number taken


        // if((draftPosition - 1) != i)                                //replace old teamsay pos
        //     teams[i] = Team();                                        //...with a blank team
