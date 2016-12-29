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
        string posit, squad, first, last;
        int rank;
    public:
    	Player();

    	int getRank();

    	NodeData *makeFromStream(istream &in);
    	void toPlayer(NodeData*);
    	string playerInfo();

};

#endif