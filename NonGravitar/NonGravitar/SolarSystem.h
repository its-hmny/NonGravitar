#pragma once

typedef class Planet* p_planet;
typedef class Game* p_game;

struct planetList {
	bool planetDestroyed;
	int x_coordinate;
	int y_coordinate;
	p_planet currentPlanet;
	planetList* next;
};
typedef struct planetList* p_list;


class SolarSystem {
protected:
	char canvas[25][110];
	p_list head;
	bool allPlanetDestroyed;
public:
	SolarSystem(bool a = false, int difficultyLevel = 0, int planetToDo = 3);
	void initializeList(int planetToDo, int difficultyLevel);
	void printPlanetsOnCanvas();
	void updateCanvasView(p_game game);
	void objectOnCanvas(int x, int y, char shape);
	bool checkAllPlanetDestroyed();
	void initializeSurface();
	p_planet returnPlanetpointer(int x, int y);
	bool objectOnCanvasToBool(int x, int y, char shape);
	~SolarSystem();
};