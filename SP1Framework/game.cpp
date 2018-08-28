// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>

//using namespace std;
bool contactcheck = true;
bool contactcheckLevel2 = true;
bool contactcheckLevel21 = true;
bool contactcheckLevel22= true;
bool movementLock = false;

double  g_dElapsedTime;
double  g_dDeltaTime;

double  g_dGuardTimeX = 0.0;
double  g_dGuardTimeY = 0.0;
double  g_dGuardTimeZ = 0.0;

double  g_dGuardTimeXLevel2 = 0.0;
double  g_dGuardTimeYLevel2 = 0.0;
double  g_dGuardTimeZLevel2 = 0.0;
double  g_dRotationTime = 0.0;
double  g_dRotationTime3 = 0.0;

double g_dGuardMove = 0.0;
double g_dBullet1 = 0.0;

double  g_dGameOver = 0.0;
bool    g_abKeyPressed[K_COUNT];

bool Hidden1Stage2 = false;
bool Hidden2Stage2 = false;
bool Hidden3Stage2 = false;

double startgame = 1.0; //SPLASHSCREEN TIME
char level1[250][250]; //To store level 1 map into a 2D array 
char level2[250][250]; //To store level 2 map into a 2D array 
char Level2Hidden[250][250]; //To store the hidden passages of Level 2 into a 2D array
char level3[300][300]; //To store level 3 map into a 2D array 
char Level3Hidden[300][300]; // To store the hidden map of level 3 into a 2D array
signed int MenuItem = 0;
int level = 0;

char ShiveNumber = '0';
char KeyNumber = '0';
char KeyFragment = '0';
char lives = '2';


// Game specific variables here
SGameChar   g_sChar; //Player character
SGameChar   g_sLevel2Char; //Level 2 Characters
SGameChar   g_sLevel3Char; //Level 3 Characters

SGameChar   g_sLevel1GuardCells; //Level 1 guards
SGameChar   g_sLevel1GuardCafe;
SGameChar   g_sLevel1GuardField1;
SGameChar   g_sLevel1GuardField2;

SGameChar   g_sLevel1PrisonerCells; //Level 1 Prisoners
SGameChar   g_sLevel1PrisonerShowers;
SGameChar   g_sLevel1PrisonerCafe;

SGameChar   g_sLevel2RotatingGuard; //Level 2 Guards
SGameChar   g_sLevel2UpGuard;
SGameChar   g_sLevel2DownGuard;
SGameChar   g_sLevel2LeftGuard;
SGameChar   g_sLevel2RightGuard;
SGameChar   g_sLevel2CafeGuard;

SGameChar   g_sLevel2PrisonerCell; //Level 2 Prisoner

SGameChar   g_sLevel3Guard[3]; //Level 3 Guard
SGameChar   g_sMidGLOS[3];
//------------------------------------------------------------------
//LEVEL 1 LOS/Arrows
SGameChar   g_sRightArr[4];
SGameChar   g_sLeftArr[4];
SGameChar   g_sUpF1Arr[4];
SGameChar   g_sUpF2Arr[4];
SGameChar   g_sUpCArr[4];
SGameChar   g_sDownF1Arr[4];
SGameChar   g_sDownF2Arr[4];
SGameChar   g_sDownCArr[4];

//LEVEL 2 ARROWS

SGameChar   g_sUpGuardDownLOS[13];
SGameChar   g_sUpGuardUpLOS[13];

SGameChar   g_sDownGuardUpLOS[13];
SGameChar   g_sDownGuardDownLOS[13];

SGameChar   g_sRightGuardLeftLOS[13];
SGameChar   g_sRightGuardRightLOS[13];

SGameChar   g_sLeftGuardRightLOS[13];
SGameChar   g_sLeftGuardLeftLOS[13];

SGameChar   g_sRotatingGuardDownLOS[18];
SGameChar   g_sRotatingGuardUpLOS[18];
SGameChar   g_sRotatingGuardRightLOS[34];
SGameChar   g_sRotatingGuardLeftLOS[34];

SGameChar   g_sCafeRotatingGuardRightLOS[20];
SGameChar   g_sCafeRotatingGuardUpLOS[5];

//LEVEL 3 ARROWS
SGameChar   g_sLeftGHorLOS[25];
SGameChar   g_sLeftGVerLOS[16];
SGameChar   g_sRightGHorLOS[25];
SGameChar   g_sRightGVerLOS[16];


EGAMESTATES g_eGameState = S_SPLASHSCREEN;

double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

					   
Console g_Console(300, 300, "SP1 Framework"); // Console object

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

void init(void)
{
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;

	//g_Console.getConsoleSize().X / 2;
	//g_Console.getConsoleSize().Y / 2;

	//LEVEL 1 CHARACTERS
	g_sChar.m_cLocation.X = 6; //Player spawn point
	g_sChar.m_cLocation.Y = 4;

	g_sLevel1GuardCells.m_cLocation.X = 4; //Spawn Point of Guard near the Cells area
	g_sLevel1GuardCells.m_cLocation.Y = 8;

	g_sLevel1GuardCafe.m_cLocation.X = 45; //Spawn Point of Guard near the Cafe area
	g_sLevel1GuardCafe.m_cLocation.Y = 11;

	g_sLevel1GuardField1.m_cLocation.X = 85; //Spawn Point of Guard 1 near the Field area
	g_sLevel1GuardField1.m_cLocation.Y = 12;

	g_sLevel1GuardField2.m_cLocation.X = 95;  //Spawn Point of Guard 2 near the Field area
	g_sLevel1GuardField2.m_cLocation.Y = 4;

	g_sLevel1PrisonerCells.m_cLocation.X = 15; //Spawn Point of Prisoner near the Cells area
	g_sLevel1PrisonerCells.m_cLocation.Y = 4;

	g_sLevel1PrisonerShowers.m_cLocation.X = 45;  //Spawn Point of Prisoner near the Showers area
	g_sLevel1PrisonerShowers.m_cLocation.Y = 24;

	g_sLevel1PrisonerCafe.m_cLocation.X = 43;  //Spawn Point of Prisoner near the Cafe area
	g_sLevel1PrisonerCafe.m_cLocation.Y = 11;

	//LEVEL 1 ARROWS
	//LEVEL 1 DIRECTION POINTERS 
	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 5;
		int yy = 8;
		if (sett == 1)
		{
			xx = 6;
			yy = 7;
		}
		if (sett == 2)
		{
			xx = 6;
			yy = 8;
		}
		if (sett == 3)
		{
			xx = 6;
			yy = 9;
		}
		g_sRightArr[sett].m_cLocation.X = xx; //Spawn of direction arrow (CELL) RIGHT
		g_sRightArr[sett].m_cLocation.Y = yy;
	}

	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 13;
		int yy = 8;
		if (sett == 1)
		{
			xx = 13;
			yy = 7;
		}
		if (sett == 2)
		{
			xx = 12;
			yy = 8;
		}
		if (sett == 3)
		{
			xx = 12;
			yy = 9;
		}
		g_sLeftArr[sett].m_cLocation.X = xx; //Spawn of direction arrow (CELL) LEFT
		g_sLeftArr[sett].m_cLocation.Y = yy;
	}

	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 85;
		int yy = 11;
		if (sett == 1)
		{
			xx = 84;
			yy = 10;
		}
		if (sett == 2)
		{
			xx = 85;
			yy = 10;
		}
		if (sett == 3)
		{
			xx = 86;
			yy = 10;
		}
		g_sUpF1Arr[sett].m_cLocation.X = xx; //Spawn of direction arrow (FIELD 1) DOWN
		g_sUpF1Arr[sett].m_cLocation.Y = yy;
	}
	//g_sUpF1Arr.m_cLocation.X = 85; //FIELD 1
	//g_sUpF1Arr.m_cLocation.Y = 11; 

	//g_sDownF1Arr.m_cLocation.X = 85; //FIELD 1
	//g_sDownF1Arr.m_cLocation.Y = 6;
	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 85;
		int yy = 6;
		if (sett == 1)
		{
			xx = 84;
			yy = 7;
		}
		if (sett == 2)
		{
			xx = 85;
			yy = 7;
		}
		if (sett == 3)
		{
			xx = 86;
			yy = 7;
		}
		g_sDownF1Arr[sett].m_cLocation.X = xx; //Spawn of direction arrow (FIELD 1) DOWN
		g_sDownF1Arr[sett].m_cLocation.Y = yy;
	}

	//g_sUpF2Arr.m_cLocation.X = 95; //FIELD 2
	//g_sUpF2Arr.m_cLocation.Y = 10;
	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 95;
		int yy = 10;
		if (sett == 1)
		{
			xx = 94;
			yy = 9;
		}
		if (sett == 2)
		{
			xx = 95;
			yy = 9;
		}
		if (sett == 3)
		{
			xx = 96;
			yy = 9;
		}
		g_sUpF2Arr[sett].m_cLocation.X = xx; //Spawn of direction arrow (FIELD 2) UP
		g_sUpF2Arr[sett].m_cLocation.Y = yy;
	}

	//g_sDownF2Arr.m_cLocation.X = 95; //FIELD 2
	//g_sDownF2Arr.m_cLocation.Y = 5;
	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 95;
		int yy = 5;
		if (sett == 1)
		{
			xx = 94;
			yy = 6;
		}
		if (sett == 2)
		{
			xx = 95;
			yy = 6;
		}
		if (sett == 3)
		{
			xx = 96;
			yy = 6;
		}
		g_sDownF2Arr[sett].m_cLocation.X = xx; //Spawn of direction arrow (FIELD 2) DOWN
		g_sDownF2Arr[sett].m_cLocation.Y = yy;
	}

	//g_sUpCArr.m_cLocation.X = 45; //CAFETERIA
	//g_sUpCArr.m_cLocation.Y = 10;

	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 45;
		int yy = 10;
		if (sett == 1)
		{
			xx = 44;
			yy = 9;
		}
		if (sett == 2)
		{
			xx = 45;
			yy = 9;
		}
		if (sett == 3)
		{
			xx = 46;
			yy = 9;
		}
		g_sUpCArr[sett].m_cLocation.X = xx; //Spawn of direction arrow (CAFE UP) 
		g_sUpCArr[sett].m_cLocation.Y = yy;
	}

	//g_sDownCArr.m_cLocation.X = 45;//CAFETERIA
	//g_sDownCArr.m_cLocation.Y = 7;

	for (int sett = 0; sett < 4; sett++)
	{
		int xx = 45;
		int yy = 7;
		if (sett == 1)
		{
			xx = 44;
			yy = 8;
		}
		if (sett == 2)
		{
			xx = 45;
			yy = 8;
		}
		if (sett == 3)
		{
			xx = 46;
			yy = 8;
		}
		g_sDownCArr[sett].m_cLocation.X = xx; //Spawn of direction arrow (CAFE DOWN)
		g_sDownCArr[sett].m_cLocation.Y = yy;
	}

	//--------------------------------------------------------------------------------------

	//LEVEL 2 CHARACTERS
	g_sLevel2Char.m_cLocation.X = 46; //Level 2 Character spawn point (46, 3)
	g_sLevel2Char.m_cLocation.Y = 3;

	g_sLevel2RotatingGuard.m_cLocation.X = 36;
	g_sLevel2RotatingGuard.m_cLocation.Y = 20;

	g_sLevel2UpGuard.m_cLocation.X = 36;
	g_sLevel2UpGuard.m_cLocation.Y = 2;

	g_sLevel2DownGuard.m_cLocation.X = 36;
	g_sLevel2DownGuard.m_cLocation.Y = 38;
	
	g_sLevel2RightGuard.m_cLocation.X = 70;
	g_sLevel2RightGuard.m_cLocation.Y = 20;
	
	g_sLevel2LeftGuard.m_cLocation.X = 2;
	g_sLevel2LeftGuard.m_cLocation.Y = 20;
	
	g_sLevel2CafeGuard.m_cLocation.X = 2;
	g_sLevel2CafeGuard.m_cLocation.Y = 28;

	//LEVEL 2 CHARACTERS
	g_sLevel2PrisonerCell.m_cLocation.X = 42;
	g_sLevel2PrisonerCell.m_cLocation.Y = 8;

	//LEVEL 2 ARROWS/LOS

	//g_sLevel2UpGuard.m_cLocation.X = 36;
	//g_sLevel2UpGuard.m_cLocation.Y = 2;

	
	int xxL2 = 35;
	int yyL2 = 19;

	for (int sett = 0; sett < 3; sett++) // LOOP TO SET THE FIRST LANES
	{

		g_sUpGuardDownLOS[sett].m_cLocation.X = xxL2;
		g_sUpGuardDownLOS[sett].m_cLocation.Y = 3;
		
	    g_sDownGuardUpLOS[sett].m_cLocation.X = xxL2;
		g_sDownGuardUpLOS[sett].m_cLocation.Y = 37;
		
		g_sLeftGuardRightLOS[sett].m_cLocation.X = 3;
		g_sLeftGuardRightLOS[sett].m_cLocation.Y = yyL2;

		g_sRightGuardLeftLOS[sett].m_cLocation.X = 69;
		g_sRightGuardLeftLOS[sett].m_cLocation.Y = yyL2;

		//when going in the reverse directions
		g_sUpGuardUpLOS[sett].m_cLocation.X = xxL2;
		g_sUpGuardUpLOS[sett].m_cLocation.Y = 15;

		g_sDownGuardDownLOS[sett].m_cLocation.X = xxL2;
		g_sDownGuardDownLOS[sett].m_cLocation.Y = 25;

		g_sLeftGuardLeftLOS[sett].m_cLocation.X = 28;
		g_sLeftGuardLeftLOS[sett].m_cLocation.Y = yyL2;

		g_sRightGuardRightLOS[sett].m_cLocation.X = 45;
		g_sRightGuardRightLOS[sett].m_cLocation.Y = yyL2;

		xxL2++;
		yyL2++;
	}

	xxL2 = 32;
	yyL2 = 18;
	for (int sett = 3; sett < 12; sett++)
	{
		
		g_sUpGuardDownLOS[sett].m_cLocation.X = xxL2;
		g_sUpGuardDownLOS[sett].m_cLocation.Y = 4;
		
		g_sDownGuardUpLOS[sett].m_cLocation.X = xxL2;
		g_sDownGuardUpLOS[sett].m_cLocation.Y = 36;

		//Reverse direction
		g_sUpGuardUpLOS[sett].m_cLocation.X = xxL2;
		g_sUpGuardUpLOS[sett].m_cLocation.Y = 14;

		g_sDownGuardDownLOS[sett].m_cLocation.X = xxL2;
		g_sDownGuardDownLOS[sett].m_cLocation.Y = 26;


		if (yyL2 < 23)
		{ 
			g_sLeftGuardRightLOS[sett].m_cLocation.X = 4;
			g_sLeftGuardRightLOS[sett].m_cLocation.Y = yyL2;

			g_sRightGuardLeftLOS[sett].m_cLocation.X = 68;
			g_sRightGuardLeftLOS[sett].m_cLocation.Y = yyL2;

			//Reverse Direction
			g_sLeftGuardLeftLOS[sett].m_cLocation.X = 27;
			g_sLeftGuardLeftLOS[sett].m_cLocation.Y = yyL2;

			g_sRightGuardRightLOS[sett].m_cLocation.X = 46;
			g_sRightGuardRightLOS[sett].m_cLocation.Y = yyL2;
			yyL2++;
		}
		
		xxL2++;
	}


	for (int sett = 0; sett < 30; sett++)
	{
		if (sett < 18)
		{
			g_sRotatingGuardUpLOS[sett].m_cLocation.X = 36;
			g_sRotatingGuardUpLOS[sett].m_cLocation.Y = 20;
		}
	}

	int yyL2Up = 19; //For the rotating guard in the center
	int yyL2Down = 21; //For the rotating guard in the center
	for (int sett = 0; sett < 18; sett++)
	{
		g_sRotatingGuardUpLOS[sett].m_cLocation.X = 36;
		g_sRotatingGuardUpLOS[sett].m_cLocation.Y = yyL2Up;

		g_sRotatingGuardDownLOS[sett].m_cLocation.X = 36;
		g_sRotatingGuardDownLOS[sett].m_cLocation.Y = yyL2Down;

		yyL2Up--;
		yyL2Down++;
	}

	int xxL2Right = 37; //For the rotating guard in the center
	int xxL2Left = 35; //For the rotating guard in the center
	for (int sett = 0; sett < 35; sett++)
	{
		g_sRotatingGuardLeftLOS[sett].m_cLocation.X = xxL2Left;
		g_sRotatingGuardLeftLOS[sett].m_cLocation.Y = 20;

		g_sRotatingGuardRightLOS[sett].m_cLocation.X = xxL2Right;
		g_sRotatingGuardRightLOS[sett].m_cLocation.Y = 20;

		xxL2Right++;
		xxL2Left--;
	}

	int yyL2CafeUp = 27; //For the rotating guard in the cafe
	int xxL2CafeRight = 3; //For the rotating guard in the cafe
	for (int sett = 0; sett < 18; sett++)
	{
		if (sett < 3)
		{
			g_sCafeRotatingGuardUpLOS[sett].m_cLocation.X = 2;
			g_sCafeRotatingGuardUpLOS[sett].m_cLocation.Y = yyL2CafeUp;
			yyL2CafeUp--;
		}
		g_sCafeRotatingGuardRightLOS[sett].m_cLocation.X = xxL2CafeRight;
		g_sCafeRotatingGuardRightLOS[sett].m_cLocation.Y = 28;
		xxL2CafeRight++;
	}
	//------------------------------------------------------------------------------
	//LEVEL 3 CHARACTERS

	g_sLevel3Char.m_cLocation.X = 58; //Level 2 Character spawn point (46, 3)
	g_sLevel3Char.m_cLocation.Y = 3;

	g_sLevel3Guard[0].m_cLocation.X = 12;
	g_sLevel3Guard[0].m_cLocation.Y = 18;

	g_sLevel3Guard[1].m_cLocation.X = 46;
	g_sLevel3Guard[1].m_cLocation.Y = 18;

	g_sLevel3Guard[2].m_cLocation.X = 81;
	g_sLevel3Guard[2].m_cLocation.Y = 18;

	g_sLeftGHorLOS[0].m_cLocation.X = 13;
	g_sLeftGHorLOS[0].m_cLocation.Y = 18;

	int yy;

	yy = 17;
	for (int sett = 1; sett < 4; sett++)
	{
		g_sLeftGHorLOS[sett].m_cLocation.Y = yy;
		g_sLeftGHorLOS[sett].m_cLocation.X = 14;
		yy++;
	}
	yy = 16;
	for (int sett = 4; sett < 9; sett++)
	{
		g_sLeftGHorLOS[sett].m_cLocation.Y = yy;
		g_sLeftGHorLOS[sett].m_cLocation.X = 15;
		yy++;
	}
	yy = 15;
	for (int sett = 9; sett < 16; sett++)
	{
		g_sLeftGHorLOS[sett].m_cLocation.Y = yy;
		g_sLeftGHorLOS[sett].m_cLocation.X = 16;
		yy++;
	}
	yy = 14;
	for (int sett = 16; sett < 25; sett++)
	{
		g_sLeftGHorLOS[sett].m_cLocation.Y = yy;
		g_sLeftGHorLOS[sett].m_cLocation.X = 17;
		yy++;
	}

	g_sRightGHorLOS[0].m_cLocation.X = 80;
	g_sRightGHorLOS[0].m_cLocation.Y = 18;

	int yy1;
	yy1 = 17;
	for (int sett = 1; sett < 4; sett++)
	{
		g_sRightGHorLOS[sett].m_cLocation.Y = yy1;
		g_sRightGHorLOS[sett].m_cLocation.X = 79;
		yy1++;
	}
	yy1 = 16;
	for (int sett = 4; sett < 9; sett++)
	{
		g_sRightGHorLOS[sett].m_cLocation.Y = yy1;
		g_sRightGHorLOS[sett].m_cLocation.X = 78;
		yy1++;
	}
	yy1 = 15;
	for (int sett = 9; sett < 16; sett++)
	{
		g_sRightGHorLOS[sett].m_cLocation.Y = yy1;
		g_sRightGHorLOS[sett].m_cLocation.X = 77;
		yy1++;
	}
	yy1 = 14;
	for (int sett = 16; sett < 25; sett++)
	{
		g_sRightGHorLOS[sett].m_cLocation.Y = yy1;
		g_sRightGHorLOS[sett].m_cLocation.X = 76;
		yy1++;
	}

	g_sLeftGVerLOS[0].m_cLocation.X = 12;
	g_sLeftGVerLOS[0].m_cLocation.Y = 17;

	int xx;
	xx = 11;

	for (int sett = 1; sett < 4; sett++)
	{
		g_sLeftGVerLOS[sett].m_cLocation.Y = 16;
		g_sLeftGVerLOS[sett].m_cLocation.X = xx;
		xx++;
	}
	xx = 10;
	for (int sett = 4; sett < 9; sett++)
	{
		g_sLeftGVerLOS[sett].m_cLocation.Y = 15;
		g_sLeftGVerLOS[sett].m_cLocation.X = xx;
		xx++;
	}
	xx = 9;
	for (int sett = 9; sett < 16; sett++)
	{
		g_sLeftGVerLOS[sett].m_cLocation.Y = 14;
		g_sLeftGVerLOS[sett].m_cLocation.X = xx;
		xx++;
	}

	g_sRightGVerLOS[0].m_cLocation.X = 81;
	g_sRightGVerLOS[0].m_cLocation.Y = 17;
	int xx1;
	xx1 = 80;
	for (int sett = 1; sett < 4; sett++)
	{
		g_sRightGVerLOS[sett].m_cLocation.Y = 16;
		g_sRightGVerLOS[sett].m_cLocation.X = xx1;
		xx1++;
	}
	xx1 = 79;
	for (int sett = 4; sett < 9; sett++)
	{
		g_sRightGVerLOS[sett].m_cLocation.Y = 15;
		g_sRightGVerLOS[sett].m_cLocation.X = xx1;
		xx1++;
	}
	xx1 = 78;
	for (int sett = 9; sett < 16; sett++)
	{
		g_sRightGVerLOS[sett].m_cLocation.Y = 14;
		g_sRightGVerLOS[sett].m_cLocation.X = xx1;
		xx1++;
	}
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
}

