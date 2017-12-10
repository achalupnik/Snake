#include "Map.h"

const int Map::Oryg_map_x=30;
const int Map::Oryg_map_y=20;

int Map::Map_x=Map::Oryg_map_x;
int Map::Map_y=Map::Oryg_map_y;

Map::Map(void)
{
	map=new int *[Map_x];
	for(int i=0;i<Map_y;i++)
		map[i]=new int[Map_x];


	for(int i=0;i!=Map_y;i++)
		for(int j=0;j!=Map_x;j++)
			map[i][j]=0;
}


Map::~Map(void)
{
}


void Map::Reset(Position2D clear)
{
	map[clear.y][clear.x]=0;
}


void Map::Draw(int version)
{
	if(version==2)
	{
		if(Map_x>9)
		{
			cout<<"  ";
			int r;
			for(int i=0;i!=10;i++)
				cout<<" ";
			for(r=1;r<(Map_x-2)/10;r++)
				for(int j=0;j!=10;j++)
					cout<<r;
			for(int i=0;i<(Map_x-1)%10;i++)
				cout<<r;
			cout<<endl;

		}


		cout<<"   ";
		for(int i=(Map_x-2)/10;i!=0;i--)
		{
			for(int j=1;j!=10;j++)
				cout<<j;
			cout<<"0";
		}
		for(int i=1;i!=(Map_x-1)%10;i++)
			cout<<i;
		cout<<endl;
	}

//-----------

	for(int i=0;i!=Map_y;i++)
	{
		if(version==2)
		{
			if(i!=0 && i!=Map_y-1)
				printf("%2i",i);
			else
				cout<<"  ";
		}
		for(int j=0;j!=Map_x;j++)
			Choice(map[i][j]);
		cout<<endl;
	}
}



void Map::Frame()
{
	for(int i=0;i!=Map_x;i++)
	{
		cout<<i<<"\t"<<(Map_y-1)<<"\n";
		map[0][i]=3;
		map[Map_y-1][i]=3;
	}

	for(int i=0;i!=Map_y;i++)
	{
		map[i][0]=4;
		map[i][Map_x-1]=4;
	}
	map[0][0]=5;
	map[0][Map_x-1]=6;
	map[Map_y-1][0]=7;
	map[Map_y-1][Map_x-1]=8;

}


void Map::Player_position(vector<Position2D>& player,char last)
{
	for(int i=0;i!=player.size();i++)
		map[player[i].y][player[i].x]=1;

	switch(last)
	{
	case 'w':
		map[player[0].y][player[0].x]=10;
		break;
	case 's':
		map[player[0].y][player[0].x]=11;
		break;
	case 'a':
		map[player[0].y][player[0].x]=12;
		break;
	case 'd':
		map[player[0].y][player[0].x]=13;
		break;
	}
}


void Map::Mouse_position(Position2D& mouse)
{
	map[mouse.y][mouse.x]=2;
}


/*void Map::Obstacle(int r)
{
	int x,y;


	while(1)
	{
		Draw(2);
		cout<<"Podanie 0 konczy wczytywanie \nx: ";
		cin>>x;
		if(x==0)
			break;
		cout<<"y: ";
		cin>>y;
		if(y==0)
			break;
		if(Check(x,y))
			if(r==1)
				map[y][x]=9;
			else
				map[y][x]=0;
		system("cls");
	}
}*/


/*bool Map::Check(int x,int y)
{
	if(x>0 && x<Map_x-1 && y>0 && y<Map_y-1)
		return 1;
	return 0;
}*/


void Map::Gotoxy(int x, int y,int idea)
{
  COORD c;
  c.X = x ;
  c.Y = y ;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
  Choice(idea);
}


