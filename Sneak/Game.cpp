#include"Game.h"
#include<ctime>
#include<cstdlib>



Game::Game(void):lvl(1),size(0),move(0),camp(1)
{
}


Game::~Game(void)
{
}


void Game::Reset(Map& m)
{
	for(int i=0;i<m.Map_y;i++)
		for(int j=0;j<m.Map_x;j++)
			m.map[i][j]=0;
}


void Game::Start(Map& m)
{
	system("cls");
	system("title Snake MAXIMA");
	cout<<"Start Game"<<endl<<"Zagrasz:\n1) Graj!\n2) Potyczka\n Kreator map:\n3) Ustaw wielkosc mapy\n4) Ustaw przeszkode\n5) Resetuj mape\n6) Zapisz Mape\n7) Wczytaj Mape\n\n8) Wyjscie\n------------------\n";
	cin>>version;
	
	if(version==1)
	{

		Load_maps("mapa",m);
		cout<<"Poziom:\n1) Kuternoga\n2) Slabeusz\n3) Mierny\n4) Sredni\n5) Hardcore\n";
		cin>>lvl;

		player[0].x=1;
		player[0].y=7;
		mouse.x=1;
		mouse.y=2;
		camp=0;


		char last='w';
		system("cls");
	m.Player_position(Ret_player(),last);
	m.Mouse_position(Ret_mouse());
	m.Draw(1);
	m.Gotoxy(21,21,16);


		while(1)
	{
		m.Player_position(Ret_player(),last);
		m.Mouse_position(Ret_mouse());
		Player_move(last,m);
		Kill(m);
		m.Reset(Ret_clear());
		if(player[0].x==21 && player[0].y==21)
			break;

	}
		system("cls");
		cout<<"Gratuluje! Oto koniec twej sciezki\n";
		system("pause");
		exit(1);
		
	}

		
	switch(version)
	{
	case 2:
		cout<<"Poziom:\n1) Kuternoga\n2) Slabeusz\n3) Mierny\n4) Sredni\n5) Hardcore\n";
		cin>>lvl;
		system("pause");
		break;
	case 4:
		system("cls");
		m.Create_obstacle(Ret_mouse());

		system("cls");
		//m.Obstacle(1);
		cout<<"Mapa zaktualizowana"<<endl;
		system("pause");
		Start(m);
		break; 
	case 3:
		system("cls");
		//Reset(m);

		for(int i=0;i<m.Map_y-2;i++)
				delete[] m.map[i];
		//delete[] m.map;

		cout<<"Podaj wysokosc: ";
		cin>>m.Map_y;
		m.Map_y+=2;
		cout<<"Podaj szerokosc: ";
		cin>>m.Map_x;
		m.Map_x+=2;
//		Over_max(m);
		m.map=new int *[m.Map_x];
			for(int i=0;i<m.Map_y;i++)
			{
				m.map[i]=new int[m.Map_x];
				for(int j=0;j<m.Map_x;j++)
					m.map[i][j]=0;
			}

		//Reset(m);
		
		/*if(m.Map_x>m.Oryg_map_x || m.Map_y>m.Oryg_map_y)
		{
			//map[x][x]
			
			

			
			
			cout<<"\nx - nie moze byc wieksze od "<<m.Oryg_map_x-2<<"\ny - nie moze byc wieksze od "<<m.Oryg_map_y-2<<endl;
			system("pause");
			m.Map_x=m.Oryg_map_x;
			m.Map_y=m.Oryg_map_y;
		}*/

		After_change_map(m);
		
		cout<<endl;
		system("cls");
		m.Draw(2);
		system("pause");
		Start(m);
		break;
	case 5:
		for(int i=0;i<m.Map_y-2;i++)
				delete[] m.map[i];
		//delete[] m.map;

		m.Map_x=m.Oryg_map_x;
		m.Map_y=m.Oryg_map_y;

		m.map=new int *[m.Map_x];
			for(int i=0;i<m.Map_y;i++)
				m.map[i]=new int[m.Map_x];

		Reset(m);

		After_change_map(m);
		Start(m);
		break;
	/*case 4:
		system("cls");
		m.Obstacle(2);
		Start(m);
		break; */
	case 8:
		exit(1);
	case 6:
		fstream plik;
		plik.open("Mapy.txt",ios::app);
		char nazwa[20];
		cout<<"Podaj nazwe pliku: ";
		cin>>nazwa;
		plik<<nazwa<<" "<<m.Map_x<<" "<<m.Map_y<<" ";
		for(int i=0;i!=m.Map_y;i++)
			for(int j=0;j!=m.Map_x;j++)
				if(m.map[i][j]==9)
					plik<<j<<" "<<i<<" ";
		plik<<0<<endl;
		plik.close();
		Start(m);
		break;	
	//case 4:  
	}

	if(version==7)
	{
		cout<<"Jakiej mapy szukasz: ";
		char mapa[20];
		cin>>mapa;
		
		Load_maps(mapa,m);
		

		system("pause");
		Start(m);
	}
	
	system("cls");
}



