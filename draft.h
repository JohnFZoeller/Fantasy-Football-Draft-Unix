#ifndef DRAFT_H
#define DRAFT_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Draft{
	private:
		struct LinkNode{
			LinkNode *next;
			NodeData *pick;
		}
		LinkNode *head;

	public:
		Draft();
		~Draft();

		void setUp();
		void startDraft();
		void makeBoard();
		void displayBoard();
		void newRound();
		int autoPick();
		bool insert();
		bool pick();

};

#endif