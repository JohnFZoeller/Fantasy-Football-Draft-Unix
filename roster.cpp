#include "roster.h"
//0 - QB //1 - RB //2 - RB //3 - R/W //4 - WR //5 - WR //6 - TE //7 - DE //8 - K
Roster::Roster(){ players = new Player[16]; }

void Roster::add(NodeData* adding, WINDOW *board){
	switch(adding->getPos()){
		case 'W' :	{	if(players[4].getRank() == 0) players[4].toPlayer(adding);
						else if(players[5].getRank() == 0) players[5].toPlayer(adding);
						else if(players[3].getRank() == 0) players[3].toPlayer(adding);
						else toBench(adding);
						break;
		}
		case 'R' :	{	if(players[1].getRank() == 0) players[1].toPlayer(adding);
						else if(players[2].getRank() == 0) players[2].toPlayer(adding);
						else if(players[3].getRank() == 0) players[3].toPlayer(adding);
						else toBench(adding);
						break;
		}
		case 'T' :	{	if(players[6].getRank() == 0) players[6].toPlayer(adding);
						else toBench(adding);
						break;
		}
		case 'Q' :	{	if(players[0].getRank() == 0) players[0].toPlayer(adding);
						else toBench(adding);
						break;
		}
		case 'K' : 	{	if(players[8].getRank() == 0) players[8].toPlayer(adding);
						else toBench(adding);
						break;
		}
		case 'D' :	{	if(players[7].getRank() == 0) players[7].toPlayer(adding);
						else toBench(adding);
						break;
		}
		default: break;
	}
}

void Roster::displayRoster(WINDOW *board){
	wclear(board);
	box(board, 0 , 0);								// 0, 0 gives default characters 
	mvwprintw(board, 1, 1, "MY ROSTER");			//print title
	mvwprintw(board, 3, 1, "QB : ");
	mvwprintw(board, 4, 1, "RB : ");
	mvwprintw(board, 5, 1, "RB : ");
	mvwprintw(board, 6, 1, "RW : ");
	mvwprintw(board, 7, 1, "WR : ");
	mvwprintw(board, 8, 1, "WR : ");
	mvwprintw(board, 9, 1, "TE : ");
	mvwprintw(board, 10, 1, "DT : ");
	mvwprintw(board, 11, 1, "KK : ");
	for(int i = 12; i < 19; i++){
		mvwprintw(board, i, 1, "BE : ");
	}

	for(int j = 0; j < 16; j++){
		mvwprintw(board, j+3, 7, players[j].playerInfo().c_str());
	}
	wrefresh(board);
}

void Roster::toBench(NodeData* benching){
	for(int i = 9; i < 16; i++){
		if(players[i].getRank() == 0){
			players[i].toPlayer(benching);
			break;
		}
	}
}