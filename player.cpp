#include "player.h"

Player::Player(){
	spot = team = first = last = "";
}

NodeData* Player::makeFromStream(istream& in){
    // int stock;
    // string director, title, year;

    // in.get();
    // in.get();
    // in >> stock;
    // in.get();
    // in.get();
    // getline(in, director, ',');
    // in.get();
    // getline(in, title, ',');
    // in.get();
    // getline(in, year, '\n');

    // year.erase(4);

    //NodeData* john = new NodeData(director + " " + title, stock);
	cout << "make from stream called" << endl;
	NodeData* john;
    return john;
}