void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[W] = isKeyPressed(0x57);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[S] = isKeyPressed(0x53);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[A] = isKeyPressed(0x41);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[D] = isKeyPressed(0x44);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_RETURN] = isKeyPressed(0x52);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_INTERACT] = isKeyPressed(0x45);
	g_abKeyPressed[K_CRAFT] = isKeyPressed(0x43);
	g_abKeyPressed[K_NEXTLEVEL] = isKeyPressed(0x54);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
}

void update(double dt)
{
	// update the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	g_dBullet1 += dt;

	g_dGuardMove += dt;

	g_dGuardTimeX += g_dDeltaTime;
	g_dGuardTimeY += g_dDeltaTime;
	g_dGuardTimeZ += g_dDeltaTime;
	g_dGuardTimeXLevel2 += dt;
    g_dGuardTimeYLevel2 += g_dDeltaTime;
	g_dGuardTimeZLevel2 += g_dDeltaTime;
	g_dRotationTime += g_dDeltaTime;
	g_dRotationTime3 += g_dDeltaTime;
	g_dGameOver += dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAMELEVEL1: gameplayLevel1(); // gameplay logic when we are in the Level 1
		break;
	case S_GAMELEVEL2: gameplayLevel2(); // gameplay logic when we are in the Level 2
		break;
	case S_GAMELEVEL3: gameplayLevel3(); // gameplay logic when we are in the Level 3
		break;
	case S_GAMEOVER: gameoverwait();
		break;
	}
}

void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;

	case S_GAMELEVEL1:
		renderLevelOne(); //Renders all the characters in Lvl 1
		break;
	case S_GAMELEVEL2:
		renderLevelTwo();  //Renders all the characters in Lvl 2
		break;
	case S_GAMELEVEL3:
		renderLevelThree();  //Renders all the characters in Lvl 3
		break;
	case S_GAMEEXIT: g_bQuitGame;
		break;
	case S_GAMEOVER: gameovercondition();
		break;
	case S_CLEAR: renderClear();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > g_dBounceTime && (g_abKeyPressed[K_DOWN] || g_abKeyPressed[S]))
	{
		MenuItem = (MenuItem + 1) % 4;
		g_dBounceTime = g_dElapsedTime + 0.125;
	}
	if (g_dElapsedTime > g_dBounceTime && (g_abKeyPressed[K_UP] || g_abKeyPressed[W]))
	{
		MenuItem = (MenuItem - 1) % 4;
		g_dBounceTime = g_dElapsedTime + 0.125;
		if (MenuItem == -1)
		{
			MenuItem = 3;
		}
	}
	if (g_abKeyPressed[K_ENTER])
	{
		if (MenuItem == 0)
		{
			g_eGameState = S_GAMELEVEL1;
			loadTutorialMap();
		}
		if (MenuItem == 1)
		{
			g_eGameState = S_GAMELEVEL2;
			loadBronzeMap();
		}
		if (MenuItem == 2)
		{
			g_eGameState = S_GAMELEVEL3;
			loadSteelMap();
		}
		if(MenuItem == 3)
		{
			g_bQuitGame = true;
		}
	}
}



//Global Variables for AI

//LEVEL 1
int move = 0;
int move1 = 0;
int move2 = 0;

int count = 0;
int count1 = 0;
int count2 = 0;

//LEVEL 2
int TurnCount = 0;
int moveLevel2 = 0;
int move1Level2 = 0;

int Level2Count1 = 0;
int Level2Count2 = 0;

