#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "team.h" 
#include "draft.h"
#include "bPlus.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <vector>

using namespace std;

void intro();

int main()
{
    //primitives
    int numTeams, numUsers, draftPosition, i, j;
    bool itsIn;
    char type;
    string teamName;

    //abstracts
    Team *arr;
    NodeData *ptr;
    Draft draft;
    bPlus tree;
    vector <NodeData*> allV;


    //------------------------------------PART ONE--------------------------------
    intro();

    //get number of teams
    cin >> numTeams;
    cin.clear();
    cin.ignore(100, '\n');

    while(numTeams < 4 || numTeams > 12){
        cout << "Choose between 4 and 12 teams: ";
        cin >> numTeams;
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << endl << "Ok, there will be " << numTeams << " teams. " << endl << endl;
    arr = new Team[numTeams];
    draft.setNum(numTeams);

    cout << "How many teams will be users–– not autopick? (0-" << numTeams << "): ";
    cin >> numUsers;
    cin.clear();
    cin.ignore(100, '\n'); 

    while(numUsers < 0 || numUsers > numTeams){
        cout << "Choose between 0 and " << numTeams << " users: ";
        cin >> numUsers;
        cin.clear();
        cin.ignore(100, '\n');
    }  

    cout << "Ok, there will be " << numUsers << " users and " << (numTeams - numUsers) 
    << " autopicks" << endl;

    for(i = 0; i < numUsers; i++)
    {
        cout << "Enter user " << i + 1 << "'s  name: ";
        getline(cin, teamName);
        cout << "Enter draft position (1 - " << numTeams << ") : ";
        cin >> draftPosition;
        cin.clear();
        cin.ignore(100, '\n');

        while(draftPosition < 1 || draftPosition > numTeams){
            cout << "Draft position must be between 1 and " << numTeams << ": ";
            cin >> draftPosition;
            cin.clear();
            cin.ignore(100,'\n');
        }

        arr[i] = Team(teamName, draftPosition, true);
        arr[draftPosition - 1] = arr[i];

        if((draftPosition - 1) != i)
            arr[i] = Team();
    }

    for(j = 0; j < numTeams; j++)
        if(arr[j].getUser() == false)
            arr[j] = Team("auto", (j + 1), false);


    //----------------------------ADD SHELL SCRIPT HERE----------------------
        //wget player list
        //awk to format into text file for use.
    //----------------------------END SHELL SCRIPT---------------------------


    //-------------------------------END PART ONE----------------------------
    //now read in player list into vector, will be b+ tree once thats done
    //----------------------------------PART TWO----------------------------
    ifstream in("players.txt");
    
    if (!in){
        cout << "File could not be opened." << endl;
        return 1;
    }

    while(!in.eof()){
        type = in.get();
        in.unget();

        Player john;
        ptr = john.makeFromStream(in);

        for(int i = 0; i < allV.size(); i++){
            if(ptr == allV[i])
                delete ptr;
        }
        if(ptr != NULL)
            allV.push_back(ptr);
        // itsIn = all.insert(ptr);
        // if(!itsIn)
        //     delete ptr;
    }

    //---------------------------------END PART TWO----------------------------
    //--------------------------------PART THREE-----------------------------

    draft.setUp();
    draft.makeBoard(arr, numTeams);
    draft.startDraft(arr, allV, numTeams);

}

void intro()
{
	system("sh clear.sh");
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "           FANTASY FOOTBALL DRAFT SIMULATOR - JOHN ZOELLER" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Welcome to The Draft Machine. "
    << "Default teams consist of: " << endl 
    << "1 Quarterback" << endl
    << "2 Running backs" << endl
    << "2 Wide Recievers " << endl
    << "1 Flex" << endl
    << "1 Tight End " << endl
    << "1 Defense " << endl
    << "1 Kicker" << endl
    << "8 Bench spots" << endl << endl
    << "How many teams will there be? (4-12):  ";
}

