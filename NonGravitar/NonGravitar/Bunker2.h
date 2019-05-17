#pragma once
#include "Bunker.h"

typedef class Bullets* p_bullets;
typedef class Game* p_game;

class Bunker2 : public Bunker {
protected:
	p_bullets center;
public:
	Bunker2();
	void bunkerShoot(int x, int y);
	void updateShoot(p_planet currentP, p_game myGame);
	void eliminateAllShoot(p_planet currentP);
	~Bunker2();
};