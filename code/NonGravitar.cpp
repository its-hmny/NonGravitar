/*	NonGravitar -> Game created by Enea Guidi, Simone Boldrini, Marco Tomasone and Gabriele Salvarani	
	Please see the README to understand more about the gameplay and the system requirements		*/

#include "Game.h"
#include "SolarSystem.h"
#include "Planet.h"
#include "Spaceship.h"
#include <iostream>
#include <Windows.h>
using namespace std;

/*	POINTERS TYPE DEFINITION	*/
typedef class SolarSystem* p_solarSystem;
typedef class Planet* p_planet;
typedef class Game* p_game;
typedef class Spaceship* p_spaceship;

/*	GLOBAL VARIABLE DECLARATION	*/
int currentSolarSystemNumber = 0;
p_solarSystem currentSS = NULL;
p_planet currentP = NULL;
p_game myGame = NULL;
p_spaceship player = NULL;
int iterationCounter = 0;
bool game_restart = false;

/*	FUNCTION DECLARATION	*/
void ShowConsoleCursor(bool showFlag);
void setupGame();
void SolarSystemView();
void SetupPlanetView();
void PlanetView();
void returnToSSView();
void SetupNextSS();
void returnToPreviousSS();
void gameOver();

int main() {
	restart:
	setupGame();
	while (myGame->checkGameRunning()) {
		SolarSystemView();
		//If the Spaceship is on a planet in Solar System view then a pointer to that planet is returned
		if (currentP != NULL) {
			SetupPlanetView();
			while (myGame->checkGameRunning() && currentP != NULL) {
				PlanetView();
				//Player in Planet view wants to return to Solar System view
				if (player->returnPosition('y') == 1) {
					returnToSSView();
				}
			}
		}
		//Player want to go in the next Solar System (only if he has destroyed all the planet in the current Solar System)
		else if (player->returnPosition('x') == 108 && currentSS->checkAllPlanetDestroyed()) {
			SetupNextSS();
		}
		//Player wants to go back in the previous Solar System
		else if (player->returnPosition('x') == 1 && currentSolarSystemNumber > 0) {
			returnToPreviousSS();
		}
	}
	gameOver();
	if (game_restart) goto restart;
	else return(0);
}

/*	FUNCTIONS DEFINITION	*/

//Disable the cursor showing while refreshing the screen
void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

//Setup the gameplay and make it ready to play, it assign to currentSS the first Solar System generated
void setupGame() {
	myGame = new Game();
	player = new Spaceship();
	ShowConsoleCursor(false);
	myGame->startScreen(game_restart);
	currentSS = myGame->sendPointer(currentSolarSystemNumber);
}

void SolarSystemView() {
	currentSS->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), ' ');
	player->Move(currentP, myGame);
	currentSS->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), 'V');
	currentP = currentSS->returnPlanetpointer(player->returnPosition('x'), player->returnPosition('y'));
	iterationCounter++;
	if ((iterationCounter % 25) == 0) {
		myGame->changeFuel(1, false);
		iterationCounter = 0;
	}
	currentSS->updateCanvasView(myGame);
}

//Takes care of setting up the Planet view for the selected planet
void SetupPlanetView() {
	myGame->transactionAnimation();
	currentSS->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), ' ');
	player->resetCoordinate(true, currentP);
}

void PlanetView() {
	currentP->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), ' ');
	player->Move(currentP, myGame);
	currentP->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), 'V');
	iterationCounter++;
	if ((iterationCounter % 25) == 0) {
		currentP->bunkerShoot();
		myGame->changeFuel(1, false);
		iterationCounter = 0;
	}
	currentP->updateShoot(myGame);
	currentP->updateCanvasView(myGame);
}

//Used when the player wants to return to the Solar System view, especially clear all the bullets from the canvas
void returnToSSView() {
	myGame->transactionAnimation();
	currentP->updateShoot(myGame);
	currentP->clearAllBullets();
	currentP->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), ' ');
	player->resetCoordinate(false, currentP);
	currentP = NULL;
}

//Create the next Solar System (only when the first is completely destroyed)
void SetupNextSS() {
	myGame->transactionAnimation();
	myGame->newSolarSystem();
	currentSS->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), ' ');
	player->resetCoordinate(false, currentP);
	currentSS = myGame->sendPointer(++currentSolarSystemNumber);
}

//Used if the player wants to go back to the previous Solar System
void returnToPreviousSS() {
	myGame->transactionAnimation();
	currentSS->objectOnCanvas(player->returnPosition('x'), player->returnPosition('y'), ' ');
	player->resetCoordinate(false, currentP);
	currentSS = myGame->sendPointer(--currentSolarSystemNumber);
}

void gameOver() {
	game_restart = myGame->gameOver();
	system("CLS");
	myGame->~Game();
	myGame = NULL,	currentP = NULL, currentSS = NULL;
	player->resetCoordinate(false, NULL);
	currentSolarSystemNumber = 0;
}