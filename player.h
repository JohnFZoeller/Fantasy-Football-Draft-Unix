#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <fstream>
#include "nodedata.h"
using namespace std;

class Player
{
    private:
        string spot, team, first, last;
    public:
    	Player();

    	NodeData *makeFromStream(istream &in);
};

#endif