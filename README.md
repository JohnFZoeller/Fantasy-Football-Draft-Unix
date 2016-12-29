# Personal---FantasyFootballDrafter
How I compile and run: g++ *.cpp -lcurses -Wall -Werror; ./a.out;

Notes(12/28/16):  Curses implemented!  works real nice for two rounds.

Notes(9/8): Switching out the bst for a vector so that I can write the autopick function for the computer. Going to have to implement the b+ tree completely from scratch and ive never done it before- so my plan is to get all the functionality down and then switch to the b+ tree. 

Notes(9/9): Semi-working version available, but without b+ tree yet.  Just started that implementation. 

Notes(10/29):  Free day before i start studying for midterms, cleaned some things up, added some time delays.  Downloaded the ncurses library in order to make my draft board.  So thats the next thing.  Ive decided to put the B+ tree on hold until the draft looks perfect with just the vector.  


The goal here is going to be to make a fantasy football draft machine that runs on the command line.   This is going
to be really similar to other fantasy football draft machines such as ESPN's or YAHOO's.

I NEED to make this for a few reasons:

a) I cant run ESPN's draft on my computer during class because my laptop is 9 years old and the fan starts freaking out everytime I open a draft. 

b) I want to be able to simulate entire drafts in less than a few minutes. If I make my own program I can adjust how fast the draft goes.
