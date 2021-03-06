#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>

void gameovercondition()
{
	renderGameOver();
}

void gameplayLevel1()
{                               // gameplay logic
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacterLevel1();    // moves the character, collision detection, physics, etc
	Level1AIMovement(); //AI movement
	Level1ItemInteractions();         // sound can be played here too.
	prisonerInteraction();
	levelonelose();
}

void gameplayLevel2()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacterLevel2();    // moves the character, collision detection, physics, etc
	Level2ItemInteractions();
	Level2AIMovement(); //AI movement 
	leveltwolose();
													  // sound can be played here too.
}

void gameplayLevel3()
{
	processUserInput();
	moveCharacterLevel3();
	Level3ItemInteractions();
	levelthreelose();
	Level3AIMovement();
	
}

void renderLevelOne()
{
	renderTutorialMap();  // renders the map to the buffer first
	renderCharacter();   // renders the character into the buffer
	renderArrowLevel1();
	renderDialogue();
	renderUserInterface(); //Renders the inventory
	prisonerInteraction();
}

void renderLevelTwo()
{
	renderBronzeMap(); // renders the map to the buffer first
	renderArrowLevel2();
	renderCharacter();   // renders the character into the buffer
	renderUserInterface();
	
}

void renderLevelThree()
{
	renderSteelMap();
	renderCharacter();
	renderLOS3();
	renderUserInterface();
}

