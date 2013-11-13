
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

public:
    // constructor
    Menu();
	~Menu();
	void initialize(Graphics *g, Input *i);
	void update();
	void releaseAll();
	void resetAll();
	int getSelectedItem() { return selectedItem; }
	void displayMenu();
	void pointerCheckerWrappingWithTitle(int &pointer, vector<string> menu);
	void pointerCheckerWrappingWithoutTitle(int &pointer, vector<string> menu);
	void pointerCheckerNoWrappingWithTitle(int &pointer, vector<string> menu);
	void pointerCheckerNoWrappingWithoutTitle(int &pointer, vector<string> menu);
	void confirmChecker(bool &keyPressed);
	void buildMenuWithTitle(vector<string> Menu, int col, menu menuName);
	void buildMenuWithoutTitle(vector<string> Menu, int col, menu menuName);
	void changeToMenuWithTitle(int desiredInput, menu endMenu);
	void changeToMenuWithoutTitle(int desiredInput, menu endMenu);
	bool done;
};
#endif

