#ifndef DRAFT_H
#define DRAFT_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include "nodedata.h"
#include "team.h"
#include <unistd.h>
#include <ncurses.h>

#include <vector>
#include <cctype>

using namespace std;

class Draft{
	private:
		struct LinkNode{
			LinkNode *next;
			NodeData *pick;
		};
		LinkNode *head;
		int numTeams;
		unsigned int compTime;
		unsigned int userTime;

	public:
		Draft();
		~Draft();

		//getters setters
		void setNum(int);
		int getNum();
		//board functions
		void setUp(); //calls makeboard and newround
		void startDraft(Team *arr, vector<NodeData*>&, int); //calls display board and new round 
		void makeBoard(Team *arr, int);
		void newRound();
		void autoPick(Team, vector<NodeData*>&);
		void autoP(Team, vector<NodeData*>&);
		void toBoard();

		void pick(Team, vector<NodeData*>&);
		void nextTen(vector<NodeData*>&);

		//List functions
		void insertEnd(NodeData*);
		void displayList();
		bool editNode(NodeData*);


};

#endif