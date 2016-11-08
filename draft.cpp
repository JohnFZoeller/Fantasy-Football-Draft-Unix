#include "draft.h"

Draft::Draft(){
	head = NULL;
	numTeams = 0;
	compTime = userTime = 0;
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

	cout << endl << "Draft Time Settings:" << endl;

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
	userTime = uTime * 1000000;

	//-------------user time ^^^   comp time vvv--------------------
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
	compTime = cTime * 1000000;

	cout << endl << "PLEASE FULLSCREEN YOUR TERMINAL WINDOW" << endl;
	usleep(3000000);
}

/*The idea is to always display the last three rounds.
*/
void Draft::makeBoard(Team *arr, int teams){
	string line = "===================================================================";
	string thin = "-------------------------------------------------------------------";
	int i = 0;
	unsigned int millis = 1000000;

	cout << "Ready?" << endl;
	usleep(millis);
	cout << "Set" << endl;
	usleep(millis);
	cout << "GO!" << endl;

	system("sh clear.sh");


	//BOARD TITLE - put the timer next to the name
	cout << line + line << endl;
	cout << setw(55) << "JOHN ZOELLER'S DRAFT MACHINE" << endl;	 //timer should go here
	cout << line + line << endl;
	//END BOARD TITLE 

	//DRAFT ORDER'
	int j = 0;
	for(; j < 2; j++){
		cout <<  setw(4) << '|';
		for(int i = 0; i < teams; i++){
			if(j == 0)
				cout << "team " << (i + 1) << setw(6) << '|';
			else if(j == 1)
				cout << arr[i].getName() << setw(8) << '|';
		}
		cout << endl;
	}
	cout << line + line << endl;
}

void Draft::startDraft(Team *arr, vector<NodeData*>& a, int nTeams){
	char newRound;
	srand(time(0));

	while(true){
		for(int i = 0; i < nTeams; i++){
			if(arr[i].getUser())
				pick(arr[i], a);
			else if(!arr[i].getUser())
				autoP(arr[i], a);
		}
		for(int i = (nTeams - 1); i > -1; i--){
			if(arr[i].getUser())
				pick(arr[i], a);
			else if(!arr[i].getUser())
				autoP(arr[i], a);
		}
		cout << endl << "KEEP GOING? (y/n): ";
		cin >> newRound;
		cin.clear();
		cin.ignore(100, '\n');
		if(tolower(newRound) == 'n')
			break;
	}
}

void Draft::newRound(){
	//for(int i = 0; i < 10; i++)
		//insertEnd();
}

void Draft::autoP(Team computer, vector<NodeData*>& a){
	int random = rand() % 100;
	int counter = 0;
	int skipNum = 0;

	usleep(compTime);

	if(random < 70)
		skipNum = 0;
	else if(random >= 70 && random < 85)
		skipNum = 1;
	else if(random > 85)
		skipNum = 2;

	for(int i = 0; i < a.size(); i++){
		if(!a[i]->getTaken()){
			if(counter == skipNum){
				a[i]->setTaken(true);
				insertEnd(a[i]);
				computer.roster.add(a[i]);
				toBoard();
				break;
			}
			else counter++;
		}
	}
}

void Draft::toBoard(){
//could add to board queue so that when the round is finished you can complete output
	//output name to first column
}


void Draft::pick(Team user, vector<NodeData*>& a){
	char yesNo;
	int rank;

	//cout << (userTime / 1000000) << " seconds to pick. " << endl;
	//scraping user time limit until i get curses working. 

	nextTen(a);
	//user options
	user.roster.displayRoster();
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

