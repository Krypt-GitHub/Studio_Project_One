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

double  g_dElapsedTime;
double  g_dDeltaTime;
double  g_dGuardTimeX = 0.0;
double  g_dGuardTimeY = 0.0;
double  g_dGuardTimeZ = 0.0;
double  g_dRotationTime = 0.0;
double  g_dGameOver = 0.0;
bool    g_abKeyPressed[K_COUNT];

bool Hidden1Stage2 = false;
bool Hidden2Stage2 = false;
bool Hidden3Stage2 = false;

double startgame = 1.0; //SPLASHSCREEN TIME
char level1[125][125]; //To store level 1 map into a 2D array 
char level2[250][250]; //To store level 2 map into a 2D array 
char Level2Hidden[250][250]; //To store the hidden passages of Level 2 into a 2D array
char level3[125][125]; //To store level 3 map into a 2D array 
signed int MenuItem = 0;
int level = 0;

char ShiveNumber = '0';
char KeyNumber = '0';
char lives = 50;


// Game specific variables here
SGameChar   g_sChar; //Player character

SGameChar   g_sLevel2Char; //Level 2 Characters

SGameChar   g_sLevel1GuardCells; //Level 1 guards
SGameChar   g_sLevel1GuardCafe;
SGameChar   g_sLevel1GuardField1;
SGameChar   g_sLevel1GuardField2;

SGameChar   g_sLevel1PrisonerCells; //Level 1 Prisoners
SGameChar   g_sLevel1PrisonerShowers;
SGameChar   g_sLevel1PrisonerCafe;

SGameChar g_sLevel2RotatingGuard;

//----------------------------------------------------------
SGameChar   g_sRightArr;
SGameChar   g_sLeftArr;
SGameChar   g_sUpF1Arr;
SGameChar   g_sUpF2Arr;
SGameChar   g_sUpCArr;
SGameChar   g_sDownF1Arr;
SGameChar   g_sDownF2Arr;
SGameChar   g_sDownCArr;

