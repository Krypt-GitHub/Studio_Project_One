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
double  g_dGameOver = 0.0;
bool    g_abKeyPressed[K_COUNT];

char level1[125][125];
double startgame = 1.0; //SPLASHSCREEN TIME
char level2[125][125];
char level3[125][125];
signed int MenuItem = 0;
int level = 0;


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

EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

					   // Console object
Console g_Console(300, 300, "SP1 Framework");

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

	g_sChar.m_cLocation.X = 6; //Player spawn point
	g_sChar.m_cLocation.Y = 4;

	g_sLevel2Char.m_cLocation.X = 46; //Level 2 Character spawn point
	g_sLevel2Char.m_cLocation.Y = 3; 

	g_sLevel1GuardCells.m_cLocation.X = 3; //Spawn Point of Guard near the Cells area
	g_sLevel1GuardCells.m_cLocation.Y = 10; 

	g_sLevel1GuardCafe.m_cLocation.X = 35; //Spawn Point of Guard near the Cafe area
	g_sLevel1GuardCafe.m_cLocation.Y = 15; 
	
	g_sLevel1GuardField1.m_cLocation.X = 105; //Spawn Point of Guard 1 near the Field area
	g_sLevel1GuardField1.m_cLocation.Y = 15;
	
	g_sLevel1GuardField2.m_cLocation.X = 115;  //Spawn Point of Guard 2 near the Field area
	g_sLevel1GuardField2.m_cLocation.Y = 5;

	g_sLevel1PrisonerCells.m_cLocation.X = 15; //Spawn Point of Prisoner near the Cells area
	g_sLevel1PrisonerCells.m_cLocation.Y = 4;

	g_sLevel1PrisonerShowers.m_cLocation.X = 45;  //Spawn Point of Prisoner near the Showers area
	g_sLevel1PrisonerShowers.m_cLocation.Y = 25;

	g_sLevel1PrisonerCafe.m_cLocation.X = 45;  //Spawn Point of Prisoner near the Cafe area
	g_sLevel1PrisonerCafe.m_cLocation.Y = 10;
	g_sChar.m_cLocation.X = 6; //Player spawn point
	g_sChar.m_cLocation.Y = 4;

	g_sLevel2Char.m_cLocation.X = 46; //Level 2 Character spawn point
	g_sLevel2Char.m_cLocation.Y = 3; 

	g_sLevel1GuardCells.m_cLocation.X = 3; //Spawn Point of Guard near the Cells area
	g_sLevel1GuardCells.m_cLocation.Y = 10; 

	g_sLevel1GuardCafe.m_cLocation.X = 35; //CAFE GUARD POINTS
	g_sLevel1GuardCafe.m_cLocation.Y = 13; 
	
	g_sLevel1GuardField1.m_cLocation.X = 105; //Spawn Point of Guard 1 near the Field area
	g_sLevel1GuardField1.m_cLocation.Y = 15;
	
	g_sLevel1GuardField2.m_cLocation.X = 115;  //Spawn Point of Guard 2 near the Field area
	g_sLevel1GuardField2.m_cLocation.Y = 5;

	g_sLevel1PrisonerCells.m_cLocation.X = 15; //Spawn Point of Prisoner near the Cells area
	g_sLevel1PrisonerCells.m_cLocation.Y = 4;

	g_sLevel1PrisonerShowers.m_cLocation.X = 45;  //Spawn Point of Prisoner near the Showers area
	g_sLevel1PrisonerShowers.m_cLocation.Y = 25;

	g_sLevel1PrisonerCafe.m_cLocation.X = 40;  //Spawn Point of Prisoner near the Cafe area
	g_sLevel1PrisonerCafe.m_cLocation.Y = 10;

	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
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
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;
	g_dGuardTimeX += g_dDeltaTime;
	g_dGuardTimeY += g_dDeltaTime;
	g_dGameOver += dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAMELEVEL1: gameplayLevel1(); // gameplay logic when we are in the Level 1
		break;
	case S_GAMELEVEL2: gameplayLevel2();
		break;
	case S_GAMELEVEL3: gameplayLevel3();
		break;
	case S_GAMEOVER: gameoverwait();
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAMELEVEL1: renderLevelOne();
		break;
	case S_GAMELEVEL2: renderLevelTwo();
		break;
	case S_GAMELEVEL3: renderLevelThree();
		break;
	case S_GAMEEXIT: g_bQuitGame;
		break;
	case S_GAMEOVER: gameovercondition();
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
		}
		if (MenuItem == 1)
		{
			g_eGameState = S_GAMELEVEL2;
		}
		if (MenuItem == 2)
		{
			g_eGameState = S_GAMELEVEL3;
		}
		if(MenuItem == 3)
		{
			g_bQuitGame = true;
		}
	}
}

void gameoverwait()
{
	if (g_dGameOver >= 5.0)
	{
		g_eGameState = S_SPLASHSCREEN;
		g_dGameOver = 0; //To always reset the spawn
	}
}

