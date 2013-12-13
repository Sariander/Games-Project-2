// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Spacewar constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "American Hobo";
const char GAME_TITLE[] = "American Hobo: The Resistance";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float FULL_HEALTH = 10;

// RECT Definitions
const RECT COLLISION_BOX_HERO = { -5, -12, 5, 12 };
const RECT COLLISION_BOX_SWORD = { -16, -16, 16, 16 };
const RECT COLLISION_BOX_BOTTLE = { -20, -20, 20, 20 };
const RECT COLLISION_BOX_HOBO = { -10, -19, 10, 19 };
const RECT COLLISION_BOX_BRAWLER = { -10, -19, 10, 19 };
const RECT COLLISION_BOX_THROWER = { -10, -19, 10, 19 };
const RECT COLLISION_BOX_BOSS = { -40, -40, 40, 40 };

// graphic images
const char COLOSSEUM_IMAGE[] = "pictures\\The Colosseum.png";
const char STADIUM_IMAGE[] = "pictures\\The Stadium.png";
const char STREETS_IMAGE[] = "pictures\\The Streets.png";
const char TITLE_IMAGE[] = "pictures\\Title Screen.png";
const char CONTROLS_IMAGE[] = "pictures\\Control Screen.png";
const char TRANSITION1_IMAGE[] = "pictures\\Streets Cut Scene Complete.png";
const char TRANSITION2_IMAGE[] = "pictures\\Stadium Cut Scene Complete.png";
const char TRANSITION3_IMAGE[] = "pictures\\Colliseum Cut Scene Complete.png";
const char HOBO_IMAGE[] = "pictures\\Hobo Minion.png"; 
const char HERO_IMAGE[] = "pictures\\Hero.png";
const char BRAWLER_IMAGE[] = "pictures\\brawler.png";
const char SWORD_IMAGE[] = "pictures\\Sword.png";
const char SWORD_CELS_IMAGE[] = "pictures\\Sword Cel Sheet.png";
const char HERO_CELS_IMAGE[] = "pictures\\Hero Cel Sheet.png";
const char BOSS_CELS_IMAGE[] = "pictures\\Boss Cel Sheet.png";
const char HOBO_CELS_IMAGE[] = "pictures\\Hobo Minion Cel Sheet.png";
const char BRAWLER_CELS_IMAGE[] = "pictures\\Hobo Brawler Cel Sheet.png";
const char GAME_OVER_IMAGE[] = "pictures\\GameOver Screen.png";
const char WIN_IMAGE[] = "pictures\\Win Screen.png";
const char HEART_IMAGE[] = "pictures\\heartsheet.png";
const char THROWER_CELS_IMAGE[] = "pictures\\thrower cel sheet.png";
const char MOLOTOV_CELS_IMAGE[] = "pictures\\Molotov Cel Sheet.png";

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

const char SWORD_SWING[] = "swordImpact";
const char SWORD_SLASH[] = "swordSlash";
const char SOUNDTRACK[] = "Soundtrack";
const char DEATH_SOUND[] = "hoboDeath";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key  

const UCHAR HERO_LEFT_KEY = VK_LEFT;
const UCHAR HERO_RIGHT_KEY = VK_RIGHT;
const UCHAR HERO_UP_KEY = VK_UP;
const UCHAR HERO_DOWN_KEY = VK_DOWN;
const UCHAR HERO_ATTACK_KEY = VK_SPACE;
const UCHAR HERO_DASH_KEY = VK_SHIFT;


// weapon types
enum WEAPON {SWORD, TORPEDO, MILK, EYE};
enum GameStates { Title, Controls, Level1, Level2, Level3, MenuScreen, GameOver, Win, ScoreScreen, Transition1, Transition2, Transition3 };
enum menu{ main, title, retry, scores };
enum ownership{null, purchased, cannotpurchase};
enum DIRECTION { NONE, LEFT, RIGHT, DOWN, UP};

//level config
const int LEVEL_1_HOBOS = 10;
const int LEVEL_1_BRAWLERS = 0;
const int LEVEL_1_THROWERS = 0;
const int LEVEL_1_KILLCOUNT = LEVEL_1_HOBOS + LEVEL_1_BRAWLERS + LEVEL_1_THROWERS;
const int LEVEL_2_HOBOS = 5;
const int LEVEL_2_BRAWLERS = 10;
const int LEVEL_2_THROWERS = 0;
const int LEVEL_2_KILLCOUNT = LEVEL_2_HOBOS + LEVEL_2_BRAWLERS + LEVEL_2_THROWERS;
const int LEVEL_3_HOBOS = 0;
const int LEVEL_3_BRAWLERS = 20;
const int LEVEL_3_THROWERS = 0;
const int LEVEL_3_KILLCOUNT = LEVEL_3_HOBOS + LEVEL_3_BRAWLERS + LEVEL_3_THROWERS;

const int HOBO_NUMBER = 10;
const int BRAWLER_NUMBER = 10;
const int THROWER_NUMBER = 5;

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif
