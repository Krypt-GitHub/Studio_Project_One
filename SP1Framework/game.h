#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	W,
    K_DOWN,
	S,
    K_LEFT,
	A,
    K_RIGHT,
	D,
    K_ESCAPE,
    K_SPACE,
	K_RETURN,
	K_ENTER,
	K_INTERACT,
	K_CRAFT,
	K_NEXTLEVEL,
    K_COUNT

};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAMELEVEL1,
	S_GAMELEVEL2,
	S_GAMELEVEL3,
	S_GAMEEXIT,
    S_COUNT,
	S_GAMEOVER,
	S_CLEAR
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

void gameplayLevel1();     // gameplay logic
void gameplayLevel2();     // gameplay logic
void gameplayLevel3();     // gameplay logic

void Level1AIMovement();
void Level2AIMovement();
void Level3AIMovement();

void moveCharacterLevel1();       // moves the character, collision detection, physics, etc
void moveCharacterLevel2();       // moves the character, collision detection, physics, etc
void moveCharacterLevel3();       // moves the character, collision detection, physics, etc

void Level1ItemInteractions();
void Level2ItemInteractions();
void Level3ItemInteractions();

void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen
void renderTutorialMap();   // renders the map to the buffer first
void renderBronzeMap();   // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer

void renderLevelOne();
void renderLevelTwo();
void renderLevelThree();

void renderUserInterface();

void levelonelose();
void leveltwolose();
void levelthreelose();


void renderSteelMap();
void renderDialogue();
void renderClear();
void renderArrowLevel1();
void renderArrowLevel2();

void prisonerInteraction();

void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void renderGameOver();//For AI to move forward
void gameoverwait();
void gameovercondition();//For AI to move 

void loadTutorialMap();
void loadBronzeMap();
void loadSteelMap();


void HiddenEntranceOne();
void HiddenEntranceTwo();
void HiddenEntranceThree();
void HiddenMap();

void RemoveHidden();
#endif // _GAME_H