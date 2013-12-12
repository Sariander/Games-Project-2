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
	oldPlayerHealth = heroNS::HEALTH_MAX;
	currentLevel = 1;
	returnDebounce = false;
	fKeyDebounce = false;
	scorePushed = false;
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
	if (!titleScreen.initialize(graphics, 0, 0, 0, &titleTexture))
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

	//Initialize Heart Texture
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing heart texture!"));

	int heartPos = 0;
	for(int i = 0; i<5; i++)
	{
		//Initialize Hearts
		if (!hearts[i].initialize(graphics, heartNS::WIDTH, heartNS::HEIGHT, 3, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hearts"));
		hearts[i].setY(GAME_HEIGHT/20);
		hearts[i].setX(heartPos + 50);
		heartPos += heartNS::WIDTH;
	}

	//Initialize Hero
	if (!hero.initialize(this, heroNS::WIDTH, heroNS::HEIGHT, heroNS::TEXTURE_COLS, &heroTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hero"));
	hero.setCollisionType(entityNS::BOX);
	hero.setEdge(COLLISION_BOX_HERO_STANDING);
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


	for(int i=0; i<HOBO_NUMBER; i++)
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

		if (!hobo[i].sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

		hobo[i].sword.setCollisionType(entityNS::BOX);
		hobo[i].sword.setEdge(COLLISION_BOX_SWORD);
	}

	//Initialize Brawler Texture
	if (!brawlerTexture.initialize(graphics, BRAWLER_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Brawler texture!"));

	for(int i=0; i<BRAWLER_NUMBER; i++)
	{
		//initialize Brawler
		if (!brawler[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &brawlerTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Brawler"));
		brawler[i].setCollisionType(entityNS::BOX);
		brawler[i].setEdge(COLLISION_BOX_BRAWLER);
		brawler[i].setPosition(VECTOR2(brawlerNS::X, brawlerNS::Y));
		brawler[i].setX(brawler[i].getPositionX());
		brawler[i].setY(brawler[i].getPositionY());

		brawler[i].setFrameDelay(hoboNS::ANIMATION_DELAY);
		brawler[i].setFrames(hoboNS::RIGHT_WALK_START, hoboNS::RIGHT_WALK_END);
		brawler[i].setCurrentFrame(hoboNS::RIGHT_WALK_START);

		brawler[i].setActive(false);
		brawler[i].setVisible(false);

		if (!brawler[i].sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

		brawler[i].sword.setCollisionType(entityNS::BOX);
		brawler[i].sword.setEdge(COLLISION_BOX_SWORD);
	}

	//thrower texture
	if (!throwerTexture.initialize(graphics, THROWER_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing thrower texture!"));

	//Initialize bottle Texture
	if (!bottleTexture.initialize(graphics, MOLOTOV_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing molotov texture!"));

	for(int i=0; i<THROWER_NUMBER; i++)
	{
		//Initialize Thrower
		if (!thrower[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &throwerTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));
		thrower[i].setCollisionType(entityNS::BOX);
		thrower[i].setEdge(COLLISION_BOX_THROWER);
		thrower[i].setPosition(VECTOR2(hoboNS::X, hoboNS::Y));
		thrower[i].setX(hobo[i].getPositionX());
		thrower[i].setY(hobo[i].getPositionY());

		thrower[i].setFrameDelay(hoboNS::ANIMATION_DELAY);
		thrower[i].setFrames(hoboNS::RIGHT_WALK_START, hoboNS::RIGHT_WALK_END);
		thrower[i].setCurrentFrame(hoboNS::RIGHT_WALK_START);

		thrower[i].setActive(false);
		thrower[i].setVisible(false);

		if (!thrower[i].bottle.initialize(this, bottleNS::WIDTH, bottleNS::HEIGHT, bottleNS::TEXTURE_COLS, &bottleTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));

		thrower[i].bottle.setCollisionType(entityNS::BOX);
		brawler[i].sword.setEdge(COLLISION_BOX_BOTTLE);
		thrower[i].bottle.setActive(false);
		thrower[i].bottle.setVisible(false);
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
		for (int i = 0; i < HOBO_NUMBER; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
		}
		for (int i = 0; i < BRAWLER_NUMBER; i++)
		{
			brawler[i].setActive(false);
			brawler[i].setVisible(false);

		}
		for (int i = 0; i < THROWER_NUMBER; i++)
		{
			thrower[i].setActive(false);
			thrower[i].setVisible(false);
		}
		hero.heal();
		initializeLevel1();
		fKeyDebounce = true;
	}
	if(input->isKeyDown(0x71) && !fKeyDebounce)
	{
		for (int i = 0; i < HOBO_NUMBER; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
		}
		for (int i = 0; i < BRAWLER_NUMBER; i++)
		{
			brawler[i].setActive(false);
			brawler[i].setVisible(false);

		}
		for (int i = 0; i < THROWER_NUMBER; i++)
		{
			thrower[i].setActive(false);
			thrower[i].setVisible(false);
		}
		hero.heal();
		initializeLevel2();
		fKeyDebounce = true;
	}
	if(input->isKeyDown(0x72) && !fKeyDebounce)
	{
		for (int i = 0; i < HOBO_NUMBER; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
		}
		for (int i = 0; i < BRAWLER_NUMBER; i++)
		{
			brawler[i].setActive(false);
			brawler[i].setVisible(false);

		}
		for (int i = 0; i < THROWER_NUMBER; i++)
		{
			thrower[i].setActive(false);
			thrower[i].setVisible(false);
		}
		hero.heal();
		initializeLevel3();
		fKeyDebounce = true;
	}
	//Hard coded title menu interface
	if (gameStates == Title && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if (mainMenu->getSelectedItem() == 0)
		{
			gameStates = Level1;
			currentLevel = 1;
			initializeLevel1();
			mainMenu->setMenuName(main);
			score = 0;
			hero.heal();
			scorePushed = false;
			returnDebounce = true;
		}
		else if (mainMenu->getSelectedItem() == 1)
		{
			gameStates = Controls;
			returnDebounce = true;
		}
		else if (mainMenu->getSelectedItem() == 2)
		{
			PostQuitMessage(1);
		}
	}
	//Leave controls screen
	if (gameStates == Controls && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		gameStates = Title;
		returnDebounce = true;
	}
	//Go to menu after level 1
	if (gameStates == Level1 && killCount == 0)
	{
		gameStates = MenuScreen;
		mainMenu->setMenuName(main);
		currentLevel = 2;
	}
	//Hardcoded menu after level 1
	if(gameStates == MenuScreen && currentLevel == 2 && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if (mainMenu->getSelectedItem() == 1)
		{
			if (hero.health < 10 && mainMenu->getCurrentMoney() >= 200)
			{
				hero.health++;
				mainMenu->setCurrentMoney(mainMenu->getCurrentMoney() - 200);
				setScore(mainMenu->getCurrentMoney());
			}
		}
		if (mainMenu->getSelectedItem() == 2)
		{
			//Give projectile ammo
		}
		if (mainMenu->getSelectedItem() == 3)
		{
			initializeLevel2();
		}
		returnDebounce = true;
	}
	//Go to menu after level 2
	if (gameStates == Level2 && killCount == 0)
	{
		gameStates = MenuScreen;
		mainMenu->setMenuName(main);
		currentLevel = 3;
	}
	//Hardcoded menu after level 2
	if(gameStates == MenuScreen && currentLevel == 3 && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if (mainMenu->getSelectedItem() == 1)
		{
			if (hero.health < 10 && mainMenu->getCurrentMoney() >= 200)
			{
				hero.health++;
				mainMenu->setCurrentMoney(mainMenu->getCurrentMoney() - 200);
				setScore(mainMenu->getCurrentMoney());
			}
		}
		if (mainMenu->getSelectedItem() == 2)
		{
			//Give projectile ammo
		}
		if (mainMenu->getSelectedItem() == 3)
		{
			initializeLevel3();
		}
		returnDebounce = true;
	}
	//Win afetr level 3
	if (gameStates == Level3 && killCount == 0)
	{
		gameStates = Win;
	}
	//Deprecated currently by hard coded menu
	if (gameStates == MenuScreen && mainMenu->done)
	{
		gameStates = Level1;
		mainMenu->done = false;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
	}
	//Death response
	if (hero.getHealth() <= 0)
	{
		gameStates = GameOver;
		mainMenu->setMenuName(retry);
		hero.heal();
		for (int i = 0; i<HOBO_NUMBER; i++)
		{
			hobo[i].setActive(false);
			hobo[i].setVisible(false);
			hobo[i].setHealth(hoboNS::HEALTH_MAX);
		}
		for (int i = 0; i<BRAWLER_NUMBER; i++)
		{
			brawler[i].setActive(false);
			brawler[i].setVisible(false);
			brawler[i].setHealth(brawlerNS::HEALTH_MAX);
		}
		for (int i = 0; i<THROWER_NUMBER; i++)
		{
			thrower[i].setActive(false);
			thrower[i].setVisible(false);
			thrower[i].setHealth(throwerNS::HEALTH_MAX);
		}
		score = 0;
		mainMenu->setCurrentMoney(0);
	}
	//Retry code
	if (gameStates == GameOver && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if (mainMenu->getSelectedItem() == 0)
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
		else if (mainMenu->getSelectedItem() == 1)
		{
			PostQuitMessage(1);
		}
	}
	//Cycle back to level 1 currently, change to send back to title menu screen
	if (gameStates == Win && !returnDebounce)
	{
		if (!scorePushed)
		{
			string s;
			stringstream temp;
			temp << score;
			s = temp.str();
			scorePushed = true;
			mainMenu->scoreScreen.push_back(s);
		}
		if (input->isKeyDown(VK_RETURN))
		{
			gameStates = ScoreScreen;
			mainMenu->setMenuName(scores);
			returnDebounce = true;
		}
	}
	if (gameStates == ScoreScreen && !returnDebounce)
	{
		if (input->isKeyDown(VK_RETURN))
		{
			gameStates = Title;
			mainMenu->setMenuName(title);
			returnDebounce = true;
		}
	}
}

void AmericanHobo::initializeLevel1()
{
		gameStates = Level1;
		killCount = LEVEL_1_KILLCOUNT;
		hoboSpawnCount = LEVEL_1_HOBOS;
		brawlerSpawnCount = LEVEL_1_BRAWLERS;
		throwerSpawnCount = LEVEL_1_THROWERS;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
}
void AmericanHobo::initializeLevel2()
{
		gameStates = Level2;
		killCount = LEVEL_2_KILLCOUNT;
		hoboSpawnCount = LEVEL_2_HOBOS;
		brawlerSpawnCount = LEVEL_2_BRAWLERS;
		throwerSpawnCount = LEVEL_2_THROWERS;
		hero.setX(GAME_WIDTH / 2);
		hero.setY(GAME_HEIGHT / 2);
}
void AmericanHobo::initializeLevel3()
{
		gameStates = Level3;
		killCount = LEVEL_3_KILLCOUNT;
		hoboSpawnCount = LEVEL_3_HOBOS;
		brawlerSpawnCount = LEVEL_3_BRAWLERS;
		throwerSpawnCount = LEVEL_3_THROWERS;
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
	case GameOver:
		mainMenu->update();
		break;
	case Controls:

		break;
	case Level1:
	case Level2:
	case Level3:
		hero.update(frameTime);
		//sword.update(frameTime);
		//spawn hobos and brawlers
		if (spawnCooldown < 0 && (hoboSpawnCount > 0 || brawlerSpawnCount > 0 || throwerSpawnCount >0))
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
			if(throwerSpawnCount > 0)
			{
				for(int i = 0; i<THROWER_NUMBER; i++)
				{
					if(!thrower[i].getActive())
					{
						thrower[i].spawn(gameStates);
						throwerSpawnCount--;
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
		for(int i=0; i<THROWER_NUMBER; i++)
		{
			thrower[i].update(frameTime);
		}

		
		updateHearts();
		
		break;

	case MenuScreen:
		mainMenu->update();
		updateHearts();

		break;
	case ScoreScreen:

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
	for(int i=0; i<THROWER_NUMBER; i++)
	{
		thrower[i].ai(frameTime, hero);
	}
}

//=============================================================================
// Handle collisions
//=============================================================================
void AmericanHobo::collisions()
{
	VECTOR2 collisionVector;

	for(int i = 0; i < HOBO_NUMBER; i++) {
		if(hobo[i].collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, hobo[i].getVelocity());
		}
	}

	for(int i = 0; i < BRAWLER_NUMBER; i++) {
		if(brawler[i].collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, brawler[i].getVelocity());

		}
	}

	for(int i = 0; i < THROWER_NUMBER; i++) {
		if(thrower[i].collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, -thrower[i].getVelocity());

		}
	}

	for(int i = 0; i < HOBO_NUMBER; i++) {
		if(hobo[i].sword.collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, hobo[i].getVelocity());
		}
	}

	for(int i = 0; i < BRAWLER_NUMBER; i++) {
		if(brawler[i].sword.collidesWith(hero,collisionVector)) {
			hero.damage(SWORD, brawler[i].getVelocity());

		}
	}

	for (int i = 0; i < THROWER_NUMBER; i++) {
		if (thrower[i].bottle.collidesWith(hero, collisionVector)) {
			hero.damage(SWORD, thrower[i].getVelocity());

		}
	}

	for(int i = 0; i < HOBO_NUMBER; i++) {
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

		for(int i = 0; i < BRAWLER_NUMBER; i++) {
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

	for(int i = 0; i < THROWER_NUMBER; i++) {
		if(hero.sword.collidesWith(thrower[i],collisionVector)) {
			switch(hero.dir) {
			case 0:
				break;
			case 1:
				if(thrower[i].damage(SWORD, D3DXVECTOR2(-1,0)))
				{
					killCount--;
					setScore(getScore() + 75);
				}
				break;
			case 2:
				if(thrower[i].damage(SWORD, D3DXVECTOR2(1,0)))
				{
					killCount--;
					setScore(getScore() + 75);
				}
				break;
			case 3:
				if(thrower[i].damage(SWORD, D3DXVECTOR2(0,1)))
				{
					killCount--;
					setScore(getScore() + 75);
				}
				break;
			case 4:
				if(thrower[i].damage(SWORD, D3DXVECTOR2(0,-1)))
				{
					killCount--;
					setScore(getScore() + 75);
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
	s << "Score: " << score << "         Kills remaining: " << killCount;
    graphics->spriteBegin();
	switch (gameStates)
	{
	case Win:
		win.draw();
		break;
	case GameOver:
		gameOver.draw();
		mainMenu->displayMenu();
		break;
	case Title:
		titleScreen.draw();
		//timerFont->print("Press Enter to continue", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 8);
		mainMenu->displayMenu();
		break;
	case Controls:
		controls.draw();
		timerFont->print("Press Enter to continue", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 8);
		break;
	case ScoreScreen:
		mainMenu->displayMenu();
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
		for(int i=0; i<THROWER_NUMBER; i++)
		{
			thrower[i].draw(frameTime);
		}
		killFont->print(s.str(), GAME_WIDTH / 2 - 100, GAME_HEIGHT / 20);
		for(int i=0; i<5; i++)
		{
			hearts[i].draw();
		}
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
		for(int i=0; i<THROWER_NUMBER; i++)
		{
			thrower[i].draw(frameTime);
		}
		killFont->print(s.str(), GAME_WIDTH / 2 - 100, GAME_HEIGHT / 20);
		for(int i=0; i<5; i++)
		{
			hearts[i].draw();
		}
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
		for(int i=0; i<THROWER_NUMBER; i++)
		{
			thrower[i].draw(frameTime);
		}
		killFont->print(s.str(), GAME_WIDTH / 2 - 100, GAME_HEIGHT / 20);
		for(int i=0; i<5; i++)
		{
			hearts[i].draw();
		}
		break;
	case MenuScreen:
		mainMenu->displayMenu();
		std::stringstream j;
		j << "Score: " << score;
		killFont->print(j.str(), GAME_WIDTH / 2 - 100, GAME_HEIGHT / 20);
		for(int i=0; i<5; i++)
		{
			hearts[i].draw();
		}
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
	heartTexture.onLostDevice();
	throwerTexture.onLostDevice();
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
	heartTexture.onResetDevice();
	throwerTexture.onResetDevice();
	mainMenu->resetAll();
    Game::resetAll();
    return;
}

void AmericanHobo::updateHearts()
{
	if(oldPlayerHealth != hero.getHealth())
	{
			oldPlayerHealth = hero.getHealth();
			switch(oldPlayerHealth)
			{
			case 1:
				hearts[0].setCurrentFrame(1);
				hearts[1].setCurrentFrame(2);
				hearts[2].setCurrentFrame(2);
				hearts[3].setCurrentFrame(2);
				hearts[4].setCurrentFrame(2);
				break;
			case 2:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(2);
				hearts[2].setCurrentFrame(2);
				hearts[3].setCurrentFrame(2);
				hearts[4].setCurrentFrame(2);
				break;
			case 3:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(1);
				hearts[2].setCurrentFrame(2);
				hearts[3].setCurrentFrame(2);
				hearts[4].setCurrentFrame(2);
				break;
			case 4:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(2);
				hearts[3].setCurrentFrame(2);
				hearts[4].setCurrentFrame(2);
				break;
			case 5:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(1);
				hearts[3].setCurrentFrame(2);
				hearts[4].setCurrentFrame(2);
				break;
			case 6:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(0);
				hearts[3].setCurrentFrame(2);
				hearts[4].setCurrentFrame(2);
				break;
			case 7:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(0);
				hearts[3].setCurrentFrame(1);
				hearts[4].setCurrentFrame(2);
				break;
			case 8:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(0);
				hearts[3].setCurrentFrame(0);
				hearts[4].setCurrentFrame(2);
				break;
			case 9:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(0);
				hearts[3].setCurrentFrame(0);
				hearts[4].setCurrentFrame(1);
				break;
			case 10:
				hearts[0].setCurrentFrame(0);
				hearts[1].setCurrentFrame(0);
				hearts[2].setCurrentFrame(0);
				hearts[3].setCurrentFrame(0);
				hearts[4].setCurrentFrame(0);
				break;
			}
	}
}
