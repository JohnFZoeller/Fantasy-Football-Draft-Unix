#include "roster.h"
//0 - QB
//1 - RB
//2 - RB
//3 - R/W
//4 - WR
//5 - WR
//6 - TE
//7 - DE
//8 - K
//9-16 = bench
Roster::Roster(){
	players = new Player[16];
}

void Roster::add(NodeData* adding){
	
	switch(adding->getPos()){
		case 'W' :	{	if(players[4].getRank() == 0) players[4].toPlayer(adding);
						else if(players[5].getRank() == 0) players[5].toPlayer(adding);
						else toBench(adding);
						cout << *adding;
						break;
					}
		case 'R' :	{	if(players[1].getRank() == 0) players[1].toPlayer(adding);
						else if(players[2].getRank() == 0) players[2].toPlayer(adding);
						else toBench(adding);
						cout << *adding;
						break;
					}
		case 'T' :	{	if(players[6].getRank() == 0) players[6].toPlayer(adding);
						else toBench(adding);
						cout << *adding;
						break;
					}
		case 'Q' :	{	if(players[0].getRank() == 0) players[0].toPlayer(adding);
						else toBench(adding);
						cout << *adding;
						break;

					}
		default: break;
	}
}

void Roster::displayRoster(){
	for(int i = 0; i < 16; i++){
			players[i].playerInfo();
	}
}

void Roster::toBench(NodeData* benching){
	for(int i = 9; i < 16; i++){
		if(players[i].getRank() == 0)
			players[i].toPlayer(benching);
	}
}