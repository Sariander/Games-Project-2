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
	spawned = false;
	//Initialize Streets Texture
	if (!streetsTM.initialize(graphics, STREETS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Streets texture!"));

	//Initialize Streets
	if (!streets.initialize(graphics, 0, 0, 0, &streetsTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Streets"));

	//Initialize Stadium Texture
	if (!stadiumTM.initialize(graphics, STADIUM_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Stadium texture!"));

	//Initialize Stadium
	if (!stadium.initialize(graphics, 0, 0, 0, &stadiumTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Stadium"));

	//Initialize Colosseum Texture
	if (!colosseumTM.initialize(graphics, COLOSSEUM_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Colosseum texture!"));

	//Initialize Colosseum
	if (!colosseum.initialize(graphics, 0, 0, 0, &colosseumTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Colosseum"));

	//Intialize Title Texture
	if (!titleTM.initialize(graphics, TITLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Title texture!"));

	//Intialize Title
	if (!titleScreen.initialize(graphics, 0, 0, 0, &titleTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Title"));

	//Intialize Controls Texture
	if (!controlsTM.initialize(graphics, CONTROLS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Controls texture!"));

	//Intialize Controls
	if (!controls.initialize(graphics, 0, 0, 0, &controlsTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Controls"));

	//Initialize Game Over Texture
	if (!gameOverTM.initialize(graphics, GAME_OVER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Game Over texture!"));

	//Initialize Game Over
	if (!gameOver.initialize(graphics, 0, 0, 0, &gameOverTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Game Over"));

	//Initialize Win Texture
	if (!winTM.initialize(graphics, WIN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Win texture!"));

	//Initialize Win
	if (!win.initialize(graphics, 0, 0, 0, &winTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Win"));

	//Initialize Hero Texture
	if (!heroTM.initialize(graphics, HERO_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Hero texture!"));

	//Initialize Heart Texture
	if (!heartTM.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing heart texture!"));

	int heartPos = 0;
	for(int i = 0; i<5; i++)
	{
		//Initialize Hearts
		if (!hearts[i].initialize(graphics, heartNS::WIDTH, heartNS::HEIGHT, 3, &heartTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hearts"));
		hearts[i].setY(GAME_HEIGHT/20);
		hearts[i].setX(heartPos + 50);
		heartPos += heartNS::WIDTH;
	}

	//Initialize Hero
	if (!hero.initialize(this, heroNS::WIDTH, heroNS::HEIGHT, heroNS::TEXTURE_COLS, &heroTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hero"));
	hero.setCollisionType(entityNS::BOX);
	hero.setEdge(COLLISION_BOX_HERO);
	hero.setX(GAME_WIDTH / 2);
	hero.setY(GAME_HEIGHT / 2);
	hero.setFrameDelay(heroNS::ANIMATION_DELAY);
	hero.setFrames(heroNS::STAND_RIGHT, heroNS::STAND_RIGHT);
	hero.setCurrentFrame(heroNS::STAND_RIGHT);

	//Initialize Sword Texture
	if (!swordTM.initialize(graphics, SWORD_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Sword texture!"));

	if (!hero.sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

	hero.sword.setCollisionType(entityNS::BOX);
	hero.sword.setEdge(COLLISION_BOX_SWORD);
	hero.sword.setX(GAME_WIDTH / 2 + 60);
	hero.sword.setY(GAME_HEIGHT / 2);

	//Initialize Hobo Texture
	if (!hoboTM.initialize(graphics, HOBO_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Hobo texture!"));

	for(int i=0; i<HOBO_NUMBER; i++)
	{
		//Initialize Hobo
		if (!hobo[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &hoboTM))
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

		if (!hobo[i].sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

		hobo[i].sword.setCollisionType(entityNS::BOX);
		hobo[i].sword.setEdge(COLLISION_BOX_SWORD);
	}

	//Initialize Brawler Texture
	if (!brawlerTM.initialize(graphics, BRAWLER_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Brawler texture!"));

	for(int i=0; i<BRAWLER_NUMBER; i++)
	{
		//initialize Brawler
		if (!brawler[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &brawlerTM))
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

		if (!brawler[i].sword.initialize(this, swordNS::WIDTH, swordNS::HEIGHT, swordNS::TEXTURE_COLS, &swordTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sword"));

		brawler[i].sword.setCollisionType(entityNS::BOX);
		brawler[i].sword.setEdge(COLLISION_BOX_SWORD);
	}

	//thrower texture
	if (!throwerTM.initialize(graphics, THROWER_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing thrower texture!"));

	//Initialize bottle Texture
	if (!bottleTM.initialize(graphics, MOLOTOV_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing molotov texture!"));

	for(int i=0; i<THROWER_NUMBER; i++)
	{
		//Initialize Thrower
		if (!thrower[i].initialize(this, hoboNS::WIDTH, hoboNS::HEIGHT, hoboNS::TEXTURE_COLS, &throwerTM))
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

		if (!thrower[i].bottle.initialize(this, bottleNS::WIDTH, bottleNS::HEIGHT, bottleNS::TEXTURE_COLS, &bottleTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));

		thrower[i].bottle.setCollisionType(entityNS::BOX);
		brawler[i].sword.setEdge(COLLISION_BOX_BOTTLE);
		thrower[i].bottle.setActive(false);
		thrower[i].bottle.setVisible(false);
	}
	//Initialize Boss Texture
	if (!bossTM.initialize(graphics, BOSS_CELS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Boss texture!"));

	//Initialize Boss
	if (!boss.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss"));
	boss.setCollisionType(entityNS::BOX);
	boss.setEdge(COLLISION_BOX_BOSS);
	boss.setX(GAME_WIDTH / 2);
	boss.setY(GAME_HEIGHT / 2 + 100);
	boss.setFrameDelay(bossNS::ANIMATION_DELAY);
	boss.setFrames(bossNS::BOSS_WALK_1, bossNS::BOSS_WALK_3);
	boss.setCurrentFrame(bossNS::BOSS_WALK_2);
	boss.setActive(false);
	boss.setVisible(false);

	//Initialize Boss Weapon Texture
	if (!bossWepTM.initialize(graphics, BOSS_WEP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing Boss texture!"));

	//Initialize Boss Weapon
	for (int i = 0; i < bossNS::NUM_BALLS; i++)
	{	/*
		if (!boss.sword[i].initialize(this, spikeballNS::WIDTH, spikeballNS::HEIGHT, spikeballNS::TEXTURE_COLS, &throwerTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));
		boss.sword[i].setCollisionType(entityNS::CIRCLE);
		boss.sword[i].setCollisionRadius(swordNS::WIDTH / 2);
		boss.sword[i].setActive(false);
		boss.sword[i].setVisible(false);
		*/
		if (!boss.spikeball[i].initialize(this, spikeballNS::WIDTH, spikeballNS::HEIGHT, spikeballNS::TEXTURE_COLS, &bossWepTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Hobo"));
		//boss.spikeball[i].setCollisionType(entityNS::BOX);
		//boss.spikeball[i].setCollisionRadius(swordNS::WIDTH / 2);
		boss.spikeball[i].setActive(false);
		boss.spikeball[i].setVisible(false);
		boss.spikeball[i].setX(boss.getX());
		boss.spikeball[i].setY(boss.getY());
	}

	//Intialize Transition 1 Texture
	if (!transition1TM.initialize(graphics, TRANSITION1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing transition1 texture!"));

	//Intialize Transition 1
	if (!transition1.initialize(graphics, 0, 0, 0, &transition1TM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Controls"));

	//Initialize Transition 2 Texture
	if (!transition2TM.initialize(graphics, TRANSITION2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing transition2 texture!"));

	//Initialize Transition 2
	if (!transition2.initialize(graphics, 0, 0, 0, &transition2TM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Controls"));

	//Initialize Transition 3 Texture
	if (!transition3TM.initialize(graphics, TRANSITION3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing transition2 texture!"));

	//Initialize Transition 3
	if (!transition3.initialize(graphics, 0, 0, 0, &transition3TM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Controls"));

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

	//Level Skip Cheat Code (F1)
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
	//Level Skip Cheat Code (F2)
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
	//Level Skip Cheat Code (F3)
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
	//Health Cheat Code (F4)
	if (input->isKeyDown(0x73) && !fKeyDebounce)
	{
		hero.heal();
	}
	//Hard coded title menu interface
	if (gameStates == Title && input->isKeyDown(VK_RETURN) && !returnDebounce)
	{
		if (mainMenu->getSelectedItem() == 0)
		{
			gameStates = Transition1;
			timerCount = 3;
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
	if (gameStates == Transition1 && timerCount < 0)
	{
		gameStates = Level1;
		currentLevel = 1;
		initializeLevel1();
		mainMenu->setMenuName(main);
		score = 0;
		hero.heal();
		scorePushed = false;
		spawned = false;
		returnDebounce = true;
	}
	//Go to menu after level 1
	if (gameStates == Level1 && killCount == 0)
	{
		gameStates = Transition2;
		mainMenu->setMenuName(main);
		currentLevel = 2;
		timerCount = 3;
	}
	if (gameStates == Transition2 && timerCount < 0)
	{
		gameStates = MenuScreen;
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
		gameStates = Transition3;
		mainMenu->setMenuName(main);
		currentLevel = 3;
		timerCount = 3;
	}
	if (gameStates == Transition3 && timerCount < 0)
	{
		gameStates = MenuScreen;
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
	if (gameStates == Level3 && killCount == 0 && boss.getHealth() == 0)
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
		hero.setColorTimer(0);
		hero.setCurrentFrame(heroNS::STAND_RIGHT);
		hero.setVelocity(D3DXVECTOR2(0, 0));
		hero.setHitTimer(0);
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
		hero.setColorTimer(0);
		hero.setCurrentFrame(heroNS::STAND_RIGHT);
		hero.setVelocity(D3DXVECTOR2(0, 0));
		hero.setHitTimer(0);
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
		hero.setColorTimer(0);
		hero.setCurrentFrame(heroNS::STAND_RIGHT);
		hero.setVelocity(D3DXVECTOR2(0, 0));
		hero.setHitTimer(0);
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

		for(int i=0; i<HOBO_NUMBER; i++)
		{
			hobo[i].update(frameTime);
		}
		for (int i = 0; i < BRAWLER_NUMBER; ++i)
		{
			brawler[i].update(frameTime);
		}

		for(int i=0; i<THROWER_NUMBER; i++)
		{
			thrower[i].update(frameTime);
			 
		}

		updateHearts();
		if (!spawned && gameStates == Level3)
		{
			boss.spawn(gameStates);
			spawned = true;
		}
		boss.update(frameTime);

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
	for(int i=0; i<HOBO_NUMBER; i++)
	{
		hobo[i].ai(frameTime, hero);
	}
	for(int i = 0; i < BRAWLER_NUMBER; i++) {
		brawler[i].ai(frameTime, hero);
	}
	for(int i=0; i<THROWER_NUMBER; i++)
	{
		thrower[i].ai(frameTime, hero);
	}
	boss.ai(frameTime, hero);
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

	if (boss.collidesWith(hero, collisionVector)) {
		hero.damage(SWORD, boss.getVelocity());
	}

	for (int i = 0; i < bossNS::NUM_BALLS; i++) {
		if (boss.spikeball[i].collidesWith(hero, collisionVector)) {
			hero.damage(SWORD, boss.spikeball[i].getVelocity());
			char buff[] = "HEY LISTEN!";
			OutputDebugString(buff);

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

	if(hero.sword.collidesWith(boss, collisionVector)) {
		if(boss.damage(SWORD, D3DXVECTOR2(0,0)))
		{
			killCount--;
			setScore(getScore() + 75);
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
	case Transition1:
		transition1.draw();
		break;
	case Transition2:
		transition2.draw();
		break;
	case Transition3:
		transition3.draw();
		break;
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
		boss.draw(frameTime);
		for (int i = 0; i < bossNS::NUM_BALLS; ++i)
		{
			//boss.sword[i].draw();
			boss.spikeball[i].draw();
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
	transition1TM.onLostDevice();
	transition2TM.onLostDevice();
	transition3TM.onLostDevice();
	streetsTM.onLostDevice();
	stadiumTM.onLostDevice();
	colosseumTM.onLostDevice();
	hoboTM.onLostDevice();
	heroTM.onLostDevice();
	brawlerTM.onLostDevice();
	swordTM.onLostDevice();
	heartTM.onLostDevice();
	throwerTM.onLostDevice();
	bossTM.onLostDevice();
	bossWepTM.onLostDevice();
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
	transition1TM.onResetDevice();
	transition2TM.onResetDevice();
	transition3TM.onResetDevice();
	streetsTM.onResetDevice();
	stadiumTM.onResetDevice();
	colosseumTM.onResetDevice();
	hoboTM.onResetDevice();
	heroTM.onResetDevice();
	brawlerTM.onResetDevice();
	swordTM.onResetDevice();
	heartTM.onResetDevice();
	throwerTM.onResetDevice();
	bossTM.onResetDevice();
	bossWepTM.onResetDevice();
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