//AI MOVEMENT
void Level1AIMovement()
{
	if (g_dGuardTimeX >= 0.20)
	{
		count = 1;

		//FOR CELL GUARD
		if (g_sLevel1GuardCells.m_cLocation.X < 14 && move != 10) //X starts at 3
		{
			/*g_sLeftArr.m_cLocation.X = 12;*/
			for (int sett = 0; sett < 4; sett++)
			{
				int xx = 0;
				if (sett == 0)
				{
					xx = 13;
				}
				else
				{
					xx = 12;
				}
				g_sLeftArr[sett].m_cLocation.X = xx; //Spawn of direction arrow (CELL)
			}
			g_sLevel1GuardCells.m_cLocation.X++;
			for (int inc = 0; inc < 4; inc++)
			{
				g_sRightArr[inc].m_cLocation.X++;
			}
			g_dGuardTimeX = 0.0;
			move++;
		}
	}

	if (g_dGuardTimeX >= 0.20 && move == 10)
	{

		count = 2;

		contactcheck = false;
		//FOR CELL GUARD
		if (g_sLevel1GuardCells.m_cLocation.X > 2)
		{
			for (int sett = 0; sett < 4; sett++)
			{
				int xx = 0;
				if (sett == 0)
				{
					xx = 5;
				}
				else
				{
					xx = 6;
				}
				g_sRightArr[sett].m_cLocation.X = xx; //Spawn of direction arrow (CELL)
			}
			/*	g_sRightArr.m_cLocation.X = 4;*/
			g_sLevel1GuardCells.m_cLocation.X--;
			for (int inc = 0; inc < 4; inc++)
			{
				g_sLeftArr[inc].m_cLocation.X--;
			}
			/*g_sLeftArr.m_cLocation.X--;*/
			g_dGuardTimeX = 0.0;
		}

		//TO RESET FOR LOOPING
		if (g_sLevel1GuardCells.m_cLocation.X == 4)
		{
			move = 0;
		}
	}
	////////////////////

	if (g_dGuardTimeZ >= 0.25)
	{
		count1 = 1;
		if (move2 == 0)
		{
			for (int sett = 0; sett < 4; sett++)
			{
				int yy = 0;
				if (sett == 0)
				{
					yy = 10;
				}
				else
				{
					yy = 9;
				}
				g_sUpF2Arr[sett].m_cLocation.Y = yy; //Spawn of direction arrow (CELL)
			}
			/*g_sUpF2Arr.m_cLocation.Y = 10;*/
			/*g_sDownF1Arr.m_cLocation.Y = 6;*/
			for (int sett = 0; sett < 4; sett++)
			{
				int yy = 0;
				if (sett == 0)
				{
					yy = 6;
				}
				else
				{
					yy = 7;
				}
				g_sDownF1Arr[sett].m_cLocation.Y = yy; //Spawn of direction arrow (CELL)
			}
		}
		//FOR FIELD GUARDS
		if (g_sLevel1GuardField1.m_cLocation.Y > 3 && move2 != 7) //Y starts at 15
		{
			contactcheck = true;
			g_sLevel1GuardField1.m_cLocation.Y--;
			for (int inc = 0; inc < 4; inc++)
			{
				g_sUpF1Arr[inc].m_cLocation.Y--;
			}
			/*g_sUpF1Arr.m_cLocation.Y--;*/
			g_dGuardTimeZ = 0.0;
		}


		if (g_sLevel1GuardField2.m_cLocation.Y < 12 && move2 != 7) //Y starts at 5
		{
			contactcheck = true;
			g_sLevel1GuardField2.m_cLocation.Y++;
			for (int inc = 0; inc < 4; inc++)
			{
				g_sDownF2Arr[inc].m_cLocation.Y++;
			}
			/*g_sDownF2Arr.m_cLocation.Y++;*/
			g_dGuardTimeZ = 0.0;
			move2++;
		}
	}

	if (g_dGuardTimeZ >= 0.25 && move2 == 7)
	{
		contactcheck = false;

		//FOR FIELD GUARDS
		if (g_sLevel1GuardField1.m_cLocation.Y < 12) //Y starts at 5
		{
			count1 = 2;
			g_sLevel1GuardField1.m_cLocation.Y++;
			/*g_sDownF1Arr.m_cLocation.Y++;*/
			for (int inc = 0; inc < 4; inc++)
			{
				g_sDownF1Arr[inc].m_cLocation.Y++;
			}
			g_dGuardTimeZ = 0.0;

		}
		if (g_sLevel1GuardField2.m_cLocation.Y > 4/*3*/) //Y starts at 5
		{
			g_sLevel1GuardField2.m_cLocation.Y--;
			g_dGuardTimeZ = 0.0;
			/*g_sUpF2Arr.m_cLocation.Y--;*/
			for (int dec = 0; dec < 4; dec++)
			{
				g_sUpF2Arr[dec].m_cLocation.Y--;
			}
		}

		if (g_sLevel1GuardField1.m_cLocation.Y == 12)
		{
			/*g_sUpF1Arr.m_cLocation.Y = 11;*/
			for (int sett = 0; sett < 4; sett++)
			{
				int yy = 0;
				if (sett == 0)
				{
					yy = 11;
				}
				else
				{
					yy = 10;
				}
				g_sUpF1Arr[sett].m_cLocation.Y = yy; //Spawn of direction arrow (CELL)
			}

			for (int sett = 0; sett < 4; sett++)
			{
				int yy = 0;
				if (sett == 0)
				{
					yy = 5;
				}
				else
				{
					yy = 6;
				}
				g_sDownF2Arr[sett].m_cLocation.Y = yy; //Spawn of direction arrow (CELL)
			}
			/*g_sDownF2Arr.m_cLocation.Y = 5;*/
			move2 = 0;
		}
	}
	//////////////////////

	if (g_dGuardTimeY >= 0.35)
	{
		if (move1 == 0)
		{
			/*g_sDownCArr.m_cLocation.Y = 7;*/
			for (int sett = 0; sett < 4; sett++)
			{
				int yy = 0;
				if (sett == 0)
				{
					yy = 7;
				}
				else
				{
					yy = 8;
				}
				g_sDownCArr[sett].m_cLocation.Y = yy; //Spawn of direction arrow (CELL)
			}
		}
		contactcheck = true;
		//FOR CAFE GUARD
		if (g_sLevel1GuardCafe.m_cLocation.Y > 6 && move1 != 5) //Y starts at 13
		{
			count2 = 1;
			g_sLevel1GuardCafe.m_cLocation.Y--;
			/*g_sUpCArr.m_cLocation.Y--;*/
			for (int dec = 0; dec < 4; dec++)
			{
				g_sUpCArr[dec].m_cLocation.Y--;
			}
			g_dGuardTimeY = 0.0;
			move1++;
		}
	}

	if (g_dGuardTimeY >= 0.35 && move1 == 5)
	{
		count2 = 2;
		contactcheck = false;
		//FOR CAFE GUARD
		if (g_sLevel1GuardCafe.m_cLocation.Y < 13)
		{
			g_sLevel1GuardCafe.m_cLocation.Y++;
			/*g_sDownCArr.m_cLocation.Y++;*/
			for (int dec = 0; dec < 4; dec++)
			{
				g_sDownCArr[dec].m_cLocation.Y++;
			}
			g_dGuardTimeY = 0.0;
		}
		if (g_sLevel1GuardCafe.m_cLocation.Y == 11)
		{
			/*g_sUpCArr.m_cLocation.Y = 10;*/
			for (int sett = 0; sett < 4; sett++)
			{
				int yy = 0;
				if (sett == 0)
				{
					yy = 10;
				}
				else
				{
					yy = 9;
				}
				g_sUpCArr[sett].m_cLocation.Y = yy; //Spawn of direction arrow (CELL)
			}
			move1 = 0;
		}
	}
}
void Level2AIMovement()
{
	int yyL2 = 19;
	//For the turning AI situated in the center of the map
	if (g_dRotationTime >= 0 && g_dRotationTime <= 1.0)
	{
		TurnCount = 1;
	}
	if (g_dRotationTime >= 1.0 && g_dRotationTime <= 2.0)
	{
		TurnCount = 2;
	}
	if (g_dRotationTime >= 2.0 && g_dRotationTime <= 3.0)
	{
		TurnCount = 3;
	}
	if (g_dRotationTime >= 3.0 && g_dRotationTime <= 4.0)
	{
		TurnCount = 4;
	}
	if (g_dRotationTime >= 4.0)
	{
		g_dRotationTime = 0;
	}

	int XX = 34; //USED TO SET THE X VALUES OF THE RENDER

	//For the Up and down guards (Total 14, 6 down first)
	if (g_dGuardTimeYLevel2 >= 0.25 && moveLevel2 != 12) //MOVING FORWARD
	{
		contactcheckLevel21 = true;
		Level2Count1 = 0;

		for (int inc = 0; inc < 12; inc++)// INCREMENT LOOP
		{
			g_sUpGuardDownLOS[inc].m_cLocation.Y++;
			g_sDownGuardUpLOS[inc].m_cLocation.Y--;
		}
		g_sLevel2UpGuard.m_cLocation.Y++;
		g_sLevel2DownGuard.m_cLocation.Y--;

		for (int sett = 0; sett < 12; sett++) //SETTING LOOP
		{
			int yy2 = 0;
			int yy = 0;
			if (sett < 3)
			{
				XX++;

				g_sUpGuardUpLOS[sett].m_cLocation.X = XX;
				g_sDownGuardDownLOS[sett].m_cLocation.X = XX;
				yy = 13;
				yy2 = 27;
			}
			else
			{
				yy = 12;
				yy2 = 28;
			}
			g_sUpGuardUpLOS[sett].m_cLocation.Y = yy;
			g_sDownGuardDownLOS[sett].m_cLocation.Y = yy2;
		}


		g_dGuardTimeYLevel2 = 0.0;
		++moveLevel2;
	}

	XX = 34; //RESET THE SETTER

	if (g_dGuardTimeYLevel2 >= 0.25 && moveLevel2 == 12)
	{
		contactcheckLevel21 = false; // MOVING BACKWARD

		Level2Count1 = 1;
		for (int inc = 0; inc < 12; inc++) //INCREMENT LOOP
		{
			g_sUpGuardUpLOS[inc].m_cLocation.Y--;
			g_sDownGuardDownLOS[inc].m_cLocation.Y++;
		}

		g_sLevel2UpGuard.m_cLocation.Y--;
		g_sLevel2DownGuard.m_cLocation.Y++;

		g_dGuardTimeYLevel2 = 0;

		for (int sett = 0; sett < 13; sett++) //SETTING LOOP
		{
			int yy2 = 0;
			int yy = 0;
			if (sett < 3)
			{
				XX++;

				g_sUpGuardDownLOS[sett].m_cLocation.X = XX;
				g_sDownGuardUpLOS[sett].m_cLocation.X = XX;
				yy = 5;
				yy2 = 35;
			}
			else
			{
				yy = 6;
				yy2 = 34;
			}
			g_sUpGuardDownLOS[sett].m_cLocation.Y = yy;
			g_sDownGuardUpLOS[sett].m_cLocation.Y = yy2;
		}


		if (g_sLevel2UpGuard.m_cLocation.Y == 4)
		{
			moveLevel2 = 2;
		}
	}

	int YY = 18; //USED TO SET THE Y VALUES OF THE RENDER

	//For the Right and Left guards (Total 14, 6 down first)
	if (g_dGuardTimeXLevel2 >= 0.25 && move1Level2 != 26) //Moving "FOWARD"
	{
		contactcheckLevel22 = true;

		Level2Count2 = 0;

		for (int inc = 0; inc < 13; inc++)
		{
			g_sLeftGuardRightLOS[inc].m_cLocation.X++;
			g_sRightGuardLeftLOS[inc].m_cLocation.X--;
		}

		g_sLevel2LeftGuard.m_cLocation.X++;
		g_sLevel2RightGuard.m_cLocation.X--;

		for (int sett = 0; sett < 13; sett++) //SETTING LOOP
		{
			int xx2 = 0;// for the left guard
			int xx = 0;
			if (sett < 3)
			{
				xx2 = 27;
				xx = 45;
				YY++;
				g_sLeftGuardLeftLOS[sett].m_cLocation.Y = YY;
				g_sRightGuardRightLOS[sett].m_cLocation.Y = YY;
			}
			else
			{
				xx2 = 26;
				xx = 46;
			}
			g_sLeftGuardLeftLOS[sett].m_cLocation.X = xx2;
			g_sRightGuardRightLOS[sett].m_cLocation.X = xx;
		}

		g_dGuardTimeXLevel2 = 0.0;
		++move1Level2;
	}

	YY = 18;

	if (g_dGuardTimeXLevel2 >= 0.25 && move1Level2 == 26) //MOVING IN THE REVERSE DIRECTION
	{
		contactcheckLevel22 = false;
		Level2Count2 = 1;

		for (int inc = 0; inc < 13; inc++)
		{
			g_sLeftGuardLeftLOS[inc].m_cLocation.X--;
			g_sRightGuardRightLOS[inc].m_cLocation.X++;
		}

		g_sLevel2LeftGuard.m_cLocation.X--;
		g_sLevel2RightGuard.m_cLocation.X++;
		
		for (int sett = 0; sett < 13; sett++) //SETTING LOOP
		{
			int xx2 = 0;// for the left guard
			int xx = 0; // for the right guard
			if (sett < 3)
			{
				xx = 67;
				xx2 = 5;
				YY++;
				g_sLeftGuardLeftLOS[sett].m_cLocation.Y = YY;
				g_sRightGuardLeftLOS[sett].m_cLocation.Y = YY;
			}
			else
			{
				xx = 66;
				xx2 = 6;
			}
			g_sLeftGuardRightLOS[sett].m_cLocation.X = xx2;
			g_sRightGuardLeftLOS[sett].m_cLocation.X = xx;
		}

		g_dGuardTimeXLevel2 = 0;


		if (g_sLevel2LeftGuard.m_cLocation.X == 4)
		{
			move1Level2 = 2;
		}
	}
}

int tracker3 = 1;
bool contactcheck31 = true;
bool contactcheck32 = true;
bool contactcheck33 = true;
bool contactcheck34 = true;

void Level3AIMovement()
{
	if (g_dRotationTime3 >= 0.0)
	{
		tracker3 = 1;
		contactcheck31 = false;
	}

	if (g_dRotationTime3 > 0.4)
	{
		tracker3 = 2;
		contactcheck31 = true;
		contactcheck32 = false;
	}

	if (g_dRotationTime3 > 0.8)
	{
		contactcheck32 = true;
		contactcheck33 = false;
		tracker3 = 1;
		g_sLeftGHorLOS[0].m_cLocation.X = 11;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 10;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 9;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 8;
		}
		for (int sett = 16; sett < 25; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 7;
		}

		g_sRightGHorLOS[0].m_cLocation.X = 82;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 83;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 84;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 85;
		}
		for (int sett = 16; sett < 25; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 86;
		}
	}

	if (g_dRotationTime3 > 1.2)
	{
		contactcheck33 = true;
		contactcheck34 = false;
		tracker3 = 2;
		g_sLeftGVerLOS[0].m_cLocation.Y = 19;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sLeftGVerLOS[sett].m_cLocation.Y = 20;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sLeftGVerLOS[sett].m_cLocation.Y = 21;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sLeftGVerLOS[sett].m_cLocation.Y = 22;
		}

		g_sRightGVerLOS[0].m_cLocation.Y = 19;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sRightGVerLOS[sett].m_cLocation.Y = 20;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sRightGVerLOS[sett].m_cLocation.Y = 21;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sRightGVerLOS[sett].m_cLocation.Y = 22;
		}
	}
	if (g_dRotationTime3 > 1.6)
	{
		contactcheck34 = true;
		tracker3 = 0;
		g_sLeftGHorLOS[0].m_cLocation.X = 13;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 14;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 15;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 16;
		}
		for (int sett = 16; sett < 25; sett++)
		{
			g_sLeftGHorLOS[sett].m_cLocation.X = 17;
		}

		g_sRightGHorLOS[0].m_cLocation.X = 80;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 79;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 78;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 77;
		}
		for (int sett = 16; sett < 25; sett++)
		{
			g_sRightGHorLOS[sett].m_cLocation.X = 76;
		}

		g_sLeftGVerLOS[0].m_cLocation.Y = 17;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sLeftGVerLOS[sett].m_cLocation.Y = 16;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sLeftGVerLOS[sett].m_cLocation.Y = 15;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sLeftGVerLOS[sett].m_cLocation.Y = 14;
		}

		g_sRightGVerLOS[0].m_cLocation.Y = 17;
		for (int sett = 1; sett < 4; sett++)
		{
			g_sRightGVerLOS[sett].m_cLocation.Y = 16;
		}
		for (int sett = 4; sett < 9; sett++)
		{
			g_sRightGVerLOS[sett].m_cLocation.Y = 15;
		}
		for (int sett = 9; sett < 16; sett++)
		{
			g_sRightGVerLOS[sett].m_cLocation.Y = 14;
		}
		g_dRotationTime3 = 0.0;
	}
}
void renderLOS3()
{
	switch (tracker3)
	{
	case 1:
	{
		for (int sett = 0; sett < 25; sett++)
		{
			g_Console.writeToBuffer(g_sLeftGHorLOS[sett].m_cLocation, "Û", 0X08);
			g_Console.writeToBuffer(g_sRightGHorLOS[sett].m_cLocation, "Û", 0X08);
		}
	}
	break;
	case 2:
	{
		for (int sett = 0; sett < 16; sett++)
		{
			g_Console.writeToBuffer(g_sLeftGVerLOS[sett].m_cLocation, "Û", 0X08);
			g_Console.writeToBuffer(g_sRightGVerLOS[sett].m_cLocation, "Û", 0X08);
		}
	}
	break;
	}
}

