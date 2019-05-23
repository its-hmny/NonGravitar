#include "SolarSystem.h"
#include "Planet.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <cmath>
using namespace std;

SolarSystem::SolarSystem(bool a, int difficultyLevel, int planetToDo) {
	allPlanetDestroyed = a;
	createFrame();
	head = NULL;
	initializeList(planetToDo, difficultyLevel);
	printPlanetsOnCanvas();
}

//This method initializes all the nodes, which contains the Planet pointer and other values
void SolarSystem::initializeList(int planetToDo, int difficultyLevel) {
	while (planetToDo > 0) {
		p_list tmp1 = head, tmp2 = NULL;
		if (head != NULL) {
			tmp2 = new planetList;
			tmp2->planetDestroyed = false;
			tmp2->x_coordinate = (rand() % 107) + 2;
			tmp2->y_coordinate = (rand() % 22) + 2;
			//This while check that the spot randomly chosen is empty (equal to ' ')
			while (!objectOnCanvasToBool(tmp2->x_coordinate, tmp2->y_coordinate, ' ')) {
				tmp2->x_coordinate = (rand() % 107) + 2;
				tmp2->y_coordinate = (rand() % 22) + 2;
			}
			objectOnCanvas(tmp2->x_coordinate, tmp2->y_coordinate, 'O');
			tmp2->currentPlanet = new Planet(difficultyLevel);
			tmp2->next = NULL;
			//This part attaches the new node to the rest of the list
			tmp1 = head;
			while (tmp1->next != NULL) {
				tmp1 = tmp1->next;
			}
			tmp1->next = tmp2;
			printPlanetsOnCanvas();
			planetToDo--;
		}
		else {
			head = new planetList;
			head->planetDestroyed = false;
			head->x_coordinate = (rand() % 107) + 2;
			head->y_coordinate = (rand() % 22) + 2;
			head->currentPlanet = new Planet(difficultyLevel);
			head->next = NULL;
			objectOnCanvas(head->x_coordinate, head->y_coordinate, 'O');
			printPlanetsOnCanvas();
			tmp1 = head;
			planetToDo--;
		}
	}
}

//Used to put again the planet on the canvas
void SolarSystem::printPlanetsOnCanvas() {
	p_list temp = head;
	while (temp != NULL) {
		temp->planetDestroyed = temp->currentPlanet->areAllDestroied();
		if (temp->planetDestroyed == false) {
			canvas[temp->y_coordinate][temp->x_coordinate] = 'O';
			temp = temp->next;
		}
		else {
			objectOnCanvas(temp->x_coordinate, temp->y_coordinate, ' ');
			canvas[temp->y_coordinate][temp->x_coordinate] = 'x';
			temp = temp->next;
		}
	}
}

//Refreshes the users view and give color to each point of the canvas
void SolarSystem::updateCanvasView(p_game game) {
	system("CLS");
	printPlanetsOnCanvas();
	char isATitle[110] = { "             Score:                           Health points:                  Fuel:                         \0" };
	game->setGameData(isATitle);

	const int WIDTH = 110;
	const int HEIGHT = 26;
	SMALL_RECT windowSize = { 0, 0, WIDTH - 1 , HEIGHT - 1 };
	COORD bufferSize = { WIDTH, HEIGHT };
	COORD characterBufferSize = { WIDTH, HEIGHT };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WIDTH - 1, HEIGHT - 1 };
	CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	for (int x = 0; x < WIDTH; x++) {
		int y = 0;
		consoleBuffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)isATitle[x];
		consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;

	}
	for (int y = 1; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			consoleBuffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)canvas[y - 1][x];
			if(canvas[y-1][x] == '*') consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_GREEN;
			else if (canvas[y-1][x] == '@' || canvas[y-1][x]== 'A' || canvas[y-1][x] == 'x') consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_RED;
			else if (canvas[y-1][x] == 'o' || canvas[y-1][x] == 'O') consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN;
			else consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		}
	}
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	Sleep(100);
}

//Put on the canvas every type of object
void SolarSystem::objectOnCanvas(int x, int y, char shape) {
	canvas[y][x] = shape;
}

bool SolarSystem::checkAllPlanetDestroyed() {
	p_list temp = head->next;
	allPlanetDestroyed = head->planetDestroyed;
	while ((allPlanetDestroyed) && (temp != NULL)) {
		allPlanetDestroyed = temp->planetDestroyed;
		temp = temp->next;
	}
	return(allPlanetDestroyed);
}

//Create a frame at the edge and at the same time initializes every single cell of the matrix
void SolarSystem::createFrame() {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 110; j++) {
			if ((i == 24) || (i == 0) || (j == 0) || (j == 109)) {
				canvas[i][j] = '#';
			}
			else canvas[i][j] = ' ';
		}
	}
}

//Compares the coordinates and return the Planet pointer, used to enter the Planet view of the game
p_planet SolarSystem::returnPlanetpointer(int x, int y) {
	p_list tmp = head;
	while (tmp != NULL) {
		if (tmp->x_coordinate == x && tmp->y_coordinate == y) {
			return(tmp->currentPlanet);
		}
		else {
			tmp = tmp->next;
		}
	}
	return(NULL);
}

//Used to check that a cell is empty
bool SolarSystem::objectOnCanvasToBool(int x, int y, char shape) {
	return(shape == canvas[y][x]);
}

SolarSystem::~SolarSystem() {}