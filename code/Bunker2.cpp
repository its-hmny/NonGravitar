#include "Bunker2.h"
#include "Bunker.h"
#include "Bullets.h"
#include "Planet.h"
#include "Game.h"
#include <iostream>

Bunker2::Bunker2() : Bunker() {
	center = new Bullets();
	healthPoints += 100;
}

void Bunker2::bunkerShoot(int x, int y) {
	Bunker::bunkerShoot(x, y);
	center->addNewBullet(x, y);
}

void Bunker2::updateShoot(p_planet currentP, p_game myGame) {
	Bunker::updateShoot(currentP, myGame);
	center->updateShoot(0, -1, currentP, myGame);
}

void Bunker2::eliminateAllShoot(p_planet currentP) {
	Bunker::eliminateAllShoot(currentP);
	center->cleanTheGarbage(currentP);
}

Bunker2::~Bunker2() {}