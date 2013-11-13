#ifndef _AMERICANHOBO_H    
#define _AMERICANHOBO_H         
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "torpedo.h"
#include "entity.h"
#include "ship.h"
#include "turret.h"
#include "cybovine.h"
#include "hero.h"
#include "sword.h"
#include "hobo.h"
#include "menu.h"
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

	Ship ship;
	Cybovine cybovine;
	//
	Image streets, stadium, colosseum;
	Sword sword;
	Hero hero;
	Hobo hobo;
	TextureManager streetsTexture, stadiumTexture, colosseumTexture;
	TextureManager heroTexture, swordTexture, hoboTexture;

	GameStates gameStates;

	Menu *mainMenu;
	TextDX *timerFont;

	float timerCount;
	float timeInState;
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
};

#endif
