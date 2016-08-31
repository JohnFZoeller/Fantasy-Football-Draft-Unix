#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include <string>
#include "roster.h"

using namespace std;

class Team
{
    private:
        string name;                                        //name of team
        int position;                                         //drafting position
        bool user;
        Roster roster;

    public:
        Team();                                                 //constructors
        Team(string n, int p, bool a);
        Team(const Team &obj);
        ~Team() {};

        void setUser(bool);                                                   //manipulators
        bool getUser();
        void setPosition(int);
        int getPosition();

        const Team &operator=(const Team&rhs);          //overloads
        bool operator==(const Team &) const;
        bool operator!=(const Team &) const;

        void displayBasics();                                                //helpers

};

#endif