#include "draft.h"

Draft::Draft(){
	head = NULL;
}

Draft::~Draft(){}

void Draft::setUp(){
	// takes care of:
	// time between picks
	// makes the board
}

void Draft::startDraft(){
	//displays the board
	//runs the timer
}

void Draft::makeBoard(){
	//instantiates the linked list
	//one round at a time
}

void Draft::displayBoard(){
	//displays the timer and the draft board
}

void Draft::newRound(){
	//calls the insertNode function for each of the picks in a round
}

int Draft::autoPick(){
	//integrates the autopick algorithm
}

bool Draft::insert(){
	LinkNode *ptr = new LinkNode;
	ptr->next = NULL;
	ptr->pick = new NodeData;

	if(head == NULL)
		head = ptr;
	else if(head != NULL){
		for(LinkNode *i = head; i->next != NULL; i = i->next)
			continue;
		//need to insert the node
	}
}

bool Draft::pick(){}

