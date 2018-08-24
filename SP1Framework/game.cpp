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
bool movementLock = false;

double  g_dElapsedTime;
double  g_dDeltaTime;
double  g_dLevel2Timer;

double  g_dGuardTimeX = 0.0;
double  g_dGuardTimeY = 0.0;
double  g_dGuardTimeZ = 0.0;

double  g_dGuardTimeXLevel2 = 0.0;
double  g_dGuardTimeYLevel2 = 0.0;
double  g_dGuardTimeZLevel2 = 0.0;
double  g_dRotationTime = 0.0;
double  g_dRotationTime3 = 0.0;

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
char lives = 50;


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

SGameChar   g_sLevel3Guard[3]; //Level 3 Guard
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
SGameChar   g_sUpGuardDownLOS[26];
SGameChar   g_sDownGuardUpLOS[26];
SGameChar   g_sRightGuardLeftLOS[26];
SGameChar   g_sLeftGuardRightLOS[26];

SGameChar   g_sUpGuardUpLOS[26];
SGameChar   g_sDownGuardDownLOS[26];
SGameChar   g_sRightGuardRightLOS[26];
SGameChar   g_sLeftGuardLeftLOS[26];

SGameChar   g_sLeftGHorLOS[25];
SGameChar   g_sLeftGVerLOS[16];
SGameChar   g_sRightGHorLOS[25];
SGameChar   g_sRightGVerLOS[16];