//CHARACTER MOVEMENT
void moveCharacterLevel1()
{
	int CeX = g_sLevel1GuardCells.m_cLocation.X;
	int CeY = g_sLevel1GuardCells.m_cLocation.Y;

	int CaX = g_sLevel1GuardCafe.m_cLocation.X;
	int CaY = g_sLevel1GuardCafe.m_cLocation.Y;

	int F1X = g_sLevel1GuardField1.m_cLocation.X;
	int F1Y = g_sLevel1GuardField1.m_cLocation.Y;

	int F2X = g_sLevel1GuardField2.m_cLocation.X;
	int F2Y = g_sLevel1GuardField2.m_cLocation.Y;

	int Ch1X = g_sChar.m_cLocation.X;
	int Ch1Y = g_sChar.m_cLocation.Y;


	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Updating the location of the character based on the key press

	//Level 1
	if (movementLock == false)
	{
		if ((g_abKeyPressed[K_UP] || g_abKeyPressed[W]) && level1[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == ' ') //To move up checking
		{
			PlaySound(TEXT("mysound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
			if (((Ch1X == CeX) && (Ch1Y == CeY + 1)) || ((Ch1X == CaX) && (Ch1Y == CaY + 1)) || ((Ch1X == F1X) && (Ch1Y == F1Y + 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y + 1)))
			{
				/*Ch1Y = */g_sChar.m_cLocation.Y++;
				g_eGameState = S_GAMEOVER;
			}
		}
		if ((g_abKeyPressed[K_LEFT] || g_abKeyPressed[A]) && g_sChar.m_cLocation.X > 0 && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == ' ')
		{
			PlaySound(TEXT("mysound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;

			if (((Ch1X == CeX + 1) && (Ch1Y == CeY)) || ((Ch1X == CaX + 1) && (Ch1Y == CaY)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X + 1) && (Ch1Y == F2Y)))
			{
				g_sChar.m_cLocation.X++;
				g_eGameState = S_GAMEOVER;
			}
		}
		if ((g_abKeyPressed[K_DOWN] || g_abKeyPressed[S]) && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && g_sChar.m_cLocation.X > 0 && level1[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == ' ')
		{
			PlaySound(TEXT("mysound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
			if (((Ch1X == CeX) && (Ch1Y == CeY - 1)) || ((Ch1X == CaX) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X) && (Ch1Y == F1Y - 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y - 1)))
			{
				g_sChar.m_cLocation.Y--;
				g_eGameState = S_GAMEOVER;
			}
		}
		if ((g_abKeyPressed[K_RIGHT] || g_abKeyPressed[D]) && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1 && g_sChar.m_cLocation.X > 0 && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == ' ')
		{
			PlaySound(TEXT("mysound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
			if (((Ch1X == CeX - 1) && (Ch1Y == CeY)) || ((Ch1X == CaX - 1) && (Ch1Y == CaY)) || ((Ch1X == F1X - 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X - 1) && (Ch1Y == F2Y)))
			{
				g_sChar.m_cLocation.X--;
				g_eGameState = S_GAMEOVER;
			}
		}
	}

	if (g_abKeyPressed[K_SPACE])
	{
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}
void moveCharacterLevel2()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	//Level 2
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[W]) && level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] == ' ') //To move up checking
	{
		g_sLevel2Char.m_cLocation.Y--;
		bSomethingHappened = true;

	}
	if ((g_abKeyPressed[K_LEFT] || g_abKeyPressed[A]) && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] == ' ')
	{
		g_sLevel2Char.m_cLocation.X--;
		bSomethingHappened = true;
	}
	if ((g_abKeyPressed[K_DOWN] || g_abKeyPressed[S]) && level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] == ' ')
	{
		g_sLevel2Char.m_cLocation.Y++;
		bSomethingHappened = true;
	}
	if ((g_abKeyPressed[K_RIGHT] || g_abKeyPressed[D]) && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == ' ')
	{
		g_sLevel2Char.m_cLocation.X++;
		bSomethingHappened = true;
	}
	
	if (g_abKeyPressed[K_SPACE])
	{
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}
void moveCharacterLevel3()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	//Level 2
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[W]) && level3[g_sLevel3Char.m_cLocation.Y - 1][g_sLevel3Char.m_cLocation.X] == ' ') //To move up checking
	{
		g_sLevel3Char.m_cLocation.Y--;
		bSomethingHappened = true;

	}
	if ((g_abKeyPressed[K_LEFT] || g_abKeyPressed[A]) && level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X - 1] == ' ')
	{
		g_sLevel3Char.m_cLocation.X--;
		bSomethingHappened = true;
	}
	if ((g_abKeyPressed[K_DOWN] || g_abKeyPressed[S]) && level3[g_sLevel3Char.m_cLocation.Y + 1][g_sLevel3Char.m_cLocation.X] == ' ')
	{
		g_sLevel3Char.m_cLocation.Y++;
		bSomethingHappened = true;
	}
	if ((g_abKeyPressed[K_RIGHT] || g_abKeyPressed[D]) && level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] == ' ')
	{
		g_sLevel3Char.m_cLocation.X++;
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_SPACE])
	{
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.08; // 125ms should be enough
	}
}

//ITEM INTERACTIONS
void Level1ItemInteractions()
{
	COORD c = g_Console.getConsoleSize();

	if (g_abKeyPressed[K_INTERACT] && level1[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == 'S') //To move up checking
	{
		//separate it later
		ShiveNumber += 1;
		level1[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
		renderTutorialMap();
	}
	else if (g_abKeyPressed[K_INTERACT] && level1[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'S') //To move up checking
	{
		ShiveNumber += 1;
		level1[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'S')
	{
		ShiveNumber += 1;
		level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'S')
	{
		ShiveNumber += 1;
		level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
	}
	if (g_abKeyPressed[K_INTERACT] && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '~') //To move up checking
	{
		if (ShiveNumber == '3')
		{
			level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
			ShiveNumber = '0';
		}

	}

	if (g_sChar.m_cLocation.X == 73 && g_sChar.m_cLocation.Y == 22)
	{
		g_eGameState = S_CLEAR;
	}
}
void Level2ItemInteractions()
{
	COORD c = g_Console.getConsoleSize();

	//OBTAINING A SHIVE RELATIVE TO THE POSITION OF THE PLAYER
	if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] == 'S') 
	{
		//separate it later
		ShiveNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] == 'S') 
	{
		ShiveNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == 'S')
	{
		ShiveNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] == 'S')
	{
		ShiveNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] = ' ';
	}
	//----------------------------------------------------------------------------------------------------------
	//OBTAINING A KEY RELATIVE TO THE POSITION OF THE PLAYER
	if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] == 'K')
	{
		//separate it later
		KeyNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] == 'K')
	{
		KeyNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == 'K')
	{
		KeyNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] == 'K')
	{
		KeyNumber += 1;
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] = ' ';
	}

	//----------------------------------------------------------------------------------------------------------
	//INTERACTING WITH THE WALLS RELATIVE TO THE PLAYER'S COORDS
	if (g_abKeyPressed[K_INTERACT] && Level2Hidden[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == '}' && ShiveNumber >= '1')
	{
		ShiveNumber -= 1; //REMOVES 1 SHIVE
		Hidden1Stage2 = true; //ALLOWS FOR THE CALLING OF THE FUNCTION THAT FULLY RENDERS ONE HIDDEN PATHWAY
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] = ' '; //EDITS THE PATHWAY TO BE BLANK FOR THE PLAYER TO PROGRESS

	}
	else if (g_abKeyPressed[K_INTERACT] && Level2Hidden[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == ']' && ShiveNumber >= '1')
	{

		ShiveNumber -= 1;
		Hidden2Stage2 = true;
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && Level2Hidden[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] == ')' && ShiveNumber >= '1')
	{
		ShiveNumber -= 1;
		Hidden3Stage2 = true;
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] = ' ';
	}

	//-----------------------------------------------------------------------------------------------------------------------------------

	if (Hidden1Stage2 == true)
	{
		HiddenEntranceOne();
	}
	if (Hidden2Stage2 == true)
	{
		HiddenEntranceTwo();
	}
	if (Hidden3Stage2 == true)
	{
		HiddenEntranceThree();
	}
    //-----------------------------------------------------------------------------------------------------------------------------------

	if (g_abKeyPressed[K_INTERACT] && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == '~' && (ShiveNumber == '3' || KeyNumber == '1')) //To move up checking
	{
		//separate it later
		ShiveNumber = '0';
		KeyNumber = '0';
		level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] = ' ';
		g_eGameState = S_CLEAR;
	}

	//----------------------------------------------------------------------------------------------------------------------------------

	if (g_abKeyPressed[K_INTERACT] && (Level2Hidden[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] == '{' || Level2Hidden[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] == '{'))
	{
		level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] = ' ';
		level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] = ' ';
	}
}
void Level3ItemInteractions()
{
	COORD c = g_Console.getConsoleSize();

	//OBTAINING A SHIVE RELATIVE TO THE POSITION OF THE PLAYER
	if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y + 1][g_sLevel3Char.m_cLocation.X] == 'S')
	{
		//separate it later
		ShiveNumber += 1;
		level3[g_sLevel3Char.m_cLocation.Y + 1][g_sLevel3Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y - 1][g_sLevel3Char.m_cLocation.X] == 'S')
	{
		ShiveNumber += 1;
		level3[g_sLevel3Char.m_cLocation.Y - 1][g_sLevel3Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] == 'S')
	{
		ShiveNumber += 1;
		level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X - 1] == 'S')
	{
		ShiveNumber += 1;
		level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X - 1] = ' ';
	}

	//OBTAINING A FRAGMENT RELATIVE TO THE POSITION OF THE PLAYER
	if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y + 1][g_sLevel3Char.m_cLocation.X] == 'S')
	{
		//separate it later
		KeyFragment += 1;
		level3[g_sLevel3Char.m_cLocation.Y + 1][g_sLevel3Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y - 1][g_sLevel3Char.m_cLocation.X] == 'S')
	{
		KeyFragment += 1;
		level3[g_sLevel3Char.m_cLocation.Y - 1][g_sLevel3Char.m_cLocation.X] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] == 'S')
	{
		KeyFragment += 1;
		level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] = ' ';
	}
	else if (g_abKeyPressed[K_INTERACT] && level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X - 1] == 'S')
	{
		KeyFragment += 1;
		level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X - 1] = ' ';
	}

	//------------------------------------------------------------------------------------------------------------------

	if (g_abKeyPressed[K_INTERACT] && Level3Hidden[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] == '}' && ShiveNumber >= '1')
	{
		ShiveNumber -= 1; //REMOVES 1 SHIVE
		level3[g_sLevel3Char.m_cLocation.Y][g_sLevel3Char.m_cLocation.X + 1] = ' '; //EDITS THE PATHWAY TO BE BLANK FOR THE PLAYER TO PROGRESS
	}

	if (g_sLevel3Char.m_cLocation.X == 63 && g_sLevel3Char.m_cLocation.Y == 3)
	{
		HiddenMap(); //ALLOWS FOR THE CALLING OF THE FUNCTION THAT FULLY RENDERS ONE HIDDEN PATHWAY
		g_sLevel3Char.m_cLocation.X += 63;
		g_sLevel3Char.m_cLocation.Y += 22;
	}
}

