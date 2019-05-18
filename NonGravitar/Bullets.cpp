#include "Bullets.h"
#include "Planet.h"
#include "Game.h"
#include <iostream>
using namespace std;

Bullets::Bullets() {
	head = NULL;
}

void Bullets::addNewBullet(int x, int y) {
	if (head == NULL) {
		head = new bulletsList;
		head->coordinateX = x;
		head->coordinateY = y;
		head->shape = '.';
		head->next = NULL;
		head->toEliminate = false;
	}
	else {
		ptr_list tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new bulletsList;
		tmp->next->toEliminate = false;
		tmp = tmp->next;
		tmp->coordinateX = x;
		tmp->coordinateY = y;
		tmp->shape = '.';
		tmp->next = NULL;
	}
}

void Bullets::updateShoot(int xToIncrement, int yToIncrement, p_planet currentP, p_game myGame) {
	ptr_list tmp = head;
	while (tmp != NULL) {
		currentP->objectOnCanvas(tmp->coordinateX, tmp->coordinateY, ' ');
		tmp->coordinateX = tmp->coordinateX + xToIncrement;
		tmp->coordinateY = tmp->coordinateY + yToIncrement;
		char toErase = currentP->returnCanvasPoint(tmp->coordinateX, tmp->coordinateY);
		if ((toErase == '*') || (toErase == '#') || (toErase == 'o') || (toErase == 'O')) {
			tmp->toEliminate = true;
		}
		else if (toErase == '@') {
			currentP->bunkerHit(tmp->coordinateX, tmp->coordinateY);
			myGame->changeScore();
			tmp->toEliminate = true;
		}
		else if (toErase == 'A') {
			currentP->bunkerHit(tmp->coordinateX, tmp->coordinateY);
			myGame->changeScore();
			tmp->toEliminate = true;
		}
		else if (toErase == 'V') {
			myGame->changeHP();
		}
		else {
			currentP->objectOnCanvas(tmp->coordinateX, tmp->coordinateY, tmp->shape);
		}
		tmp = tmp->next;
	}
	head = deleteFromList(head);
}

//Clean the list from the element that aren't useful to the gameplay
ptr_list Bullets::deleteFromList(ptr_list head) {
	if (head != NULL) {
		if (head->toEliminate == true) {
			ptr_list tmp = head->next;
			delete head;
			return(deleteFromList(tmp));
		}
		else {
			head->next = deleteFromList(head->next);
			return(head);
		}
	}
	else {
		return(head);
	}
}

//Used to clear all the shots in the list, especially when a bunker is destroyed
void Bullets::cleanTheGarbage(p_planet currentP) {
	ptr_list tmp1 = head;
	ptr_list tmp2 = NULL;
	while (tmp1 != NULL) {
		currentP->objectOnCanvas(tmp1->coordinateX, tmp1->coordinateY, ' ');
		tmp2 = tmp1->next;
		delete tmp1;
		tmp1 = NULL;
		tmp1 = tmp2;
	}
	head = NULL;
}

Bullets::~Bullets() {}