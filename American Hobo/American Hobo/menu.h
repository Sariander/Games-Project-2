
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef MENU_H                 // Prevent multiple definitions if this 
#define MENU_H 

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include <vector>
#include "input.h"
using std::vector;
using std::string;
using std::stringstream;

namespace menuNS
{ }

// inherits from Entity class
class Menu
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;
   Input   *input;         // pointer to the input system
   Graphics *graphics;
   int selectedItem;
   int currentMoney;
   vector<string> mainMenu;
   vector<string> subMenu1;
   vector<string> subMenu2;
   vector<string> subMenu3;
   vector<string> subMenu4;
   vector<string> subMenu5;
   vector<string> subMenu6;
   string menuHeading1, menuHeading2;
   D3DXVECTOR2 menuAnchor;
   int verticalOffset;
   int horizontalOffset;
   int linePtr;
   COLOR_ARGB highlightColor ;
   COLOR_ARGB normalColor;
   COLOR_ARGB boughtColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;
   bool mainDepressedLastFrame;
   bool sub1DepressedLastFrame;
   bool sub2DepressedLastFrame;
   bool sub3DepressedLastFrame;
   bool sub4DepressedLastFrame;
   bool sub5DepressedLastFrame;
   bool sub6DepressedLastFrame;
   menu menuName;
   ownership ownage;

public:
    // constructor
    Menu();
	~Menu();
	bool done;
	void initialize(Graphics *g, Input *i);
	void update();
	void releaseAll();
	void resetAll();
	int getSelectedItem() {return selectedItem;}
	void displayMenu();
	void pointerCheckerWrappingWithTitle(int &pointer, vector<string> menuVector);
	void pointerCheckerWrappingWithoutTitle(int &pointer, vector<string> menuVector);
	void pointerCheckerNoWrappingWithTitle(int &pointer, vector<string> menuVector);
	void pointerCheckerNoWrappingWithoutTitle(int &pointer, vector<string> menuVector);
	void confirmChecker(bool &keyPressed);
	void buildMenuWithTitle(vector<string> menuVector, int col, menu menuState);
	void buildMenuWithoutTitle(vector<string> menuVector, int col, menu menuName);
	void changeToMenuWithTitle(int desiredInput, menu endMenu);
	void changeToMenuWithoutTitle(int desiredInput, menu endMenu);
	void exitMainMenu();
	void purchaseThis(int desiresInput, int price);
	void purchaseHealth(int desiresInput, int price, int health);
	void purchaseResponse();
	void moneyDebugger();
};
#endif

