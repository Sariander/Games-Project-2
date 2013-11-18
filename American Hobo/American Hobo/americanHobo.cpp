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

	hobosActive = 0;
	brawlersActive = 0;
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

	//Intialize Title Texture
	if (!titleTexture.initialize(graphics, TITLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Title texture!"));

	//Intialize Title
	if (!title.initialize(graphics, 0, 0, 0, &titleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Title"));

	//Intialize Controls Texture
	if (!controlsTexture.initialize(graphics, CONTROLS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Controls texture!"));

	//Intialize Controls
	if (!controls.initialize(graphics, 0, 0, 0, &controlsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Controls"));

	//Initialize Hero Texture
	if (!heroTexture.initialize(graphics, HERO_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Hero texture!"));

	//Initialize Hero
	if (!hero.initialize(this, heroNS::WIDTH, heroNS::HEIGHT, heroNS::TEXTURE_COLS, &heroTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hero"));
	hero.setCollisionType(entityNS::BOX);
	hero.setEdge(COLLISION_BOX_HERO);
	hero.setX(GAME_WIDTH / 2);
	hero.setY(GAME_HEIGHT / 2);
	hero.setFrameDelay(heroNS::ANIMATION_DELAY);
	hero.setFrames(heroNS::STAND_RIGHT, heroNS::STAND_RIGHT);
	hero.setCurrentFrame(heroNS::STAND_RIGHT);


	//Initialize Sword Texture
	if (!swordTexture.initialize(graphics, SWORD_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Sword texture!"));

	if (!hero.sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

	hero.sword.setCollisionType(entityNS::BOX);
	hero.sword.setEdge(COLLISION_BOX_SWORD);
	hero.sword.setX(GAME_WIDTH / 2 + 60);
	hero.sword.setY(GAME_HEIGHT / 2);


	//Initialize Hobo Texture
	if (!hoboTexture.initialize(graphics, HOBO_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Hobo texture!"));


	for(int i=0; i<10; i++)
	{
		//Initialize Hobo
		if (!hobo[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &hoboTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));
		hobo[i].setCollisionType(entityNS::BOX);
		hobo[i].setEdge(COLLISION_BOX_HOBO);
		hobo[i].setPosition(VECTOR2(hoboNS::X, hoboNS::Y));
		hobo[i].setX(hobo[i].getPositionX());
		hobo[i].setY(hobo[i].getPositionY());

		hobo[i].setFrameDelay(hoboNS::ANIMATION_DELAY);
		hobo[i].setFrames(hoboNS::RIGHT_WALK_START, hoboNS::RIGHT_WALK_END);
		hobo[i].setCurrentFrame(hoboNS::RIGHT_WALK_START);

		hobo[i].setActive(false);
		hobo[i].setVisible(false);
	}

	//Initialize Brawler Texture
	if (!brawlerTexture.initialize(graphics, BRAWLER_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Brawler texture!"));

	for(int i=0; i<10; i++)
	{
		//initialize Brawler
		if (!brawler[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &brawlerTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Brawler"));
		brawler[i].setCollisionType(entityNS::BOX);
		brawler[i].setEdge(COLLISION_BOX_HOBO);
		brawler[i].setPosition(VECTOR2(brawlerNS::X, brawlerNS::Y));
		brawler[i].setX(brawler[i].getPositionX());
		brawler[i].setY(brawler[i].getPositionY());

		brawler[i].setFrameDelay(hoboNS::ANIMATION_DELAY);
		brawler[i].setFrames(hoboNS::RIGHT_WALK_START, hoboNS::RIGHT_WALK_END);
		brawler[i].setCurrentFrame(hoboNS::RIGHT_WALK_START);

		brawler[i].setActive(false);
		brawler[i].setVisible(false);
	}

	//Initialize Fonts
	timerFont = new TextDX();
	killFont = new TextDX();

	if(timerFont->initialize(graphics, 30, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing timer font"));

	if (killFont->initialize(graphics, 25, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing kill font"));

	//Initialize Menus
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	timerCount = 3;
	spawnCooldown = 2;
	spawnCount = 0;
	killCount = 1;
	gameStates = Title;
    return;
}



//=============================================================================
// Update all game items
//=============================================================================
void AmericanHobo::gameStateUpdate()
{
	timerCount -= frameTime;
	if (gameStates == Title && input->isKeyDown(VK_RETURN))
	{
		timerCount = 0;
	}
	if (gameStates == Title && timerCount < 0)
	{
		gameStates = Controls;
		timerCount = 7;
	}
	if (gameStates == Controls && input->isKeyDown(VK_RETURN))
	{
		timerCount = 0;
	}
	if (gameStates == Controls && timerCount < 0)
	{
		gameStates = Level1;
		timerCount = 5;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
	}
	if (gameStates == Level1 && killCount < 0)
	{
		gameStates = Level2;
		killCount = 15;
		timerCount = 5;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
	}
	if (gameStates == Level2 && killCount < 0)
	{
		gameStates = Level3;
		killCount = 15;
		timerCount = 5;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
	}
	if (gameStates == Level3 && killCount < 0)
	{
		gameStates = MenuScreen;
	}
	if (gameStates == MenuScreen && mainMenu->done)
	{
		gameStates = Level1;
		mainMenu->done = false;
		timerCount = 5;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
	}
}

void AmericanHobo::update()
{	
	gameStateUpdate();
	spawnCooldown -= frameTime;
	switch (gameStates)
	{
	case Title:

		break;
	case Controls:

		break;
	case Level1:
		hero.update(frameTime);
		//sword.update(frameTime);
		if (spawnCooldown < 0 && spawnCount < 10)
		{
			hobo[spawnCount].setActive(true);
			hobo[spawnCount].setVisible(true);
			spawnCount++;
			spawnCooldown = 2;
		}
		for(int i=0; i<10; i++)
		{
			hobo[i].update(frameTime);
			brawler[i].update(frameTime);
		}
		break;
	case Level2:
		hero.update(frameTime);
		//sword.update(frameTime);
		for(int i=0; i<10; i++)
		{
			hobo[i].update(frameTime);
			brawler[i].update(frameTime);
		}
		break;
	case Level3:
		hero.update(frameTime);
		//sword.update(frameTime);
		for(int i=0; i<10; i++)
		{
			hobo[i].update(frameTime);
			brawler[i].update(frameTime);
		}
		break;
	case MenuScreen:
		mainMenu->update();
		break;
	}

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void AmericanHobo::ai()
{
	for(int i=0; i<10; i++)
	{
		hobo[i].ai(frameTime, hero);
		brawler[i].ai(frameTime, hero);
	}
}

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
	s << "Kills remaining: " << killCount;
    graphics->spriteBegin();
	switch (gameStates)
	{
	case Title:
		title.draw();
		timerFont->print("Press Enter to continue", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 8);
		break;
	case Controls:
		controls.draw();
		timerFont->print("Press Enter to continue", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 8);
		break;
	case Level1:
		streets.draw();
		killFont->print(s.str(), GAME_WIDTH / 2 - 75, GAME_HEIGHT / 20);
		hero.draw();
		hero.sword.draw();
		for(int i=0; i<10; i++)
		{
			hobo[i].draw();
			brawler[i].draw();
		}
		break;
	case Level2:
		stadium.draw();
		killFont->print(s.str(), GAME_WIDTH / 2 - 75, GAME_HEIGHT / 20);
		hero.draw();
		hero.sword.draw();
		for(int i=0; i<10; i++)
		{
			hobo[i].draw();
			brawler[i].draw();
		}
		break;
	case Level3:
		colosseum.draw();
		killFont->print(s.str(), GAME_WIDTH / 2 - 75, GAME_HEIGHT / 20);
		hero.draw();
		hero.sword.draw();
		for(int i=0; i<10; i++)
		{
			hobo[i].draw();
			brawler[i].draw();
		}
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
	hoboTexture.onLostDevice();
	heroTexture.onLostDevice();
	brawlerTexture.onLostDevice();
	swordTexture.onLostDevice();
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
	hoboTexture.onResetDevice();
	heroTexture.onResetDevice();
	brawlerTexture.onResetDevice();
	swordTexture.onResetDevice();
	mainMenu->resetAll();
    Game::resetAll();
    return;
}