SGameChar   g_sCafeUpArr;
SGameChar   g_sCafeRightArr;

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
	g_dLevel2Timer = 120.0;

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
	
	g_sLevel2LeftGuard.m_cLocation.X = 70;
	g_sLevel2LeftGuard.m_cLocation.Y = 20;
	
	g_sLevel2RightGuard.m_cLocation.X = 2;
	g_sLevel2RightGuard.m_cLocation.Y = 20;
	
	g_sLevel2CafeGuard.m_cLocation.X = 2;
	g_sLevel2CafeGuard.m_cLocation.Y = 28;

	//LEVEL 2 ARROWS/LOS

	int GlobalSett = 0;
	
	for (int yy = 2; yy < 4; yy++) //Setting of coordinates for LOS of Up guard
	{
		for (int xx = 32; xx < 41; xx++)
		{
			if (g_sUpGuardDownLOS[GlobalSett].m_cLocation.X != g_sLevel2Char.m_cLocation.X && g_sUpGuardDownLOS[GlobalSett].m_cLocation.Y != g_sLevel2Char.m_cLocation.Y)
			{
				g_sUpGuardDownLOS[GlobalSett].m_cLocation.X = xx;
				g_sUpGuardDownLOS[GlobalSett].m_cLocation.Y = yy;
				GlobalSett++;
			}
		}
	}

	GlobalSett = 0;

	for (int yy = 16; yy > 14; yy--) //Setting of coordinates for LOS of Up guard
	{
		for (int xx = 40; xx > 31; xx--)
		{
			if (g_sUpGuardUpLOS[GlobalSett].m_cLocation.X != g_sLevel2Char.m_cLocation.X && g_sUpGuardUpLOS[GlobalSett].m_cLocation.Y != g_sLevel2Char.m_cLocation.Y)
			{
				g_sUpGuardUpLOS[GlobalSett].m_cLocation.X = xx;
				g_sUpGuardUpLOS[GlobalSett].m_cLocation.Y = yy;
				GlobalSett++;
			}
		}
	}

	GlobalSett = 0;

	for (int yy = 38; yy > 36; yy--) //Setting of coordinates for LOS of Down guard
	{
		for (int xx = 32; xx < 41; xx++)
		{
			if (g_sDownGuardUpLOS[GlobalSett].m_cLocation.X != g_sLevel2Char.m_cLocation.X && g_sDownGuardUpLOS[GlobalSett].m_cLocation.Y != g_sLevel2Char.m_cLocation.Y)
			{
				g_sDownGuardUpLOS[GlobalSett].m_cLocation.X = xx;
				g_sDownGuardUpLOS[GlobalSett].m_cLocation.Y = yy;
				GlobalSett++;
			}
		}
	}

	GlobalSett = 0;

	for (int yy = 18; yy < 23; yy++) //Setting of coordinates for LOS of Right guard
	{
		for (int xx = 2; xx < 5; xx++)
		{
			if (g_sRightGuardLeftLOS[GlobalSett].m_cLocation.X != g_sLevel2Char.m_cLocation.X && g_sRightGuardLeftLOS[GlobalSett].m_cLocation.Y != g_sLevel2Char.m_cLocation.Y)
			{
				g_sRightGuardLeftLOS[GlobalSett].m_cLocation.X = xx;
				g_sRightGuardLeftLOS[GlobalSett].m_cLocation.Y = yy;
				GlobalSett++;
			}
		}
	}

	GlobalSett = 0;

	for (int yy = 22; yy > 17; yy--) //Setting of coordinates for LOS of Left guard
	{
		for (int xx = 68; xx < 71; xx++)
		{
			if (g_sLeftGuardRightLOS[GlobalSett].m_cLocation.X != g_sLevel2Char.m_cLocation.X && g_sLeftGuardRightLOS[GlobalSett].m_cLocation.Y != g_sLevel2Char.m_cLocation.Y)
			{
				g_sLeftGuardRightLOS[GlobalSett].m_cLocation.X = xx;
				g_sLeftGuardRightLOS[GlobalSett].m_cLocation.Y = yy;
				GlobalSett++;
			}
		}
	}

	g_sCafeUpArr.m_cLocation.X = 2;
	g_sCafeUpArr.m_cLocation.Y = 27;

	g_sCafeRightArr.m_cLocation.X = 3;
    g_sCafeRightArr.m_cLocation.Y = 28;

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
	g_dLevel2Timer -= dt;
	g_dGuardTimeX += g_dDeltaTime;
	g_dGuardTimeY += g_dDeltaTime;
	g_dGuardTimeZ += g_dDeltaTime;
	g_dGuardTimeXLevel2 += g_dDeltaTime;
    g_dGuardTimeYLevel2 += g_dDeltaTime;
	g_dGuardTimeZLevel2 += g_dDeltaTime;
	g_dRotationTime += g_dDeltaTime;
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
		g_dLevel2Timer = 120.0;
		ShiveNumber = '0';
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
	
	//For the Up and down guards (Total 14, 6 down first)
	if (g_dGuardTimeYLevel2 >= 0.25 && moveLevel2 != 14) //MOVING FORWARD
	{
		Level2Count1 = 0;

		for (int Set = 0; Set < 27; Set++)
		{
			int yy = 0;
			if (Set < 11)
			{
				yy = 2;
			}
			else
			{
				yy = 3;
			}
			g_sUpGuardDownLOS[Set].m_cLocation.Y = yy;
		}
		g_sLevel2UpGuard.m_cLocation.Y++;
		g_sLevel2DownGuard.m_cLocation.Y--;


		for (int i = 0; i < 27; i++)
		{
			g_sUpGuardDownLOS[i].m_cLocation.Y++;
			g_sDownGuardUpLOS[i].m_cLocation.Y--;
		}

		g_dGuardTimeYLevel2 = 0;
		++moveLevel2;
	}
	if (g_dGuardTimeYLevel2 >= 0.25 && moveLevel2 == 14)
	{
		contactcheckLevel2 = false; // MOVING BACKWARD
		Level2Count1 = 1;

		g_sLevel2UpGuard.m_cLocation.Y--;
		g_sLevel2DownGuard.m_cLocation.Y++;
		for (int i = 0; i < 27; i++)
		{
			g_sUpGuardUpLOS[i].m_cLocation.Y--;
			g_sDownGuardDownLOS[i].m_cLocation.Y++;
		}
		g_dGuardTimeYLevel2 = 0;

		if (g_sLevel2UpGuard.m_cLocation.Y == 2)
		{
			moveLevel2 = 0;
		}
	}

	//For the Right and Left guards (Total 14, 6 down first)
	if (g_dGuardTimeXLevel2 >= 0.25 && move1Level2 != 27) //Moving "FOWARD"
	{
		contactcheckLevel2 = true;
		Level2Count2 = 0;

		g_sLevel2RightGuard.m_cLocation.X++;
		g_sLevel2LeftGuard.m_cLocation.X--;
		for (int i = 0; i < 27; i++)
		{
			g_sRightGuardLeftLOS[i].m_cLocation.X++;
			g_sLeftGuardRightLOS[i].m_cLocation.X--;
		}

		g_dGuardTimeXLevel2 = 0;
		++move1Level2;
	}
	if (g_dGuardTimeXLevel2 >= 0.25 && move1Level2 == 27)
	{
		contactcheckLevel2 = false;
		Level2Count2 = 1;

		g_sLevel2RightGuard.m_cLocation.X--;
		g_sLevel2LeftGuard.m_cLocation.X++;
		for (int i = 0; i < 27; i++)
		{
			g_sRightGuardLeftLOS[i].m_cLocation.X--;
			g_sLeftGuardRightLOS[i].m_cLocation.X++;
		}

		g_dGuardTimeXLevel2 = 0;
		if (g_sLevel2RightGuard.m_cLocation.X == 2)
		{
			move1Level2 = 0;
		}
	}
}

