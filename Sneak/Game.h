#pragma once
#include<time.h>
#include "BackUp.h"
#include "Map.h"
#include<fstream>

int const how_long=10; //koñcowa d³ugoœæ wê¿a

class Game
{
private:
	//int DT;
	int version;
	int lvl;
	int size;
	int move;
	int camp;
	Position2D Player[how_long];
	Position2D mouse;
	//Position2D minus;
	//Position2D plus;
	vector<Position2D> player;
	Position2D clear;
public:
	void Fail();
	void Start(Map& m);
	void Target_position(Map& m);
	void Add(Map& m);
	Position2D& Ret_mouse();
	vector<Position2D>& Ret_player();
	void Player_move(char& last,Map& m);
	void Bingo(Map& m);
	void Aside(Map& m);
	bool Check(char z);
	void Lvl(clock_t& czas);
	Position2D Ret_clear();
	void Kill(Map& m);
	//void Over_max(Map &m);
	void Reset(Map& m);
	void After_change_map(Map& m);
	void Load_maps(char Log_horizon[20], Map& m);
	

	Game(void);
	~Game(void);
};