void gameovercondition()
{
	renderGameOver();
}

void gameplayLevel1()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacterLevel1();    // moves the character, collision detection, physics, etc
	Level1AIMovement(); //AI movement 
	                   // sound can be played here too.
}

void gameplayLevel2()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacterLevel2();    // moves the character, collision detection, physics, etc
							  //AI movement 
						// sound can be played here too.
}

void gameplayLevel3()
{

}

//Global Variables for AI

int move = 0;
int move1 = 0;

void Level1AIMovement()
{	
	if (g_dGuardTimeX >= 0.20)
	{
		//FOR CELL GUARD
		if (g_sLevel1GuardCells.m_cLocation.X < 13 && move != 10) //X starts at 3
		{
			g_sLevel1GuardCells.m_cLocation.X++;
			g_dGuardTimeX = 0.0;
		
		}
		//FOR FIELD GUARDS
		if (g_sLevel1GuardField1.m_cLocation.Y > 5 && move != 10) //Y starts at 15
		{
			g_sLevel1GuardField1.m_cLocation.Y--;
			g_dGuardTimeX = 0.0;
		
		}
		if (g_sLevel1GuardField2.m_cLocation.Y < 15 && move != 10) //Y starts at 5
		{
			g_sLevel1GuardField2.m_cLocation.Y++;
			g_dGuardTimeX = 0.0;
			move++;
		}
	}

	if (g_dGuardTimeX >= 0.20 && move == 10)
	{
		//FOR CELL GUARD
		if (g_sLevel1GuardCells.m_cLocation.X > 2)
		{
			g_sLevel1GuardCells.m_cLocation.X--;
			g_dGuardTimeX = 0.0;
		}
		//FOR FIELD GUARDS
		if (g_sLevel1GuardField1.m_cLocation.Y < 15) //Y starts at 5
		{
			g_sLevel1GuardField1.m_cLocation.Y++;
			g_dGuardTimeX = 0.0;
		}
		if (g_sLevel1GuardField2.m_cLocation.Y > 5) //Y starts at 5
		{
			g_sLevel1GuardField2.m_cLocation.Y--;
			g_dGuardTimeX = 0.0;
		}
		
		//TO RESET FOR LOOPING
		if (g_sLevel1GuardCells.m_cLocation.X == 3)
		{
			move = 0;
		}
	}

	if (g_dGuardTimeY >= 0.35)
	{
		//FOR CAFE GUARD
		if (g_sLevel1GuardCafe.m_cLocation.Y > 3 && move1 != 6) //Y starts at 13
		{
			g_sLevel1GuardCafe.m_cLocation.Y--;
			g_dGuardTimeY = 0.0;
			move1++;
		}
	}

	if (g_dGuardTimeY >= 0.35 && move1 == 6)
	{
		//FOR CAFE GUARD
		if (g_sLevel1GuardCafe.m_cLocation.Y < 13)
		{
			g_sLevel1GuardCafe.m_cLocation.Y++;
			g_dGuardTimeY = 0.0;
		}
		if (g_sLevel1GuardCafe.m_cLocation.Y == 13)
		{
			move1 = 0;
		}
	}
}

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
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[W]) && level1[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'x') //To move up checking
	{
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
		if (((Ch1X == CeX) && (Ch1Y == CeY + 1)) || ((Ch1X == CaX) && (Ch1Y == CaY + 1)) || ((Ch1X == F1X) && (Ch1Y == F1Y + 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y + 1)))
		{
			/*Ch1Y = */g_sChar.m_cLocation.Y++;
			g_eGameState = S_GAMEOVER;
		}
	}
	if ((g_abKeyPressed[K_LEFT] || g_abKeyPressed[A]) && g_sChar.m_cLocation.X > 0 && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'x')
	{
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
		if (((Ch1X == CeX + 1) && (Ch1Y == CeY)) || ((Ch1X == CaX+1) && (Ch1Y == CaY)) || ((Ch1X == F1X+1) && (Ch1Y == F1Y)) || ((Ch1X == F2X+1) && (Ch1Y == F2Y)))
		{
			g_sChar.m_cLocation.X++;
			g_eGameState = S_GAMEOVER;
		}
	}
	if ((g_abKeyPressed[K_DOWN] || g_abKeyPressed[S]) && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && g_sChar.m_cLocation.X > 0 && level1[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == 'x')
	{
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
		if (((Ch1X == CeX) && (Ch1Y == CeY - 1)) || ((Ch1X == CaX) && (Ch1Y == CaY - 1)) || ((Ch1X == F1X) && (Ch1Y == F1Y - 1)) || ((Ch1X == F2X) && (Ch1Y == F2Y - 1)))
		{
			g_sChar.m_cLocation.Y--;
			g_eGameState = S_GAMEOVER;
		}
	}
	if ((g_abKeyPressed[K_RIGHT] || g_abKeyPressed[D]) && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1 && g_sChar.m_cLocation.X > 0 && level1[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'x')
	{
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
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[W]) && level2[g_sLevel2Char.m_cLocation.Y - 1][g_sLevel2Char.m_cLocation.X] == 'x') //To move up checking
	{
		g_sLevel2Char.m_cLocation.Y--;
		bSomethingHappened = true;

	}
	if ((g_abKeyPressed[K_LEFT] || g_abKeyPressed[A]) && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X - 1] == 'x')
	{
		g_sLevel2Char.m_cLocation.X--;
		bSomethingHappened = true;
	}
	if ((g_abKeyPressed[K_DOWN] || g_abKeyPressed[S]) && level2[g_sLevel2Char.m_cLocation.Y + 1][g_sLevel2Char.m_cLocation.X] == 'x')
	{
		g_sLevel2Char.m_cLocation.Y++;
		bSomethingHappened = true;
	}
	if ((g_abKeyPressed[K_RIGHT] || g_abKeyPressed[D]) && level2[g_sLevel2Char.m_cLocation.Y][g_sLevel2Char.m_cLocation.X + 1] == 'x')
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
		g_dBounceTime = g_dElapsedTime + 0.06; // 125ms should be enough
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
		if (level = 1)
		{
			level = 0;
			g_sChar.m_cLocation.X = 6; //Player spawn point
			g_sChar.m_cLocation.Y = 4;
		}
		else if (level = 2)
		{
			level = 0;
			g_sLevel2Char.m_cLocation.X = 46; //Level 2 Character spawn point
			g_sLevel2Char.m_cLocation.Y = 3;
		}
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

