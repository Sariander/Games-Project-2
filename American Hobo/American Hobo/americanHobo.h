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

using std::string;



class AmericanHobo : public Game
{
private:
    // game items 

	Image earth;
	Image menuScreen;
	Image textScreen;
	Image playButton;
	Image gameoverButton;
	Image winButton;

	Image streets, stadium, colosseum;
	Image title, controls;
	//Sword sword;
	Hero hero;
	Hobo hobo[10];
	Brawler brawler[10];
	TextureManager streetsTexture, stadiumTexture, colosseumTexture;
	TextureManager titleTexture, controlsTexture;
	TextureManager heroTexture, swordTexture, hoboTexture, brawlerTexture;

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
	int hobosActive;
	int brawlersActive;
	int killCount;
	int currentLevel;
	//
	TextureManager shipTexture; 
	TextureManager shotTexture, shipShotTexture;
	TextureManager earthTexture; 
	TextureManager baseTexture, eyeTexture;
	TextureManager turret1Texture, turret2Texture, turret3Texture, turret4Texture;
	TextureManager turret5Texture, turret6Texture, turret7Texture, turret8Texture;
	TextureManager milkShotTexture;
	TextureManager healthTexture, scoreTexture;
	TextureManager menuScreenTexture, textScreenTexture, playButtonTexture, gameoverButtonTexture, winTexture;
	TextureManager eyeblastTexture;

	bool menu;
	bool text;
	bool gameStart;

	string introText;

	float textTimer;
	float textWait;

	

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
	int getScore();
};

#endif
