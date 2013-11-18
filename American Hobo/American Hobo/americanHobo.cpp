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

	score = 0;
	hobosActive = 0;
	brawlersActive = 0;
	currentLevel = 1;
	returnDebounce = false;
	fKeyDebounce = false;
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

	//Initialize Game Over Texture
	if (!gameOverTexture.initialize(graphics, GAME_OVER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Game Over texture!"));

	//Initialize Game Over
	if (!gameOver.initialize(graphics, 0, 0, 0, &gameOverTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Game Over"));

	//Initialize Win Texture
	if (!winTexture.initialize(graphics, WIN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Win texture!"));

	//Initialize Win
	if (!win.initialize(graphics, 0, 0, 0, &winTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Win"));

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
	
	killCount = 0;
	gameStates = Title;

	audio->playCue(SOUNDTRACK);
    return;
}

void AmericanHobo::setScore(int newScore)
{
	score = newScore;
}
int AmericanHobo::getScore()
{
	return score;
}


//=============================================================================
// Update all game items
//=============================================================================
void AmericanHobo::gameStateUpdate()
{
	timerCount -= frameTime;
	if(!input->isKeyDown(VK_RETURN))
		returnDebounce = false;

	if(!input->isKeyDown(0x70) && !input->isKeyDown(0x71) && !input->isKeyDown(0x72))
		fKeyDebounce = false;

	if(input->isKeyDown(0x70) && !fKeyDebounce)
	{
		for(int i=0; i<10; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
			brawler[i].setActive(false);
			brawler[i].setVisible(false);
		}
		hero.heal();
		initializeLevel1();
		fKeyDebounce = true;
	}
	if(input->isKeyDown(0x71) && !fKeyDebounce)
	{
		for(int i=0; i<10; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
			brawler[i].setActive(false);
			brawler[i].setVisible(false);
		}
		hero.heal();
		initializeLevel2();
		fKeyDebounce = true;
	}
	if(input->isKeyDown(0x72) && !fKeyDebounce)
	{
		for(int i=0; i<10; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
			brawler[i].setActive(false);
			brawler[i].setVisible(false);
		}
		hero.heal();
		initializeLevel3();
		fKeyDebounce = true;
	}
	if (gameStates == Title && input->isKeyDown(VK_RETURN))
	{
		gameStates = Controls;
		timerCount = 5;
		returnDebounce = true;
	}
	if (gameStates == Controls && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		currentLevel = 1;
		initializeLevel1();
		returnDebounce = true;
	}
	if (gameStates == Level1 && killCount == 0)
	{
		gameStates = MenuScreen;
		currentLevel = 2;
	}
	if(gameStates == MenuScreen && currentLevel == 2 && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if(mainMenu->getSelectedItem() == 2)
			initializeLevel2();
		else
			if(hero.health < 10 && mainMenu->getCurrentMoney() > 200)
			{
				hero.health++;
				mainMenu->setCurrentMoney(mainMenu->getCurrentMoney() - 200);
				setScore(mainMenu->getCurrentMoney());
			}
		returnDebounce = true;
		//else
		//restore health
	}
	if (gameStates == Level2 && killCount == 0)
	{
		gameStates = MenuScreen;
		currentLevel = 3;
	}
	if(gameStates == MenuScreen && currentLevel == 3 && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if(mainMenu->getSelectedItem() == 2)
			initializeLevel3();
		else
			if(hero.health < 10 && mainMenu->getCurrentMoney() > 200)
			{
				hero.health++;
				mainMenu->setCurrentMoney(mainMenu->getCurrentMoney() - 200);
				setScore(mainMenu->getCurrentMoney());
			}
		returnDebounce = true;
	}
	if (gameStates == Level3 && killCount == 0)
	{
		gameStates = Win;
	}
	if (gameStates == MenuScreen && mainMenu->done)
	{
		gameStates = Level1;
		mainMenu->done = false;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
	}
	if (hero.getHealth() <= 0)
	{
		gameStates = GameOver;
		hero.heal();
		for (int i = 0; i<10; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
		}
		for (int i = 0; i<10; i++)
		{
			brawler[i].setActive(false);
			brawler[i].setVisible(false);
		}
		score = 0;
		mainMenu->setCurrentMoney(0);
	}
	if (gameStates == GameOver)
	{
		if (input->isKeyDown(VK_RETURN))
		{
			if (currentLevel == 1)
			{
				initializeLevel1();
			}
			if (currentLevel == 2)
			{
				initializeLevel2();
			}
			if (currentLevel == 3)
			{
				initializeLevel3();
			}
		}
	}
	if (gameStates == Win)
	{
		if (input->isKeyDown(VK_RETURN))
		{
			initializeLevel1();
		}
	}
	
}

void AmericanHobo::initializeLevel1()
{
		gameStates = Level1;
		killCount = LEVEL_1_KILLCOUNT;
		hoboSpawnCount = LEVEL_1_HOBOS;
		brawlerSpawnCount = LEVEL_1_BRAWLERS;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
}
void AmericanHobo::initializeLevel2()
{
		gameStates = Level2;
		killCount = LEVEL_2_KILLCOUNT;
		hoboSpawnCount = LEVEL_2_HOBOS;
		brawlerSpawnCount = LEVEL_2_BRAWLERS;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
}
void AmericanHobo::initializeLevel3()
{
		gameStates = Level3;
		killCount = LEVEL_3_KILLCOUNT;
		hoboSpawnCount = LEVEL_3_HOBOS;
		brawlerSpawnCount = LEVEL_3_BRAWLERS;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
}

void AmericanHobo::update()
{	
	gameStateUpdate();
	mainMenu->setCurrentMoney(score);
	spawnCooldown -= frameTime;
	switch (gameStates)
	{
	case Title:

		break;
	case Controls:

		break;
	case Level1:
	case Level2:
	case Level3:
		hero.update(frameTime);
		//sword.update(frameTime);
		//spawn hobos and brawlers
		if (spawnCooldown < 0 && (hoboSpawnCount > 0 || brawlerSpawnCount > 0))
		{
			if(hoboSpawnCount > 0)
			{
				for(int i = 0; i<HOBO_NUMBER; i++)
				{
					if(!hobo[i].getActive())
					{
						hobo[i].spawn(gameStates);
						hoboSpawnCount--;
						break;
					}
				}
			}
			if(brawlerSpawnCount > 0)
			{
				for(int i = 0; i<BRAWLER_NUMBER; i++)
				{
					if(!brawler[i].getActive())
					{
						brawler[i].spawn(gameStates);
						brawlerSpawnCount--;
						break;
					}
				}
			}
			spawnCooldown = 2;
		}

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

	for(int i = 0; i < 10; i++) {
		if(hobo[i].collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, hobo[i].getVelocity());
		}
	}

	for(int i = 0; i < 10; i++) {
		if(brawler[i].collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, brawler[i].getVelocity());

		}
	}

	for(int i = 0; i < 10; i++) {
		if(hero.sword.collidesWith(hobo[i],collisionVector)) {
			switch(hero.dir) {
			case 0:
				break;
			case 1:
				if(hobo[i].damage(SWORD, D3DXVECTOR2(-1,0)))
				{
					killCount--;
					setScore(getScore() + 50);
				}
				break;
			case 2:
				if(hobo[i].damage(SWORD, D3DXVECTOR2(1,0)))
				{
					killCount--;
					setScore(getScore() + 50);
				}
				break;
			case 3:
				if(hobo[i].damage(SWORD, D3DXVECTOR2(0,1)))
				{
					killCount--;
					setScore(getScore() + 50);
				}
				break;
			case 4:
				if(hobo[i].damage(SWORD, D3DXVECTOR2(0,-1)))
				{
					killCount--;
					setScore(getScore() + 50);
				}
				break;
			}
		}
	}

		for(int i = 0; i < 10; i++) {
		if(hero.sword.collidesWith(brawler[i],collisionVector)) {
			switch(hero.dir) {
			case 0:
				break;
			case 1:
				if(brawler[i].damage(SWORD, D3DXVECTOR2(-1,0)))
				{
					killCount--;
					setScore(getScore() + 100);
				}
				break;
			case 2:
				if(brawler[i].damage(SWORD, D3DXVECTOR2(1,0)))
				{
					killCount--;
					setScore(getScore() + 100);
				}
				break;
			case 3:
				if(brawler[i].damage(SWORD, D3DXVECTOR2(0,1)))
				{
					killCount--;
					setScore(getScore() + 100);
				}
				break;
			case 4:
				if(brawler[i].damage(SWORD, D3DXVECTOR2(0,-1)))
				{
					killCount--;
					setScore(getScore() + 100);
				}
				break;
			}
		}
	}
}


//=============================================================================
// Render game items
//=============================================================================
void AmericanHobo::render()
{
	std::stringstream s;
	s << "Score: " << score << "         Kills remaining: " << killCount << "              Health: " << hero.getHealth();
    graphics->spriteBegin();
	switch (gameStates)
	{
	case Win:
		win.draw();
		break;
	case GameOver:
		gameOver.draw();
		break;
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
		hero.draw(frameTime);
		hero.sword.draw();
		for(int i=0; i<10; i++)
		{
			hobo[i].draw(frameTime);
			brawler[i].draw(frameTime);
		}
		killFont->print(s.str(), GAME_WIDTH / 4 - 75, GAME_HEIGHT / 20);
		break;
	case Level2:
		stadium.draw();
		hero.draw(frameTime);
		hero.sword.draw();
		for(int i=0; i<10; i++)
		{
			hobo[i].draw(frameTime);
			brawler[i].draw(frameTime);
		}
		killFont->print(s.str(), GAME_WIDTH / 4 - 75, GAME_HEIGHT / 20);
		break;
	case Level3:
		colosseum.draw();
		hero.draw(frameTime);
		hero.sword.draw();
		for(int i=0; i<10; i++)
		{
			hobo[i].draw(frameTime);
			brawler[i].draw(frameTime);
		}
		killFont->print(s.str(), GAME_WIDTH / 4 - 75, GAME_HEIGHT / 20);
		break;
	case MenuScreen:
		mainMenu->displayMenu();
		std::stringstream j;
		j << "Score: " << score << "       Health: " << hero.getHealth();
		killFont->print(s.str(), GAME_WIDTH / 4 - 75, GAME_HEIGHT / 20);
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
