#include "draft.h"

Draft::Draft(){
	head = NULL;
	numTeams = 0;
	compTime = userTime = 0;
}
//adding comments


Draft::~Draft(){}

void Draft::setNum(int num){ numTeams = num; }

int Draft::getNum(){ return numTeams; }

void Draft::pickTime(){
	double cTime;
	//int uTime;
	unsigned int millis = 1000000;

	//cout << endl << "Draft Time Settings:" << endl;

	// do{																//user time
	// 	cout << "Enter between 15-45 seconds per draft pick: ";
	// 	cin >> uTime;
	// 	cin.clear();
	// 	cin.ignore(100, '\n');
	// } while(uTime > 45 || uTime < 15);

	// do{																//auto time
	// 	cout << "Enter between 0-5 seconds per autopick: ";
	// 	cin >> cTime;
	// 	cin.clear();
	// 	cin.ignore(100, '\n');
	// } while(cTime < 0.0 || cTime > 5.0);
	cTime = .6;
	//userTime = uTime * 1000000;										//format time
	compTime = cTime * 1000000;										//format time
	//cout << endl << "PLEASE FULLSCREEN YOUR TERMINAL WINDOW" << endl;
	usleep(1000000);
	cout << "Ready?" << endl;
	usleep(millis);
	cout << "Set" << endl;
	usleep(millis);
	cout << "GO!" << endl;
	system("clear;");
}