//WHAT WILL MAKE THE PLAYER LOSE
void levelonelose()
{
	int CeX = g_sLevel1GuardCells.m_cLocation.X;
	int CeY = g_sLevel1GuardCells.m_cLocation.Y;

	int CaX = g_sLevel1GuardCafe.m_cLocation.X;
	int CaY = g_sLevel1GuardCafe.m_cLocation.Y;

	int F1X = g_sLevel1GuardField1.m_cLocation.X;
	int F1Y = g_sLevel1GuardField1.m_cLocation.Y;

	int F2X = g_sLevel1GuardField2.m_cLocation.X;
	int F2Y = g_sLevel1GuardField2.m_cLocation.Y;

	int Ch1X = g_sChar.m_cLocation.X;
	int Ch1Y = g_sChar.m_cLocation.Y;

	for (int sett = 0; sett < 4; sett++)
	{
		if ( (((Ch1X == g_sRightArr[sett].m_cLocation.X) && (Ch1Y == g_sRightArr[sett].m_cLocation.Y)) || ((Ch1X == g_sUpF1Arr[sett].m_cLocation.X) && (Ch1Y == g_sUpF1Arr[sett].m_cLocation.Y)) || ((Ch1X == g_sDownF2Arr[sett].m_cLocation.X) && (Ch1Y == g_sDownF2Arr[sett].m_cLocation.Y)) || ((Ch1X == g_sUpCArr[sett].m_cLocation.X) && (Ch1Y == g_sUpCArr[sett].m_cLocation.Y))) && (contactcheck == true))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
				lives = '2';
			}
		}
	}

	for (int sett = 0; sett < 4; sett++)
	{
		if ((((Ch1X == g_sLeftArr[sett].m_cLocation.X) && (Ch1Y == g_sLeftArr[sett].m_cLocation.Y)) || ((Ch1X == g_sUpF2Arr[sett].m_cLocation.X) && (Ch1Y == g_sUpF2Arr[sett].m_cLocation.Y)) || ((Ch1X == g_sDownF1Arr[sett].m_cLocation.X) && (Ch1Y == g_sDownF1Arr[sett].m_cLocation.Y)) || ((Ch1X == g_sDownCArr[sett].m_cLocation.X) && (Ch1Y == g_sDownCArr[sett].m_cLocation.Y))) && (contactcheck == false))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
				lives = '2';
			}
		}
	}

	if (((Ch1X == CeX) && (Ch1Y == CeY)) || ((Ch1X == CaX) && (Ch1Y == CaY)) || ((Ch1X == F1X) && (Ch1Y == F1Y)) || ((Ch1X == F2X) && (Ch1Y == F2Y)))
	{
		lives = lives - 1;
		if (lives != '0') {
			g_sChar.m_cLocation.X = 6;
			g_sChar.m_cLocation.Y = 4;
		}
		else {
			g_eGameState = S_GAMEOVER;
			lives = '2';
		}
	}
}
void leveltwolose()
{
	int CH2X = g_sLevel2Char.m_cLocation.X;
	int CH2Y = g_sLevel2Char.m_cLocation.Y;

	int RtY = g_sLevel2RotatingGuard.m_cLocation.Y;
	int RtX = g_sLevel2RotatingGuard.m_cLocation.X;

	int CRtX = g_sLevel2CafeGuard.m_cLocation.X;
	int CRtY = g_sLevel2CafeGuard.m_cLocation.Y;

	int UX = g_sLevel2UpGuard.m_cLocation.X;
	int UY = g_sLevel2UpGuard.m_cLocation.Y;

	int DX = g_sLevel2DownGuard.m_cLocation.X;
	int DY = g_sLevel2DownGuard.m_cLocation.Y;

	int RX = g_sLevel2RightGuard.m_cLocation.X;
	int RY = g_sLevel2RightGuard.m_cLocation.Y;

	int LX = g_sLevel2LeftGuard.m_cLocation.X;
	int LY = g_sLevel2LeftGuard.m_cLocation.Y;

	if (TurnCount == 1) //for the rotating guards
	{
		if ((RtX == g_sLevel2Char.m_cLocation.X && (RtY - g_sLevel2Char.m_cLocation.Y >= 0)) || (CRtX == g_sLevel2Char.m_cLocation.X && (CRtY - g_sLevel2Char.m_cLocation.Y <= 3)))
		{
			lives -= 1;
			g_sLevel2Char.m_cLocation.X = 46;
			g_sLevel2Char.m_cLocation.Y = 3;

			if (lives == '0')
			{
				g_eGameState = S_GAMEOVER;
			}
		}
	}
	if (TurnCount == 2) //for the rotating guards
	{
		if (RtY == g_sLevel2Char.m_cLocation.Y && (g_sLevel2Char.m_cLocation.X - RtX <= 35) || (CRtY == g_sLevel2Char.m_cLocation.Y && (g_sLevel2Char.m_cLocation.X - CRtX <= 20)))
		{
			lives -= 1;
			g_sLevel2Char.m_cLocation.X = 46;
			g_sLevel2Char.m_cLocation.Y = 3;

			if (lives == '0')
			{
				g_eGameState = S_GAMEOVER;
			}
		}
	}
	if (TurnCount == 3) // for the rotating guards
	{
		if (RtX == g_sLevel2Char.m_cLocation.X && (g_sLevel2Char.m_cLocation.Y - RtY >= 0) || (CRtX == g_sLevel2Char.m_cLocation.X && (CRtY - g_sLevel2Char.m_cLocation.Y <= 3)))
		{
			lives -= 1;
			g_sLevel2Char.m_cLocation.X = 46;
			g_sLevel2Char.m_cLocation.Y = 3;

			if (lives == '0')
			{
				g_eGameState = S_GAMEOVER;
			}
		}
	}
	if (TurnCount == 4)
	{
		if (RtY == g_sLevel2Char.m_cLocation.Y && (RtX - g_sLevel2Char.m_cLocation.X >= 0) || (CRtY == g_sLevel2Char.m_cLocation.Y && (g_sLevel2Char.m_cLocation.X - CRtX <= 20)))
		{
			lives -= 1;
			g_sLevel2Char.m_cLocation.X = 46;
			g_sLevel2Char.m_cLocation.Y = 3;

			if (lives == '0')
			{
				g_eGameState = S_GAMEOVER;
			}
		}
	}

	for (int sett = 0; sett < 12; sett++) // for moving forward (up and down guards)
	{
		if ((((CH2X == g_sUpGuardDownLOS[sett].m_cLocation.X) && (CH2Y == g_sUpGuardDownLOS[sett].m_cLocation.Y)) || ((CH2X == g_sDownGuardUpLOS[sett].m_cLocation.X) && (CH2Y == g_sDownGuardUpLOS[sett].m_cLocation.Y))) && (contactcheckLevel21 == true))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
				lives = '2';
			}
		}
	}
	for (int sett = 0; sett < 13; sett++) // for moving forward (left and right guards)
	{
		if ((((CH2X == g_sLeftGuardRightLOS[sett].m_cLocation.X) && (CH2Y == g_sLeftGuardRightLOS[sett].m_cLocation.Y)) || ((CH2X == g_sRightGuardLeftLOS[sett].m_cLocation.X) && (CH2Y == g_sRightGuardLeftLOS[sett].m_cLocation.Y))) && (contactcheckLevel22 == true))
		{
			{
				lives = lives - 1;
				if (lives != '0') {
					g_sLevel2Char.m_cLocation.X = 46;
					g_sLevel2Char.m_cLocation.Y = 3;
				}
				else {
					g_eGameState = S_GAMEOVER;
					lives = '2';
				}
			}
		}

		for (int sett = 0; sett < 12; sett++) // for moving backwards (up and down guards)
		{
			if ((((CH2X == g_sUpGuardUpLOS[sett].m_cLocation.X) && (CH2Y == g_sUpGuardUpLOS[sett].m_cLocation.Y)) || ((CH2X == g_sDownGuardDownLOS[sett].m_cLocation.X) && (CH2Y == g_sDownGuardDownLOS[sett].m_cLocation.Y))) && (contactcheckLevel21 == false))
			{
				lives = lives - 1;
				if (lives != '0') {
					g_sLevel2Char.m_cLocation.X = 46;
					g_sLevel2Char.m_cLocation.Y = 3;
				}
				else {
					g_eGameState = S_GAMEOVER;
					lives = '2';
				}
			}
		}
		for (int sett = 0; sett < 13; sett++) // for moving backwards (left and right guards)
		{
			if ((((CH2X == g_sLeftGuardLeftLOS[sett].m_cLocation.X) && (CH2Y == g_sLeftGuardLeftLOS[sett].m_cLocation.Y)) || ((CH2X == g_sRightGuardRightLOS[sett].m_cLocation.X) && (CH2Y == g_sRightGuardRightLOS[sett].m_cLocation.Y))) && (contactcheckLevel22 == false))
			{
				{
					lives = lives - 1;
					if (lives != '0') {
						g_sLevel2Char.m_cLocation.X = 46;
						g_sLevel2Char.m_cLocation.Y = 3;
					}
					else {
						g_eGameState = S_GAMEOVER;
						lives = '2';
					}
				}
			}
		}
        
	}
}
void levelthreelose()
	{
		int leftX = g_sLevel3Guard[0].m_cLocation.X;
		int leftY = g_sLevel3Guard[0].m_cLocation.Y;

		int midX = g_sLevel3Guard[1].m_cLocation.X;
		int midY = g_sLevel3Guard[1].m_cLocation.Y;

		int rightX = g_sLevel3Guard[2].m_cLocation.X;
		int rightY = g_sLevel3Guard[2].m_cLocation.Y;

		int Ch1X = g_sLevel3Char.m_cLocation.X;
		int Ch1Y = g_sLevel3Char.m_cLocation.Y;

		for (int sett = 0; sett < 25; sett++)
		{
			if ((((Ch1X == g_sLeftGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGHorLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGHorLOS[sett].m_cLocation.Y))) && (contactcheck31 == false))
			{
				lives = lives - 1;
				if (lives != '0') {
					g_sChar.m_cLocation.X = 6;
					g_sChar.m_cLocation.Y = 4;
				}
				else {
					g_eGameState = S_GAMEOVER;
					lives = '2';
				}
			}
		}

		for (int sett = 0; sett < 16; sett++)
		{
			if ((((Ch1X == g_sLeftGVerLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGVerLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGVerLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGVerLOS[sett].m_cLocation.Y))) && (contactcheck32 == false))
			{
				lives = lives - 1;
				if (lives != '0') {
					g_sChar.m_cLocation.X = 6;
					g_sChar.m_cLocation.Y = 4;
				}
				else {
					g_eGameState = S_GAMEOVER;
					lives = '2';
				}
			}
		}

		for (int sett = 0; sett < 25; sett++)
		{
			if ((((Ch1X == g_sLeftGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGHorLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGHorLOS[sett].m_cLocation.Y))) && (contactcheck33 == false))
			{
				lives = lives - 1;
				if (lives != '0') {
					g_sChar.m_cLocation.X = 6;
					g_sChar.m_cLocation.Y = 4;
				}
				else {
					g_eGameState = S_GAMEOVER;
					lives = '2';
				}
			}
		}

		for (int sett = 0; sett < 16; sett++)
		{
			if ((((Ch1X == g_sLeftGVerLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGVerLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGVerLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGVerLOS[sett].m_cLocation.Y))) && (contactcheck34 == false))
			{
				lives = lives - 1;
				if (lives != '0') {
					g_sChar.m_cLocation.X = 6;
					g_sChar.m_cLocation.Y = 4;
				}
				else {
					g_eGameState = S_GAMEOVER;
					lives = '2';
				}
			}
		}

		if (((Ch1X == leftX) && (Ch1Y == leftY)) || ((Ch1X == midX) && (Ch1Y == midY)) || ((Ch1X == rightX) && (Ch1Y == rightY)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
				lives = '2';
			}
		}
	}


int PcDial = 0;
int PcafeDial = 0;
int PshowerDial = 0;
int intelcountlevel1 = 0;

void prisonerInteraction()
{
	int Ch1X = g_sChar.m_cLocation.X;
	int Ch1Y = g_sChar.m_cLocation.Y;

	int PcX = g_sLevel1PrisonerCells.m_cLocation.X;
	int PcY = g_sLevel1PrisonerCells.m_cLocation.Y;

	int PcafeX = g_sLevel1PrisonerCafe.m_cLocation.X;
	int PcafeY = g_sLevel1PrisonerCafe.m_cLocation.Y;

	int PshowerX = g_sLevel1PrisonerShowers.m_cLocation.X;
	int PshowerY = g_sLevel1PrisonerShowers.m_cLocation.Y;

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	COORD c = g_Console.getConsoleSize();
	c.X = 39;
	c.Y = 34;

	if (g_abKeyPressed[K_INTERACT])
	{
		bSomethingHappened = true;
		if (((Ch1X - 1 == PcX) && (Ch1Y == PcY)) || ((Ch1X + 1 == PcX) && (Ch1Y == PcY)) || ((Ch1Y - 1 == PcY) && (Ch1X == PcX)) || ((Ch1Y + 1 == PcY) && (Ch1X == PcX)))
		{
			if (PcDial == 7)
			{
				PcDial = 0;
			}
			PcDial++;
		}

		if (((Ch1X - 1 == PcafeX) && (Ch1Y == PcafeY)) || ((Ch1X + 1 == PcafeX) && (Ch1Y == PcafeY)) || ((Ch1Y - 1 == PcafeY) && (Ch1X == PcafeX)) || ((Ch1Y + 1 == PcafeY) && (Ch1X == PcafeX)))
		{
			if (PcafeDial == 5)
			{
				PcafeDial = 0;
			}
			PcafeDial++;
		}

		if (((Ch1X - 1 == PshowerX) && (Ch1Y == PshowerY)) || ((Ch1X + 1 == PshowerX) && (Ch1Y == PshowerY)) || ((Ch1Y - 1 == PshowerY) && (Ch1X == PshowerX)) || ((Ch1Y + 1 == PshowerY) && (Ch1X == PshowerX)))
		{
			if (PshowerDial == 6)
			{
				PshowerDial = 0;
			}
			PshowerDial++;
		}
	}
	if (bSomethingHappened)
	{
		g_dBounceTime = g_dElapsedTime + 0.1;
	}
}

void crafting()
{
	if (KeyFragment == 3)
	{
		COORD c;
		c.X = 0;
		c.Y = 0;

		g_Console.writeToBuffer(c, "You can now craft a Key, press 'C' to craft one", 0xF0);
		if (g_abKeyPressed[K_CRAFT])
		{
			KeyFragment -= 3;
			KeyNumber += 1;
		}
	}
}

void renderDialogue()
{
	COORD c = g_Console.getConsoleSize();

	c.X = 28;
	c.Y = 27;

	g_Console.writeToBuffer(c, "Dialogue:", 0xF0);

	c.X = 30;
	c.Y = 31;

	//PrisonerCell Dialogue


	switch (PcDial)
	{
	case 1:
		movementLock = true;
		g_Console.writeToBuffer(c, "Prisoner: What do you want?", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          Why are you in my cell?", 0xF0);
		break;
	case 2:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: Do you know anything about the secret", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        passage to get out of this place?", 0xF0);
		break;
	case 3:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: How the hell do you know about that", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          Who the hell are you?", 0xF0);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: Just shut up and tell me", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        what I want to know.", 0xF0);
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Alright chill out dude, I don't", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          know much, but I do know someone who", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          might just have the info you need.", 0xF0);
		break;
	case 6:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Well, that guy in the cafe.", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          He probably can tell you more.", 0xF0);
		movementLock = false;
		break;
	case 7:
		c.Y = 31;
		g_Console.writeToBuffer(c, " ", 0xF0);
		intelcountlevel1 = 1;
		break;
	}

	//PrisonerCafe Dialogue

	c.X = 31;
	c.Y = 31;

	switch (PcafeDial)
	{
	case 1:
		movementLock = true;
		g_Console.writeToBuffer(c, "Faizal: Hey nigger! You know anything", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        bout that secret passage", 0xF0);
		break;
	case 2:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Not so loud my man. Alright, there", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          really isn't much I can tell you,", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          but all I know is...", 0xF0);
		break;
	case 3:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: What do you mean by isn't much?", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        That dude in the cell told me", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "        you knew everything.", 0xF0);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Your great friend Ryan is", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          the one who actually planned", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          this entire thing, go ask him", 0xF0);
		c.Y = 34;
		g_Console.writeToBuffer(c, "          He should be in the toilet.", 0xF0);
		movementLock = false;
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, " ", 0xF0);
		intelcountlevel1 = 2;
		break;
	}

	//Ryan Dialogue

	c.X = 31;
	c.Y = 31;

	switch (PshowerDial)
	{
	case 1:
		movementLock = true;
		g_Console.writeToBuffer(c, "Faizal: Well, I haven't thought that you are the", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        one who knows about the secret passage", 0xF0);
		break;
	case 2:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: I wasn't planning to let you know", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          either, I was about to leave you", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          to rot in this hellhole", 0xF0);
		break;
	case 3:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: You better reveal it to me", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        or else you won't be leaving this", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "        place once the authorities know about it", 0xF0);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: Fine, I've been planning this sweet", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "      escape since day one so you better not", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "      screw my plan over.", 0xF0);
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: That wall right there, at the", 0xF0);
		c.Y = 32;
		g_Console.writeToBuffer(c, "      other end of this toilet, there is a crack.", 0xF0);
		c.Y = 33;
		g_Console.writeToBuffer(c, "      However, I just can't seem to break it open", 0xF0);
		c.Y = 34;
		g_Console.writeToBuffer(c, "      Though... you can try using the shives lying around", 0xF0);
		level1[22][72] = '~';
		movementLock = false;
		break;
	case 6:
		c.Y = 31;
		g_Console.writeToBuffer(c, " ", 0xF0);
		intelcountlevel1 = 3;

		break;
	}
}

