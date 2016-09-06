#ifndef DRAFT_H
#define DRAFT_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include "bintree.h"
#include "nodedata.h"
#include "team.h"
using namespace std;

class Draft{
	private:
		struct LinkNode{
			LinkNode *next;
			NodeData *pick;
		};
		LinkNode *head;
		int numTeams;

	public:
		Draft();
		~Draft();

		//getters setters
		void setNum(int);
		int getNum();
		//board functions
		void setUp(); //calls makeboard and newround
		void startDraft(Team *arr, BinTree&); //calls display board and new round 
		void makeBoard(Team *arr);
		void newRound();
		void autoPick(Team, BinTree&);
		void pick(Team, BinTree&);

		//List functions
		void insertEnd();
		void displayList();
		bool editNode(NodeData*);


};

#endif