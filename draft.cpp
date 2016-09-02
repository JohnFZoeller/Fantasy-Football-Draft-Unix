#include "draft.h"

Draft::Draft(){
	head = NULL;
}

Draft::~Draft(){}

void Draft::setUp(){
	// takes care of:
	// time between picks
	// makes the boardfire
	
}

void Draft::startDraft(){
	//displays the board
	//runs the timer
}

/*The idea is to always display the last three rounds.
*/
void Draft::makeBoard(){
	string line = "==========================================";
	string thin = "------------------------------------------";

	newRound();

	//BOARD TITLE
	cout << line + line << endl;
	cout << setw(55) << "JOHN ZOELLER'S DRAFT MACHINE" << endl;	
	cout << line + line << endl;

	//TEAMS
	for(int j = 0; j < 2; j++){
		cout <<  setw(4) << '|';
		for(int i = 0; i < 10; i++)
			cout << setw(6) << "team" << (i + 1) << '|';
		cout << endl;
	}
	cout << line + line << endl;

	//ROUNDS : k = 3 rounds at a time; j = 2 lines per pick; i = 10
	for(int k = 0; k < 3; k++){
		for(int j = 0; j < 2; j++){
			cout << k + 1;
			cout << setw(3) << '|';
			for(int i = 0; i < 10; i++)
				cout << setw(8) << '|';
			cout << endl;
		}

		cout << thin + thin << endl;
	}
	displayList();

}

void Draft::displayBoard(){
	//display the timer and the draft board
}

void Draft::newRound(){
	for(int i = 0; i < 10; i++)
		insertEnd();
}

int Draft::autoPick(){
	//integrates the autopick algorithm
	return 0;
}

bool Draft::pick(){return true;}

void Draft::insertEnd(){ //change to insertEnd(NodeData* insert){}
	LinkNode *ptr = new LinkNode;
	ptr->next = NULL;
	ptr->pick = new NodeData; //change to ptr->pick = insert;

	if(head == NULL)
		head = ptr;	
	else if(head != NULL){
		LinkNode *i = head;
		for(; i->next != NULL; i = i->next)
			continue;
		i->next = ptr;
	}
}

void Draft::displayList(){
	if(head == NULL)
		cout << "empty list" << endl;
	else if(head != NULL){
		for(LinkNode *i = head; i != NULL; i = i->next)
			cout << *i->pick << endl;
	}
}



