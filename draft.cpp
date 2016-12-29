#include "draft.h"

Draft::Draft(){
	head = NULL;
	numTeams = 0;
	compTime = userTime = 0;
}

Draft::~Draft(){}

void Draft::setNum(int num){
	//collapse
	numTeams = num;
}

int Draft::getNum(){
	//collapse
	return numTeams;
}

void Draft::pickTime(){
	int uTime, cTime;
	unsigned int millis = 1000000;

	cout << endl << "Draft Time Settings:" << endl;

	do{																//user time
		cout << "Enter between 15-45 seconds per draft pick: ";
		cin >> uTime;
		cin.clear();
		cin.ignore(100, '\n');
	} while(uTime > 45 || uTime < 15);

	do{																//auto time
		cout << "Enter between 0-5 seconds per autopick: ";
		cin >> cTime;
		cin.clear();
		cin.ignore(100, '\n');
	} while(cTime < 0 || cTime > 5);

	userTime = uTime * 1000000;										//format time
	compTime = cTime * 1000000;										//format time
	cout << endl << "PLEASE FULLSCREEN YOUR TERMINAL WINDOW" << endl;
	usleep(1000000);
	cout << "Ready?" << endl;
	usleep(millis);
	cout << "Set" << endl;
	usleep(millis);
	cout << "GO!" << endl;
	system("sh clear.sh");
}

void Draft::makeBoard(Team *arr, vector<NodeData*>& a, int teams){
	int sY = 8, sX = 0, w = 14, h = 4, ch, j = 0, z = 0;
	string tName;			
	WINDOW *board[35]; //timer + players + menu  + roster + titles +    title +    teams(2)
					   //ar[34]  arr[33]   ar[32]  ar[31]   arr[20-29]    ar[30]  ar[0-19]
	initscr();											//start curses
	cbreak();											//line buffer off
	keypad(stdscr, TRUE);								//to use f1
	printw("Press F1 to exit");							//print 
	refresh();											//output

	board[30] = createWin(4, 100, 1, 0);				//title
	mvwprintw(board[30], 1, 10, "John Zoeller Draft");	//print T
	wrefresh(board[30]);								//output

	board[34] = createWin(4, 40, 1, 101);				//timer
	mvwprintw(board[34], 1, 1, "TIMER");				//print time
	wrefresh(board[34]);								//output

	for(int k = 0; k < 10; k++){						//team names
		board[k + 20] = createWin(3, 14, 5, (sX + (w * k)));
		tName = arr[k].getUser() ? to_string(arr[k].getPosition()) 
		+ " " + arr[k].getName() : to_string(k + 1) + " Auto";

		mvwprintw(board[k + 20], 1, 1, tName.c_str());
		wrefresh(board[k + 20]);
	} 

	for(int i = 0; i < 10; i++){
		board[i] = createWin(h, w, (sY + (h * j)), (sX + (w * i)));
	} j++;
	for(int a = 19; a >= 10; a--){
		board[a] = createWin(h, w, (sY + (h * j)), (sX + (w * z)));
		z++;
	}

	board[33] = createWin(20, 45, 16, 0);				//players
	mvwprintw(board[33], 1, 1, "PLAYERS");				//print title
	wrefresh(board[33]);								//output

	board[32] = createWin(10, 45, 16, 46);				//menu
	mvwprintw(board[32], 1, 1, "MENU");					//print title
	wrefresh(board[32]);								//output

	board[31] = createWin(20, 45, 16, 92);				//roster
	mvwprintw(board[31], 1, 1, "MY ROSTER");				//print title
	wrefresh(board[31]);								//output

	while((ch = getch()) != KEY_F(1)){					//drafting
		startDraft(arr, a, teams, board);
	}

	for(int i = 0; i < 35; i++){						//delete windows
		if(board[i] != NULL)
			destroy_win(board[i]);
	}

	endwin();
}

