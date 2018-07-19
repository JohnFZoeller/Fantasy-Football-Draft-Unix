#ifndef DRAFT_H
#define DRAFT_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "nodedata.h"
#include "team.h"
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#include <cctype>
#include <sstream>
#include <unordered_map>

using namespace std;
const int BOARD_SIZE = 35, TITLE = 30, HEIGHT = 0, WIDTH = 1, START_X = 2, 
START_Y = 3, PLAYERS_AVAILABLE = 33;

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
		WINDOW *draftBoard[BOARD_SIZE];

	public:
		Draft();
		~Draft();

		//getters setters
		void setNumTeams(int);
		const int getNumTeams() const;

		//board functions
		void pickTime(); 
		void startDraft(Team *arr, vector<NodeData*>&, int, WINDOW **board);
		void makeBoard(Team *arr, vector<NodeData*>&, int);
		void autoP(Team &, vector<NodeData*>&, WINDOW **board, const int &pick);
		void toBoard(NodeData *player, WINDOW **board, const int &pick);
		void makeWindow(const string& name, int *dims, const int& windowNumber);

		void pick(Team &, vector<NodeData*>&, WINDOW **board, const int &pick);
		void nextTen(vector<NodeData*>&, WINDOW **board);
		void roundUp(int, WINDOW *);
		void clearBoard(WINDOW **board);
		bool notNums(char *, int &);

		//List functions
		void insertEnd(NodeData*);
		void displayList();

		//curses functions
		void destroy_win(WINDOW *);
		WINDOW *createWin(int, int, int, int);
		char *toCharArr(NodeData *a);
		char *toChar2(NodeData *a);
};

#endif