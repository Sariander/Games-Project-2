#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuName = title;
	ownage = null;
	currentMoney = 0;
}

Menu::~Menu()
{
	releaseAll();
}

void Menu::initialize(Graphics *g, Input *i)
{
	mainMenu.push_back("Main Menu"); 
	mainMenu.push_back("Recovery - 200"); mainMenu.push_back("Projectile Ammo (Not in yet) - 100"); mainMenu.push_back("Done");
	titleMenu.push_back("Play"); titleMenu.push_back("Controls");
	retryMenu.push_back("Retry"); retryMenu.push_back("Exit");
	scoreScreen.push_back("Scores");
	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(50,50);
	input = i;
	verticalOffset = 45;
	horizontalOffset = 160;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 20, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 25, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 35, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
	mainDepressedLastFrame = false;
	titleMenuDepressedLastFrame = false;
	done = false;
}

void Menu::setCurrentMoney(int score)
{
	currentMoney = score;
}

void Menu::update()
{	
	if (input->isKeyDown(VK_UP))
	{
		upDepressedLastFrame = true;
	}
	if (!input->isKeyDown(VK_UP) && upDepressedLastFrame)
	{
		upDepressedLastFrame = false;
		linePtr--;
		ownage = null;
	}
	if (input->isKeyDown(VK_DOWN))
	{
		downDepressedLastFrame = true;
	}
	if (!input->isKeyDown(VK_DOWN) && downDepressedLastFrame)
	{
		downDepressedLastFrame = false;
		linePtr++;
		ownage = null;
	}
	switch (menuName)
	{
	case main:
		pointerCheckerWrappingWithTitle(linePtr, mainMenu);
		confirmChecker(mainDepressedLastFrame);
		exitMainMenu();
		break;
	case title:
		pointerCheckerWrappingWithoutTitle(linePtr, titleMenu);
		confirmChecker(titleMenuDepressedLastFrame);
	case retry:
		pointerCheckerWrappingWithoutTitle(linePtr, retryMenu);
		confirmChecker(retryMenuDepressedLastFrame);
		break;
	}
}

void Menu::displayMenu()
{
	if (menuName == title)
	{
		menuAnchor = D3DXVECTOR2(400, 325);
		buildMenuWithoutTitle(titleMenu, 0, title);
		menuAnchor = D3DXVECTOR2(50, 50);
	}
	else if (menuName == retry)
	{
		menuAnchor = D3DXVECTOR2(300, 325);
		buildMenuWithoutTitle(retryMenu, 0, retry);
		menuAnchor = D3DXVECTOR2(50, 50);
	}
	else if (menuName == scores)
	{
		menuAnchor = D3DXVECTOR2(275, 50);
		buildMenuWithTitle(scoreScreen, 0, scores);
		menuAnchor = D3DXVECTOR2(50, 50);
	}
	else
	{
		buildMenuWithTitle(mainMenu, 0, main);
	}
	purchaseResponse();
}

void Menu::pointerCheckerWrappingWithTitle(int &pointer, vector<string> menuVector)
{
	if (pointer < 1) pointer = menuVector.size() - 1;
	if (pointer > menuVector.size() - 1) pointer = 1;
}

void Menu::pointerCheckerWrappingWithoutTitle(int &pointer, vector<string> menuVector)
{
	if (pointer < 0) pointer = menuVector.size() - 1;
	if (pointer > menuVector.size() - 1) pointer = 0;
}

void Menu::pointerCheckerNoWrappingWithTitle(int &pointer, vector<string> menuVector)
{
	if (pointer < 1) pointer = 1;
	if (pointer > menuVector.size() - 1) pointer = menuVector.size() - 1;
}

void Menu::pointerCheckerNoWrappingWithoutTitle(int &pointer, vector<string> menuVector)
{
	if (pointer < 0) pointer = 0;
	if (pointer > menuVector.size() - 1) pointer = menuVector.size() - 1;
}

void Menu::confirmChecker(bool &keyPressed)
{
	if (input->isKeyDown(VK_RETURN))
	{
		keyPressed = true;
	}
	if (!input->isKeyDown(VK_RETURN) && keyPressed)
	{
		keyPressed = false;
		selectedItem = linePtr;
	}
	else selectedItem = -1;
}

void Menu::buildMenuWithTitle(vector<string> menuVector, int col, menu menuState)
{
	for (int i = 0; i < menuVector.size(); ++i)
	{
		if (i == 0)
		{
			menuHeadingFont->print(menuVector[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
		}
		else
		{
			if (linePtr == i && menuName == menuState)
				menuItemFontHighlight->print(menuVector[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
			else
				menuItemFont->print(menuVector[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
		}
	}
}

void Menu::buildMenuWithoutTitle(vector<string> menuVector, int col, menu menuState)
{
	for (int i = 0; i < menuVector.size(); ++i)
	{
		if (linePtr == i && menuName == menuState)
			menuItemFontHighlight->print(menuVector[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
		else
			menuItemFont->print(menuVector[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
	}
}

void Menu::changeToMenuWithTitle(int desiredInput, menu endMenu)
{
	if (selectedItem == desiredInput)
	{
		menuName = endMenu;
		linePtr = 1;
		ownage = null;
	}
}

void Menu::changeToMenuWithoutTitle(int desiredInput, menu endMenu)
{
	if (selectedItem == desiredInput)
	{
		menuName = endMenu;
		linePtr = 0;
		ownage = null;
	}
}

void Menu::exitMainMenu()
{
	if (selectedItem == mainMenu.size() - 1)
	{
		done = true;
		ownage = null;
	}
}

void Menu::purchaseThis(int desiredInput, int price)
{
	if (selectedItem == desiredInput && price <= currentMoney)
	{
		ownage = purchased;
		currentMoney -= price;
		//Give item
	}
	else if (selectedItem == desiredInput && price > currentMoney)
	{
		ownage = cannotpurchase;
	}
}

void Menu::purchaseHealth(int desiredInput, int price, int health)
{
	if (price <= currentMoney && hero.health < 10)
	{
		ownage = purchased;
		currentMoney -= price;
		hero.health += health;
		if (hero.health > 10)
		{
			hero.health = 10;
		}
		//Give health
		//Check health against max, set to max if over
	}
	else if (selectedItem == desiredInput && price > currentMoney)
	{
		ownage = cannotpurchase;
	}
}

void Menu::purchaseResponse()
{
	if (ownage == purchased)
	{
		menuHeadingFont->print("Purchased", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2);
	}
	if (ownage == cannotpurchase)
	{
		menuHeadingFont->print("Too Expensive", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2);
	}
}

void Menu::releaseAll()
{
	menuItemFont->onLostDevice();
	menuHeadingFont->onLostDevice();
	menuItemFontHighlight->onLostDevice();
	return;
}

void Menu::resetAll()
{
	menuItemFont->onResetDevice();
	menuHeadingFont->onResetDevice();
	menuItemFontHighlight->onResetDevice();
	return;
}