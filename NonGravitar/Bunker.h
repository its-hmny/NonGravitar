#pragma once
#include "Bullets.h"

typedef class Bullets* p_bullets;
typedef class Planet* p_planet;
typedef class Game* p_game;

class Bunker {
protected:
	int healthPoints;
	p_bullets left;
	p_bullets right;
public:
	Bunker();
	void bunkerShoot(int x, int y);
	void updateShoot(p_planet currentP, p_game myGame);
	void eliminateAllShoot(p_planet currentP);
	void decrementHP();
	bool isDestroyed();
	~Bunker();
};