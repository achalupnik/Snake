#include "BackUp.h"
#include "Game.h"
#include "Map.h"
#include<conio.h>

int main()	//Do rozbudowy - poczytaæ o - settextattribut, consoleset
{
	char last='w';
	Map m;
	Game g;

	g.Target_position(m);
	g.Add(m);
	m.Frame();
	m.Player_position(g.Ret_player(),last);
	m.Mouse_position(g.Ret_mouse());
	g.Start(m);
	/*
	if(Map_x!=30 || Map_y!=20)
	{
		for(int i=0;i!=Map_y;i++)
			for(int j=0;j!=Map_x;j++)
				m.map[i][j]=0;
		m.Frame();
		Player[0].x=Map_x/2;
		Player[0].y=Map_y/2;
		m.Player_position(g.Ret_player(),last);
		m.Mouse_position(g.Ret_mouse());

	}*/
	system("cls");
	m.Player_position(g.Ret_player(),last);
	m.Mouse_position(g.Ret_mouse());
	m.Draw(1);
	//m.Gotoxy(21,21,16);
	

	while(1)
	{
		m.Player_position(g.Ret_player(),last);
		m.Mouse_position(g.Ret_mouse());
		g.Player_move(last,m);
		g.Kill(m);
		m.Reset(g.Ret_clear());


	}
	
	system("pause");
	exit(1);
	return 0;
}
	

/*
for(int i=0;i!=256;i++)
		cout<<i<<"."<<char(i)<<"\t";*/


/*
Beep(500, 500);
	Beep(600, 400);
	Beep(700, 300);
        Sleep(50);
        Beep(600, 200);
	Beep(800, 100);
	Beep(700, 600);
	Beep(600, 400);
	Beep(700, 300);
	Beep(900, 500);
	Sleep(30);
	Beep(600, 300);
	Beep(900, 100);
	Beep(600, 300);
	Beep(300, 500);
	*/


