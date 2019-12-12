#pragma once
#include "Bunker.h"
#include "Bunker2.h"
#include "SolarSystem.h"

typedef class Bunker* p_bunker1;
struct bunkerList1 {
	bool bunkerDestroyed;
	int x_pos;
	int y_pos;
	p_bunker1 actual;
	bunkerList1* next;
};

typedef class Bunker2* p_bunker2;
struct bunkerList2 {
	bool bunkerDestroyed;
	int x_pos;
	int y_pos;
	p_bunker2 actual;
	bunkerList2* next;
};

typedef struct bunkerList1* p_bunkerList1;
typedef struct bunkerList2* p_bunkerList2;
typedef class Game* p_game;

class Planet : public SolarSystem{
protected:
	p_bunkerList1 toList1;
	p_bunkerList2 toList2;
public:
	Planet(int level = 0);
	void setupSurface(int level);
	char returnCanvasPoint(int x, int y);
	int typeCarburante(int x, int y);
	int countChar(char c);
	void delAttRay();
	int return_y_height(int x_lenght);
	void bunkerShoot();
	void clearAllBullets();
	void updateShoot(p_game myGame);
	p_bunkerList1 setupBunker1List(int toDo);
	p_bunkerList2 setupBunkerList2(int toDo);
	void putOnCanvas(p_bunkerList1 one, p_bunkerList2 two);
	bool areAllDestroied();
	void bunkerHit(int x, int y);
	p_bunkerList1 checkIfDestroyedBunker1(p_bunkerList1 current);
	p_bunkerList2 checkIfDestroyedBunker2(p_bunkerList2 current);
	bool elementInRow(int y);
	~Planet();
};