#ifndef ROSTER_H
#define ROSTER_H
#include <iostream>
#include <string>
#include <ncurses.h>
#include "player.h"
#include "nodedata.h"
using namespace std;


class Roster
{
    private:
        Player *players;

    public:
        Roster();

        void add(NodeData*, WINDOW *board);
        void displayRoster(WINDOW *board);
     	void toBench(NodeData*);
};

#endif