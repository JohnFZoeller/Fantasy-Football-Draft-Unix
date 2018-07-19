#include "player.h"

Player::Player() : position(""), nflTeam(""), first(""), last(""), rank(0) {}

int Player::getRank() const { return rank; }

NodeData* Player::makeFromStream(istream& in) {
	in >> rank;
	in.get();
	in.get();
	getline(in, nflTeam, ' ');
	getline(in, position, ',');
	in.get();
	getline(in, first, ' ');
	getline(in, last, '\n');

	if(last[last.length() - 1] == ',')
		last.pop_back();

	return new NodeData(rank, first, last, nflTeam, position);
}

void Player::toPlayer(NodeData* change) {
	position = change->getPosition();
	nflTeam = change->getSquad();
	first = change->getFirst();
	last = change->getLast();
	rank = change->getRank();
}

string Player::playerInfo() const { 
	return first + " " + last + "    " + nflTeam; 
}