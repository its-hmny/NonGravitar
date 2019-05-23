#include "Planet.h"
#include "Game.h"
#include "Bunker.h"
#include "Bunker2.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>
using namespace std;

Planet::Planet(int level) : SolarSystem(true, 0, 0) {
	setupSurface(level);
	srand(time(NULL));
	toList1 = setupBunker1List(rand() % 2 + 3);
	toList2 = setupBunkerList2(rand() % 2 + 3);
	putOnCanvas(toList1, toList2);
}

//Create the "hill" and the "plane" parts of the planet's surface
void Planet::setupSurface(int level) {
	int hPart = (rand() % 10) + 13 - level;
	int parz = 0;
	int i = 1;
	int temp = 0;
	int molt = 0;
	bool carbSet = false;
	int nextCarb = 10;
	int  valueRandCarburante = 0;

	do {
		while (i < 109) {
			do {
				parz = (rand() % 3) - 1;
				molt = (rand() % 5) + 2;
			} while (((parz * molt) + hPart > 20) || (hPart + (molt * parz) < 7 - level));
			if (i < nextCarb)
				carbSet = true;
			else
				carbSet = false;
			for (temp = molt; temp > 0 && i < 109; temp--) {
				canvas[parz + hPart][i] = '*';
				if (parz == 0 && carbSet == false) {
					valueRandCarburante = typeCarburante(parz + hPart, i);
					if (valueRandCarburante == 2) {
						carbSet = true;
						canvas[hPart - 1][i] = 'O';
						nextCarb = i + 16 + (level * 2);
					}
					else if (valueRandCarburante == 1) {
						carbSet = true;
						canvas[hPart - 1][i] = 'o';
						nextCarb = i + 16 + (level * 2);
					}
				}
				hPart = parz + hPart;
				i++;
			}
		}
	} while ((countChar('O') + countChar('o') < 1 || countChar('O') + countChar('o') > 7) && elementInRow(4));
}

//Counts the how many char equal to the input are in the matrix
int Planet::countChar(char c) {
	int countP = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 110; j++) {
			if (canvas[i][j] == c)
				countP++;
		}
	}
	return countP;
}

//Delete the attraction ray of the Spaceship
void Planet::delAttRay() {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 110; j++) {
			if (canvas[i][j] == 92 || canvas[i][j] == 47)
				canvas[i][j] = ' ';
		}
	}
}

//QUESTO NON SO CHE CAZZO SCRIVERCI
int Planet::typeCarburante(int x, int y) {
	int r = (rand() % 10) + y * x;
	if (r % 5 == 0)
		return 1;
	else if (r % 7 == 0)
		return 2;
	else return 0;
}

char Planet::returnCanvasPoint(int x, int y) {
	return canvas[y][x];
}

//Used to assign y to Bunkers, return the position immediatly after the "ground"
int Planet::return_y_height(int x_lenght) {
	int i = 0;
	while (canvas[i][x_lenght] != '*') {
		i++;
	}
	return(--i);
}

void Planet::bunkerShoot() {
	p_bunkerList1 tmp = toList1;
	while (tmp != NULL) {
		tmp->bunkerDestroyed = tmp->actual->isDestroyed();
		if (!tmp->bunkerDestroyed) {
			objectOnCanvas(tmp->x_pos, tmp->y_pos, '@');
			tmp->actual->bunkerShoot(tmp->x_pos, tmp->y_pos - 1);
		}
		tmp = tmp->next;
	}
	p_bunkerList2 tmp2 = toList2;
	while (tmp2 != NULL) {
		tmp2->bunkerDestroyed = tmp2->actual->isDestroyed();
		if (!tmp2->bunkerDestroyed) {
			objectOnCanvas(tmp2->x_pos, tmp2->y_pos, 'A');
			tmp2->actual->bunkerShoot(tmp2->x_pos, tmp2->y_pos - 1);
		}
		tmp2 = tmp2->next;
	}
}

//Delete all the shots of the Bunker, used especially when a bunker is destroyed or the player returned to the Solar System view
void Planet::clearAllBullets() {
	p_bunkerList1 tmp1 = toList1;
	while (tmp1 != NULL) {
		tmp1->actual->eliminateAllShoot(this);
		tmp1 = tmp1->next;
	}
	p_bunkerList2 tmp2 = toList2;
	while (tmp2 != NULL) {
		tmp2->actual->eliminateAllShoot(this);
		tmp2 = tmp2->next;
	}
}

