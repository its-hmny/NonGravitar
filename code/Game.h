#pragma once

typedef class SolarSystem* p_solarSystem;

struct Galaxy {
	int solarSystemNumber;
	p_solarSystem currentSolarSystem;
	struct Galaxy* next;
};
typedef struct Galaxy* p_galaxy;

class Game {
protected:
	bool gameIsRunning;
	int score;
	int fuel;
	int healthPoints;
	p_galaxy head;
public:
	Game(bool a = true, int c = 0, int d = 15, int e = 5);
	void newSolarSystem();
	p_solarSystem sendPointer(int number);
	bool checkGameRunning();
	void setGameData(char title[110]);
	void changeFuel(int changeToApply, bool isToAdd);
	void startScreen(bool mustPrintScreen);
	bool gameOver();
	void pauseScreen();
	void changeHP();
	void changeScore();
	void transactionAnimation();
	~Game();
};