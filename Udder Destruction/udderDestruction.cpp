#include "udderDestruction.h"
#include <cmath>
#include <time.h>
#include <sstream>
using std::sprintf;


//=============================================================================
// Constructor
//=============================================================================
UdderDestruction::UdderDestruction()
{
	textWait = .50f;
	textTimer = 0.0f;
	
	introText = "Help us Milk Man, you are Earth’s only hope!\nThere is an evil Cyborg Bovine on a collision course with Earth!\n";
	introText.append("You must shoot it down before it gets too close or all of Earth will be lost!\nWe have retrofitted your milk delivery van with engines and a laser cannon.\n\n");
	introText.append("The controls are very simple, press the “left arrow key” button to strafe the ship to the\n left. Press the “right arrow key” button to strafe the ship to the right.\n\n");
	introText.append("To shoot the laser cannon, just press the “up arrow key” button.\nNow get out there Milk Man, you and your van are the only thing that can stop the \nCybovine from having its Milky Way with Earth!\n\n");
	introText.append("Press Enter to begin the battle!");
	
	gameStart = true;
}

//=============================================================================
// Destructor
//=============================================================================
UdderDestruction::~UdderDestruction()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void UdderDestruction::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    //Initialize Earth Texture
    if (!earthTexture.initialize(graphics,EARTH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//Initialize Earth
    if (!earth.initialize(graphics,0,0,0,&earthTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing earth"));
	earth.setScale(.01);
	earth.setX(GAME_WIDTH*0.05f - earth.getWidth()*0.25f*earth.getScale());
	earth.setY(GAME_WIDTH*0.05f - earth.getHeight()*0.25f*earth.getScale());

	if(!menuScreenTexture.initialize(graphics,SCREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!menuScreen.initialize(graphics, 1280, 800, 0,&menuScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu screen"));
	menuScreen.setCenterX(GAME_WIDTH/2);
	menuScreen.setCenterY(GAME_HEIGHT/1.8);
	menu = true;

	if(!textScreenTexture.initialize(graphics,TEXTSCREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text texture"));
	if (!textScreen.initialize(graphics, 0, 0, 0,&textScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text screen"));
	textScreen.setCenterX(GAME_WIDTH/2);
	textScreen.setCenterY(GAME_HEIGHT/2);
	text = false;
	

	if(!playButtonTexture.initialize(graphics,PLAYBUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing play button texture"));
	if(!playButton.initialize(graphics, 281, 134, 0, &playButtonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing play button"));
	playButton.setCenterX(GAME_WIDTH/2);
	playButton.setCenterY(GAME_HEIGHT/1.3);


	if(!gameoverButtonTexture.initialize(graphics,GAMEOVER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover texture"));
	if(!gameoverButton.initialize(graphics, 400, 134, 0, &gameoverButtonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover"));
	gameoverButton.setCenterX(GAME_WIDTH/2);
	gameoverButton.setCenterY(GAME_HEIGHT/2);

	if(!winTexture.initialize(graphics,WIN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover texture"));
	if(!winButton.initialize(graphics, 400, 134, 0, &winTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover"));
	winButton.setCenterX(GAME_WIDTH/2);
	winButton.setCenterY(GAME_HEIGHT/2);


	if(!healthTexture.initialize(graphics, HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health texture"));
	if(!scoreTexture.initialize(graphics, SCORE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score texture"));

	ship.healthHUD.setScale(.5);
	if(!ship.healthHUD.initialize(graphics,620,193,0, &healthTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health"));
	ship.healthHUD.setX(GAME_WIDTH - ship.healthHUD.getWidth()*ship.healthHUD.getScale() - GAME_HEIGHT/20);
	ship.healthHUD.setY(GAME_HEIGHT/20);

	ship.scoreHUD.setScale(.5);
	if(!ship.scoreHUD.initialize(graphics,0,0,0, &scoreTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score"));
	ship.scoreHUD.setX(GAME_WIDTH - ship.healthHUD.getWidth()*ship.healthHUD.getScale() - GAME_HEIGHT/20);
	ship.scoreHUD.setY(GAME_HEIGHT/5.5);

	gameFont  = new TextDX();
	gameFont ->initialize(graphics,30,true,false,"Calibri");

	//Intialize Eye and Base textures
	if(!baseTexture.initialize(graphics,CYBOVINE_BASE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine base texture"));
	if(!eyeTexture.initialize(graphics,CYBOVINE_EYE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine eye texture"));

	//Intialize Eye and Base
	if(!cybovine.initialize(this,0,0,0,&eyeTexture))
		 throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing eye"));
	cybovine.setCenterX(GAME_WIDTH/2 - cybovine.base.getWidth()/2);
	cybovine.setCenterY(GAME_HEIGHT/2 - cybovine.base.getWidth()/2);
	if(!cybovine.base.initialize(graphics, 0, 0, 0, &baseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing base"));
	cybovine.base.setX(cybovine.getX());
	cybovine.base.setY(cybovine.getY());

	//Initialize Turret Textures
	if(!turret1Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret2Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret3Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE3))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret4Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE4))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret5Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE5))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret6Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE6))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret7Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE7))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	if(!turret8Texture.initialize(graphics,CYBOVINE_TURRET_IMAGE8))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cybovine turret texture"));
	
	//Initialize Milk shot texture
	if(!milkShotTexture.initialize(graphics, SHOT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing milk shot texture"));

	if(!eyeblastTexture.initialize(graphics, EYEBLAST_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing eyeblast texture"));
	
	if (!cybovine.eyeblast.initialize(this, 0, 0, 0, &eyeblastTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing eyeblast"));
	cybovine.eyeblast.setX(GAME_WIDTH/2);
	cybovine.eyeblast.setY(cybovine.getCenterY() - cybovine.eyeblast.getHeight()/2);
	//cybovine.eyeblast.setVisible(true);


	//Initialize Turrets
	if (!cybovine.turret1.initialize(this, 0, 0, 0, &turret1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet1"));
	cybovine.turret1.setX(cybovine.getX());
	cybovine.turret1.setY(cybovine.getY());
	cybovine.turret1.rotOffset = 0.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret1.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}

	if (!cybovine.turret2.initialize(this, 0, 0, 0, &turret2Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet2"));
	cybovine.turret2.setX(cybovine.getX());
	cybovine.turret2.setY(cybovine.getY());
	cybovine.turret2.rotOffset = 90.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret2.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	if (!cybovine.turret3.initialize(this, 0, 0, 0, &turret3Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet3"));
	cybovine.turret3.setX(cybovine.getX());
	cybovine.turret3.setY(cybovine.getY());
	cybovine.turret3.rotOffset = 180.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret3.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	if (!cybovine.turret4.initialize(this, 0, 0, 0, &turret4Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet4"));
	cybovine.turret4.setX(cybovine.getX());
	cybovine.turret4.setY(cybovine.getY());
	cybovine.turret4.rotOffset = 270.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret4.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	if (!cybovine.turret5.initialize(this, 0, 0, 0, &turret5Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet5"));
	cybovine.turret5.setX(cybovine.getX());
	cybovine.turret5.setY(cybovine.getY());
	cybovine.turret5.rotOffset = 45.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret5.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	if (!cybovine.turret6.initialize(this, 0, 0, 0, &turret6Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet6"));
	cybovine.turret6.setX(cybovine.getX());
	cybovine.turret6.setY(cybovine.getY());
	cybovine.turret6.rotOffset = 135.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret6.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	if (!cybovine.turret7.initialize(this, 0, 0, 0, &turret7Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet7"));
	cybovine.turret7.setX(cybovine.getX());
	cybovine.turret7.setY(cybovine.getY());
	cybovine.turret7.rotOffset = 235.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret7.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	if (!cybovine.turret8.initialize(this, 0, 0, 0, &turret8Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing teet8"));
	cybovine.turret8.setX(cybovine.getX());
	cybovine.turret8.setY(cybovine.getY());
	cybovine.turret8.rotOffset = 315.0f;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		cybovine.turret8.shotBuffer[i].initialize(this, milkShotNS::WIDTH, milkShotNS::HEIGHT,milkShotNS::TEXTURE_COLS, &milkShotTexture);
	}
	
	//Initialize Ship Texture
    if (!shipTexture.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	//Initialize Ship
	if (!ship.initialize(this, 0, 0, 0, &shipTexture))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	//Initialize Ship Shots
	for(int i = 0; i < shipNS::NUM_SHOTS; i++)
		shipShotTexture.initialize(graphics,SHIP_SHOT_IMAGE);

	for(int i = 0; i < shipNS::NUM_SHOTS; i++)
		ship.shotBuffer[i].initialize(this, 0, 0, 0, &shipShotTexture);
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void UdderDestruction::update()
{	
	if(textTimer > 0)
		textTimer -= frameTime;

	if(gameStart)
	{
		audio->playCue(SOUNDTRACK);
		gameStart = false;
	}
	if(input ->isKeyDown(ENTER_KEY))
	{
		char buff[100];
		sprintf(buff, "%f\n", textTimer);
		OutputDebugString(buff);

		if(textTimer <= 0.0f) {
			if(!menu)
				text = false;
			if(menu) {
				text = true;
				menu = false;
				textTimer = textWait;
			}
		}
	}

	if((!menu) && (!text)) {
		cybovine.update(frameTime);
		ship.update(frameTime);

		if(ship.getHealth() > 0 && cybovine.getHealth() > 0) {
			earth.setScale(earth.getScale() + frameTime*.005);
			earth.setX(GAME_WIDTH*0.05f - earth.getWidth()*0.25f*earth.getScale());
			earth.setY(GAME_WIDTH*0.05f - earth.getWidth()*0.25f*earth.getScale());
		}
	}
 
}


//=============================================================================
// Artificial Intelligence
//=============================================================================
void UdderDestruction::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void UdderDestruction::collisions()
{
	VECTOR2 collisionVector;
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret1.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret1.shotBuffer[i].setVisible(false);
			cybovine.turret1.shotBuffer[i].setActive(false);
		}
	}
		for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret2.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret2.shotBuffer[i].setVisible(false);
			cybovine.turret2.shotBuffer[i].setActive(false);
		}
	}
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret3.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret3.shotBuffer[i].setVisible(false);
			cybovine.turret3.shotBuffer[i].setActive(false);
		}
	}
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret4.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret4.shotBuffer[i].setVisible(false);
			cybovine.turret4.shotBuffer[i].setActive(false);
		}
	}
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret5.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret5.shotBuffer[i].setVisible(false);
			cybovine.turret5.shotBuffer[i].setActive(false);
		}
	}
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret6.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret6.shotBuffer[i].setVisible(false);
			cybovine.turret6.shotBuffer[i].setActive(false);
		}
	}
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret7.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret7.shotBuffer[i].setVisible(false);
			cybovine.turret7.shotBuffer[i].setActive(false);
		}
	}
	for(int i = 0; i < turretNS::NUM_SHOTS; i++)
	{
		if(cybovine.turret8.shotBuffer[i].collidesWith(ship,collisionVector))
		{
			ship.damage(MILK);
			cybovine.turret8.shotBuffer[i].setVisible(false);
			cybovine.turret8.shotBuffer[i].setActive(false);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret1, collisionVector)) {
			cybovine.turret1.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret2, collisionVector)) {
			cybovine.turret2.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret3, collisionVector)) {
			cybovine.turret3.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret4, collisionVector)) {
			cybovine.turret4.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret5, collisionVector)) {
			cybovine.turret5.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret6, collisionVector)) {
			cybovine.turret6.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret7, collisionVector)) {
			cybovine.turret7.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine.turret8, collisionVector)) {
			cybovine.turret8.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.shotBuffer[i].ready = true;
			ship.score += 5000 + rand()%2500;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		if(ship.shotBuffer[i].collidesWith(cybovine, collisionVector)) {
			cybovine.damage(TORPEDO);
			ship.shotBuffer[i].setVisible(false);
			ship.shotBuffer[i].setActive(false);
			ship.score += 10000 + rand()%5000;
		}
	}

	if(cybovine.collidesWith(ship, collisionVector))
	{
		ship.damage(EYE);
	}
}


//=============================================================================
// Render game items
//=============================================================================
void UdderDestruction::render()
{
    graphics->spriteBegin();
	
	if(text && !menu) {
		textScreen.draw();
		gameFont->print(introText,textScreen.getX() + 50, textScreen.getY() + 50);
	}

	if(menu && !text) {
		menuScreen.draw();
		playButton.draw();
	} 

	if(!menu && !text) {
		earth.draw();				
		cybovine.draw(frameTime);
		ship.draw(frameTime);

		std::stringstream stuff;
		stuff << ship.score;
		gameFont->print(stuff.str(),ship.scoreHUD.getX() + 20,ship.scoreHUD.getCenterY() - 15);

		if(ship.getHealth() <= 0.0f) {
			gameoverButton.draw();
			ship.healthHUD.setVisible(true);
			cybovine.setVisible(false);
			cybovine.turret1.setVisible(false);
			cybovine.turret2.setVisible(false);
			cybovine.turret3.setVisible(false);
			cybovine.turret4.setVisible(false);
			cybovine.turret5.setVisible(false);
			cybovine.turret6.setVisible(false);
			cybovine.turret7.setVisible(false);
			cybovine.turret8.setVisible(false);
		}
		if(cybovine.getHealth() <= 0.0f)
		{
			winButton.draw();
		}
	}
    graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void UdderDestruction::releaseAll()
{
    shipTexture.onLostDevice();
	shotTexture.onLostDevice();
	earthTexture.onLostDevice();
	baseTexture.onLostDevice();
	eyeTexture.onLostDevice();
	eyeblastTexture.onLostDevice();
	turret1Texture.onLostDevice();
	turret2Texture.onLostDevice();
	turret3Texture.onLostDevice();
	turret4Texture.onLostDevice();
	turret5Texture.onLostDevice();
	turret6Texture.onLostDevice();
	turret7Texture.onLostDevice();
	turret8Texture.onLostDevice();
	milkShotTexture.onLostDevice();
	healthTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void UdderDestruction::resetAll()
{
    shipTexture.onResetDevice();
	shotTexture.onResetDevice();
	earthTexture.onResetDevice();
	baseTexture.onResetDevice();
	eyeTexture.onResetDevice();
	turret1Texture.onResetDevice();
	turret2Texture.onResetDevice();
	turret3Texture.onResetDevice();
	turret4Texture.onResetDevice();
	turret5Texture.onResetDevice();
	turret6Texture.onResetDevice();
	turret7Texture.onResetDevice();
	turret8Texture.onResetDevice();
	milkShotTexture.onResetDevice();
	healthTexture.onResetDevice();

    Game::resetAll();
    return;
}
