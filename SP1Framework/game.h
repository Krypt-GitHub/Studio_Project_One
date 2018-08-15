#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP, // Up keys
	W,
    K_DOWN, // Down Keys
	S,
    K_LEFT,  // Left Keys
	A,
    K_RIGHT, // Right Keys
	D,
    K_ESCAPE, // Escaping the game
    K_SPACE, // Chaning of colour
    K_COUNT, 
	K_RETURN, //Returning from the level to the title screen
	K_ENTER  //Selection of levels
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAMELEVEL1,
	S_GAMELEVEL2,
	S_GAMELEVEL3,
	S_GAMEEXIT,
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen

void gameplayLevel1();            // gameplay logic
void gameplayLevel2();
void gameplayLevel3();

void moveCharacterLevel1();       // moves the character, collision detection, physics, etc
void Level1AIMovement();

void moveCharacterLevel2();

void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen
void renderLevelOne();          // renders the game stuff in LEVEL 1
void renderLevelTwo();          // renders the game stuff in LEVEL 2
void renderLevelThree();          // renders the game stuff in LEVEL 3
void renderTutorialMap();   // renders the map to the buffer first
void renderBronzeMap();   // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void characterInteraction();

#endif // _GAME_H