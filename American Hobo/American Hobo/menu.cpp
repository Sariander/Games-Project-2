
#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuName = main;
}

Menu::~Menu()
{
	releaseAll();
}

void Menu::initialize(Graphics *g, Input *i)
{
	mainMenu.push_back("Main Menu");
	mainMenu.push_back("Weapons");
	mainMenu.push_back("Armor");
	mainMenu.push_back("Stats");
	mainMenu.push_back("Done");
	subMenu1.push_back("Weapons");
	subMenu1.push_back("Swords");
	subMenu1.push_back("Shields");
	subMenu1.push_back("Back");
	subMenu2.push_back("Armor");
	subMenu2.push_back("Armor 1");
	subMenu2.push_back("Armor 2");
	subMenu2.push_back("Back");
	subMenu3.push_back("Stats");
	subMenu3.push_back("Stat 1");
	subMenu3.push_back("Stat 2");
	subMenu3.push_back("Stat 3");
	subMenu3.push_back("Stat 4");
	subMenu3.push_back("Back");
	subMenu4.push_back("Swords");
	subMenu4.push_back("Sword 1");
	subMenu4.push_back("Sword 2");
	subMenu4.push_back("Back");
	subMenu5.push_back("Shields");
	subMenu5.push_back("Shield 1");
	subMenu5.push_back("Shield 2");
	subMenu5.push_back("Back");
	subMenu6.push_back("Price");
	subMenu6.push_back("100");
	subMenu6.push_back("200");
	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(125,10);
	input = i;
	verticalOffset = 35;
	horizontalOffset = 150;
	linePtr = 1;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 17, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 20, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 30, true, false, "Calibri") == false)
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
	}
	if (input->isKeyDown(VK_DOWN))
	{
		downDepressedLastFrame = true;
	}
	if (!input->isKeyDown(VK_DOWN) && downDepressedLastFrame)
	{
		downDepressedLastFrame = false;
		linePtr++;
	}
	switch (menuName)
	{
	case main:
		pointerCheckerWrappingWithTitle(linePtr, mainMenu);
		confirmChecker(mainDepressedLastFrame);
		changeToMenuWithTitle(1, sub1);
		changeToMenuWithTitle(2, sub2);
		changeToMenuWithTitle(3, sub3);
		if (selectedItem == mainMenu.size() - 1)
		{
			done = true;
		}
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
		changeToMenuWithTitle(subMenu2.size() - 1, main);
		break;
	case sub3:
		pointerCheckerWrappingWithTitle(linePtr, subMenu3);
		confirmChecker(sub3DepressedLastFrame);
		changeToMenuWithTitle(subMenu3.size() - 1, main);
		break;
	case sub4:
		pointerCheckerWrappingWithTitle(linePtr, subMenu4);
		confirmChecker(sub4DepressedLastFrame);
		changeToMenuWithTitle(subMenu4.size() - 1, sub1);
		break;
	case sub5:
		pointerCheckerWrappingWithTitle(linePtr, subMenu5);
		confirmChecker(sub5DepressedLastFrame);
		changeToMenuWithTitle(subMenu5.size() - 1, sub1);
		break;
	case sub6:
		pointerCheckerWrappingWithTitle(linePtr, subMenu6);
		confirmChecker(sub6DepressedLastFrame);
		changeToMenuWithTitle(subMenu6.size() - 1, sub1);
		break;
	}
}

void Menu::displayMenu()
{
	buildMenuWithTitle(mainMenu, 0, main); 
	if (menuName == sub1 || menuName == sub4 || menuName == sub5)
	{
		buildMenuWithTitle(subMenu1, 1, sub1);
	}
	if (menuName == sub2 || menuName == sub6)
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
		buildMenuWithTitle(subMenu6, 2, sub6);
	}
}

void Menu::pointerCheckerWrappingWithTitle(int &pointer, vector<string> menu)
{
	if (pointer < 1) pointer = menu.size() - 1;
	if (pointer > menu.size() - 1) pointer = 1;
}

void Menu::pointerCheckerWrappingWithoutTitle(int &pointer, vector<string> menu)
{
	if (pointer < 0) pointer = menu.size() - 1;
	if (pointer > menu.size() - 1) pointer = 0;
}

void Menu::pointerCheckerNoWrappingWithTitle(int &pointer, vector<string> menu)
{
	if (pointer < 1) pointer = 1;
	if (pointer > menu.size() - 1) pointer = menu.size() - 1;
}

void Menu::pointerCheckerNoWrappingWithoutTitle(int &pointer, vector<string> menu)
{
	if (pointer < 0) pointer = 0;
	if (pointer > menu.size() - 1) pointer = menu.size() - 1;
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

void Menu::buildMenuWithTitle(vector<string> Menu, int col, menu menu)
{
	for (int i = 0; i < Menu.size(); ++i)
	{
		if (i == 0)
		{
			menuHeadingFont->print(Menu[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
		}
		else
		{
			if (linePtr == i && menuName == menu)
				menuItemFontHighlight->print(Menu[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
			else
				menuItemFont->print(Menu[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
		}
	}
}

void Menu::buildMenuWithoutTitle(vector<string> Menu, int col, menu menu)
{
	for (int i = 0; i < Menu.size(); ++i)
	{
		if (linePtr == i && menuName == menu)
			menuItemFontHighlight->print(Menu[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
		else
			menuItemFont->print(Menu[i], menuAnchor.x + horizontalOffset * col, menuAnchor.y + verticalOffset * i);
	}
}

void Menu::changeToMenuWithTitle(int desiredInput, menu endMenu)
{
	if (selectedItem == desiredInput)
	{
		menuName = endMenu;
		linePtr = 1;
	}
}

void Menu::changeToMenuWithoutTitle(int desiredInput, menu endMenu)
{
	if (selectedItem == desiredInput)
	{
		menuName = endMenu;
		linePtr = 0;
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