void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
	if (g_abKeyPressed[K_RETURN])
	{
		g_eGameState = S_SPLASHSCREEN;
	}
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer();
}

void renderSplashScreen()  // renders the splash screen
{
	using namespace std;

	COORD c = g_Console.getConsoleSize();
	string line;
	ifstream myfile("titlescreen.txt");

	c.X = 1;
	c.Y = 1;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int col = 0; col < line.size(); col++)
			{
				if (line[col] == '#')
				{
					line[col] = 219;
				}
				g_Console.writeToBuffer(c, line[col], 0XF1);
				c.X++;
			}
			c.Y++;
			c.X = 1;
		}
	}

	c.X = 21;
	c.Y = 20;
	g_Console.writeToBuffer(c, "Welcome to the BlackStone Prison Complex, do your best to escape", 0XF1);
	c.X = 21;
	c.Y = 21;
	g_Console.writeToBuffer(c, "----------------------------------------------------------------", 0XF1);
	c.X = 21;
	c.Y = 22;
	g_Console.writeToBuffer(c, " Complex: Stone", 0XF1);
	c.X = 21;
	c.Y = 23;
	g_Console.writeToBuffer(c, " Complex: Bronze", 0XF1);
	c.X = 21;
	c.Y = 24;
	g_Console.writeToBuffer(c, " Complex: Steel", 0XF1);
	c.X = 21;
	c.Y = 25;
	g_Console.writeToBuffer(c, " Exit the Game", 0XF1);
	if (MenuItem == 0)
	{
		c.X = 20;
		c.Y = 22;
		g_Console.writeToBuffer(c, (char)4, 0XF1);
	}
	else if (MenuItem == 1)
	{
		c.X = 20;
		c.Y = 23;
		g_Console.writeToBuffer(c, (char)4, 0XF1);
	}
	else if (MenuItem == 2)
	{
		c.X = 20;
		c.Y = 24;
		g_Console.writeToBuffer(c, (char)4, 0XF1);
	}
	else if (MenuItem == 3)
	{
		c.X = 20;
		c.Y = 25;
		g_Console.writeToBuffer(c, (char)4, 0XF1);
	}
}


