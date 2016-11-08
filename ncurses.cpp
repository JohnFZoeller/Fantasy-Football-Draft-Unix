#include <iostream>
#include <ncurses.h>
using namespace std;

int main(){
	int john = 4;

	//begin program
	initscr(); 
	raw();	   
	//begin program


	start_color();
	init_pair(1, COLOR_RED, COLOR_BLUE); //foreground, backgroud
	attron(COLOR_PAIR(1)); //START COLOR

	printw("ahh my eyes");

	attroff(COLOR_PAIR(1)); //END COLOR




	//end program
	getch();
	endwin();
	//end program

	return 0;

}

	// printw("this is the string %d", john );
	// addch('a');
	// move(12, 13);  //y, x

	// mvprintw(15, 20, "movement");
	// mvaddch(12, 50, '@');

/*
	attron(A_STANDOUT | A_UNDERLINE);
	mvprintw(12, 40, "ReAD THIS NOT");
	attroff(A_STANDOUT | A_UNDERLINE);*/