int tracker3 = 1;
bool contactcheck31 = true;
bool contactcheck32 = true;

void Level3AIMovement()
{
	if (g_dRotationTime3 >= 0.0)
	{
		tracker3 = 1;
		contactcheck31 = true;
	}
	if (g_dRotationTime3 > 0.2)
	{
		tracker3 = 2;
		contactcheck31 = false;
	}
	if (g_dRotationTime3 > 0.4)
	{
		tracker3 = 1;
		contactcheck32 = true;
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
	if (g_dRotationTime3 > 0.6)
	{
		tracker3 = 2;
		contactcheck32 = false;
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
	if (g_dRotationTime3 > 0.8)
	{
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
	//Level 3
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
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
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

	if (((Ch1X == CeX) && (Ch1Y == CeY)) || ((Ch1X == CaX) && (Ch1Y == CaY)) || ((Ch1X == F1X) && (Ch1Y == F1Y)) || ((Ch1X == F2X) && (Ch1Y == F2Y))) //IF THE PLAYER COLLIDES INTO A GUARD
	{
		lives = lives - 1;
		if (lives != '0') {
			g_sChar.m_cLocation.X = 6;
			g_sChar.m_cLocation.Y = 4;
		}
		else {
			g_eGameState = S_GAMEOVER;
		}
	}

	if (contactcheck == true)
	{
		////THIS IS DETECTION WHEN ALL GUARDS ARE MOVING FORWARD////
		//FOR IF PLAYER NORTH OF GUARD//
		if (((Ch1X == CeX) && (Ch1Y == CeY - 1)) || ((Ch1X == CaX) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X) && (Ch1Y == F1Y - 1)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF PLAYER DIAGONALLY RIGHT TO GUARD//
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY - 1)) || ((Ch1X == CaX + 1) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y - 1)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF PLAYER DIAGONALLY LEFT TO GUARD//
		if (((Ch1X == CaX - 1) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X - 1) && (Ch1Y == F1Y - 1))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF THE PLAYER IS EAST OF GUARD//
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY)) || ((Ch1X == CaX + 1) && (Ch1Y == CaY)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X + 1) && (Ch1Y == F2Y))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF THE PLAYER IS WEST OF GUARD//
		if (((Ch1X == CaX - 1) && (Ch1Y == CaY)) || ((Ch1X == F1X - 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X - 1) && (Ch1Y == F2Y))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF THE PLAYER IS SOUTH OF GUARD//
		if (((Ch1X == CeX) && (Ch1Y == CeY + 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y + 1))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF THE PLAYER IS DIAGONALLY RIGHT BELOW//
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY + 1)) || ((Ch1X == F2X + 1) && (Ch1Y == F2Y + 1))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF THE PLAYER IS DIAGONALLY LEFT BELOW//
		if ((Ch1X == F2X - 1) && (Ch1Y == F2Y + 1)) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
	}
    
	////IF ALL GUARDS ARE MOVING BACKWARDS////
	if (contactcheck == false)
	{
		//FOR IF PLAYER IS NORTH OF GUARD//
		if (((Ch1X == CeX) && (Ch1Y == CeY - 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y - 1))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//FOR IF PLAYER DIAGONALLY RIGHT TO GUARD//
		if ((Ch1X == F2X + 1) && (Ch1Y == F2Y - 1)) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//FOR IF PLAYER DIAGONALLY FRONT LEFT TO GUARD//
		if (((Ch1X == CeX - 1) && (Ch1Y == CeY - 1)) || ((Ch1X == F2X - 1) && (Ch1Y == F2Y - 1))) {
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF PLAYER IS EAST OF GUARD//
		if (((Ch1X == CaX + 1) && (Ch1Y == CaY)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X + 1) && (Ch1Y == F2Y)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}

		//FOR IF PLAYER IS WEST OF GUARD//
		if (((Ch1X == CeX - 1) && (Ch1Y == CeY)) || ((Ch1X == CaX - 1) && (Ch1Y == CaY)) || ((Ch1X == F1X - 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X - 1) && (Ch1Y == F2Y)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//FOR IF PLAYER SOUTH OF GUARD//
		if (((Ch1X == CeX) && (Ch1Y == CeY + 1)) || ((Ch1X == CaX) && (Ch1Y == CaY + 1)) || ((Ch1X == F1X) && (Ch1Y == F1Y + 1)))
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
		//FOR IF PLAYER SOUTH RIGHT BELOW//
		if (((Ch1X == CaX + 1) && (Ch1Y == CaY + 1)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y + 1)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//FOR IF PLAYER SOUTH LEFT BELOW//
		if (((Ch1X == F1X - 1) && (Ch1Y == F1Y + 1)) || ((Ch1X == CeX - 1) && (Ch1Y == CeY + 1)) || ((Ch1X == CaX - 1) && (Ch1Y == CaY + 1)))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sChar.m_cLocation.X = 6;
				g_sChar.m_cLocation.Y = 4;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
	}
}
void leveltwolose()
{
	int CH2X = g_sLevel2Char.m_cLocation.X;
	int CH2Y = g_sLevel2Char.m_cLocation.Y;

	int RtX = g_sLevel2RotatingGuard.m_cLocation.X;
	int RtY = g_sLevel2RotatingGuard.m_cLocation.Y;

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

	if (TurnCount == 1)
	{
		if ((RtX == g_sLevel2Char.m_cLocation.X && (RtY - g_sLevel2Char.m_cLocation.Y >= 0)) || (CRtX == g_sLevel2Char.m_cLocation.X && (g_sLevel2Char.m_cLocation.Y - CRtY <= 3)))
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
	if (TurnCount == 2)
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
	if (TurnCount == 3)
	{
		if (RtX == g_sLevel2Char.m_cLocation.X && (g_sLevel2Char.m_cLocation.Y - RtY >= 0) || (CRtX == g_sLevel2Char.m_cLocation.X && (g_sLevel2Char.m_cLocation.Y - CRtY <= 3)))
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

	
		//IF IN FRONT OF THE GUARD (Radius is 2 tiles for North, south, east and west, radius is one tile for NE, SE, SW, NW) 
		if ((UY + 2 == CH2Y && UX == CH2X) || (DY - 2 == CH2Y && DX == CH2X) || (RY == CH2Y && RX - 2 == CH2X) || (LY == CH2Y && LX + 2 == CH2X))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//TO YOUR BOTTOM RIGHT (REFERENCE TO UP GUARD)
		if ((UX + 1 == CH2X && UY + 1 == CH2Y) || (DX + 1 == CH2X && DY - 1 == CH2Y) || (RX - 1 == CH2X && RY - 1 == CH2Y) || (LX + 1 == CH2X && LY + 1 == CH2Y))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//TO YOUR BOTTOM LEFT (REFERENCE TO UP GUARD)
		if ((UX - 1 == CH2X && UY + 1 == CH2Y) || (DX - 1 == CH2X && DY - 1 == CH2Y) || (RX - 1 == CH2X && RY + 1 == CH2Y) || (LX + 1 == CH2X && LY - 1 == CH2Y))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//TO THE RIGHT
		if ((UX + 2 == CH2X && UY == CH2Y) || (DX + 2 == CH2X && DY == CH2Y) || (RX == CH2X && RY - 2 == CH2Y) || (LX == CH2X && LY + 2 == CH2Y))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//TO THE LEFT
		if ((UX - 2 == CH2X && UY == CH2Y) || (DX - 2 == CH2X && DY == CH2Y) || (RX == CH2X && RY + 2 == CH2Y) || (LX == CH2X && LY - 2 == CH2Y))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//TOP RIGHT
		if ((UX + 1 == CH2X && UY - 1 == CH2Y) || (DX + 1 == CH2X && DY + 1 == CH2Y) || (RX + 1 == CH2X && RY - 1 == CH2Y) || (LX - 1 == CH2X && LY + 1 == CH2Y))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//TOP LEFT
		if ((UX - 1 == CH2X && UY - 1 == CH2Y) || (DX - 1 == CH2X && DY + 1 == CH2Y) || (RX + 1 == CH2X && RY + 1 == CH2Y) || (LX - 1 == CH2X && LY - 1 == CH2Y))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
			}
		}
		//IF BEHIND
		if ((UY - 2 == CH2Y && UX == CH2X) || (DY + 2 == CH2Y && DX == CH2X) || (RY == CH2Y && RX + 2 == CH2X) || (LY == CH2Y && LX - 2 == CH2X))
		{
			lives = lives - 1;
			if (lives != '0') {
				g_sLevel2Char.m_cLocation.X = 46;
				g_sLevel2Char.m_cLocation.Y = 3;
			}
			else {
				g_eGameState = S_GAMEOVER;
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
			if ((((Ch1X == g_sLeftGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGHorLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGHorLOS[sett].m_cLocation.Y))) && (contactcheck31 == true))
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
			if ((((Ch1X == g_sLeftGVerLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGVerLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGVerLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGVerLOS[sett].m_cLocation.Y))) && (contactcheck31 == false))
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
			if ((((Ch1X == g_sLeftGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sLeftGHorLOS[sett].m_cLocation.Y)) || ((Ch1X == g_sRightGHorLOS[sett].m_cLocation.X) && (Ch1Y == g_sRightGHorLOS[sett].m_cLocation.Y))) && (contactcheck32 == true))
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
int intelcount = 0;

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

		g_Console.writeToBuffer(c, "You can now craft a Key, press 'C' to craft one", 0x03);
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

	g_Console.writeToBuffer(c, "Dialogue:", 0x03);

	c.X = 30;
	c.Y = 31;

	//PrisonerCell Dialogue

	switch (PcDial)
	{
	case 1:
		movementLock = true;
		g_Console.writeToBuffer(c, "Prisoner: What do you want?", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          Why are you in my cell?", 0x03);
		break;
	case 2:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: Do you know anything about the secret", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        passage to get out of this place?", 0x03);
		break;
	case 3:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: How the hell do you know about that", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          Who the hell are you?", 0x03);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: Just shut up and tell me", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        what I want to know.", 0x03);
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Alright chill out dude, I don't", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          know much, but I do know someone who", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          might just have the info you need.", 0x03);
		break;
	case 6:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Well, that guy in the cafe.", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          He probably can tell you more.", 0x03);
		movementLock = false;
		break;
	case 7:
		c.Y = 31;
		g_Console.writeToBuffer(c, " ", 0x03);
		intelcount = 1;
		break;
	}

	//PrisonerCafe Dialogue

	c.X = 31;
	c.Y = 31;

	switch (PcafeDial)
	{
	case 1:
		movementLock = true;
		g_Console.writeToBuffer(c, "Faizal: Hey nigger! You know anything", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        bout that secret passage", 0x03);
		break;
	case 2:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Not so loud my man. Alright, there", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          really isn't much I can tell you,", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          but all I know is...", 0x03);
		break;
	case 3:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: What do you mean by isn't much?", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        That dude in the cell told me", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "        you knew everything.", 0x03);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Your great friend Ryan is", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          the one who actually planned", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          this entire thing, go ask him", 0x03);
		c.Y = 34;
		g_Console.writeToBuffer(c, "          He should be in the toilet.", 0x03);
		movementLock = false;
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, " ", 0x03);
		intelcount = 2;
		break;
	}

	//Ryan Dialogue

	c.X = 31;
	c.Y = 31;

	switch (PshowerDial)
	{
	case 1:
		movementLock = true;
		g_Console.writeToBuffer(c, "Faizal: Well, I haven't thought that you are the", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        one who knows about the secret passage", 0x03);
		break;
	case 2:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: I wasn't planning to let you know", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "          either, I was about to leave you", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "          to rot in this hellhole", 0x03);
		break;
	case 3:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Faizal: You better reveal it to me", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        or else you won't be leaving this", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "        place once the authorities know about it", 0x03);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: Fine, I've been planning this sweet", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "      escape since day one so you better not", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "      screw my plan over.", 0x03);
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: That wall right there, at the", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "      other end of this toilet, there is a crack.", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "      However, I just can't seem to break it open", 0x03);
		c.Y = 34;
		g_Console.writeToBuffer(c, "      Though... you can try using the shives lying around", 0x03);
		level1[22][72] = '~';
		movementLock = false;
		break;
	case 6:
		c.Y = 31;
		g_Console.writeToBuffer(c, " ", 0x03);
		intelcount = 3;

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
				g_Console.writeToBuffer(c, line[col], 0x03);
				c.X++;
			}
			c.Y++;
			c.X = 1;
		}
	}

	c.X = 21;
	c.Y = 20;
	g_Console.writeToBuffer(c, "Welcome to the BlackStone Prison Complex, do your best to escape", 0X0F);
	c.X = 21;
	c.Y = 21;
	g_Console.writeToBuffer(c, "----------------------------------------------------------------", 0X0F);
	c.X = 21;
	c.Y = 22;
	g_Console.writeToBuffer(c, " Complex: Stone", 0X0F);
	c.X = 21;
	c.Y = 23;
	g_Console.writeToBuffer(c, " Complex: Bronze", 0X0F);
	c.X = 21;
	c.Y = 24;
	g_Console.writeToBuffer(c, " Complex: Steel", 0X0F);
	c.X = 21;
	c.Y = 25;
	g_Console.writeToBuffer(c, " Exit the Game", 0X0F);
	if (MenuItem == 0)
	{
		c.X = 20;
		c.Y = 22;
		g_Console.writeToBuffer(c, (char)4, 0X0F);
	}
	else if (MenuItem == 1)
	{
		c.X = 20;
		c.Y = 23;
		g_Console.writeToBuffer(c, (char)4, 0X0F);
	}
	else if (MenuItem == 2)
	{
		c.X = 20;
		c.Y = 24;
		g_Console.writeToBuffer(c, (char)4, 0X0F);
	}
	else if (MenuItem == 3)
	{
		c.X = 20;
		c.Y = 25;
		g_Console.writeToBuffer(c, (char)4, 0X0F);
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
			g_Console.writeToBuffer(c, level1[x][y], 0x03);
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

//void renderLevelTwo()
void renderBronzeMap()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	//Rendering text from top to bottom??
	for (int y = 0; y < 250; y++)
	{
		c.X = y;
		for (int x = 0; x < 250; x++)
		{
			c.Y = x;
			g_Console.writeToBuffer(c, level2[x][y], 0x03);
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
		g_Console.writeToBuffer(g_sCafeUpArr.m_cLocation, (char)30, 0X0F);
		break;
	case 2:
		g_Console.writeToBuffer(g_sCafeRightArr.m_cLocation, (char)16, 0X0F);
		break;
	case 3:
		g_Console.writeToBuffer(g_sCafeUpArr.m_cLocation, (char)30, 0X0F);
		break;
	case 4:
		g_Console.writeToBuffer(g_sCafeRightArr.m_cLocation, (char)16, 0X0F);
		break;
	}

	switch (Level2Count1)
	{
	case 0:
		for (int sett = 0; sett < 26; sett++)
		{
			g_Console.writeToBuffer(g_sUpGuardDownLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
			g_Console.writeToBuffer(g_sDownGuardUpLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
		break;

	case 1:
		for (int sett = 0; sett < 26; sett++)
		{
			g_Console.writeToBuffer(g_sUpGuardUpLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
			g_Console.writeToBuffer(g_sDownGuardDownLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
		break;
	}

	switch (Level2Count2)
	{
	case 0:
		for (int sett = 0; sett < 26; sett++)
		{
			g_Console.writeToBuffer(g_sRightGuardLeftLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
			g_Console.writeToBuffer(g_sLeftGuardRightLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
		}
		break;
	case 1:
		for (int sett = 0; sett < 26; sett++)
		{
			g_Console.writeToBuffer(g_sRightGuardRightLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
			g_Console.writeToBuffer(g_sLeftGuardLeftLOS[sett].m_cLocation, "Û", 0X08); //RENDER DIRECTION
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
			g_Console.writeToBuffer(c, level3[x][y], 0x03);
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
		g_Console.writeToBuffer(c, "Controls:", 0x03);
		c.Y = 28;
		g_Console.writeToBuffer(c, "Move: W, A, S, D", 0x03);
		c.Y = 29;
		g_Console.writeToBuffer(c, "Move: Arrow keys", 0x03);
		c.Y = 30;
		g_Console.writeToBuffer(c, "Interact: E ", 0x03);
		c.Y = 31;
		g_Console.writeToBuffer(c, "Return titlescreen: R", 0x03);

		c.X = 108;
		c.Y = 2;
		g_Console.writeToBuffer(c, "Intel:", 0x03);
		switch (intelcount)
		{
		case 1:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> The Prisoner in the Cafe knows", 0x03);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  something about this secret", 0x03);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  passage.", 0x03);
			break;
		case 2:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> Someone in the toilet holds", 0x03);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  the information I need.", 0x03);
			break;
		case 3:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> That person happened to be Ryan!", 0x03);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  Well I still need to", 0x03);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  get the required tools.", 0x03);
			break;
		}

		c.X = 108;
		c.Y = 11;
		g_Console.writeToBuffer(c, "Items:", 0x03);
		c.X = 120;
		c.Y = 23;
		g_Console.writeToBuffer(c, "Lives:", 0x03);
		c.X = 128;
		c.Y = 23;
		g_Console.writeToBuffer(c, lives, 0x03);
		if (ShiveNumber > '0')
		{
			c.X = 110;
			c.Y = 12;
			g_Console.writeToBuffer(c, "Shive(s)", 0x03);
			c.X = 108;
			c.Y = 12;
			g_Console.writeToBuffer(c, ShiveNumber, 0x03);
		}
		if (KeyNumber > '0')
		{
			c.X = 110;
			c.Y = 23;
			g_Console.writeToBuffer(c, "Key(s)", 0x03);
			c.X = 108;
			c.Y = 23;
			g_Console.writeToBuffer(c, KeyNumber, 0x03);
		}
	}

	if (level == 2)
	{
		//Controls
		c.X = 80;
		c.Y = 2;
		g_Console.writeToBuffer(c, "Controls:", 0x03);
		c.Y = 3;
		g_Console.writeToBuffer(c, "Move: W, A, S, D", 0x03);
		c.Y = 4;
		g_Console.writeToBuffer(c, "Move: Arrow keys", 0x03);
		c.Y = 5;
		g_Console.writeToBuffer(c, "Interact: E ", 0x03);
		c.Y = 6;
		g_Console.writeToBuffer(c, "Return titlescreen: R", 0x03);

		c.X = 108;
		c.Y = 2;
		g_Console.writeToBuffer(c, "Intel:", 0x03);
		switch (intelcount)
		{
		case 1:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> The Prisoner in the Cafe knows", 0x03);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  something about this secret", 0x03);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  passage.", 0x03);
			break;
		case 2:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> Someone in the toilet holds", 0x03);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  the information I need.", 0x03);
			break;
		case 3:
			c.Y = 3;
			g_Console.writeToBuffer(c, "> That person happened to be Ryan!", 0x03);
			c.Y = 4;
			g_Console.writeToBuffer(c, "  Well I still need to", 0x03);
			c.Y = 5;
			g_Console.writeToBuffer(c, "  get the required tools.", 0x03);
			break;
		}

		c.X = 108;
		c.Y = 11;
		g_Console.writeToBuffer(c, "Items:", 0x03);
		c.X = 120;
		c.Y = 23;
		g_Console.writeToBuffer(c, "Lives:", 0x03);
		c.X = 128;
		c.Y = 23;
		g_Console.writeToBuffer(c, lives, 0x03);
		if (ShiveNumber > '0')
		{
			c.X = 110;
			c.Y = 12;
			g_Console.writeToBuffer(c, "Shive(s)", 0x03);
			c.X = 108;
			c.Y = 12;
			g_Console.writeToBuffer(c, ShiveNumber, 0x03);
		}
		if (KeyNumber > '0')
		{
			c.X = 110;
			c.Y = 23;
			g_Console.writeToBuffer(c, "Key(s)", 0x03);
			c.X = 108;
			c.Y = 23;
			g_Console.writeToBuffer(c, KeyNumber, 0x03);
		}
	}

	if (level == 3)
	{
		//Controls
		c.X = 2;
		c.Y = 34;
		g_Console.writeToBuffer(c, "Controls:", 0x03);
		c.Y = 35;
		g_Console.writeToBuffer(c, "Move: W, A, S, D", 0x03);
		c.Y = 36;
		g_Console.writeToBuffer(c, "Move: Arrow keys", 0x03);
		c.Y = 37;
		g_Console.writeToBuffer(c, "Interact: E ", 0x03);
		c.Y = 38;
		g_Console.writeToBuffer(c, "Return titlescreen: R", 0x03);

		c.X = 26;
		c.Y = 34;
		g_Console.writeToBuffer(c, "Items:", 0x03);
		c.X = 138;
		c.Y = 38;
		g_Console.writeToBuffer(c, "Lives:", 0x03);
		c.X = 144;
		c.Y = 38;
		g_Console.writeToBuffer(c, lives, 0x03);
		if (ShiveNumber > '0')
		{
			c.X = 28;
			c.Y = 35;
			g_Console.writeToBuffer(c, "Shive(s)", 0x03);
			c.X = 26;
			c.Y = 35;
			g_Console.writeToBuffer(c, ShiveNumber, 0x03);
		}
		if (KeyNumber > '0')
		{
			c.X = 28;
			c.Y = 36;
			g_Console.writeToBuffer(c, "Key(s)", 0x03);
			c.X = 26;
			c.Y = 36;
			g_Console.writeToBuffer(c, KeyNumber, 0x03);
		}
		if (KeyFragment > '0')
		{
			c.X = 28;
			c.Y = 37;
			g_Console.writeToBuffer(c, "Key Fragment(s)", 0x03);
			c.X = 26;
			c.Y = 37;
			g_Console.writeToBuffer(c, KeyNumber, 0x03);
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
				}
				g_Console.writeToBuffer(c, line[col], 0x03);
				c.X++;
			}
			c.Y++;
			c.X = 1;
		}
		myfile.close();
	}
	c.X = 20;
	c.Y = 25;
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
		g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, 0x0C); //Player Character rendering

		g_Console.writeToBuffer(g_sLevel1GuardCells.m_cLocation, (char)2, 0X0F); //Rendering of Guard near the cells area
		g_Console.writeToBuffer(g_sLevel1GuardCafe.m_cLocation, (char)2, 0X0F); //Rendering of Guard near the Cafe area
		g_Console.writeToBuffer(g_sLevel1GuardField1.m_cLocation, (char)2, 0X0F); //Rendering of Guard near the Field area
		g_Console.writeToBuffer(g_sLevel1GuardField2.m_cLocation, (char)2, 0X0F); //Rendering of Guard near the Field area

		g_Console.writeToBuffer(g_sLevel1PrisonerCells.m_cLocation, (char)2, 0X0B); //Rendering of Guard near the cells area
		g_Console.writeToBuffer(g_sLevel1PrisonerCafe.m_cLocation, (char)2, 0X0B); //Rendering of Guard near the cafe area
		g_Console.writeToBuffer(g_sLevel1PrisonerShowers.m_cLocation, (char)2, 0X0B); //Rendering of Guard near the showers area
	}
	if (level == 2)
	{
		g_Console.writeToBuffer(g_sLevel2Char.m_cLocation, (char)1, 0x0C);
		g_Console.writeToBuffer(g_sLevel2RotatingGuard.m_cLocation, (char)1, 0X0F);
		g_Console.writeToBuffer(g_sLevel2DownGuard.m_cLocation, (char)1, 0X0F);
		g_Console.writeToBuffer(g_sLevel2LeftGuard.m_cLocation, (char)1, 0X0F);
		g_Console.writeToBuffer(g_sLevel2RightGuard.m_cLocation, (char)1, 0X0F);
		g_Console.writeToBuffer(g_sLevel2UpGuard.m_cLocation, (char)1, 0X0F);
		g_Console.writeToBuffer(g_sLevel2CafeGuard.m_cLocation, (char)1, 0X0A);
	}
	if (level == 3)
	{
		g_Console.writeToBuffer(g_sLevel3Char.m_cLocation, (char)1, 0x0C);
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
				g_Console.writeToBuffer(c, line[col], 0x03);
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

