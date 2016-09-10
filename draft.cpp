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

	while(uTime > 45 || uTime < 15){
		cout << "Must choose between 15-45 seconds: ";
		cin >> uTime;
		cin.clear();
		cin.ignore(100, '\n');
	}

	cout << endl << "How much time for the computer? (seconds 0-5): ";
	cin >> cTime;
	cin.clear();
	cin.ignore(100, '\n');

	while(cTime < 0 || cTime > 5){
		cout << "Must be between 0 and 5: ";
		cin >> cTime;
		cin.clear();
		cin.ignore(100, '\n');
	}
	cout << endl;
}

void Draft::startDraft(Team *arr, vector<NodeData*>& a, int nTeams){
	char newRound;
	srand(time(0));

	while(true){
		for(int i = 0; i < nTeams; i++){
			if(arr[i].getUser())
				pick(arr[i], a);
			else if(!arr[i].getUser())
				autoPick(arr[i], a);
		}
		for(int i = (nTeams - 1); i > -1; i--){
			if(arr[i].getUser())
				pick(arr[i], a);
			else if(!arr[i].getUser())
				autoPick(arr[i], a);
		}
		cout << endl << "KEEP GOING? (y/n): ";
		cin >> newRound;
		cin.clear();
		cin.ignore(100, '\n');
		if(tolower(newRound) == 'n')
			break;
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
	//for(int i = 0; i < 10; i++)
		//insertEnd();
}

//autopick is gonna be on hold until i get a b+ implementation 
void Draft::autoPick(Team computer, vector<NodeData*>& a){
	int random = rand() % 100;
	int counter = 0;

	cout << "Team " << computer.getPosition() << ": ";

	if(random < 70){
		for(int i = 0; i < a.size(); i++){
			if(!a[i]->getTaken()){
				a[i]->setTaken(true);
				insertEnd(a[i]);
				computer.roster.add(a[i]);
				break;
			}
		}
	}
	else if(random >= 70 && random < 85){
		for(int i = 0; i < a.size(); i++){
			if(!a[i]->getTaken() && counter == 1){
				a[i]->setTaken(true);
				insertEnd(a[i]);
				computer.roster.add(a[i]);
				break;
			}
			else if(!a[i]->getTaken() && counter == 0){
				counter++;
			}
		}
	}
	else if(random >= 85 && random < 92){
		for(int i = 0; i < a.size(); i++){
			if(!a[i]->getTaken() && counter == 2){
				a[i]->setTaken(true);
				insertEnd(a[i]);
				computer.roster.add(a[i]);
				break;
			}
			else if(!a[i]->getTaken() && counter != 2){
				counter++;
			}
		}
	}
	else if(random >= 92 && random < 97){
		for(int i = 0; i < a.size(); i++){
			if(!a[i]->getTaken() && counter == 3){
				a[i]->setTaken(true);
				insertEnd(a[i]);
				computer.roster.add(a[i]);
				break;
			}
			else if(!a[i]->getTaken() && counter != 3){
				counter++;
			}
		}
	}
	else if(random >= 97){
		for(int i = 0; i < a.size(); i++){
			if(!a[i]->getTaken() && counter == 4){
				a[i]->setTaken(true);
				insertEnd(a[i]);
				computer.roster.add(a[i]);
				break;
			}
			else if(!a[i]->getTaken() && counter != 4){
				counter++;
			}
		}
	}

}

void Draft::pick(Team user, vector<NodeData*>& a){
	char yesNo;
	int rank;

	nextTen(a);
	//user options
		//-pause the draft
		//-view my team
		//-view another team
		//-view draft board

	while(true){
		cout << endl << "Please enter the number corresponding to the player you want: ";
		cin >> rank;
		cin.clear();
		cin.ignore(100, '\n');

		if(!a[rank - 1]->getTaken()){
			cout << "You chose " << *a[rank - 1] << " Pick this player? (y/n): ";
			cin >> yesNo;
			cin.clear();
			cin.ignore(100, '\n');
			if(tolower(yesNo) == 'y'){
				break;
			}
		}
		else if(a[rank - 1]->getTaken()){
			cout << "Player not available, choose again. " << endl;
		}
	}

	a[rank - 1]->setTaken(true);
	insertEnd(a[rank - 1]);
	user.roster.add(a[rank - 1]);
}

void Draft::nextTen(vector<NodeData*>& a){
	int i = 0, morePlayers = 10;
	char yesNo;

	cout << endl << "Next 10 available: " << endl;

	while(true){
		for(; i < morePlayers; i++){
			if(!a[i]->getTaken()){
				cout << *a[i];
			}
			else if(a[i]->getTaken())
				morePlayers++;
		}

		cout << "Display 10 more? (y/n): ";
		cin >> yesNo;
		cin.clear();
		cin.ignore(100, '\n');
		if(tolower(yesNo) == 'n')
			break;
		morePlayers += 10;
	}
}

//------------------------------Linked List functions------------------------------
void Draft::insertEnd(NodeData* inserting){
	LinkNode *ptr = new LinkNode;
	ptr->next = NULL;
	ptr->pick = inserting;

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