void Game::Fail()
{
	system("cls");
	if(size==how_long)
		cout<<"CONGRATULATION!\nYou WIN!";
	else
		cout<<"Game Over";
	cout<<endl<<"Score: "<<5*lvl+10*size+30-move<<endl;
	system("pause");
	exit(1);
}


void Game::Target_position(Map& m)
{
	if(camp==1)
	{
	srand(time(0));
	mouse.x=rand()%(m.Map_x-2)+1;
	mouse.y=rand()%(m.Map_y-2)+1;

	for(int i=0;player.size()!=i;i++)
	{
		if(mouse.x==player[i].x && mouse.y==player[i].y)
		{
			Target_position(m);
			return;
		}

	}
	
	if(m.map[mouse.y][mouse.x]==9)
	{
		Target_position(m);
		return;
	}
	//if(version!=2)
		m.Gotoxy(mouse.x,mouse.y,2);
	
	}
	camp=1;
}


void Game::Add(Map& m)
{
	size++;

	if(size==1)
	{
		Player[0].x=m.Map_x/2;
		Player[0].y=m.Map_y/2;
		//Player[0]={Map_x/2,Map_y/2};
		player.push_back(Player[0]);
	}else
	{
		if(size==how_long)
			Fail();
		Player[size-1].x=player[size-2].x,
		Player[size-1].y=player[size-2].y;
		//Player[size-1]={Player[size-2].x,Player[size-2].y};
		player.push_back(Player[size-1]);
	}


	/*switch(size)
	{
	case 1:
		Position2D Player0={Map_x/2,Map_y/2};
		player.push_back(Player0);
		break;
	case 2:
		Position2D Player1={player[player.size()-1].x,player[player.size()-1].y};
		player.push_back(Player1);
		break;
	case 3:
		Position2D Player2={player[player.size()-1].x,player[player.size()-1].y};
		player.push_back(Player2);
		break;
	case 4:
		Position2D Player3={player[player.size()-1].x,player[player.size()-1].y};
		player.push_back(Player3);
		break;
	case 5:
		Position2D Player4={player[player.size()-1].x,player[player.size()-1].y};
		player.push_back(Player4);
		break;
	}*/

}


Position2D& Game::Ret_mouse()
{
	return mouse;
}


vector<Position2D>& Game::Ret_player()
{
	return player;
}


void Game::Player_move(char& last,Map& m)
{
	char k='x';
	clock_t czas;
	Lvl(czas);
	m.Gotoxy(0,m.Map_y,14);
	Sleep(100);
	while(czas>clock())
	{
		if(GetAsyncKeyState(VK_LEFT)<0)//W_CHAR
		{
			k='a';
			last=k;
			break;
		}
		if(GetAsyncKeyState(VK_RIGHT)<0)
		{
			k='d';
			last=k;
			break;
		}
		if(GetAsyncKeyState(VK_UP)<0)
		{
			k='w';
			last=k;
			break;
		}
		if(GetAsyncKeyState(VK_DOWN)<0)
		{
			k='s';
			last=k;
			break;
		}
	}
	
	if(k=='x')
		k=last;

	switch(k)
	{
	case 'w':
		if(player[0].y==1)
			Fail();
		if(Check('w'))
		{
			if(mouse.x==player[0].x && mouse.y==player[0].y-1)
				Bingo(m);
			else
			{
				Aside(m);
				player[0].y--;
			}
			m.Gotoxy(player[0].x,player[0].y,10);
		}
		break;

	case 's':
		if(player[0].y==m.Map_y-2)
			Fail();
		if(Check('s'))
		{
			if(mouse.x==player[0].x && mouse.y==player[0].y+1)
				Bingo(m);
			else
			{
				Aside(m);
				player[0].y++;
			}
			m.Gotoxy(player[0].x,player[0].y,11);
		}
		break;

	case 'a':
		if(player[0].x==1)
			Fail();
		if(Check('a'))
			{
			if(mouse.x==player[0].x-1 && mouse.y==player[0].y)
				Bingo(m);

			else
			{
				Aside(m);
				player[0].x--;
			}
			m.Gotoxy(player[0].x,player[0].y,12);
		}
		break;

	case 'd': 
		if(player[0].x==m.Map_x-2)
			Fail();
		if(Check('d'))
			{
				if(mouse.x==player[0].x+1 && mouse.y==player[0].y)
					Bingo(m);
				else
				{
					Aside(m);
					player[0].x++;
				
				}
				m.Gotoxy(player[0].x,player[0].y,13);
			}
		break;
	}



}


