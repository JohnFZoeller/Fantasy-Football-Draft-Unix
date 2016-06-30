#include <iostream>
#include <string>
#include <fstream>
#include "team.h" 

using namespace std;

void intro();

int main()
{
    int numTeams, numUsers, draftPosition, i, j;
    string teamName;
    Team *arr;

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















