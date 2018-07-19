#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <fstream>
#include "nodedata.h"
using namespace std;

class Player{
    private:
        string position, nflTeam, first, last;
        int rank;

    public:
    	Player();

    	int getRank() const ;

    	NodeData *makeFromStream(istream &in);
    	void toPlayer(NodeData*);
    	string playerInfo() const;
};

#endif