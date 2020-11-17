#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

int mapheight, mapwidth, gamespeed, obstacle[99][99], l, holesize,  jumphigh, hole, score, maxmapheight;
int playposy, playposx;
bool endgame;

void setup()
{
	//Höhe der Map
	mapheight = 20;
	//Länge der Map
	mapwidth = 24;

	holesize = 7;
	//Startposition des Spielers X Koordinate
	playposx = mapwidth / 4; 
	//Startposition des Spielers Y Koordinate
	playposy = mapheight / 3;
	
	l = mapwidth;
	//Höhe die der Vogel pro Taste fliegt
	jumphigh = 3;
	//Score auf 0 setzen
	score = 0;
	//Gamespeed festlegen
	gamespeed = 10;
	//Spielende auf Falsch setzen
	endgame = false;
	
	maxmapheight = mapheight - 8;

	//generiere ein Loch das mindestens eine Höhe von 2px hat
	hole = rand() % maxmapheight + 2;

}

void map()
{

	//clear Screen
	system("cls");
	//Score ausgeben
	cout << "Score: " << score << endl;
	
	

	cout << endl;
	//erstellen Map Y Achse
	for (int i = 0; i < mapheight; i++)
	{
		
	//erstellen X Achse
		for (int j = 0; j < mapwidth; j++)
		{

			
			//wenn x Achse oben und unten erreicht sind dann mache einen Unterstrich
			//-1 wird verwendet damit man die Linie im Terminal sieht
			if (i == 0 || i == mapheight - 1) {
				cout << "_";
			}


			//zeichne den Vogel wenn er die Koordinaten hat
			 else if (playposx == j && playposy == i)
			{
				cout << "-";
			}
			//zeichne das Hindernis wenn es die Koordinaten hat
			else if (obstacle[j][i] == 1)
			{
				cout << "|";
			}

			//zeichne sonst Leerzeichen
			else
			{
				cout << " ";
			}
		}

		cout << endl;
		
	}

	cout << endl;

	
}

void playerlogic()
{
	//wenn Leerzeichen gedrückt wird
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		//bewege Koordinaten des Vogels nach oben
		playposy = playposy - jumphigh;
		//damit es nicht so schnell passiert
		Sleep(33);
	}
	else
	{
			//lasse den Vogel runter falllen
			playposy++;
		
	}

}

void gamelogic() {
	//logik damit immer neue Obstacles erstellt werden
	//1 bedeutet das ein Hindernis vorhanden ist
	for (int k = 0; k < mapheight; k++)
	{
		obstacle[l][k] = 1;
		

	}


	//die Schleife ist dafür da, dass die random dass das Random Loch angezeigt wird
	//0 bedeutet das kein Hindernis vorhanden ist
	
	for (int i = 0; i < holesize; i++)
	{
		obstacle[l][hole+i] = 0;
	}
	
	
	l--;
	

	//Abstand zwischen den Obstaclen
	for (int i = 0; i < mapheight; i++)
	{
		obstacle[l + 2][i] = 0;
	}
	
	//Zählung der Punkte
	if (l == playposx - 1)
	{
		score++;
	}
	
	//Logik das immer wieder neue Hindernisse erstellt werden
	if (l == 0)
	{
		for (int i = 0; i < mapheight; i++)
		{
			obstacle[l + 1][i] = 0;
		}
		l = mapwidth - 1;

		hole = rand() % maxmapheight + 2;
		
	}
	

	//wenn Score von 10, 20, 30 erreicht wurde, dann mach das Loch kleiner
	if (score == 10 || score == 20 || score == 30)
	{
		holesize--;
		score++;
	}

}

void checkendgame()
{
	//wenn der Player einen Rand erreicht oder gegen ein Hindernis fliegt
	if (playposy == mapheight || playposy == 1 || obstacle[playposx][playposy] == 1)
	{
		endgame = true;
	}

}

int main()
{
	while (true)
	{
		setup();
		while (endgame == false)
		{

			playerlogic();
			gamelogic();
			checkendgame();
			map();
			Sleep(gamespeed);
		}
		system("cls");
		cout << "Gameover!" << endl << "Score: " << score;
		Sleep(3000);
		setup();
	}

	return 0;
}