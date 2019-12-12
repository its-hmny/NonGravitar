#include "Game.h"
#include "SolarSystem.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

Game::Game(bool a, int c, int d, int e) {
	srand(time(NULL));
	gameIsRunning = a;
	score = c;
	fuel = d;
	healthPoints = e;
	//Initialize Galaxy list (Galaxy contains one Solar System that as well contains a random number of Planet)
	head = new Galaxy;
	head->solarSystemNumber = 0;
	head->currentSolarSystem = new SolarSystem(false, head->solarSystemNumber, (rand() % (5 + head->solarSystemNumber) + 2));
	head->next = NULL;
}

//Creates a new SolarSystem and initializes all the variables of the new node
void Game::newSolarSystem() {
	p_galaxy temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	int nextSolarSystemNumber = temp->solarSystemNumber + 1;
	temp->next = new Galaxy;
	temp->next->solarSystemNumber = nextSolarSystemNumber;
	temp->next->currentSolarSystem = new SolarSystem(false, temp->solarSystemNumber, (rand() % (5 + head->solarSystemNumber) + 2));
	temp->next->next = NULL;
}

//Return the SolaSystem pointer (used to change from one SolarSystem to another)
p_solarSystem Game::sendPointer(int desiredSolarSystemNumber) {
	p_galaxy temp = head;
	while (temp != NULL) {
		if (temp->solarSystemNumber == desiredSolarSystemNumber) {
			return (temp->currentSolarSystem);
		}
		else {
			temp = temp->next;
		}
	} return(NULL);
}

bool Game::checkGameRunning() {
	if ((fuel > 0) && (healthPoints > 0)) {
		gameIsRunning = true;
		return(gameIsRunning);
	}
	else {
		gameIsRunning = false;
		return(gameIsRunning);
	}
}

void Game::setGameData(char title[110]) {
	int changeToDo = 3, i = 0;
	while ((changeToDo > 0) && (title[i] != '\0') && (i < 110)) {
		if (title[i] == ':') {
			--changeToDo;
			if (changeToDo == 2) {
				int temp = this->score;
				int divisor = 10, actualPos = i + 10;
				do {
					title[actualPos] = (temp % divisor) + 48;
					temp = temp / divisor;
					actualPos--;
				} while ((actualPos > i) && (temp != 0));
				i++;
			}
			else if (changeToDo == 1) {
				int temp = healthPoints;
				int divisor = 10, actualPos = i + 5;
				do {
					title[actualPos] = (char) ((temp % divisor) + 48);
					temp = temp / divisor;
					actualPos--;
				} while ((actualPos > i) && (temp != 0));
				i++;
			}
			else if (changeToDo == 0) {
				int temp = fuel;
				int divisor = 10, actualPos = i + 5;
				do {
					title[actualPos] = ((temp % divisor) + 48);
					temp = temp / divisor;
					actualPos--;
				} while ((actualPos > i) && (temp != 0));
				i++;
			}
		}
		i++;
	}
}

//The bool value determines if the int value should be added or subtracted, the second if checks a superior limitation of the value
void Game::changeFuel(int changeToApply, bool isToAdd) {
	if (isToAdd) {
		if ((fuel + changeToApply) > 25) {
			fuel = 25;
		}
		else {
			fuel = fuel + changeToApply;
		}
	}
	else {
		fuel = fuel - changeToApply;
	}
}

void Game::startScreen(bool mustPrintScreen) {
	if (!mustPrintScreen) {
		cout << endl << endl << endl << endl;
		cout << "\t\t\t" << "    _   __            ______                 _ __            " << endl;
		cout << "\t\t\t" << "   / | / /___  ____  / ____/________ __   __(_) /_____ ______" << endl;
		cout << "\t\t\t" << "  /  |/ / __  / __  / / __/ ___/ __ `/ | / / / __/ __ `/ ___/" << endl;
		cout << "\t\t\t" << " / /|  / /_/ / / / / /_/ / /  / /_/ /| |/ / / /_/ /_/ / /    " << endl;
		cout << "\t\t\t" << "/_/ |_/ ____/_/ /_/ ____/_/    __,_/ |___/_/ __/ __,_/_/     " << endl;
		cout << endl;
		cout << "\t       Game created by Enea Guidi, Simone Boldrini, Marco Benito Tomasone, Gabriele Salvarani" << endl << endl;
		cout << "\t\t\t\t\t     Press space to start" << endl;
		while (!(GetAsyncKeyState(VK_SPACE))) {}
	}
}

bool Game::gameOver() {
	system("CLS");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t   " << "   ______                        ____                 " << endl;
	cout << "\t\t\t   " << "  / ____/___ _____ ___  ___     / __  _   _____  _____" << endl;
	cout << "\t\t\t   " << " / / __/ __ `/ __ `__  / _     / / / / | / / _  / ___/" << endl;
	cout << "\t\t\t   " << "/ /_/ / /_/ / / / / / /  __/  / /_/ /| |/ /  __/ /    " << endl;
	cout << "\t\t\t   " << " ____/ __,_/_/ /_/ /_/ ___/    ____/ |___/ ___/_/     " << endl << endl;
	cout << "\t\t\t\t " <<"Press Y to restart the game, N to close it";
	while (1) {
		if (GetAsyncKeyState(0x59)) {
			return(true);
		}
		else if (GetAsyncKeyState(0x4E)) {
			return(false);
		}
	}
}

void Game::pauseScreen() {
	system("CLS");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t\t " << "______                    " << endl;
	cout << "\t\t\t\t\t " << "| ___ |                   " << endl;
	cout << "\t\t\t\t\t " << "| |_/ /_ _ _   _ ___  ___ " << endl;
	cout << "\t\t\t\t\t " << "|  __/ _` | | | / __|/ _ |" << endl;
	cout << "\t\t\t\t\t " << "| | | (_| | |_|  __ \  __/" << endl;
	cout << "\t\t\t\t\t " << "|_|   __,_| __,_|___/ ___|" << endl;
	cout << endl << "\t\t\t\t     ";
	system("PAUSE");
}

void Game::changeHP() {
	healthPoints--;
}

void Game::changeScore() {
	score += 100;
}

void Game::transactionAnimation() {
	for (int i = 0; i < 50; i++) {
		cout << endl;
		Sleep(20);
	}
}

Game::~Game() {}