void Draft::startDraft(Team *arr, vector<NodeData*>& a, int nTeams, WINDOW **board){
	//char newRound;

	int pickN;
	srand(time(0));

	while(true){
		pickN = 0;

		for(int i = 0; i < nTeams; i++){
			if(arr[i].getUser())
				pick(arr[i], a, board, pickN);
			else if(!arr[i].getUser())
				autoP(arr[i], a, board, pickN);
			pickN++;
		}

		for(int i = (nTeams - 1); i > -1; i--){
			if(arr[i].getUser())
				pick(arr[i], a, board, pickN);
			else if(!arr[i].getUser())
				autoP(arr[i], a, board, pickN);
			pickN++;
		}

		// cout << endl << "KEEP GOING? (y/n): ";
		// cin >> newRound;
		// cin.clear();
		// cin.ignore(100, '\n');
		// if(tolower(newRound) == 'n')
			break;
	}
}

void Draft::newRound(){
	//for(int i = 0; i < 10; i++)
		//insertEnd();
}

void Draft::autoP(Team computer, vector<NodeData*>& a, WINDOW **board, int pickN){
	int random = rand() % 100;
	int counter = 0, skipNum = 0;

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
				a[i]->setTaken(true);				//nodeData.setTaken()
				insertEnd(a[i]);					//draft.insertEnd(player)
				computer.roster.add(a[i], board[31]);			//team.roster.add(player)
				toBoard(computer, a[i], board, pickN);
				break;
			}
			else counter++;
		}
	}
}

void Draft::toBoard(Team team, NodeData* player, WINDOW **board, int pickN){
	mvwprintw(board[pickN], 1, 1, toCharArr(player));
	mvwprintw(board[pickN], 2, 1, toChar2(player));
	wrefresh(board[pickN]);
}

void Draft::pick(Team &user, vector<NodeData*>& a, WINDOW **board, int pickN){
	char yesNo;
	char num[3];
	int rank;

	//cout << (userTime / 1000000) << " seconds to pick. " << endl;
	//scraping user time limit until i get curses working. 

	nextTen(a, board);
		//-view another team
		//-view whole board

	while(true){
		mvwprintw(board[32], 1, 1, "Enter number of desired player: ");
		wrefresh(board[32]);

		mvwgetstr(board[32], 1, 35, num);
		sscanf(num, "%d", &rank);

		if(!a[rank - 1]->getTaken()){
			mvwprintw(board[32], 2, 1, "Are you sure(y/n): ");
			wrefresh(board[32]);
			yesNo = getch();
			if(tolower(yesNo) == 'y'){
				break;
			}
		}
		else if(a[rank - 1]->getTaken()){
			mvwprintw(board[32], 2, 1, "Already taken, pick again");
			wrefresh(board[32]);
		}
	}

	a[rank - 1]->setTaken(true);
	insertEnd(a[rank - 1]);
	user.roster.add(a[rank - 1], board[31]);
	user.roster.displayRoster(board[31]);
	toBoard(user, a[rank - 1], board, pickN);
}

void Draft::nextTen(vector<NodeData*>& a, WINDOW **board){
	int i = 0, morePlayers = 10, j = 3;
	char yesNo;

	mvwprintw(board[33], 1, 1, "PLAYERS");
	wrefresh(board[33]);

	while(true){
		for(; i < morePlayers; i++){
			if(!a[i]->getTaken()){
				mvwprintw(board[33], j, 1, toCharArr(a[i]));
				mvwprintw(board[33], j, 13, toChar2(a[i]));
				wrefresh(board[33]);
				j++;
			}
			else if(a[i]->getTaken())
				morePlayers++;
		}

		mvwprintw(board[33], 12, 1, "Display 10 more? (y/n): ");
		wrefresh(board[33]);

		yesNo = getch();
		if(tolower(yesNo) == 'n')
			break;
		morePlayers += 10;
		j = 3;
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

//----------------------------------Curses functions-------------------------------
WINDOW *Draft::createWin(int height, int width, int starty, int startx){	
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		// 0, 0 gives default characters 
	wrefresh(local_win);		// Show that box 		

	return local_win;
}

void Draft::destroy_win(WINDOW *local_win){	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

char *Draft::toCharArr(NodeData *a){
	char *john = new char[13];
	string player = a->getRankS() + " " + a->getFirst();

	for(int i = 0; i < 13; i++){
		john[i] = player[i];
		if(i == 12){
			john[i] = '0';
		}
	}
	return john;
}

char *Draft::toChar2(NodeData *a){
	char *john = new char[13];
	string player = a->getLast() + " " + a->getPosition();

	for(int i = 0; i < 13; i++){
		john[i] = player[i];
		if(i == 12){
			john[i] = '0';
		}
	}
	return john;
}






