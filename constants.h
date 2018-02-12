//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <vector>
//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Drachen";
const char GAME_TITLE[] = "Drachen";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1024;               // width of game in pixels
const UINT GAME_HEIGHT = 768;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 6.67428e-11f;             // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;
const float playerregen = 600;
// graphic images
const char BACKGROUND_IMAGE[] =   "pictures\\bg_version2.png";     // photo source NASA/courtesy of nasaimages.org 
const char TEXTURES_IMAGE[] = "pictures\\textures.png";  // game textures
const char SHIP_IMAGE[] = "pictures\\ship.png";
const char BULLET_IMAGE[] = "pictures\\bullet.png";
const char ENEMY_IMAGE[] = "pictures\\enemy2.png";
const char MISSILE_IMAGE[] = "pictures\\missile.png";
const char REFLECTOR_IMAGE[] = "pictures\\reflector.png";
const char SPECIAL_IMAGE[] = "pictures\\special.png";
// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
#define VK_KEY_I	0x49               //('I')	I
#define VK_KEY_W	0x57
#define VK_KEY_A	0x41
#define VK_KEY_S	0x53
#define VK_KEY_D	0x44
#define VK_KEY_O    0x4F
#define VK_KEY_P    0x50
#define VK_KEY_L    0x4C
// weapon types
enum WEAPON {TORPEDO, SHIP, PLANET};
enum State { STATE_NORMAL, STATE_BULLET, STATE_MISSILE, STATE_SPECIAL };
#endif
