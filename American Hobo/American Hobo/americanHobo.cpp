#include "americanHobo.h"
#include <cmath>
#include <time.h>
#include <sstream>
using std::sprintf;


//=============================================================================
// Constructor
//=============================================================================
AmericanHobo::AmericanHobo()
{

}

//=============================================================================
// Destructor
//=============================================================================
AmericanHobo::~AmericanHobo()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void AmericanHobo::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	//Initialize Streets Texture
	if (!streetsTexture.initialize(graphics, STREETS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Streets texture!"));

	//Initialize Streets
	if (!streets.initialize(graphics, 0, 0, 0, &streetsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Streets"));

	//Initialize Stadium Texture
	if (!stadiumTexture.initialize(graphics, STADIUM_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Stadium texture!"));

	//Initialize Stadium
	if (!stadium.initialize(graphics, 0, 0, 0, &stadiumTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Stadium"));

	//Initialize Colosseum Texture
	if (!colosseumTexture.initialize(graphics, COLOSSEUM_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Colosseum texture!"));

	//Initialize Colosseum
	if (!colosseum.initialize(graphics, 0, 0, 0, &colosseumTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Colosseum"));

	//Initialize Hero Texture
	if (!heroTexture.initialize(graphics, HERO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Hero texture!"));

	//Initialize Hero
	if (!hero.initialize(this, 0, 0, 0, &heroTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hero"));
	hero.setCollisionType(entityNS::BOX);
	hero.setEdge(COLLISION_BOX_HERO);
	hero.setX(GAME_WIDTH / 2);
	hero.setY(GAME_HEIGHT / 2);

	//Initialize Sword Texture
	if (!swordTexture.initialize(graphics, SWORD_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Sword texture!"));

	//Initialize Sword
	/*if (!sword.initialize(this, 0, 0, 0, &swordTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

	sword.setCollisionType(entityNS::BOX);
	sword.setEdge(COLLISION_BOX_SWORD);
	sword.setX(GAME_WIDTH / 2 + 60);
	sword.setY(GAME_HEIGHT / 2);
	*/

	if (!hero.sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

	hero.sword.setCollisionType(entityNS::BOX);
	hero.sword.setEdge(COLLISION_BOX_SWORD);
	hero.sword.setX(GAME_WIDTH / 2 + 60);
	hero.sword.setY(GAME_HEIGHT / 2);


	//Initialize Hobo Texture
	if (!hoboTexture.initialize(graphics, HOBO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Hobo texture!"));

	//Initialize Hobo
	if (!hobo.initialize(this, 0, 0, 0, &hoboTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));
	hobo.setCollisionType(entityNS::BOX);
	hobo.setEdge(COLLISION_BOX_HOBO);
	hobo.setX(GAME_WIDTH / 3);
	hobo.setY(GAME_HEIGHT / 3);

	//Initialize Fonts
	timerFont = new TextDX();

	if(timerFont->initialize(graphics, 30, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing timer font"));

	//Initialize Menus
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	timeInState = 0;
	timerCount = 5;
	gameStates = Level1;
    return;
}



//=============================================================================
// Update all game items
//=============================================================================
void AmericanHobo::gameStateUpdate()
{
	timeInState += frameTime;
	timerCount -= frameTime;
	if (gameStates == Level1 && timerCount < 0)
	{
		gameStates = Level2;
		timerCount = 5;
	}
	if (gameStates == Level2 && timerCount < 0)
	{
		gameStates = Level3;
		timerCount = 5;
	}
	if (gameStates == Level3 && timerCount < 0)
	{
		gameStates = MenuScreen;
	}
	if (gameStates == MenuScreen && mainMenu->done)
	{
		gameStates = Level1;
		mainMenu->done = false;
		timerCount = 5;
	}
}

void AmericanHobo::update()
{	
	gameStateUpdate();
	switch (gameStates)
	{
	case Level1:
		hero.update(frameTime);
		//sword.update(frameTime);
		hobo.update(frameTime);
		break;
	case Level2:
		hero.update(frameTime);
		//sword.update(frameTime);
		hobo.update(frameTime);
		break;
	case Level3:
		hero.update(frameTime);
		//sword.update(frameTime);
		hobo.update(frameTime);
		break;
	case MenuScreen:
		mainMenu->update();
		break;
	}

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void AmericanHobo::ai(){}

//=============================================================================
// Handle collisions
//=============================================================================
void AmericanHobo::collisions()
{
	VECTOR2 collisionVector;
}


//=============================================================================
// Render game items
//=============================================================================
void AmericanHobo::render()
{
	std::stringstream s;
	s << ceil(timerCount);
    graphics->spriteBegin();
	switch (gameStates)
	{
	case Level1:
		streets.draw();
		timerFont->print(s.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 20);
		hero.draw();
		hero.sword.draw();
		hobo.draw();
		break;
	case Level2:
		stadium.draw();
		timerFont->print(s.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 20);
		hero.draw();
		hero.sword.draw();
		hobo.draw();
		break;
	case Level3:
		colosseum.draw();
		timerFont->print(s.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 20);
		hero.draw();
		hero.sword.draw();
		hobo.draw();
		break;
	case MenuScreen:
		mainMenu->displayMenu();
		break;
	}
    graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void AmericanHobo::releaseAll()
{
	streetsTexture.onLostDevice();
	stadiumTexture.onLostDevice();
	colosseumTexture.onLostDevice();
	mainMenu->releaseAll();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void AmericanHobo::resetAll()
{
	streetsTexture.onResetDevice();
	stadiumTexture.onResetDevice();
	colosseumTexture.onResetDevice();
	mainMenu->resetAll();
    Game::resetAll();
    return;
}
