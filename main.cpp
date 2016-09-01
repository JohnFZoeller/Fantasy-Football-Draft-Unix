#include <iostream>
#include <string>
#include <fstream>
#include "team.h" 
#include "bintree.h"

using namespace std;

void intro();

int main()
{
    int numTeams, numUsers, draftPosition, i, j;
    string teamName;
    Team *arr;
    BinTree q, r, w, t, d, k;                                           //QB, RB, WR, TE, DE, K
    char type;
    NodeData *ptr;
    bool itsIn;

    //-----------------------------------------PART ONE----------------------------------------------------------------------------
    intro();

    cin >> numTeams;
    cin.clear();
    cin.ignore(100, '\n');
    cout << endl << "Ok, there will be " << numTeams << " teams. " << endl << endl;

    arr = new Team[numTeams];

    cout << "How many of those teams will be controlled by users (vs autopick) ? ";
    cin >> numUsers;
    cin.clear();
    cin.ignore(100, '\n');
    cout << "Ok, there will be " << numUsers << " users and " << (numTeams - numUsers) << " autopicks" << endl;

    for(i = 0; i < numUsers; i++)
    {
        cout << "Enter user " << i + 1 << "'s  name: ";
        getline(cin, teamName);
        cout << "Enter draft position (1 - " << numTeams << ") : ";
        cin >> draftPosition;
        cin.clear();
        cin.ignore(100, '\n');

        arr[i] = Team(teamName, draftPosition, true);
        arr[draftPosition - 1] = arr[i];

        if((draftPosition - 1) != i)
            arr[i] = Team();
    }

    for(j = 0; j < numTeams; j++)
        if(arr[j].getUser() == false)
            arr[j] = Team("auto", (j + 1), false);

    for(i = 0; i < numTeams; i++)
        arr[i].displayBasics();

    //-----------------------------------------------------------------END PART ONE---------------------------------------------------
    //now read in player list into BSTs

    ifstream in("players.txt");
    if (!in)
    {
        cout << "File could not be opened." << endl;
        return 1;
    }
    //factory later....... for now this is fine..
    while(!in.eof())
    {
        type = in.get();
        in.unget();

        if(type == 'Q')
        {
            break;
            // Qb john;
            // ptr = john.makeFromStream(in);
            // itsIn = com.insert(ptr);
            // if(!itsIn)
            //     delete ptr;
        }
        else if(type == 'R')
        {
            break;
            // Rb john;
            // ptr = john.makeFromStream(in);
            // itsIn = r.insert(ptr);
            // if(!itsIn)
            //     delete ptr;
        }
        else if(type == 'W')
        {
            Player john;
            ptr = john.makeFromStream(in);  //in player.h, need: Nodedata *makeFromStream();
            itsIn = w.insert(ptr);
            if(!itsIn)
                delete ptr;
        }
        else if(type == 'T')
        {
            break;
        }
        else if(type == 'D')
        {
            break;
        }
        else if(type == 'K')
        {
            break;
        }
    }

    cout << endl;
    in.close();
    cout << "file closed, program terminated" << endl;


}

void intro()
{
        cout << "-------------------------------------------------" << endl;
        cout << "-------------------------------------------------" << endl;
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
        << "How many teams will there be ? ";
}















