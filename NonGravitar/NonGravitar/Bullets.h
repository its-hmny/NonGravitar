#pragma once

struct bulletsList {
	int coordinateX;
	int coordinateY;
	char shape;
	bool toEliminate;
	bulletsList* next;
};

typedef bulletsList* ptr_list;
typedef class Planet* p_planet;
typedef class Game* p_game;

class Bullets {
protected:
	ptr_list head;
public:
	Bullets();
	void addNewBullet(int x, int y);
	void updateShoot(int xToIncrement, int yToIncrement, p_planet currentP, p_game myGame);
	ptr_list deleteFromList(ptr_list head);
	void cleanTheGarbage(p_planet currentP);
	~Bullets();
};