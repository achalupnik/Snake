#pragma once
#include "BackUp.h"

class Map
{
private:
friend class Game;

int const static Oryg_map_x;
int const static Oryg_map_y;

int static Map_x;
int static Map_y;

int **map;

Position2D Obst;

public:
	void Reset(Position2D clear);
	void Draw(int version);
	void Frame();
	void Player_position(vector<Position2D>& player,char last);
	void Mouse_position(Position2D& mouse);
	//void Obstacle(int r);
	//bool Check(int x,int y);
	void Gotoxy(int x, int y,int idea);
	void Choice(int idea);
	void Create_obstacle(Position2D& mouse);

	Map(void);
	~Map(void);
};

