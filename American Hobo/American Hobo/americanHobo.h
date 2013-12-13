#ifndef _AMERICANHOBO_H    
#define _AMERICANHOBO_H         
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "entity.h"
#include "hero.h"
#include "sword.h"
#include "hobo.h"
#include "menu.h"
#include "brawler.h"
#include "heart.h"
#include "thrower.h"

using std::string;



class AmericanHobo : public Game
{
private:
    // game items 

	Image menuScreen, textScreen;
	Image winButton, gameoverButton, playButton;
	Image hearts[5];
	Image transition1, transition2, transition3;

	Image streets, stadium, colosseum;
	Image titleScreen, controls, gameOver, win;
	Hero hero;
	Hobo hobo[HOBO_NUMBER];
	Brawler brawler[BRAWLER_NUMBER];
	Thrower thrower[THROWER_NUMBER];
	TextureManager streetsTM, stadiumTM, colosseumTM;
	TextureManager titleTM, controlsTM, transition1TM, transition2TM, transition3TM;
	TextureManager heroTexture, swordTexture, hoboTexture, brawlerTexture, throwerTexture, bottleTexture;
	TextureManager gameOverTexture, winTexture, heartTexture;

	GameStates gameStates;

	Menu *mainMenu;
	TextDX *timerFont;
	TextDX* killFont;

	int score;

	float timerCount;
	float timeInState;
	float spawnCooldown;
	int hoboSpawnCount;
	int brawlerSpawnCount;
	int throwerSpawnCount;
	int hobosActive;
	int brawlersActive;
	int throwersActive;
	int killCount;
	int currentLevel;
	bool returnDebounce;
	bool fKeyDebounce;

	int oldPlayerHealth;

	bool menu;
	bool text;
	bool gameStart;

	string introText;

	float textTimer;
	float textWait;

	bool scorePushed;

public:
    // Constructor
    AmericanHobo();
	TextDX *gameFont;
    // Destructor
    virtual ~AmericanHobo();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
	void gameStateUpdate();
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void initializeLevel1();
	void initializeLevel2();
	void initializeLevel3();
	void setScore(int newScore);
	void updateHearts();
	int getScore();
};

#endif