//Section (FULL RENDERING)
void renderTutorialMap()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	for (int y = 0; y < 250; y++)
	{
		c.X = y;
		for (int x = 0; x < 250; x++)
		{
			c.Y = x;
			g_Console.writeToBuffer(c, level1[x][y], 0xF0);
		}
	}
}
void loadTutorialMap()
{
	//Read the array instead of file
	using namespace std;
	COORD c;
	string line;
	ifstream myfile("map_tutorial.txt");

	c.X = 1;
	c.Y = 1;

	int x = 1;
	int y = 1;
	level = 1;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int col = 0; col < line.size(); col++)
			{
				level1[x][y] = line[col]; // Prevent the overwriting of characters that do not appear in this loop
				if (line[col] == '#')
				{
					level1[x][y] = 205;
				}
				if (line[col] == '*')
				{
					level1[x][y] = 186;
				}
				if (line[col] == '~')
				{
					level1[x][y] = 186;
				}
				if (line[col] == '3')
				{
					level1[x][y] = 219;
				}
				if (line[col] == 'H')
				{
					level1[x][y] = 219;
				}
				if (line[col] == 'A')
				{
					level1[x][y] = 185;
				}
				if (line[col] == 'B')
				{
					level1[x][y] = 204;
				}
				if (line[col] == 'C')
				{
					level1[x][y] = 201;
				}
				if (line[col] == 'D')
				{
					level1[x][y] = 187;
				}
				if (line[col] == 'E')
				{
					level1[x][y] = 203;
				}
				if (line[col] == 'F')
				{
					level1[x][y] = 202;
				}
				if (line[col] == 'G')
				{
					level1[x][y] = 200;
				}
				if (line[col] == '+')
				{
					level1[x][y] = 206;
				}
				if (line[col] == 'I')
				{
					level1[x][y] = 188;
				}
				if (line[col] == '!')
				{
					level1[x][y] = 176;
				}
				if (line[col] == 'S')
				{
					level1[x][y] = 'S';
				}

				c.X++;
				y++;
			}
			x++;
			y = 1;
			c.Y++;
			c.X = 1;
		}
		myfile.close();
	}

}
void renderArrowLevel1()
{
	switch (count)
	{
	case 1:
	{
		for (int sett = 0; sett < 4; sett++)
		{
			g_Console.writeToBuffer(g_sRightArr[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
	}
	break;
	case 2:
	{
		for (int sett = 0; sett < 4; sett++)
		{
			g_Console.writeToBuffer(g_sLeftArr[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
	}
	break;
	}

	//---------------------------------------------------------------------------------------------------------------------------

	switch (count1)
	{
	case 1:
	{
		for (int sett = 0; sett < 4; sett++)
		{
			g_Console.writeToBuffer(g_sDownF2Arr[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
		for (int sett = 0; sett < 4; sett++)
		{
			g_Console.writeToBuffer(g_sUpF1Arr[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
	}
	break;
	case 2:
	{
		for (int sett = 0; sett < 4; sett++)
		{
			g_Console.writeToBuffer(g_sUpF2Arr[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
		for (int sett = 0; sett < 4; sett++)
		{
			g_Console.writeToBuffer(g_sDownF1Arr[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
	}
	break;
	}
	//----------------------------------------------------------------------------------------------------------------------------

	switch (count2)
	{
	case 1:
	{
		for (int sett = 0; sett < 4; sett++)
		{
			if (sett == 1 && (g_sLevel1GuardCafe.m_cLocation.Y != 8 && g_sLevel1GuardCafe.m_cLocation.Y != 6 && g_sLevel1GuardCafe.m_cLocation.Y != 7 && g_sLevel1GuardCafe.m_cLocation.Y != 11))
			{
				g_Console.writeToBuffer(g_sUpCArr[sett].m_cLocation, "Û", 0X08);
			}
			if (sett != 1)
			{
				g_Console.writeToBuffer(g_sUpCArr[sett].m_cLocation, "Û", 0X08);
			} //RENDER DIRECTION
		}
	}
	break;
	case 2:
	{
		/*g_Console.writeToBuffer(g_sDownCArr.m_cLocation, (char)31, 0X0F);*/
		for (int sett = 0; sett < 4; sett++)
		{
			if (sett == 1 && (g_sLevel1GuardCafe.m_cLocation.Y != 9 && g_sLevel1GuardCafe.m_cLocation.Y != 10 && g_sLevel1GuardCafe.m_cLocation.Y != 8))
			{
				g_Console.writeToBuffer(g_sDownCArr[sett].m_cLocation, "Û", 0X08);
			}
			if (sett != 1)
			{
				g_Console.writeToBuffer(g_sDownCArr[sett].m_cLocation, "Û", 0X08);
			} //RENDER DIRECTION
		}
	}
	}
}

void renderBronzeMap()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	//Rendering text from top to bottom
	for (int y = 0; y < 250; y++)
	{
		c.X = y;
		for (int x = 0; x < 250; x++)
		{
			c.Y = x;
			g_Console.writeToBuffer(c, level2[x][y], 0xF0);
		}
	}
}
void loadBronzeMap()
{
	using namespace std;
	string line;
	COORD c;
	ifstream myfile("map_bronze.txt");

	c.X = 1;
	c.Y = 1;

	int x = 1;
	int y = 1;
	level = 2;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int col = 0; col < line.size(); col++)
			{
				level2[x][y] = line[col]; // Prevent the overwriting of characters that do not appear in this loop
				if (line[col] == '#')
				{
					level2[x][y] = 205;
				}
				if (line[col] == '{')
				{
					level2[x][y] = 205;
					Level2Hidden[x][y] = '{';
				}
				if (line[col] == '*' || line[col] == '}' || line[col] == ')' || line[col] == ']')
				{
					level2[x][y] = 186;
					if (line[col] == '}')
					{
						Level2Hidden[x][y] = '}';
					}
					else if (line[col] == ']')
					{
						Level2Hidden[x][y] = ']';
					}
					else if (line[col] == ')')
					{
						Level2Hidden[x][y] = ')';
					}
				}
				if (line[col] == 'H')
				{
					level2[x][y] = 219;
				}
				if (line[col] == 'A')
				{
					level2[x][y] = 185;
				}
				if (line[col] == '3')
				{
					level2[x][y] = 219;
				}
				if (line[col] == 'B')
				{
					level2[x][y] = 204;
				}
				if (line[col] == 'C')
				{
					level2[x][y] = 201;
				}
				if (line[col] == 'D')
				{
					level2[x][y] = 187;
				}
				if (line[col] == 'E')
				{
					level2[x][y] = 203;
				}
				if (line[col] == 'F')
				{
					level2[x][y] = 202;
				}
				if (line[col] == 'G')
				{
					level2[x][y] = 200;
				}
				if (line[col] == '+')
				{
					level2[x][y] = 206;
				}
				if (line[col] == 'I')
				{
					level2[x][y] = 188;
				}
				if (line[col] == '!')
				{
					level2[x][y] = 176;
				}
				if (line[col] == 'S')
				{
					level2[x][y] = 'S';
				}
				if (line[col] == 'K')
				{
					level2[x][y] = 'K';
				}
				if (line[col] == 47 || line[col] == 92 || line[col] == '-' || line[col] == '|' )
				{
					level2[x][y] = ' ';
					if (line[col] == 47) // ASCII 47 IS /
					{
						Level2Hidden[x][y] = 47;
					}
					if (line[col] == 92) // ASCII 92 IS '\'
					{
						Level2Hidden[x][y] = 92;
					}
					if (line[col] == '|') // Vertical walls
					{
						Level2Hidden[x][y] = '|';
					}
					if (line[col] == '-') // Horizontal walls
					{
						Level2Hidden[x][y] = '-';
					}
				}
				c.X++;
				y++;
			}
			x++;
			y = 1;
			c.Y++;
			c.X = 1;
		}
		myfile.close();
	}
}
void renderArrowLevel2()
{
	switch (TurnCount)
	{
	case 1:
		for (int sett = 0; sett < 18; sett++)
		{g_Console.writeToBuffer(g_sRotatingGuardUpLOS[sett].m_cLocation, "Û", 0X0C);}
		for (int sett = 0; sett < 4; sett++)
		{g_Console.writeToBuffer(g_sCafeRotatingGuardUpLOS[sett].m_cLocation, "Û", 0X0C);}
		break;
	case 2:
		for (int sett = 0; sett < 34; sett++)
		{g_Console.writeToBuffer(g_sRotatingGuardRightLOS[sett].m_cLocation, "Û", 0X0C);}
		for (int sett = 0; sett < 20; sett++)
		{g_Console.writeToBuffer(g_sCafeRotatingGuardRightLOS[sett].m_cLocation, "Û", 0X0C);}
		break;
	case 3:
		for (int sett = 0; sett < 18; sett++)
		{g_Console.writeToBuffer(g_sRotatingGuardDownLOS[sett].m_cLocation, "Û", 0X0C);}
		for (int sett = 0; sett < 4; sett++)
		{g_Console.writeToBuffer(g_sCafeRotatingGuardUpLOS[sett].m_cLocation, "Û", 0X0C);}
		break;
	case 4:
		for (int sett = 0; sett < 34; sett++)
		{g_Console.writeToBuffer(g_sRotatingGuardLeftLOS[sett].m_cLocation, "Û", 0X0C);}
		for (int sett = 0; sett < 20; sett++)
		{g_Console.writeToBuffer(g_sCafeRotatingGuardRightLOS[sett].m_cLocation, "Û", 0X0C);}
		break;
	}

	switch (Level2Count1)
	{
	case 0:
		for (int sett = 0; sett < 12; sett++)
		{
			g_Console.writeToBuffer(g_sUpGuardDownLOS[sett].m_cLocation, "Û", 0X08);
			g_Console.writeToBuffer(g_sDownGuardUpLOS[sett].m_cLocation, "Û", 0X08);
		}
		break;
	case 1:
		for (int sett = 0; sett < 12; sett++)
		{
			g_Console.writeToBuffer(g_sUpGuardUpLOS[sett].m_cLocation, "Û", 0X08);
			g_Console.writeToBuffer(g_sDownGuardDownLOS[sett].m_cLocation, "Û", 0X08);
		}
		break;

	}

	switch (Level2Count2)
	{
	case 0:
		for (int sett = 0; sett < 8; sett++)
		{
			g_Console.writeToBuffer(g_sLeftGuardRightLOS[sett].m_cLocation, "Û", 0X08);
			g_Console.writeToBuffer(g_sRightGuardLeftLOS[sett].m_cLocation, "Û", 0x08);
		}
		break;
	case 1:
		for (int sett = 0; sett < 8; sett++)
		{
			g_Console.writeToBuffer(g_sLeftGuardLeftLOS[sett].m_cLocation, "Û", 0X08);
			g_Console.writeToBuffer(g_sRightGuardRightLOS[sett].m_cLocation, "Û", 0X08);
		}
		break;
	}

}
void HiddenEntranceOne()
{
	COORD c;
	c.X = 0; //x = 51 + 15
	c.Y = 0; // y = 2 + 11
	for (int y = 51; y < 66 ; y++) // A forward loop to assign new values to the text on the map
	{
		c.X = y;
		for (int x = 2; x < 13; x++)
		{
			c.Y = x;
			if (Level2Hidden[x][y] == '-' && level2[x][y] == ' ')
			{
				level2[x][y] = 205;
			}
			if (Level2Hidden[x][y] == '|' && level2[x][y] == ' ')
			{
				level2[x][y] = 186;
			}
			if (Level2Hidden[x][y] == 92 && level2[x][y] == ' ')
			{
				level2[x][y] = 187;
			}
			if (Level2Hidden[x][y] == '-' && level2[x][y] == ' ')
			{
				level2[x][y] = '-';
			}
		}
	}
}
void HiddenEntranceTwo()
{
	COORD c;
	c.X = 0; // x = 54 to 85
	c.Y = 0; // y = 14 to 40
	for (int y = 54; y < 90; y++)
	{
		c.X = y;
		for (int x = 14; x < 50; x++)
		{
			c.Y = x;
			if (Level2Hidden[x][y] == '-' && level2[x][y] == ' ')
			{
				level2[x][y] = 205;
			}
			if (Level2Hidden[x][y] == '|' && level2[x][y] == ' ')
			{
				level2[x][y] = 186;
			}
			if (Level2Hidden[x][y] == 92 && level2[x][y] == ' ')
			{
				level2[x][y] = 187;
			}
			if (Level2Hidden[x][y] == '-' && level2[x][y] == ' ')
			{
				level2[x][y] = '-';
			}
		}
	}
}
void HiddenEntranceThree()
{
	COORD c;
	c.X = 0; // x = 8 to 15
	c.Y = 0; // y = 32 to 40
	for (int y = 5; y < 15; y++)
	{
		c.X = y;
		for (int x = 32; x < 45; x++)
		{
			c.Y = x;
			if (Level2Hidden[x][y] == '-' && level2[x][y] == ' ')
			{
				level2[x][y] = 205;
			}
			if (Level2Hidden[x][y] == '|' && level2[x][y] == ' ')
			{
				level2[x][y] = 186;
			}
			if (Level2Hidden[x][y] == 92 && level2[x][y] == ' ')
			{
				level2[x][y] = 187;
			}
			if (Level2Hidden[x][y] == '-' && level2[x][y] == ' ')
			{
				level2[x][y] = '-';
			}
		}
	}
}
void RemoveHidden()
{
		COORD c;
		c.X = 0; //x = 51 + 15
		c.Y = 0; // y = 2 + 11
		for (int y = 0; y < 250; y++) // A forward loop to assign new values to the text on the map
		{
			c.X = y;
			for (int x = 0; x < 250; x++)
			{
				c.Y = x;
				if (Level2Hidden[x][y] == '-')
				{
					level2[x][y] = ' ';
				}
				if (Level2Hidden[x][y] == '|')
				{
					level2[x][y] = ' ';
				}
				if (Level2Hidden[x][y] == 92)
				{
					level2[x][y] = ' ';
				}
				if (Level2Hidden[x][y] == '-')
				{
					level2[x][y] = ' ';
				}
			}
		}
}


void renderSteelMap()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	for (int y = 0; y < 300; y++)
	{
		c.X = y;
		for (int x = 0; x < 300; x++)
		{
			c.Y = x;
			g_Console.writeToBuffer(c, level3[x][y], 0xF0);
		}
	}
}
void loadSteelMap()
{
	using namespace std;
	string line;
	COORD c;
	ifstream myfile("map_steel.txt");

	c.X = 1;
	c.Y = 1;

	int x = 1;
	int y = 1;
	level = 3;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int col = 0; col < line.size(); col++)
			{
				level3[x][y] = line[col]; // Prevent the overwriting of characters that do not appear in this loop
				if (line[col] == '#')
				{
					level3[x][y] = 205;
				}
				if (line[col] == '{')
				{
					level3[x][y] = 205;
					Level3Hidden[x][y] = '{';
				}
				if (line[col] == '*' || line[col] == '}' || line[col] == ')' || line[col] == ']')
				{
					level3[x][y] = 186;
					if (line[col] == '}')
					{
						Level3Hidden[x][y] = '}';
					}
					else if (line[col] == ']')
					{
						Level3Hidden[x][y] = ']';
					}
					else if (line[col] == ')')
					{
						Level3Hidden[x][y] = ')';
					}
				}
				if (line[col] == 'H')
				{
					level3[x][y] = 219;
				}
				if (line[col] == 'A')
				{
					level3[x][y] = 185;
				}
				if (line[col] == 'B')
				{
					level3[x][y] = 204;
				}
				if (line[col] == 'C')
				{
					level3[x][y] = 201;
				}
				if (line[col] == 'D')
				{
					level3[x][y] = 187;
				}
				if (line[col] == 'E')
				{
					level3[x][y] = 203;
				}
				if (line[col] == 'F')
				{
					level3[x][y] = 202;
				}
				if (line[col] == 'G')
				{
					level3[x][y] = 200;
				}
				if (line[col] == '+')
				{
					level3[x][y] = 206;
				}
				if (line[col] == 'V')
				{
					level3[x][y] = 177;
				}
				if (line[col] == 'I')
				{
					level3[x][y] = 188;
				}
				if (line[col] == '3')
				{
					level3[x][y] = 219;
				}
				if (line[col] == '!')
				{
					level3[x][y] = 176;
				}
				if (line[col] == 'S')
				{
					level3[x][y] = 'S';
				}
				if (line[col] == 'K')
				{
					level3[x][y] = 'K';
				}
				if (line[col] == '<')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '<';
				}
				if (line[col] == '>')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '>';
				}
				if (line[col] == '/')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '/';
				}
				if (line[col] == 92)
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = 92;
				}
				if (line[col] == '^')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '^';
				}
				if (line[col] == '&')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '&';
				}
				if (line[col] == '"')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '"';
				}
				if (line[col] == '!')
				{
					level3[x][y] = ' ';
					Level3Hidden[x][y] = '!';
				}
				if (line[col] == 47 || line[col] == '-' || line[col] == '|')
				{
					level3[x][y] = ' ';
					if (line[col] == 47) // ASCII 47 IS /
					{
						Level2Hidden[x][y] = 47;
					}
					if (line[col] == '|') // Vertical walls
					{
						Level3Hidden[x][y] = '|';
					}
					if (line[col] == '-') // Horizontal walls
					{
						Level3Hidden[x][y] = '-';
					}
				}
				c.X++;
				y++;
			}
			x++;
			y = 1;
			c.Y++;
			c.X = 1;
		}
		myfile.close();
	}
}
void HiddenMap()
{
	{
		COORD c;
		c.X = 0;
		c.Y = 0;
		for (int y = 0; y < 300; y++) // A forward loop to assign new values to the text on the map
		{
			c.X = y;
			for (int x = 0; x < 300; x++)
			{
				c.Y = x;
				if (Level3Hidden[x][y] == '-' && level3[x][y] == ' ')
				{
					level3[x][y] = 205;
				}
				if (Level3Hidden[x][y] == '|' && level3[x][y] == ' ')
				{
					level3[x][y] = 186;
				}
				if (Level3Hidden[x][y] == '-' && level3[x][y] == ' ')
				{
					level3[x][y] = '-';
				}
				if (Level3Hidden[x][y] == 47 && level3[x][y] == ' ')
				{
					level3[x][y] = 188;
				}
				if (Level3Hidden[x][y] == '<' && level3[x][y] == ' ')
				{
					level3[x][y] = 202;
				}
				if (Level3Hidden[x][y] == '>' && level3[x][y] == ' ')
				{
					level3[x][y] = 203;
				}
				if (Level3Hidden[x][y] == 92 && level3[x][y] == ' ')
				{
					level3[x][y] = 200;
				}
				if (Level3Hidden[x][y] == '!' && level3[x][y] == ' ')
				{
					level3[x][y] = 177;
				}
				if (Level3Hidden[x][y] == '^' && level3[x][y] == ' ')
				{
					level3[x][y] = 187;
				}
				if (Level3Hidden[x][y] == '&' && level3[x][y] == ' ')
				{
					level3[x][y] = 201;
				}
				if (Level3Hidden[x][y] == '"' && level3[x][y] == ' ')
				{
					level3[x][y] = 'S';
				}
			}
		}
	}
}

//Section (RENDERING SPECIFIC PARTS OF THE GAME)
void renderUserInterface()
{
	COORD c = g_Console.getConsoleSize();

	if (level == 1)
	{
		//Controls
		c.X = 2;
		c.Y = 27;
		g_Console.writeToBuffer(c, "Controls:", 0xF0);
		c.Y = 28;
		g_Console.writeToBuffer(c, "Move: W, A, S, D", 0xF0);
		c.Y = 29;
		g_Console.writeToBuffer(c, "Move: Arrow keys", 0xF0);
		c.Y = 30;
		g_Console.writeToBuffer(c, "Interact: E ", 0xF0);
		c.Y = 31;
		g_Console.writeToBuffer(c, "Return titlescreen: R", 0xF0);

		c.X = 108;
		c.Y = 2;
		g_Console.writeToBuffer(c, "Intel:", 0xF0);
		switch (intelcountlevel1)
		{
		case 1:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> The Prisoner in the Cafe knows", 0xF0);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  something about this secret", 0xF0);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  passage.", 0xF0);
			break;
		case 2:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> Someone in the toilet holds", 0xF0);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  the information I need.", 0xF0);
			break;
		case 3:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> That person happened to be Ryan!", 0xF0);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  Well I still need to", 0xF0);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  get the required tools.", 0xF0);
			break;
		}

		c.X = 108;
		c.Y = 11;
		g_Console.writeToBuffer(c, "Items:", 0xF0);
		c.X = 120;
		c.Y = 23;
		g_Console.writeToBuffer(c, "Lives:", 0xF0);
		c.X = 128;
		c.Y = 23;
		g_Console.writeToBuffer(c, lives, 0xF0);
		if (ShiveNumber > '0')
		{
			c.X = 110;
			c.Y = 12;
			g_Console.writeToBuffer(c, "Shive(s)", 0xF0);
			c.X = 108;
			c.Y = 12;
			g_Console.writeToBuffer(c, ShiveNumber, 0xF0);
		}
		if (KeyNumber > '0')
		{
			c.X = 110;
			c.Y = 23;
			g_Console.writeToBuffer(c, "Key(s)", 0xF0);
			c.X = 108;
			c.Y = 23;
			g_Console.writeToBuffer(c, KeyNumber, 0xF0);
		}
	}

	if (level == 2)
	{
		//Controls
		c.X = 89;
		c.Y = 2;
		g_Console.writeToBuffer(c, "Controls:", 0xF0);
		c.Y = 3;
		g_Console.writeToBuffer(c, "Move: W, A, S, D", 0xF0);
		c.Y = 4;
		g_Console.writeToBuffer(c, "Move: Arrow keys", 0xF0);
		c.Y = 5;
		g_Console.writeToBuffer(c, "Interact: E ", 0xF0);
		c.Y = 6;
		g_Console.writeToBuffer(c, "Return titlescreen: R", 0xF0);

		c.X = 89;
		c.Y = 29;
		g_Console.writeToBuffer(c, "Intel:", 0xF0);
		switch (intelcountlevel1)
		{
		case 1:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> The Prisoner in the Cafe knows", 0xF0);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  something about this secret", 0xF0);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  passage.", 0xF0);
			break;
		case 2:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> Someone in the toilet holds", 0xF0);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  the information I need.", 0xF0);
			break;
		case 3:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> That person happened to be Ryan!", 0xF0);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  Well I still need to", 0xF0);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  get the required tools.", 0xF0);
			break;
		}

		c.X = 108;
		c.Y = 11;
		g_Console.writeToBuffer(c, "Items:", 0xF0);
		c.X = 120;
		c.Y = 23;
		g_Console.writeToBuffer(c, "Lives:", 0xF0);
		c.X = 128;
		c.Y = 23;
		g_Console.writeToBuffer(c, lives, 0xF0);
		if (ShiveNumber > '0')
		{
			c.X = 110;
			c.Y = 12;
			g_Console.writeToBuffer(c, "Shive(s)", 0xF0);
			c.X = 108;
			c.Y = 12;
			g_Console.writeToBuffer(c, ShiveNumber, 0xF0);
		}
		if (KeyNumber > '0')
		{
			c.X = 110;
			c.Y = 23;
			g_Console.writeToBuffer(c, "Key(s)", 0xF0);
			c.X = 108;
			c.Y = 23;
			g_Console.writeToBuffer(c, KeyNumber, 0xF0);
		}
	}

	if (level == 3)
	{
		//Controls
		c.X = 2;
		c.Y = 34;
		g_Console.writeToBuffer(c, "Controls:", 0xF0);
		c.Y = 35;
		g_Console.writeToBuffer(c, "Move: W, A, S, D", 0xF0);
		c.Y = 36;
		g_Console.writeToBuffer(c, "Move: Arrow keys", 0xF0);
		c.Y = 37;
		g_Console.writeToBuffer(c, "Interact: E ", 0xF0);
		c.Y = 38;
		g_Console.writeToBuffer(c, "Return titlescreen: R", 0xF0);

		c.X = 26;
		c.Y = 34;
		g_Console.writeToBuffer(c, "Items:", 0xF0);
		c.X = 138;
		c.Y = 38;
		g_Console.writeToBuffer(c, "Lives:", 0xF0);
		c.X = 144;
		c.Y = 38;
		g_Console.writeToBuffer(c, lives, 0xF0);
		if (ShiveNumber > '0')
		{
			c.X = 28;
			c.Y = 35;
			g_Console.writeToBuffer(c, "Shive(s)", 0xF0);
			c.X = 26;
			c.Y = 35;
			g_Console.writeToBuffer(c, ShiveNumber, 0xF0);
		}
		if (KeyNumber > '0')
		{
			c.X = 28;
			c.Y = 36;
			g_Console.writeToBuffer(c, "Key(s)", 0xF0);
			c.X = 26;
			c.Y = 36;
			g_Console.writeToBuffer(c, KeyNumber, 0xF0);
		}
		if (KeyFragment > '0')
		{
			c.X = 28;
			c.Y = 37;
			g_Console.writeToBuffer(c, "Key Fragment(s)", 0xF0);
			c.X = 26;
			c.Y = 37;
			g_Console.writeToBuffer(c, KeyNumber, 0xF0);
		}
	}
}
void renderGameOver()
{
	using namespace std;

	COORD c = g_Console.getConsoleSize();
	string line;
	ifstream myfile("gameover.txt");

	c.X = 1;
	c.Y = 1;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int col = 0; col < line.size(); col++)
			{
				if (line[col] == '#')
				{
					line[col] = 219;
					g_Console.writeToBuffer(c, line[col], 0x0c);
				}
				if (line[col] == '|')
				{
					line[col] = 219;
					g_Console.writeToBuffer(c, line[col], 0x08);
				}
				c.X++;
			}
			c.Y++;
			c.X = 1;
		}
		myfile.close();
	}
	c.X = 20;
	c.Y = 24;
	g_Console.writeToBuffer(c, "You got caught...You will get sent back to the title screen by pressing R", 0x0F);

	lives = '2';
	ShiveNumber = '0';
	KeyNumber = '0';
	

	if (level = 1)
	{
    	g_sChar.m_cLocation.X = 6; // To reset the spawn point of the player
	    g_sChar.m_cLocation.Y = 4;
	}
	if (level = 2)
	{
		g_sLevel2Char.m_cLocation.X = 46;
		g_sLevel2Char.m_cLocation.Y = 3;
	}
	//reset future stuff to be placed in here
}
void renderCharacter()
{
	// Draw the location of the character
	if (level == 1)
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, (char)2, 0xF0); //Player Character rendering

		g_Console.writeToBuffer(g_sLevel1GuardCells.m_cLocation, (char)2, 0XFC); //Rendering of Guard near the cells area
		g_Console.writeToBuffer(g_sLevel1GuardCafe.m_cLocation, (char)2, 0XFC); //Rendering of Guard near the Cafe area
		g_Console.writeToBuffer(g_sLevel1GuardField1.m_cLocation, (char)2, 0XFC); //Rendering of Guard near the Field area
		g_Console.writeToBuffer(g_sLevel1GuardField2.m_cLocation, (char)2, 0XFC); //Rendering of Guard near the Field area

		g_Console.writeToBuffer(g_sLevel1PrisonerCells.m_cLocation, (char)2, 0XF1); //Rendering of Guard near the cells area
		g_Console.writeToBuffer(g_sLevel1PrisonerCafe.m_cLocation, (char)2, 0XF1); //Rendering of Guard near the cafe area
		g_Console.writeToBuffer(g_sLevel1PrisonerShowers.m_cLocation, (char)2, 0XF1); //Rendering of Guard near the showers area
	}
	if (level == 2)
	{
		g_Console.writeToBuffer(g_sLevel2Char.m_cLocation, (char)2, 0xF0);
		g_Console.writeToBuffer(g_sLevel2RotatingGuard.m_cLocation, (char)2, 0XF1);
		g_Console.writeToBuffer(g_sLevel2DownGuard.m_cLocation, (char)1, 0XFC);
		g_Console.writeToBuffer(g_sLevel2LeftGuard.m_cLocation, (char)1, 0XFC);
		g_Console.writeToBuffer(g_sLevel2RightGuard.m_cLocation, (char)1, 0XFC);
		g_Console.writeToBuffer(g_sLevel2UpGuard.m_cLocation, (char)1, 0XFC);
		g_Console.writeToBuffer(g_sLevel2CafeGuard.m_cLocation, (char)2, 0XF1);
	}
	if (level == 3)
	{
		g_Console.writeToBuffer(g_sLevel3Char.m_cLocation, (char)2, 0xF0);
		for (int i = 0; i < 3; i++)
		{
			g_Console.writeToBuffer(g_sLevel3Guard[i].m_cLocation, (char)1, 0xFC);
		}
	}
}
void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());
}
void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}
void renderClear()
{
	using namespace std;

	COORD c = g_Console.getConsoleSize();
	string line;
	ifstream myfile("clear.txt");

	c.X = 1;
	c.Y = 1;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int col = 0; col < line.size(); col++)
			{
				if (line[col] == '#')
				{
					line[col] = 219;
				}
				g_Console.writeToBuffer(c, line[col], 0xF0);
				c.X++;
			}
			c.Y++;
			c.X = 1;
		}
		myfile.close();
	}

	if (g_abKeyPressed[K_RETURN])
	{
		g_eGameState = S_SPLASHSCREEN;
	}

	if (g_abKeyPressed[K_NEXTLEVEL])
	{
		g_Console.clearBuffer();
		g_eGameState = S_GAMELEVEL2;
	}

	c.X = 6;
	c.Y = 25;
	g_Console.writeToBuffer(c, "Congratulations, you won! Press R to return to titlescreen, press T to move on the the next level", 0x0F);
}