SGameChar   g_sUpRotatingArr;
SGameChar   g_sRightRotatingArr;
SGameChar   g_sDownRotatingArr;
SGameChar   g_sLeftRotatingArr;

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

	g_sLevel1GuardCells.m_cLocation.X = 3; //Spawn Point of Guard near the Cells area
	g_sLevel1GuardCells.m_cLocation.Y = 8;

	g_sLevel1GuardCafe.m_cLocation.X = 45; //Spawn Point of Guard near the Cafe area
	g_sLevel1GuardCafe.m_cLocation.Y = 11;

	g_sLevel1GuardField1.m_cLocation.X = 85; //Spawn Point of Guard 1 near the Field area
	g_sLevel1GuardField1.m_cLocation.Y = 13;

	g_sLevel1GuardField2.m_cLocation.X = 95;  //Spawn Point of Guard 2 near the Field area
	g_sLevel1GuardField2.m_cLocation.Y = 3;

	g_sLevel1PrisonerCells.m_cLocation.X = 15; //Spawn Point of Prisoner near the Cells area
	g_sLevel1PrisonerCells.m_cLocation.Y = 4;

	g_sLevel1PrisonerShowers.m_cLocation.X = 45;  //Spawn Point of Prisoner near the Showers area
	g_sLevel1PrisonerShowers.m_cLocation.Y = 24;

	g_sLevel1PrisonerCafe.m_cLocation.X = 43;  //Spawn Point of Prisoner near the Cafe area
	g_sLevel1PrisonerCafe.m_cLocation.Y = 11;

	//LEVEL 1 DIRECTION POINTERS 
	g_sRightArr.m_cLocation.X = 4; //Spawn of direction arrow (CELL)
	g_sRightArr.m_cLocation.Y = 8;

	g_sLeftArr.m_cLocation.X = 12; //Spawn of direction arrow (CELL)
	g_sLeftArr.m_cLocation.Y = 8;;

	g_sUpF1Arr.m_cLocation.X = 85; //FIELD 1
	g_sUpF1Arr.m_cLocation.Y = 12; 

	g_sDownF1Arr.m_cLocation.X = 85; //FIELD 1
	g_sDownF1Arr.m_cLocation.Y = 6;

	g_sUpF2Arr.m_cLocation.X = 95; //FIELD 2
	g_sUpF2Arr.m_cLocation.Y = 10;

	g_sDownF2Arr.m_cLocation.X = 95; //FIELD 2
	g_sDownF2Arr.m_cLocation.Y = 4;

	g_sUpCArr.m_cLocation.X = 45; //CAFETERIA
	g_sUpCArr.m_cLocation.Y = 10;

	g_sDownCArr.m_cLocation.X = 45;//CAFETERIA
	g_sDownCArr.m_cLocation.Y = 7;

	//LEVEL 2 CHARACTERS
	g_sLevel2Char.m_cLocation.X = 46; //Level 2 Character spawn point (46, 3)
	g_sLevel2Char.m_cLocation.Y = 3;

	g_sLevel2RotatingGuard.m_cLocation.X = 36;
	g_sLevel2RotatingGuard.m_cLocation.Y = 20;

	//LEVEL 2 DIRECTION POINTERS
	g_sUpRotatingArr.m_cLocation.X = 36;
	g_sUpRotatingArr.m_cLocation.Y = 19;

    g_sRightRotatingArr.m_cLocation.X = 37;
	g_sRightRotatingArr.m_cLocation.Y = 20;

    g_sDownRotatingArr.m_cLocation.X = 36;
	g_sDownRotatingArr.m_cLocation.Y = 21;

    g_sLeftRotatingArr.m_cLocation.X = 35;
	g_sLeftRotatingArr.m_cLocation.Y = 20;

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
	g_abKeyPressed[k_TITLE] = isKeyPressed(0x54);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
}

void update(double dt)
{
	// update the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;
	g_dGuardTimeX += g_dDeltaTime;
	g_dGuardTimeY += g_dDeltaTime;
	g_dGuardTimeZ += g_dDeltaTime;
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
		ShiveNumber = '0';
	}
}

//void gameovercondition()
//{
//	renderGameOver();
//}

//void gameplayLevel1()          
//{// gameplay logic
//	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
//	moveCharacterLevel1();    // moves the character, collision detection, physics, etc
//	Level1AIMovement(); //AI movement
//	Level1ItemInteractions();         // sound can be played here too.
//	prisonerInteraction();
//	levelonelose();
//}

//void gameplayLevel2()
//{
//	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
//	moveCharacterLevel2();    // moves the character, collision detection, physics, etc
//	Level2ItemInteractions();						  //AI movement 
//						// sound can be played here too.
//}


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

