#include "draft.h"

Draft::Draft(){
	head = NULL;
	numTeams = 0;
}

Draft::~Draft(){}

void Draft::setNum(int num){
	numTeams = num;
}

int Draft::getNum(){
	return numTeams;
}

void Draft::setUp(){
	int uTime, cTime;

	cout << "How much time would you like per draft pick? (seconds 15-45): ";
	cin >> uTime;
	cin.clear();
	cin.ignore(100, '\n');
	cout << endl << "How much time for the computer? (seconds 0-5): ";
	cin >> cTime;
	cout << endl;
}

void Draft::startDraft(Team *arr, BinTree& a){
	srand(time(0));

	for(int i = 0; i < 10; i++){
		if(arr[i].getUser()){
			pick(arr[i], a);
		}
		else if(!arr[i].getUser()){
			autoPick(arr[i], a);
		}
	}
}

/*The idea is to always display the last three rounds.
*/
void Draft::makeBoard(Team *arr){
	string line = "====================================================";
	string thin = "----------------------------------------------------";
	int i = 0;

	//BOARD TITLE - put the timer next to the name
	cout << line + line << endl;
	cout << setw(55) << "JOHN ZOELLER'S DRAFT MACHINE" << endl;	 //timer should go here
	cout << line + line << endl;
	//END BOARD TITLE 

	//DRAFT ORDER'
	int j = 0;
	for(; j < 2; j++){
		cout <<  setw(4) << '|';
		for(int i = 0; i < 10; i++){
			if(j == 0)
				cout << "team " << (i + 1) << setw(4) << '|';
			else if(j == 1)
				cout << arr[i].getName() << setw(6) << '|';
		}
		cout << endl;
	}
	cout << line + line << endl;
	//END DRAFT ORDER
}

void Draft::newRound(){
	for(int i = 0; i < 10; i++)
		insertEnd();
}

void Draft::autoPick(Team comp, BinTree& a){
	int random = rand() % 100;
	int rank;
	bool found = false;
	NodeData *ptr;
	NodeData *key;

	cout << "Team " << comp.getPosition() << ": ";
	//implement the autopick algorithm
		//choosing from next 5 players 1 = 70%; 2 = 15%; 3 = 7.5%; 4 = 5%; 5 = 2.5%
	if(random < 70){
		rank = 1;
		//key = new NodeData(rank);
		//found = tree.retrieve(key, ptr); //ptr is what it gets stored to, its a nodeData object
	}
	else if(random >= 70 && random < 85){
		rank = 2;
	}
	else if(random >= 85 && random < 92){
		rank = 3;
	}
	else if(random >= 92 && random < 97){
		rank = 4;
	}
	else if(random >= 97){
		rank = 5;
	}
	//retieve selected player from bst	
	//insert to linked list
	//output pick
}

void Draft::pick(Team user, BinTree& a){
	int rank;
	bool found = false;

	cout << endl << "Next 20 available: " << endl;

	a.displayAvailable();
	//user options
		//-pause
		//-10 more
	cout << endl << "Please enter the number corresponding to the player you want: ";


	cin >> rank;
}

//------------------------------Linked List functions------------------------------
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

bool Draft::editNode(NodeData *edit){
	//for every pick a for loop jumps through the linked list
	//it finds the next node whose rank is 0, and writes to that node
	//then the draft board is updated to reflect the change
	return true;
}

/*
	//TEAMS
	int j = 0;
	for(; j < 2; j++){
		cout <<  setw(4) << '|';
		for(int i = 0; i < 10; i++){
			if(j == 0)
				cout << "team " << (i + 1) << setw(4) << '|';
			else if(j == 1)
				cout << arr[i].getName() << setw(6) << '|';
		}
		cout << endl;
	}
	cout << line + line << endl;

	j = 0;
	//ROUNDS : k = 3 rounds at a time; j = 2 lines per pick; i = 10
		for(; j < 2; j++){
			if(j == 0){			//ROUND COUNTER
				cout << 1;
			}
			else if(j == 1){
				cout << " ";
			}
			cout << setw(3) << '|';
								//END ROUND COUNTER
			
			for(; ptr->next != NULL; ptr = ptr->next){
				if(j == 0){
					cout << setw(10) << '|';
				}
				else if(j == 1){
					//need to post the contents of the linked list in ascending order

					cout << "john" << ptr->pick << '|';
				}
			cout << endl;
		}

		cout << thin + thin << endl;
*/


