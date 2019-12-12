#pragma once
#include "Bullets.h"

typedef class Planet* p_planet;
typedef class Bullets* p_bullets;
typedef class Game* p_game;

class Spaceship {
protected:
	int x_position;
	int y_position;
	const int x_default_ss = 54;
	const int y_default_ss = 12;
	const int x_default_p = 4;
	const int y_default_p = 4;
	const int constantMovement = 1;
	p_bullets toShoot;
	//SIMONE AGGIUNGI AL POSTO DI STA RIGA QUELLO A CUI SERVONO STE VARIABILI
	bool carbo;	//Caso in cui la navicella passa su un carburante senza usare il raggio traente
	bool carbO;
	bool attrationRay; //Raggio traente attivo 
public:
	Spaceship();
	void resetCoordinate(bool option, p_planet currentP);
	void Move(p_planet currentP, p_game currentGame);
	int returnPosition(char xy);
	~Spaceship();
};