void Planet::updateShoot(p_game myGame) {
	p_bunkerList1 tmp1 = toList1;
	while (tmp1 != NULL) {
		tmp1->bunkerDestroyed = tmp1->actual->isDestroyed();
		tmp1->actual->updateShoot(this, myGame);
		tmp1 = tmp1->next;
	}
	p_bunkerList2 tmp2 = toList2;
	while (tmp2 != NULL) {
		tmp2->bunkerDestroyed = tmp2->actual->isDestroyed();
		tmp2->actual->updateShoot(this, myGame);
		tmp2 = tmp2->next;
	}
	toList1 = checkIfDestroyedBunker1(toList1);
	toList2 = checkIfDestroyedBunker2(toList2);
	putOnCanvas(toList1, toList2);
}

//Create and initialize the list of Bunker (Type 1)
p_bunkerList1 Planet::setupBunker1List(int toDo) {
	if (toDo == 0)
		return(NULL);
	else {
		p_bunkerList1 tmp = new bunkerList1;
		tmp->bunkerDestroyed = false;
		tmp->x_pos = rand() % 104 + 5;
		tmp->y_pos = return_y_height(tmp->x_pos);
		while (!objectOnCanvasToBool(tmp->x_pos, tmp->y_pos, ' ')) {
			tmp->x_pos = rand() % 104 + 5;
			tmp->y_pos = return_y_height(tmp->x_pos);
		}
		tmp->actual = new Bunker();
		tmp->next = setupBunker1List(toDo - 1);
		return(tmp);
	}
}

//Create and initialize the list of Bunker (Type 2)
p_bunkerList2 Planet::setupBunkerList2(int toDo) {
	if (toDo == 0)
		return(NULL);
	else {
		p_bunkerList2 tmp = new bunkerList2;
		tmp->bunkerDestroyed = false;
		tmp->x_pos = rand() % 104 + 5;
		tmp->y_pos = return_y_height(tmp->x_pos);
		while (!objectOnCanvasToBool(tmp->x_pos, tmp->y_pos, ' ')) {
			tmp->x_pos = rand() % 104 + 5;
			tmp->y_pos = return_y_height(tmp->x_pos);
		}
		tmp->actual = new Bunker2();
		tmp->next = setupBunkerList2(toDo - 1);
		return(tmp);
	}
}

//Put che char on the matrix
void Planet::putOnCanvas(p_bunkerList1 one, p_bunkerList2 two) {
	p_bunkerList1 tmp1 = one;
	while (tmp1 != NULL) {
		objectOnCanvas(tmp1->x_pos, tmp1->y_pos, '@');
		tmp1 = tmp1->next;
	}
	p_bunkerList2 tmp2 = two;
	while (tmp2 != NULL) {
		objectOnCanvas(tmp2->x_pos, tmp2->y_pos, 'A');
		tmp2 = tmp2->next;
	}
}

//Checks if all the bunker in both lists are completely destroyed
bool Planet::areAllDestroied() {
	return((toList1 == NULL) && (toList2 == NULL));
}

//Search and find for the bunker in the position given and decrements its HP
void Planet::bunkerHit(int x, int y) {
	p_bunkerList1 tmp = toList1;
	while ((tmp != NULL) && !(tmp->x_pos == x && tmp->y_pos == y)) {
		tmp = tmp->next;
	}
	//Checks if the bunker is in the first list, else checks in the second list
	if (tmp != NULL) {
		tmp->actual->decrementHP();
	}
	else {
		p_bunkerList2 tmp2 = toList2;
		while ((tmp2 != NULL) && !(tmp2->x_pos == x && tmp2->y_pos == y)) {
			tmp2 = tmp2->next;
		}
		if (tmp2 != NULL) {
			tmp2->actual->decrementHP();
		}
	}
}

p_bunkerList1 Planet::checkIfDestroyedBunker1(p_bunkerList1 current) {
	if (current != NULL) {
		if (current->bunkerDestroyed) {
			current->actual->eliminateAllShoot(this);
			current->actual->~Bunker();
			objectOnCanvas(current->x_pos, current->y_pos, ' ');
			p_bunkerList1 tmp = current->next;
			delete current;
			return(checkIfDestroyedBunker1(tmp));
		}
		else {
			current->next = checkIfDestroyedBunker1(current->next);
			return(current);
		}
	}
	else return (NULL);
}

p_bunkerList2 Planet::checkIfDestroyedBunker2(p_bunkerList2 current) {
	if (current != NULL) {
		if (current->bunkerDestroyed) {
			current->actual->eliminateAllShoot(this);
			current->actual->~Bunker2();
			objectOnCanvas(current->x_pos, current->y_pos, ' ');
			p_bunkerList2 tmp = current->next;
			delete current;
			return(checkIfDestroyedBunker2(tmp));
		}
		else {
			current->next = checkIfDestroyedBunker2(current->next);
			return(current);
		}
	}
	else return(NULL);
}

//Check that there's no asterisk on the window frame
bool Planet::elementInRow(int y) {
	return(canvas[y][0] == '*');
}

Planet::~Planet() {}