bool detect = false;

void midgLOS()
{
	int xx = 4;
	for (int sett = 0; sett < 9; sett++)
	{
		int yy = 1;
		g_sMidGLOS[sett].m_cLocation.X = g_sLevel3Guard[1].m_cLocation.X - xx;
		g_sMidGLOS[sett].m_cLocation.Y = g_sLevel3Guard[1].m_cLocation.Y - yy;
		xx--;
		if (g_sMidGLOS[sett].m_cLocation.X == g_sLevel3Char.m_cLocation.X && g_sMidGLOS[sett].m_cLocation.Y == g_sLevel3Char.m_cLocation.Y)
		{
			detect = true;
		}
	}
	xx = 5;
	for (int sett = 9; sett < 19; sett++)
	{
		int yy = g_sLevel3Guard[1].m_cLocation.Y;
		g_sMidGLOS[sett].m_cLocation.X = g_sLevel3Guard[1].m_cLocation.X - xx;
		g_sMidGLOS[sett].m_cLocation.Y = g_sLevel3Guard[1].m_cLocation.Y;
		if (sett == 13) {
			xx--;
		}
		xx--;
		if (g_sMidGLOS[sett].m_cLocation.X == g_sLevel3Char.m_cLocation.X && g_sMidGLOS[sett].m_cLocation.Y == g_sLevel3Char.m_cLocation.Y)
		{
			detect = true;
		}
	}
	xx = 4;
	for (int sett = 19; sett <28; sett++)
	{
		int yy = 1;
		g_sMidGLOS[sett].m_cLocation.X = g_sLevel3Guard[1].m_cLocation.X - xx;
		g_sMidGLOS[sett].m_cLocation.Y = g_sLevel3Guard[1].m_cLocation.Y + yy;
		xx--;
		if (g_sMidGLOS[sett].m_cLocation.X == g_sLevel3Char.m_cLocation.X && g_sMidGLOS[sett].m_cLocation.Y == g_sLevel3Char.m_cLocation.Y)
		{
			detect = true;
		}
	}
	xx = 3;
	for (int sett = 28; sett < 35; sett++)
	{
		int yy = 2;
		g_sMidGLOS[sett].m_cLocation.X = g_sLevel3Guard[1].m_cLocation.X - xx;
		g_sMidGLOS[sett].m_cLocation.Y = g_sLevel3Guard[1].m_cLocation.Y - yy;
		xx--;
		if (g_sMidGLOS[sett].m_cLocation.X == g_sLevel3Char.m_cLocation.X && g_sMidGLOS[sett].m_cLocation.Y == g_sLevel3Char.m_cLocation.Y)
		{
			detect = true;
		}
	}
	xx = 3;
	for (int sett = 35; sett < 42; sett++)
	{
		int yy = 2;
		g_sMidGLOS[sett].m_cLocation.X = g_sLevel3Guard[1].m_cLocation.X - xx;
		g_sMidGLOS[sett].m_cLocation.Y = g_sLevel3Guard[1].m_cLocation.Y + yy;
		xx--;
		if (g_sMidGLOS[sett].m_cLocation.X == g_sLevel3Char.m_cLocation.X && g_sMidGLOS[sett].m_cLocation.Y == g_sLevel3Char.m_cLocation.Y)
		{
			detect = true;
		}
	}
}

int xcord[10000];
int ycord[10000];
int bullets[10000];
int bcount = 0;
int x = 0;
bool initial = false;
bool first = true;
int cntcnt = 1;

void guardChase()
{
	if (detect == true)
	{
		if ((g_sLevel3Char.m_cLocation.Y <= 15) && (g_sLevel3Guard[1].m_cLocation.Y > 14) && g_dGuardMove == 0.0)
		{
			if (g_sLevel3Guard[1].m_cLocation.X >= 46)
			{
				g_sLevel3Guard[1].m_cLocation.X--;
			}
			if (g_sLevel3Guard[1].m_cLocation.X <= 46)
			{
				g_sLevel3Guard[1].m_cLocation.X++;
			}
			if (g_dGuardMove > 0.21)
			{
				g_dGuardMove = 0.0;
			}
		}
		else if ((g_sLevel3Char.m_cLocation.Y > 15) && (g_sLevel3Guard[1].m_cLocation.Y < 14) && g_dGuardMove == 0.0)
		{
			if (g_sLevel3Guard[1].m_cLocation.X >= 46)
			{
				g_sLevel3Guard[1].m_cLocation.X--;
			}
			if (g_sLevel3Guard[1].m_cLocation.X <= 46)
			{
				g_sLevel3Guard[1].m_cLocation.X++;
			}
			if (g_dGuardMove > 0.21)
			{
				g_dGuardMove = 0.0;
			}
		}
		else if (g_sLevel3Guard[1].m_cLocation.X != g_sLevel3Char.m_cLocation.X && g_dGuardMove == 0.0)
		{
			if (g_sLevel3Char.m_cLocation.X > g_sLevel3Guard[1].m_cLocation.X && level3[g_sLevel3Guard[1].m_cLocation.Y][g_sLevel3Guard[1].m_cLocation.X + 1] == ' ')
			{
				cntcnt = 1;
				g_sLevel3Guard[1].m_cLocation.X++;
			}
			if (g_sLevel3Char.m_cLocation.X < g_sLevel3Guard[1].m_cLocation.X && level3[g_sLevel3Guard[1].m_cLocation.Y][g_sLevel3Guard[1].m_cLocation.X - 1] == ' ')
			{
				cntcnt = 2;
				g_sLevel3Guard[1].m_cLocation.X--;
			}
		}
		if (g_sLevel3Guard[1].m_cLocation.Y != g_sLevel3Char.m_cLocation.Y && g_dGuardMove == 0.0)
		{
			if (g_sLevel3Char.m_cLocation.Y > g_sLevel3Guard[1].m_cLocation.Y && level3[g_sLevel3Guard[1].m_cLocation.Y + 1][g_sLevel3Guard[1].m_cLocation.X] == ' ')
			{
				cntcnt = 3;
				g_sLevel3Guard[1].m_cLocation.Y++;
			}
			if (g_sLevel3Char.m_cLocation.Y < g_sLevel3Guard[1].m_cLocation.Y && level3[g_sLevel3Guard[1].m_cLocation.Y - 1][g_sLevel3Guard[1].m_cLocation.X] == ' ')
			{
				cntcnt = 4;
				g_sLevel3Guard[1].m_cLocation.Y--;
			}
		}
		if (g_dGuardMove > 0.21)
		{
			g_dGuardMove = 0.0;
		}
	}
}
void renderShooting()
{
	COORD b[10000];
	//Initialise starting points for coordinates//
	if (initial == false)
	{
		for (int cords = 0; cords < 2; cords++)
		{
			switch (cntcnt)
			{
			case 1:
				xcord[cords] = g_sLevel3Guard[1].m_cLocation.X + 1;
				ycord[cords] = g_sLevel3Guard[1].m_cLocation.Y;
				break;
			case 2:
				xcord[cords] = g_sLevel3Guard[1].m_cLocation.X - 1;
				ycord[cords] = g_sLevel3Guard[1].m_cLocation.Y;
				break;
			case 3:
				xcord[cords] = g_sLevel3Guard[1].m_cLocation.X;
				ycord[cords] = g_sLevel3Guard[1].m_cLocation.Y + 1;
				break;
			case 4:
				xcord[cords] = g_sLevel3Guard[1].m_cLocation.X;
				ycord[cords] = g_sLevel3Guard[1].m_cLocation.Y - 1;
				break;
			}
		}
	}

	//Updating after every iteration//
	for (int seto = 0; seto < 2; seto++)
	{
		b[seto].X = xcord[seto];
		b[seto].Y = ycord[seto];
	}

	//this so the initialising dont repeat//
	initial = true;

	while (g_dBullet1 > 0.0 && first == true)
	{
		bullets[x] = (char)7;
		x++;
		first = false;
	}

	if (g_dBullet1 >= 0.06)
	{
		first = true;
		g_dBullet1 = 0.0;
	}

	for (int x1 = 0; x1 < x; x1++)
	{
		switch (cntcnt)
		{
		case 1:
			if (bullets[x1] == (char)7)
			{
				xcord[x1]++;
			}

			//if (level3[ycord[x1]][xcord[x1]] != ' ')
			//{
			//	bullets[x1] = ' ';
			//	xcord[x1]--;
			//}
			break;
		case 2:
			if (bullets[x1] == (char)7)
			{
				xcord[x1]--;
			}

			//if (level3[ycord[x1]][xcord[x1]] != ' ')
			//{
			//	bullets[x1] = ' ';
			//	xcord[x1]++;
			//}
			break;
		case 3:
			if (bullets[x1] == (char)7)
			{
				ycord[x1]++;
			}

			//if (level3[ycord[x1]][xcord[x1]] != ' ')
			//{
			//	bullets[x1] = ' ';
			//	ycord[x1]--;
			//}
			break;
		case 4:
			if (bullets[x1] == (char)7)
			{
				ycord[x1]--;
			}

			//if (level3[ycord[x1]][xcord[x1]] != ' ')
			//{
			//	bullets[x1] = ' ';
			//	ycord[x1]++;
			//}
			break;
		}
	}

	for (int output = 0; output < 2; output++)
	{
		g_Console.writeToBuffer(b[output], bullets[output], 0X0F);
	}
}

void gameoverwait()
{
	if (g_eGameState == S_GAMEOVER && g_abKeyPressed[K_RETURN])
	{
		g_eGameState = S_SPLASHSCREEN;
		g_dGameOver = 0; //To always reset the spawn
		RemoveHidden();
		Hidden1Stage2 = false;
		Hidden2Stage2 = false;
		Hidden3Stage2 = false;
		ShiveNumber = '0';
		KeyNumber = '0';
		KeyFragment = '0';
		intelcountlevel1 = 0;
	}
}
