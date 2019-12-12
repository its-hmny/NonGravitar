#include "Spaceship.h"
#include "Bullets.h"
#include "Game.h"
#include "SolarSystem.h"
#include "Planet.h"
#include <Windows.h>
#include <iostream>
using namespace std;

Spaceship::Spaceship() {
	x_position = x_default_ss;
	y_position = y_default_ss;
	toShoot = new Bullets();
	carbo = false;
	carbO = false;
	attrationRay = false;
}

//Reset the actual coordinates oto the default for Solar System or Planet view, deletes also the previous location
void Spaceship::resetCoordinate(bool option, p_planet currentP) {
	if (option && currentP != NULL) {
		x_position = x_default_p;
		y_position = y_default_p;
		//Clean the shots list before exiting the planet view
		toShoot->cleanTheGarbage(currentP);
	}
	else {
		x_position = x_default_ss;
		y_position = y_default_ss;
	}
}

//This function takes care of updating the spaceship coordinate and also control the attraction ray
void Spaceship::Move(p_planet currentP, p_game currentGame) {
	//Move left
	if ((GetAsyncKeyState(VK_LEFT)) && (x_position > 1)) {
		if (currentP != NULL) {
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
		if (currentP == NULL)
			x_position = x_position - constantMovement;
		else if (currentP->returnCanvasPoint(x_position - constantMovement, y_position) != '*' &&
			currentP->returnCanvasPoint(x_position - constantMovement, y_position) != 'A' &&
			currentP->returnCanvasPoint(x_position - constantMovement, y_position) != '@') {
			attrationRay = false;
			currentP->delAttRay();
			if (currentP->returnCanvasPoint(x_position - constantMovement, y_position) == 'o') {
				x_position = x_position - constantMovement;
				carbo = true;
			}
			else if (currentP->returnCanvasPoint(x_position - constantMovement, y_position) == 'O') {
				x_position = x_position - constantMovement;
				carbO = true;
			}
			else if (carbO) {
				x_position = x_position - constantMovement;
				currentP->objectOnCanvas(x_position + constantMovement, y_position, 'O');
				carbO = false;
			}
			else if (carbo) {
				x_position = x_position - constantMovement;
				currentP->objectOnCanvas(x_position + constantMovement, y_position, 'o');
				carbo = false;
			}
			else {
				x_position = x_position - constantMovement;
			}
		}
		else {
			currentGame->changeHP();
			x_position = x_default_p;
			y_position = y_default_p;
		}
	}
	//Move right
	else if ((GetAsyncKeyState(VK_RIGHT)) && (x_position < 108)) {
		if (currentP != NULL) {
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
		if (currentP == NULL)
			x_position = x_position + constantMovement;
		else if (currentP->returnCanvasPoint(x_position + constantMovement, y_position) != '*' &&
			currentP->returnCanvasPoint(x_position + constantMovement, y_position) != 'A' &&
			currentP->returnCanvasPoint(x_position + constantMovement, y_position) != '@') {
			attrationRay = false;
			currentP->delAttRay();
			if (currentP->returnCanvasPoint(x_position + constantMovement, y_position) == 'o') {
				x_position = x_position + constantMovement;
				carbo = true;
			}
			else if (currentP->returnCanvasPoint(x_position + constantMovement, y_position) == 'O') {
				x_position = x_position + constantMovement;
				carbO = true;
			}
			else if (carbO) {
				x_position = x_position + constantMovement;
				currentP->objectOnCanvas(x_position - constantMovement, y_position, 'O');
				carbO = false;
			}
			else if (carbo) {
				x_position = x_position + constantMovement;
				currentP->objectOnCanvas(x_position - constantMovement, y_position, 'o');
				carbo = false;
			}
			else {
				x_position = x_position + constantMovement;
			}
		}
		else {
			currentGame->changeHP();
			x_position = x_default_p;
			y_position = y_default_p;
		}
	}
	//Move up
	else if ((GetAsyncKeyState(VK_UP)) && (y_position > 1)) {
		if (currentP != NULL) {
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
		if (currentP == NULL)
			y_position = y_position - constantMovement;
		else if (currentP->returnCanvasPoint(x_position, y_position - constantMovement) != '*' &&
			currentP->returnCanvasPoint(x_position, y_position - constantMovement) != 'A' &&
			currentP->returnCanvasPoint(x_position, y_position - constantMovement) != '@') {
			attrationRay = false;
			currentP->delAttRay();
			if (currentP->returnCanvasPoint(x_position, y_position - constantMovement) == 'o') {
				y_position = y_position - constantMovement;
				carbo = true;
			}
			else if (currentP->returnCanvasPoint(x_position, y_position - constantMovement) == 'O') {
				y_position = y_position - constantMovement;
				carbO = true;
			}
			else if (carbO) {
				y_position = y_position - constantMovement;
				currentP->objectOnCanvas(x_position, y_position + constantMovement, 'O');
				carbO = false;
			}
			else if (carbo) {
				y_position = y_position - constantMovement;
				currentP->objectOnCanvas(x_position, y_position + constantMovement, 'o');
				carbo = false;
			}
			else {
				y_position = y_position - constantMovement;
			}
		}
		else {
			currentGame->changeHP();
			x_position = x_default_p;
			y_position = y_default_p;
		}
	}
	//Move down
	else if ((GetAsyncKeyState(VK_DOWN)) && (y_position < 23)) {
		if (currentP != NULL) {
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
		if (currentP == NULL)
			y_position = y_position + constantMovement;
		else if (currentP->returnCanvasPoint(x_position, y_position + constantMovement) != '*' && 
			currentP->returnCanvasPoint(x_position, y_position + constantMovement) != 'A' &&
			currentP->returnCanvasPoint(x_position, y_position + constantMovement) != '@') {
			attrationRay = false;
			currentP->delAttRay();
			if (currentP->returnCanvasPoint(x_position, y_position + constantMovement) == 'o') {
				y_position = y_position + constantMovement;
				carbo = true;
			}
			else if (currentP->returnCanvasPoint(x_position, y_position + constantMovement) == 'O') {
				y_position = y_position + constantMovement;
				carbO = true;
			}
			else if (carbO) {
				y_position = y_position + constantMovement;
				currentP->objectOnCanvas(x_position, y_position - constantMovement, 'O');
				carbO = false;
			}
			else if (carbo) {
				y_position = y_position + constantMovement;
				currentP->objectOnCanvas(x_position, y_position - constantMovement, 'o');
				carbo = false;
			}
			else {
				y_position = y_position + constantMovement;
			}
		}
		else {
			currentGame->changeHP();
			if (!carbo && !carbO) {
				x_position = x_default_p;
				y_position = y_default_p;
			}
			
		}
	}
	//Attraction Ray
	else if (GetAsyncKeyState(VK_LSHIFT)) {
		if (currentP != NULL) {
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
		if (currentP != NULL) {
			if ((currentP->objectOnCanvasToBool(x_position + 1, y_position + 1, ' ')) && (currentP->objectOnCanvasToBool(x_position - 1, y_position + 1, ' ') && (!currentP->objectOnCanvasToBool(x_position, y_position + 1, '*')))) {
				currentP->objectOnCanvas(x_position - 1, y_position + 1, 47);
				currentP->objectOnCanvas(x_position + 1, y_position + 1, 92);
				attrationRay = true;
				if (currentP->returnCanvasPoint(x_position, y_position + 1) == 'o') {
					currentP->objectOnCanvas(x_position, y_position + 1, ' ');
					currentGame->changeFuel(3, true);
				}
				else if (currentP->returnCanvasPoint(x_position, y_position + 2) == 'o') {
					currentP->objectOnCanvas(x_position, y_position + 2, ' ');
					currentGame->changeFuel(3, true);
				}
				else if (currentP->returnCanvasPoint(x_position, y_position + 2) == 'O') {
					currentP->objectOnCanvas(x_position, y_position + 2, ' ');
					currentGame->changeFuel(5, true);
				}
				else if (currentP->returnCanvasPoint(x_position, y_position + 1) == 'O') {
					currentP->objectOnCanvas(x_position, y_position + 1, ' ');
					currentGame->changeFuel(5, true);
				}
			}
		}
	}
	//Shoot
	else if (GetAsyncKeyState(VK_SPACE)) {
		if (currentP != NULL) {
			toShoot->addNewBullet(x_position, y_position);
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
	}
	//Pause the gameplay
	else if (GetAsyncKeyState(VK_F10)) {
		currentGame->pauseScreen();
	}
	else {
		if (currentP != NULL) {
			toShoot->updateShoot(0, 1, currentP, currentGame);
		}
	}
}

int Spaceship::returnPosition(char xy) {
	if (xy == 'x') {
		return(x_position);
	}
	else if (xy == 'y') {
		return(y_position);
	}
}

Spaceship::~Spaceship() {}