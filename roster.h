#ifndef ROSTER_H
#define ROSTER_H
#include <iostream>
#include <string>
#include "player.h"
#include "nodedata.h"
using namespace std;


class Roster
{
    private:
        Player *players;

    public:
        Roster();

        void add(NodeData*);
        void displayRoster();
     	void toBench(NodeData*);

};

#endif