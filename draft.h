#ifndef DRAFT_H
#define DRAFT_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include "nodedata.h"
using namespace std;

class Draft{
	private:
		struct LinkNode{
			LinkNode *next;
			NodeData *pick;
		};
		LinkNode *head;

	public:
		Draft();
		~Draft();

		//board functions
		void setUp(); //calls makeboard and newround
		void startDraft(); //calls display board and new round 
		void makeBoard();
		void displayBoard();
		void newRound();
		int autoPick();
		bool pick();

		//List functions
		void insertEnd();
		void displayList();


};

#endif