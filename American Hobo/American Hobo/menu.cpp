
#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuName = main;
	ownage = null;
	currentMoney = 0;
}

Menu::~Menu()
{
	releaseAll();
}

void Menu::initialize(Graphics *g, Input *i)
{
	mainMenu.push_back("Main Menu"); mainMenu.push_back("Weapons"); mainMenu.push_back("Armor");
	mainMenu.push_back("Stats"); mainMenu.push_back("Recovery"); mainMenu.push_back("Done");
	subMenu1.push_back("Weapons"); subMenu1.push_back("Swords"); 
	subMenu1.push_back("Shields"); subMenu1.push_back("Back");
	subMenu2.push_back("Armor"); subMenu2.push_back("Very Long Armor 1 - 800");
	subMenu2.push_back("Very Long Armor 2 - 1200"); subMenu2.push_back("Back");
	subMenu3.push_back("Stats"); subMenu3.push_back("Health Up - 300");
	subMenu3.push_back("Strength Up - 300"); subMenu3.push_back("Stat Up 3 - 300");
	subMenu3.push_back("Stat Up 4 - 300"); subMenu3.push_back("Back");
	subMenu4.push_back("Swords"); subMenu4.push_back("Very Long Sword 1 - 100");
	subMenu4.push_back("Very Long Sword 2 - 200"); subMenu4.push_back("Back");
	subMenu5.push_back("Shields"); subMenu5.push_back("Very Long Shield 1 - 300");
	subMenu5.push_back("Very Long Shield 2 - 500"); subMenu5.push_back("Back");
	subMenu6.push_back("Recovery"); subMenu6.push_back("25 HP - 300"); subMenu6.push_back("50 HP - 400");  subMenu6.push_back("Back");
	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(50,50);
	input = i;
	verticalOffset = 45;
	horizontalOffset = 160;
	linePtr = 1;
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
	sub1DepressedLastFrame = false;
	sub2DepressedLastFrame = false;
	sub3DepressedLastFrame = false;
	sub4DepressedLastFrame = false;
	sub5DepressedLastFrame = false;
	sub6DepressedLastFrame = false;
	done = false;
	currentMoney = 1000;
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
		changeToMenuWithTitle(1, sub1);
		changeToMenuWithTitle(2, sub2);
		changeToMenuWithTitle(3, sub3);
		changeToMenuWithTitle(4, sub6);
		exitMainMenu();
		break;
	case sub1:
		pointerCheckerWrappingWithTitle(linePtr, subMenu1);
		confirmChecker(sub1DepressedLastFrame);
		changeToMenuWithTitle(1, sub4);
		changeToMenuWithTitle(2, sub5);
		changeToMenuWithTitle(subMenu1.size() - 1, main);
		break;
	case sub2:
		pointerCheckerWrappingWithTitle(linePtr, subMenu2);
		confirmChecker(sub2DepressedLastFrame);
		purchaseThis(1, 800);
		purchaseThis(2, 1200);
		changeToMenuWithTitle(subMenu2.size() - 1, main);
		break;
	case sub3:
		pointerCheckerWrappingWithTitle(linePtr, subMenu3);
		confirmChecker(sub3DepressedLastFrame);
		purchaseThis(1, 300);
		purchaseThis(2, 300);
		purchaseThis(3, 300);
		purchaseThis(4, 300);
		changeToMenuWithTitle(subMenu3.size() - 1, main);
		break;
	case sub4:
		pointerCheckerWrappingWithTitle(linePtr, subMenu4);
		confirmChecker(sub4DepressedLastFrame);
		purchaseThis(1, 100);
		purchaseThis(2, 200);
		changeToMenuWithTitle(subMenu4.size() - 1, sub1);
		break;
	case sub5:
		pointerCheckerWrappingWithTitle(linePtr, subMenu5);
		confirmChecker(sub5DepressedLastFrame);
		purchaseThis(1, 300);
		purchaseThis(2, 500);
		changeToMenuWithTitle(subMenu5.size() - 1, sub1);
		break;
	case sub6:
		pointerCheckerWrappingWithTitle(linePtr, subMenu6);
		confirmChecker(sub6DepressedLastFrame);
		purchaseHealth(1, 300, 25);
		purchaseHealth(2, 400, 50);
		changeToMenuWithTitle(subMenu6.size() - 1, main);
		break;
	}
}

void Menu::displayMenu()
{
	moneyDebugger();
	stringstream s;
	s << "Current Money: " << currentMoney;
	menuItemFont->print(s.str(), GAME_WIDTH / 2 - 100, GAME_HEIGHT / 60);
	buildMenuWithTitle(mainMenu, 0, main); 
	if (menuName == sub1 || menuName == sub4 || menuName == sub5)
	{
		buildMenuWithTitle(subMenu1, 1, sub1);
	}
	if (menuName == sub2)
	{
		buildMenuWithTitle(subMenu2, 1, sub2);
	}
	if (menuName == sub3)
	{
		buildMenuWithTitle(subMenu3, 1, sub3);
	}
	if (menuName == sub4)
	{
		buildMenuWithTitle(subMenu4, 2, sub4);
	}
	if (menuName == sub5)
	{
		buildMenuWithTitle(subMenu5, 2, sub5);
	}
	if (menuName == sub6)
	{
		buildMenuWithTitle(subMenu6, 1, sub6);
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
	if (selectedItem == desiredInput && price <= currentMoney)
	{
		ownage = purchased;
		currentMoney -= price;
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

void Menu::moneyDebugger()
{
	if (input->isKeyDown('1') && input->isKeyDown('0'))
	{
		menuItemFont->print("Cheating in progress...", GAME_WIDTH / 4 - 100, GAME_HEIGHT / 60);
		currentMoney += 10;
	}
}