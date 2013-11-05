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
	if (!hero.initialize(graphics, 0, 0, 0, &heroTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hero"));

	hero.setX(GAME_WIDTH / 2);
	hero.setY(GAME_HEIGHT / 2);

	timerFont = new TextDX();

	if(timerFont->initialize(graphics, 30, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing timer font"));

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
		timerCount = 10;
	}
	if (gameStates == Level2 && timerCount < 0)
	{
		gameStates = Level3;
		timerCount = 15;
	}
	if (gameStates == Level3 && timerCount < 0)
	{
		gameStates = Menu;
		timerCount = 20;
	}
	if (gameStates == Menu && timerCount < 0)
	{
		gameStates = Level1;
		timerCount = 5;
	}
}

void AmericanHobo::update()
{	
	gameStateUpdate();
	switch (gameStates)
	{
	case Level1:

		break;
	case Level2:

		break;
	case Level3:

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
	std::stringstream s, s2;
	s << "Dummy Menu Screen";
	s2 << ceil(timerCount);
    graphics->spriteBegin();
	switch (gameStates)
	{
	case Level1:
		streets.draw();
		timerFont->print(s2.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 20);
		hero.draw();
		break;
	case Level2:
		stadium.draw();
		timerFont->print(s2.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 20);
		hero.draw();
		break;
	case Level3:
		colosseum.draw();
		timerFont->print(s2.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 20);
		hero.draw();
		break;
	case Menu:
		timerFont->print(s.str(), GAME_WIDTH / 2 - 100, GAME_HEIGHT / 20);
		timerFont->print(s2.str(), GAME_WIDTH / 2 - 15, GAME_HEIGHT / 10);
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
    Game::resetAll();
    return;
}