//AI MOVEMENT
void Level1AIMovement()
{
	if (g_dGuardTimeX >= 0.20)
	{
		count = 1;

		//FOR CELL GUARD
		if (g_sLevel1GuardCells.m_cLocation.X < 13 && move != 10) //X starts at 3
		{
			g_sLeftArr.m_cLocation.X = 12;
			g_sLevel1GuardCells.m_cLocation.X++;
			g_sRightArr.m_cLocation.X++;
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
			g_sRightArr.m_cLocation.X = 4;
			g_sLevel1GuardCells.m_cLocation.X--;
			g_sLeftArr.m_cLocation.X--;
			g_dGuardTimeX = 0.0;
		}

		//TO RESET FOR LOOPING
		if (g_sLevel1GuardCells.m_cLocation.X == 3)
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
			g_sUpF2Arr.m_cLocation.Y = 10;
			g_sDownF1Arr.m_cLocation.Y = 6;
		}
		//FOR FIELD GUARDS
		if (g_sLevel1GuardField1.m_cLocation.Y > 3 && move2 != 8) //Y starts at 15
		{

			g_sLevel1GuardField1.m_cLocation.Y--;
			g_sUpF1Arr.m_cLocation.Y--;
			g_dGuardTimeZ = 0.0;
		}


		if (g_sLevel1GuardField2.m_cLocation.Y < 13 && move2 != 8) //Y starts at 5
		{
			g_sLevel1GuardField2.m_cLocation.Y++;
			g_sDownF2Arr.m_cLocation.Y++;
			g_dGuardTimeZ = 0.0;
			move2++;
		}
	}

	if (g_dGuardTimeZ >= 0.25 && move2 == 8)
	{
		contactcheck = false;

		//FOR FIELD GUARDS
		if (g_sLevel1GuardField1.m_cLocation.Y < 13) //Y starts at 5
		{
			count1 = 2;
			g_sLevel1GuardField1.m_cLocation.Y++;
			g_sDownF1Arr.m_cLocation.Y++;
			g_dGuardTimeZ = 0.0;

		}
		if (g_sLevel1GuardField2.m_cLocation.Y > 3) //Y starts at 5
		{
			g_sLevel1GuardField2.m_cLocation.Y--;
			g_dGuardTimeZ = 0.0;
			g_sUpF2Arr.m_cLocation.Y--;
		}

		if (g_sLevel1GuardField1.m_cLocation.Y == 13)
		{
			g_sUpF1Arr.m_cLocation.Y = 12;
			g_sDownF2Arr.m_cLocation.Y = 4;
			move2 = 0;
		}
	}
	//////////////////////

	if (g_dGuardTimeY >= 0.35)
	{
		if (move1 == 0)
		{
			g_sDownCArr.m_cLocation.Y = 7;
		}
		contactcheck = true;
		//FOR CAFE GUARD
		if (g_sLevel1GuardCafe.m_cLocation.Y > 6 && move1 != 5) //Y starts at 13
		{
			count2 = 1;
			g_sLevel1GuardCafe.m_cLocation.Y--;
			g_sUpCArr.m_cLocation.Y--;
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
			g_sDownCArr.m_cLocation.Y++;
			g_dGuardTimeY = 0.0;
		}
		if (g_sLevel1GuardCafe.m_cLocation.Y == 11)
		{
			g_sUpCArr.m_cLocation.Y = 10;
			move1 = 0;
		}
	}
}
void Level2AIMovement()
{
	if (g_dRotationTime >= 5.0 && g_dRotationTime <= 10.0)
	{
		TurnCount = 0;
	}
	if (g_dRotationTime >= 10.0 && g_dRotationTime <= 15.0)
	{
		TurnCount = 1;
	}
	if (g_dRotationTime >= 15.0 && g_dRotationTime <= 20.0)
	{
		TurnCount = 2;
	}
	if (g_dRotationTime >= 20.0 && g_dRotationTime <= 25.0)
	{
		TurnCount = 3;
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
	}

	//----------------------------------------------------------------------------------------------------------------------------------

	if (g_abKeyPressed[K_INTERACT] && (Level2Hidden[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] == '{' || Level2Hidden[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] == '{'))
	{
		level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] = ' ';
		level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] = ' ';
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
				lives = '2';
			}
		}

		//FOR IF PLAYER DIAGONALLY RIGHT TO GUARD//
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY - 1)) || ((Ch1X == CaX + 1) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y - 1))) {
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

		//FOR IF PLAYER DIAGONALLY LEFT TO GUARD//
		if (((Ch1X == CaX - 1) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X - 1) && (Ch1Y == F1Y - 1))) {
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

		//FOR IF THE PLAYER IS EAST OF GUARD//
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY)) || ((Ch1X == CaX + 1) && (Ch1Y == CaY)) || ((Ch1X == F1X + 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X + 1) && (Ch1Y == F2Y))) {
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

		//FOR IF THE PLAYER IS WEST OF GUARD//
		if (((Ch1X == CaX - 1) && (Ch1Y == CaY)) || ((Ch1X == F1X - 1) && (Ch1Y == F1Y)) || ((Ch1X == F2X - 1) && (Ch1Y == F2Y))) {
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

		//FOR IF THE PLAYER IS SOUTH OF GUARD//
		if (((Ch1X == CeX) && (Ch1Y == CeY + 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y + 1))) {
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

		//FOR IF THE PLAYER IS DIAGONALLY RIGHT BELOW//
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY + 1)) || ((Ch1X == F2X + 1) && (Ch1Y == F2Y + 1))) {
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

		//FOR IF THE PLAYER IS DIAGONALLY LEFT BELOW//
		if ((Ch1X == F2X - 1) && (Ch1Y == F2Y + 1)) {
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
				lives = '2';
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
				lives = '2';
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
				lives = '2';
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
				lives = '2';
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
				lives = '2';
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
				lives = '2';
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
				lives = 50;
			}
		}
	}
}
void leveltwolose()
{

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

void renderDialogue()
{
	COORD c = g_Console.getConsoleSize();

	c.X = 28;
	c.Y = 29;

	g_Console.writeToBuffer(c, "Dialogue:", 0x03);

	c.X = 30;
	c.Y = 31;

	//PrisonerCell Dialogue

	switch (PcDial)
	{
	case 1:
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
		g_Console.writeToBuffer(c, "Faizal: What do you mean you can't tell me", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "        much, there momfucker in the cell told me you know lots", 0x03);
		break;
	case 4:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Prisoner: Mans not hot my lad", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "*Faizal proceeds to penetrate him in the ass*", 0x03);
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
		g_Console.writeToBuffer(c, "escape since day one so you better not", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "screw my plan over.", 0x03);
		break;
	case 5:
		c.Y = 31;
		g_Console.writeToBuffer(c, "Ryan: That wall right there, at the", 0x03);
		c.Y = 32;
		g_Console.writeToBuffer(c, "other end of this toilet, there is a crack.", 0x03);
		c.Y = 33;
		g_Console.writeToBuffer(c, "However, I just can't seem to break it open", 0x03);
		c.Y = 34;
		g_Console.writeToBuffer(c, "Though... you can try using the shives lying around", 0x03);
		level1[22][72] = '~';
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
	if (g_abKeyPressed[k_TITLE])
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
//void renderLevelOne()
//{
//	renderTutorialMap();  // renders the map to the buffer first
//	renderCharacter();   // renders the character into the buffer
//	renderDialogue();
//	renderInventory(); //Renders the inventory
//	Level1ItemInteractions();
//	prisonerInteraction();
//}
void renderTutorialMap()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	for (int y = 0; y < 125; y++)
	{
		c.X = y;
		for (int x = 0; x < 125; x++)
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

//void renderLevelTwo()
//{
//	renderBronzeMap(); // renders the map to the buffer first
//	renderCharacter();   // renders the character into the buffer
//	renderInventory();
//	Level2ItemInteractions();
//}
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

//void renderLevelThree()
//{
//	renderSteelMap();
//	renderCharacter();
//}
void renderSteelMap()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	for (int y = 0; y < 125; y++)
	{
		c.X = y;
		for (int x = 0; x < 125; x++)
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
				if (line[col] == '#')
				{
					level3[x][y] = 205;
				}
				if (line[col] == '*')
				{
					level3[x][y] = 186;
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
				if (line[col] == 'I')
				{
					level3[x][y] = 188;
				}
				if (line[col] == '!')
				{
					level3[x][y] = 176;
				}
				if (line[col] == '+')
				{
					level3[x][y] = 206;
				}
				c.X++;
				y++;
			}
			x++;
			y = 1;
			c.Y++;
			c.X = 1;
		}
	}
}

//Section (RENDERING SPECIFIC PARTS OF THE GAME)
void renderInventory()
{
	COORD c = g_Console.getConsoleSize();
	c.X = 108;
	c.Y = 2;
	g_Console.writeToBuffer(c, "Intel:", 0x03);
	switch (intelcount)
	{
	case 1:
		c.Y = 3;
		g_Console.writeToBuffer(c, "> The Prisoner in the Cafe knows something about this secret passage", 0x03);
		break;
	case 2:
		c.Y = 3;
		g_Console.writeToBuffer(c, "> Someone in the toilet holds the information I need", 0x03);
		break;
	case 3:
		c.Y = 3;
		g_Console.writeToBuffer(c, "> That person happened to be Ryan! Well I still need to get the required tools", 0x03);
		break;
	}

	c.X = 108;
	c.Y = 5;
	g_Console.writeToBuffer(c, "Items On Hand:", 0x03);
	c.X = 108;
	c.Y = 8;
	g_Console.writeToBuffer(c, "Lives:", 0x03);
	c.X = 116;
	c.Y = 8;
	g_Console.writeToBuffer(c, lives, 0x03);
	if (ShiveNumber > '0')
	{
		c.X = 110;
		c.Y = 6;
		g_Console.writeToBuffer(c, "Shive(s)", 0x03);
		c.X = 108;
		c.Y = 6;
		g_Console.writeToBuffer(c, ShiveNumber, 0x03);
	}
}
void renderArr()
{
	switch (count)
	{
	case 1:
	{
		g_Console.writeToBuffer(g_sRightArr.m_cLocation, (char)16, 0X0F); //RENDER DIRECTION
	}
	break;
	case 2:
	{
		g_Console.writeToBuffer(g_sLeftArr.m_cLocation, (char)17, 0X0F); //RENDER DIRECTION
	}
	break;
	}

	//---------------------------------------------------------------------------------------------------------------------------

	switch (count1)
	{
	case 1:
	{
		g_Console.writeToBuffer(g_sDownF2Arr.m_cLocation, (char)31, 0X0F);
		g_Console.writeToBuffer(g_sUpF1Arr.m_cLocation, (char)30, 0X0F); //RENDER DIRECTION
	}
	break;
	case 2:
	{
		g_Console.writeToBuffer(g_sUpF2Arr.m_cLocation, (char)30, 0X0F);
		g_Console.writeToBuffer(g_sDownF1Arr.m_cLocation, (char)31, 0X0F);
	}
	break;
	}
	//----------------------------------------------------------------------------------------------------------------------------

	switch (count2)
	{
	case 1:
	{
		g_Console.writeToBuffer(g_sUpCArr.m_cLocation, (char)30, 0X0F);
	}
	break;
	case 2:
	{
		g_Console.writeToBuffer(g_sDownCArr.m_cLocation, (char)31, 0X0F);
	}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	//switch (TurnCount)
	//{
	//case 1:
	//{
	//	g_Console.writeToBuffer(g_sUpRotatingArr, (char)30, 0X0F);
	//}
	//break;
	//case 2:
	//{
	//	g_Console.writeToBuffer(g_sRightRotatingArr, (char)30, 0X0F);
	//}
	//break;
	//case 3:
	//{
	//	g_Console.writeToBuffer(g_sDownRotatingArr, (char)30, 0X0F);
	//}
	//break;
	//case 4:
	//{
	//	g_Console.writeToBuffer(g_sLeftRotatingArr, (char)30, 0X0F);
	//}
	//
	//}
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
	if (level = 1)
	{
    	g_sChar.m_cLocation.X = 6; // To reset the spawn point of the player
	    g_sChar.m_cLocation.Y = 4;
		loadTutorialMap();
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
	c.X = 20;
	c.Y = 25;
	g_Console.writeToBuffer(c, "Congratulations, you won! You will get sent back to the title screen by pressing R", 0x0F);
}