void renderLevelOne()
{

	renderTutorialMap(); // renders the map to the buffer first
	renderCharacter();   // renders the character into the buffer
	characterInteraction();
}

void renderLevelTwo()
{
	renderBronzeMap(); // renders the map to the buffer first
	renderCharacter();   // renders the character into the buffer
	characterInteraction();
}

void renderLevelThree()
{

	characterInteraction();
}

void renderTutorialMap()
{
	using namespace std;
	string line;
	COORD c;
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
				if (line[col] == '#')
				{
					line[col] = 205;
				}
				if (line[col] == '*')
				{
					line[col] = 186;
				}
				if (line[col] == 'H')
				{
					line[col] = 219;
				}
				if (line[col] == 'A')
				{
					line[col] = 185;
				}
				if (line[col] == 'B')
				{
					line[col] = 204;
				}
				if (line[col] == 'C')
				{
					line[col] = 201;
				}
				if (line[col] == 'D')
				{
					line[col] = 187;
				}
				if (line[col] == 'E')
				{
					line[col] = 203;
				}
				if (line[col] == 'F')
				{
					line[col] = 202;
				}
				if (line[col] == 'G')
				{
					line[col] = 200;
				}
				if (line[col] == 'I')
				{
					line[col] = 188;
				}
				if (line[col] == '!')
				{
					line[col] = 176;
				}
				if (line[col] == ' ')
				{
					level1[x][y] = 'x';
				}
				g_Console.writeToBuffer(c, line[col], 0x03);
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

void renderBronzeMap()
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
				if (line[col] == '#')
				{
					line[col] = 205;
				}
				if (line[col] == '*')
				{
					line[col] = 186;
				}
				if (line[col] == 'H')
				{
					line[col] = 219;
				}
				if (line[col] == 'A')
				{
					line[col] = 185;
				}
				if (line[col] == 'B')
				{
					line[col] = 204;
				}
				if (line[col] == 'C')
				{
					line[col] = 201;
				}
				if (line[col] == 'D')
				{
					line[col] = 187;
				}
				if (line[col] == 'E')
				{
					line[col] = 203;
				}
				if (line[col] == 'F')
				{
					line[col] = 202;
				}
				if (line[col] == 'G')
				{
					line[col] = 200;
				}
				if (line[col] == 'I')
				{
					line[col] = 188;
				}
				if (line[col] == '!')
				{
					line[col] = 176;
				}
				if (line[col] == '+')
				{
					line[col] = 206;
				}
				if (line[col] == ' ')
				{
					level2[x][y] = 'x';
				}
				g_Console.writeToBuffer(c, line[col], 0x03);
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
	}
	c.X = 25;
	c.Y = 25;
	g_Console.writeToBuffer(c, "You lost, your mom gay", 0x0F);
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
	}
}

void characterInteraction()
{
	if (g_sChar.m_cLocation.Y - 1 == g_sLevel1GuardCells.m_cLocation.X || g_sChar.m_cLocation.Y + 1 == g_sLevel1GuardCells.m_cLocation.X || g_sChar.m_cLocation.X - 1 == g_sLevel1GuardCells.m_cLocation.X || g_sChar.m_cLocation.X + 1 == g_sLevel1GuardCells.m_cLocation.X)
	{
		COORD c = g_Console.getConsoleSize();
		g_Console.writeToBuffer(c, "Hello", 0x03);
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