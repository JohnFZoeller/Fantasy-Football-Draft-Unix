#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include <string>
#include "roster.h"
#include <vector>
#include "nodedata.h"

using namespace std;

class Team{
    friend class Draft;
    private:
        string name;                                        //name of team
        int position;                                       //drafting position
        bool user;
        Roster roster;

    public:
        Team();
        Team(string n, int p, bool a);
        Team(const Team &obj);
        ~Team() {};

        void setUser(bool);
        bool getUser();
        void setPosition(int);
        int getPosition();
        void setName(string);
        string getName();

        const Team &operator=(const Team&rhs);
        bool operator==(const Team &) const;
        bool operator!=(const Team &) const;

        void displayBasics();
};

#endif
