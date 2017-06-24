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
bool check(vector<int>& vec, int a);                                //vector.contains();
void clearIn();                                                     //clear; ignore;

int main(){
    int numTeams, numUsers = 1, draftPosition, i, j;                //primitives
    string teamName;

    Team *arr;                                                      //abstracts
    NodeData *ptr = NULL;
    Draft draft;
    vector <NodeData*> allV;                                        //all players
    vector <int> pickNum;                                           //taken Picks

    //------------------------------------PART ONE--------------------------------
    intro();
    arr = new Team[numTeams = 10];
    draft.setNum(numTeams);

    for(i = 0; i < numUsers; i++){                                  //set user info
        cout << "Enter your name: ";
        getline(cin, teamName);
        cout << endl << endl;

        do{                                                         //set draft positions
            cout << "Enter draft position (1 - " << numTeams << ") : ";
            cin >> draftPosition;
            clearIn();
        } while(draftPosition < 1 || draftPosition > numTeams || !check(pickNum, draftPosition));

        arr[draftPosition - 1] = Team(teamName, draftPosition, true);
        pickNum.push_back(draftPosition);
    }


    for(j = 0; j < numTeams; j++)                                   //fill autopicks
        if(arr[j].getUser() == false)                               //not a user?
            arr[j] = Team("auto", (j + 1), false);                  //make autopick

    //-------------------------------END PART ONE----------------------------
    //now read in player list into vector
    //----------------------------------PART TWO----------------------------
    cout << "\n\nRetreiving ESPN Player Data... \n";

    system("sh 2017.sh");
    ifstream in("players.txt");                                    //open file
    
    if(!in){                                                       //file validity
        cout << "File could not be opened.\n";
        return 1;
    }

    while(!in.eof()){
        Player john;
        ptr = john.makeFromStream(in);

        for(int i = 0; i < allV.size(); i++)                        //search whole vector
            if(ptr == allV[i])                                      //...for repeats
                delete ptr;                                         //...delete repeats

        if(ptr != NULL) allV.push_back(ptr);                        //add player
    }

    cout << "Players Acquired \n\n\n";

    //---------------------------------END PART TWO----------------------------
    //--------------------------------PART THREE-----------------------------

    draft.pickTime();
    draft.makeBoard(arr, allV, numTeams);
    return 0;
}

bool check(vector<int>& vec, int a){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == a){
            cout << "Pick taken, try again : ";
            return false;
        }
    }
    return true;
}

void intro(){
	system("clear;");
    string line = "-------------------------------------------";
    cout << line + line << endl;
    cout << "                     FANTASY FOOTBALL DRAFT SIMULATOR - JOHN ZOELLER" << endl;
    cout << line + line << endl << endl << endl;
}

void clearIn(){
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

        // arr[i] = Team(teamName, draftPosition, true);               //new team object
        // arr[draftPosition - 1] = arr[i];                            //correct array position
        // pickNum.push_back(draftPosition);                           //pick number taken


        // if((draftPosition - 1) != i)                                //replace old array pos
        //     arr[i] = Team();                                        //...with a blank team
