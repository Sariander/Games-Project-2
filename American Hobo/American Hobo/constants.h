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
const float FULL_HEALTH = 100;
const float SHIP_ANGULAR_SPEED = .05f;			////////////////////////////////[added]


// graphic images
const char EARTH_IMAGE[] = "pictures\\earth.png"; /////////////////////////////////////////////[added]
const char HEALTH_IMAGE[] = "pictures\\Health AniSeries L193.png";
const char CYBOVINE_BASE_IMAGE[] = "pictures\\Cybovine Base [T].png"; 
const char CYBOVINE_EYE_IMAGE[] = "pictures\\Cybovine Eye [T].png";
const char CYBOVINE_TURRET_IMAGE1[] = "pictures\\Cybovine Turret1 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE2[] = "pictures\\Cybovine Turret2 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE3[] = "pictures\\Cybovine Turret3 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE4[] = "pictures\\Cybovine Turret4 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE5[] = "pictures\\Cybovine Turret5 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE6[] = "pictures\\Cybovine Turret6 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE7[] = "pictures\\Cybovine Turret7 [T] 64.png";
const char CYBOVINE_TURRET_IMAGE8[] = "pictures\\Cybovine Turret8 [T] 64.png";
const char SHIP_IMAGE[]   = "pictures\\Player Ship.png";
const char SHOT_IMAGE[] = "pictures\\Milk shot.png";
const char SHIP_SHOT_IMAGE[] = "pictures\\shot.png";
const char SCREEN_IMAGE[] = "pictures\\Title screen header.png";
const char PLAYBUTTON_IMAGE[] = "pictures\\Play button AniSeries.png";
const char GAMEOVER_IMAGE[] = "pictures\\Gameover button AniSeries.png";
const char WIN_IMAGE[] = "pictures\\Win Button AniSeries.png";
const char TEXTSCREEN_IMAGE[] = "pictures\\Text screen.png";
const char SCORE_IMAGE[] = "pictures\\Score bar.png";
const char EYEBLAST_IMAGE[] = "pictures\\Cybovine blast.png";

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// audio cues
const char LASER[] = "laser";
const char MOO[] = "final cybovine moo1";
const char MOO2[] = "final cybovine shriek2";
const char SOUNDTRACK[] = "Soundtrack";


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SHIP1_LEFT_KEY    = 'A';
const UCHAR SHIP1_RIGHT_KEY   = 'D';
const UCHAR SHIP1_FORWARD_KEY = 'W';
const UCHAR SHIP1_FIRE_KEY    = 'S';
const UCHAR SHIP2_LEFT_KEY    = VK_LEFT; // left arrow
const UCHAR SHIP2_RIGHT_KEY   = VK_RIGHT; // right arrow
const UCHAR SHIP2_FORWARD_KEY = VK_UP;   // up arrow
const UCHAR SHIP2_FIRE_KEY    = VK_DOWN; // down arrow

const UCHAR SHIP_LEFT_KEY    = VK_LEFT;    /////////////////////////////[added]
const UCHAR SHIP_RIGHT_KEY   = VK_RIGHT;    

// weapon types
enum WEAPON {TORPEDO, MILK, EYE};

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
