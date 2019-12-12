#include "Bunker.h"
#include "Planet.h"
#include "Bullets.h"
#include <iostream>
using namespace std;

Bunker::Bunker() {
	left = new Bullets();
	right = new Bullets();
	healthPoints = 200;
}

void Bunker::bunkerShoot(int x, int y) {
	left->addNewBullet(x, y);
	right->addNewBullet(x, y);
}

void Bunker::updateShoot(p_planet currentP, p_game myGame) {
	left->updateShoot(-1, -1, currentP, myGame);
	right->updateShoot(1, -1, currentP, myGame);
}

void Bunker::eliminateAllShoot(p_planet currentP) {
	left->cleanTheGarbage(currentP);
	right->cleanTheGarbage(currentP);
}

void Bunker::decrementHP() {
	healthPoints = healthPoints - 100;
}

bool Bunker::isDestroyed() {
	return(healthPoints <= 0);
}

Bunker::~Bunker() {}