void Game::Bingo(Map& m)
{
	Add(m);
	for(int i=player.size()-2;i!=0;i--)
		{
			player[i].x=player[i-1].x;
			player[i].y=player[i-1].y;
		}
	player[0].x=mouse.x;
	player[0].y=mouse.y;
	if((player.size()-1)!=0)
		m.Gotoxy(player[1].x,player[1].y,1);
	Target_position(m);
}


void Game::Aside(Map& m)
{
	clear.x=player[player.size()-1].x;
	clear.y=player[player.size()-1].y;
	m.Gotoxy(clear.x,clear.y,0);
	if((player.size()-1)!=0)
		m.Gotoxy(player[0].x,player[0].y,1);
	for(int i=player.size()-1;i!=0;i--)
			{
				player[i].x=player[i-1].x;
				player[i].y=player[i-1].y;
			}
}


bool Game::Check(char z)
{
	if(size>1)
	switch(z)
	{
	case 'w':
		if(player[0].y==player[1].y+1)
			Fail();
		else 
			return 1;
	case 's':
		if(player[0].y==player[1].y-1)
			Fail();
		else 
			return 1;
	case 'a':
		if(player[0].x==player[1].x+1)
			Fail();
		else 
			return 1;
	case 'd':
		if(player[0].x==player[1].x-1)
			Fail();
		else 
			return 1;
	default:
		return 0;
	}
		return 1;

}


void Game::Kill(Map& m)
{
	for(int i=1;i<player.size();i++)
		if(player[0].x==player[i].x && player[0].y==player[i].y)
			Fail();

	if(m.map[player[0].y][player[0].x]==9)
		Fail();
}


void Game::Lvl(clock_t& czas)
{
	switch(lvl)
	{
	case 1:
		czas=clock()+2000;
		break;
	case 2:
		czas=clock()+1000;
		break;
	case 3:
		czas=clock()+500;
		break;
	case 4:
		czas=clock()+250;
		break;
	case 5:
		czas=clock()+70;
		break;
	}
}


Position2D Game::Ret_clear()
{
	return clear;
}

/*
void Game::Over_max(Map& m)
{
	if(m.Map_x>30 || m.Map_y>20)
	{
		

	/*
	m.map=new int *[Map_x];
	for(int i=0;i<Map_y;i++)
		m.map[i]=new int[Map_x];
	
	}
	}

}*/


void Game::After_change_map(Map& m)
{
		m.Frame();
		player[0].x=m.Map_x/2;
		player[0].y=m.Map_y/2;
		Target_position(m);
		m.Player_position(Ret_player(),'w');
		m.Mouse_position(Ret_mouse());
}


void Game::Load_maps(char Log_horizon[20], Map& m)
{
	fstream plik;
	int z=0;
		plik.open("Mapy.txt",ios::in);
		if(plik.good())
		{
			z++;
			char k[20];
			while(!plik.eof())
			{
				plik>>k;
				if(strcmp(k,Log_horizon)==0)
				{
					for(int i=0;i<m.Map_y-2;i++)
						delete[] m.map[i];

					plik>>m.Map_x;
					plik>>m.Map_y;

					m.Map_x+=2;
					m.Map_y+=2;

					m.map=new int *[m.Map_x];
					for(int i=0;i<m.Map_y;i++)
						m.map[i]=new int[m.Map_x];
					Reset(m);
					After_change_map(m);
					int xx,yy;
					while(1)
					{
						plik>>xx;
						if(xx==0)
							break;
						plik>>yy;
						m.map[yy][xx]=9;
					}
					z++;
					system("cls");
					cout<<"Mapa wczytana\n";
				}
				
			}
			plik.close();
		}
		if(z==0)
			cout<<"Brak dostepu do Mapy.txt\n";
		else
			if(z==1)
				cout<<"Nie ma takiej mapy\n";


		
}