void Map::Choice(int idea)
{
	switch(idea)
		{
			case 0:
				cout<<" ";
				break;
			case 1: //w¹¿
				cout<<char(219);
				break;
			case 2: //mysz
				cout<<char(254);
				break;
			case 3:
				cout<<char(45);
				break;
			case 4:
				cout<<char(179);
				break;
			case 5:
				cout<<char(218);
				break;
			case 6:
				cout<<char(191);
				break;
			case 7:
				cout<<char(192);
				break;
			case 8:
				cout<<char(217);
				break;
			case 9://przeszkoda
				cout<<char(15);
				break;
			case 10://strza³ka w góre
				cout<<char(30);
				break;
			case 11://strza³ka w dó³
				cout<<char(31);
				break;
			case 12://strza³ka w lewo
				cout<<char(17);
				break;
			case 13://strza³ka w prawo
				cout<<char(16);
				break;
			case 15://minus
				cout<<"-";
				break;
			case 16://plus
//				HANDLE hOut;
				// hOut = GetStdHandle( STD_OUTPUT_HANDLE );
				//SetConsoleTextAttribute( hOut, FOREGROUND_RED );
				cout<<"@";
				
				
				break;
			default:
				break;
		}
}


void Map::Create_obstacle(Position2D& mouse)
{
	Obst.x=1;
	Obst.y=1;
	map[Obst.y][Obst.x]=9;
	Draw(1);
	map[Obst.y][Obst.x]=0;
	Position2D player;
	player.x=Map_x/2;
	player.y=Map_y/2;

	while(1)
	{
		if(GetAsyncKeyState(VK_LEFT)<0 && !(Obst.x-1==player.x && Obst.y==player.y) && !(Obst.x-1==mouse.x && Obst.y==mouse.y))
		{
			if(Obst.x!=1)
			{
				if(map[Obst.y][Obst.x]==0)
					Gotoxy(Obst.x,Obst.y,0);
				if(map[Obst.y][Obst.x]==9)
					Gotoxy(Obst.x,Obst.y,9);
				Obst.x--;
				Gotoxy(Obst.x,Obst.y,9);
				Gotoxy(0,Map_y,0);
				Sleep(100);
			}
		}
		if(GetAsyncKeyState(VK_RIGHT)<0 && !(Obst.x+1==player.x && Obst.y==player.y) && !(Obst.x+1==mouse.x && Obst.y==mouse.y))
		{
			if(Obst.x!=Map_x-2)
			{
				if(map[Obst.y][Obst.x]==0)
					Gotoxy(Obst.x,Obst.y,0);
				if(map[Obst.y][Obst.x]==9)
					Gotoxy(Obst.x,Obst.y,9);
				Obst.x++;
				Gotoxy(Obst.x,Obst.y,9);
				Gotoxy(0,Map_y,0);
				Sleep(100);
			}
			
		}
		if(GetAsyncKeyState(VK_UP)<0 && !(Obst.x==player.x && Obst.y-1==player.y) && !(Obst.x==mouse.x && Obst.y-1==mouse.y))
		{
			if(Obst.y!=1)
			{
				if(map[Obst.y][Obst.x]==0)
					Gotoxy(Obst.x,Obst.y,0);
				if(map[Obst.y][Obst.x]==9)
					Gotoxy(Obst.x,Obst.y,9);
				Obst.y--;
				Gotoxy(Obst.x,Obst.y,9);
				Gotoxy(0,Map_y,0);
				Sleep(100);
			}
			
		}
		if(GetAsyncKeyState(VK_DOWN)<0 && !(Obst.x==player.x && Obst.y+1==player.y) && !(Obst.x==mouse.x && Obst.y+1==mouse.y))
		{
			if(Obst.y!=Map_y-2)
			{
				if(map[Obst.y][Obst.x]==0)
					Gotoxy(Obst.x,Obst.y,0);
				if(map[Obst.y][Obst.x]==9)
					Gotoxy(Obst.x,Obst.y,9);
				Obst.y++;
				Gotoxy(Obst.x,Obst.y,9);
				Gotoxy(0,Map_y,0);
				Sleep(100);
			}
			
		}
		if(GetAsyncKeyState(VK_F1)<0)
		{
			if(map[Obst.y][Obst.x]==0)
				map[Obst.y][Obst.x]=9;
			else
				if(map[Obst.y][Obst.x]==9)
					map[Obst.y][Obst.x]=0;
			Gotoxy(0,Map_y,0);
			Sleep(200);
		}
		if(GetAsyncKeyState(VK_F3)<0)
		{
			break;
		}

	}

}