void Draft::makeBoard(Team *arr, vector<NodeData*>& a, int teams){
	int sY = 8, sX = 0, w = 14, h = 4, ch, j = 0, z = 0;
	string tName;			
	WINDOW *board[35]; //timer + players + menu  + roster + titles +    title +    teams(2)
					   //ar[34]  arr[33]   ar[32]  ar[31]   arr[20-29]    ar[30]  ar[0-19]
	initscr();											//start curses
	cbreak();											//line buffer off
	keypad(stdscr, TRUE);								//to use f1
	printw("Press cntr+c to exit");							//print 
	refresh();											//output

	board[30] = createWin(4, 100, 1, 0);				//title
	wattron(board[30], A_BOLD);
	mvwprintw(board[30], 1, 10, "John Zoeller Draft");	//print T
	wrefresh(board[30]);								//output

	board[34] = createWin(4, 40, 1, 101);				//timer
	wattron(board[34], A_BOLD);
	mvwprintw(board[34], 1, 1, "ROUND");				//print time
	wrefresh(board[34]);								//output

	for(int k = 0; k < 10; k++){						//team names
		board[k + 20] = createWin(3, 14, 5, (sX + (w * k)));
		wattron(board[k + 20], A_BOLD);	

		if(arr[k].getUser()){
			tName = to_string(arr[k].getPosition()) + " " + arr[k].getName();
			wattron(board[k + 20], A_UNDERLINE);
		} else
			tName = to_string(k + 1) + " Auto";

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

	board[33] = createWin(22, 45, 16, 0);				//players
	wattron(board[33], A_BOLD);
	mvwprintw(board[33], 1, 1, "PLAYERS");				//print title
	wattroff(board[33], A_BOLD);
	wrefresh(board[33]);								//output

	board[32] = createWin(10, 45, 16, 46);				//menu
	wattron(board[32], A_BOLD);
	mvwprintw(board[32], 1, 1, "MENU");					//print title
	wattroff(board[32], A_BOLD);
	wrefresh(board[32]);								//output

	board[31] = createWin(22, 45, 16, 92);				//roster
	wattron(board[31], A_BOLD);
	mvwprintw(board[31], 1, 1, "MY ROSTER");				//print title
	wattroff(board[31], A_BOLD);
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
	int pickN, round = 0;
	srand(time(0));

	roundUp(++round, board[34]);

	while(round < 16){
		pickN = 0;

		for(int i = 0; i < nTeams; i++){
			if(arr[i].getUser()){
				pick(arr[i], a, board, pickN);
			}
			else if(!arr[i].getUser()){
				autoP(arr[i], a, board, pickN);
			}
			pickN++;
		}
		roundUp(++round, board[34]);
		for(int i = (nTeams - 1); i > -1; i--){
			if(arr[i].getUser())
				pick(arr[i], a, board, pickN);
			else if(!arr[i].getUser())
				autoP(arr[i], a, board, pickN);
			pickN++;
		}
		roundUp(++round, board[34]);
		clearBoard(board);
	}
}

void Draft::autoP(Team &computer, vector<NodeData*>& a, WINDOW **board, const int &pickN){
	int random = rand() % 100;
	int counter = 0, skipNum = 0;

	usleep(compTime);

	if(random < 60)
		skipNum = 0;
	else if(random >= 60 && random < 80)
		skipNum = 1;
	else if(random >= 80 && random < 90)
		skipNum = 2;
	else if(random >= 90 && random < 97)
		skipNum = 3;
	else if(random >= 97 && random < 100)
		skipNum = 4;

	for(int i = 0; i < a.size(); i++){
		if(!a[i]->getTaken()){									//cur player not taken
			if(counter == skipNum){								//likelyhood counter
				if(computer.roster.hasNeed(a[i])){						//player needed
					a[i]->setTaken(true);							//player taken
					insertEnd(a[i]);								//add to board
					computer.roster.add(a[i], board[31]);			//add to roster
					toBoard(a[i], board, pickN);					
					break;											//complete- exit
				} else continue;									
			}
			else counter++;
		}
	}
}

void Draft::pick(Team &user, vector<NodeData*>& a, WINDOW **board, const int &pickN){
	char num[3];
	int rank = 0;
	int temp = pickN;					//for some reason mvwgetstr resets pickN, solved

	nextTen(a, board);

	while(true){
		do{
			mvwprintw(board[32], 1, 1, "Enter rank of desired player(1-300): ");
			wrefresh(board[32]);
			mvwgetstr(board[32], 1, 38, num);
			sscanf(num, "%d", &rank);
		} while(rank < 1 || rank > 300);

		if(!a[rank - 1]->getTaken())
			break;
		else if(a[rank - 1]->getTaken()){
			mvwprintw(board[32], 2, 1, "Already taken, pick again");
			wrefresh(board[32]);
		}
	}

	a[rank - 1]->setTaken(true);
	insertEnd(a[rank - 1]);
	user.roster.add(a[rank - 1], board[31]);
	user.roster.displayRoster(board[31]);
	toBoard(a[rank - 1], board, temp);
}

void Draft::toBoard(NodeData* player, WINDOW **board, const int &pickN){

	start_color();
	switch(player->getPos()){
		case 'W' :	{	init_pair(1, COLOR_GREEN, COLOR_BLACK);
						wattron(board[pickN], COLOR_PAIR(1));
						mvwprintw(board[pickN], 1, 1, toCharArr(player));
						mvwprintw(board[pickN], 2, 1, toChar2(player));
						wrefresh(board[pickN]);
						wattroff(board[pickN], COLOR_PAIR(1));
						break;
					}
		case 'R' :	{	
						init_pair(2, COLOR_CYAN, COLOR_BLACK);
						wattron(board[pickN], COLOR_PAIR(2));
						mvwprintw(board[pickN], 1, 1, toCharArr(player));
						mvwprintw(board[pickN], 2, 1, toChar2(player));
						wrefresh(board[pickN]);
						wattroff(board[pickN], COLOR_PAIR(2));
						break;
					}
		case 'T' :	{	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
						wattron(board[pickN], COLOR_PAIR(3));
						mvwprintw(board[pickN], 1, 1, toCharArr(player));
						mvwprintw(board[pickN], 2, 1, toChar2(player));
						wrefresh(board[pickN]);
						wattroff(board[pickN], COLOR_PAIR(3));
						break;
					}
		case 'Q' :	{	init_pair(4, COLOR_RED, COLOR_BLACK);
						wattron(board[pickN], COLOR_PAIR(4));
						mvwprintw(board[pickN], 1, 1, toCharArr(player));
						mvwprintw(board[pickN], 2, 1, toChar2(player));
						wrefresh(board[pickN]);
						wattroff(board[pickN], COLOR_PAIR(4));
						break;
					}
		default: 		mvwprintw(board[pickN], 1, 1, toCharArr(player));
						mvwprintw(board[pickN], 2, 1, toChar2(player));
						wrefresh(board[pickN]);
						break;
	} 
	// mvwprintw(board[pickN], 1, 1, toCharArr(player));
	// mvwprintw(board[pickN], 2, 1, toChar2(player));
	// wrefresh(board[pickN]);
}

void Draft::nextTen(vector<NodeData*>& a, WINDOW **board){
	int i = 0, morePlayers = 15, j = 3;
	char yesNo;

	while(true){
			wclear(board[33]);											//clear players
			box(board[33], 0, 0);										//redraw box
			wattron(board[33], A_BOLD);									//BOLD ON
			mvwprintw(board[33], 1, 1, "PLAYERS");						//reprint
			wattroff(board[33], A_BOLD);								//BOLD OFF 
			wrefresh(board[33]);										//REFRESH

		for(; i < morePlayers; i++){									//i = 27, mP = 42						
			if(i > a.size() - 1) return;											//bounds check
			if(!a[i]->getTaken()){										//player taken?
				mvwprintw(board[33], j, 1, toCharArr(a[i]));			//first line
				mvwprintw(board[33], j, 13, toChar2(a[i]));				//second lines
				wrefresh(board[33]);									//refresh
				j++;													//y coord incre
			}
			else if(a[i]->getTaken())									//player was taken
				morePlayers++;											//ensures 15
		}

		do{			
			//wattron(board[33], A_BLINK);
			mvwprintw(board[33], 19, 1, "DISPLAY 15 MORE? (y/n): ");
			//wattroff(board[33], A_BOLD);
			wrefresh(board[33]);
			yesNo = getch();
		} while(tolower(yesNo) != 'y' && tolower(yesNo) != 'n');		//not a yes or no

		if(tolower(yesNo) == 'n') break;								//basically returns

		morePlayers += 15;												//always 15
		j = 3;															//y coord reset
	}
}

void Draft::roundUp(int round, WINDOW *board){
	string r = "ROUND : " + to_string(round);
	wclear(board);
	box(board, 0, 0);
	mvwprintw(board, 1, 1, r.c_str());
	wrefresh(board);
}

void Draft::clearBoard(WINDOW **board){
	usleep(1000000);
	for(int i = 0; i < 20; i++){
		wclear(board[i]);
		box(board[i], 0, 0);
		wrefresh(board[i]);
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

/*
	string john = to_string(int)
	mvwprintw(board[k + 20], 1, 1, john.c_str());
*/
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

bool Draft::notNums(char *nums, int &rank){
	for(int i = 0; i < 3; i++){
		if(isdigit(nums[i]) || !nums[i]){ //char is digit or is NULL
			continue;					  //keep going
		}
		else{							  //must be a non null non digit
			rank = 0;
			return true;
		}
	}
	return false;
}