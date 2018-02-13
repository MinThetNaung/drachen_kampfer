//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

#ifndef _Drachen_H             // Prevent multiple definitions if this 
#define _Drachen_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <time.h>
#include <fstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "playership.h"
#include "enemy.h"
#include "Bullet.h"
#include "Missile.h"
#include "reflector.h"
#include "special.h"
#include <random>

namespace drachenNS
{
	const char FONT[] = "Arial Bold";  // font
	const int FONT_BIG_SIZE = 256;     // font height
	const int FONT_SCORE_SIZE = 48;
	const COLOR_ARGB FONT_COLOR = graphicsNS::YELLOW;
	const COLOR_ARGB SHIP1_COLOR = graphicsNS::BLUE;

	const int SCREEN_SCALE = 1;                  // scale factor of space image
	const int SCREEN_WIDTH = 1024 * SCREEN_SCALE;  // width of scaled space image
	const int SCREEN_HEIGHT = 768 * SCREEN_SCALE; // height of scaled space image



	const float SHIP_LIMIT_LEFT = GAME_WIDTH / 120;
	const float SHIP_LIMIT_RIGHT = GAME_WIDTH + GAME_WIDTH / 14 - playershipNS::WIDTH;;
	const float SHIP_LIMIT_TOP = GAME_HEIGHT / 120;
	const float SHIP_LIMIT_BOTTOM = GAME_HEIGHT + GAME_HEIGHT / 12 - playershipNS::HEIGHT;

	/*const float SHIP_LIMIT_LEFT = GAME_WIDTH / 8;
	const float SHIP_LIMIT_RIGHT = GAME_WIDTH - GAME_WIDTH / 8 - playershipNS::WIDTH;
	const float SHIP_LIMIT_TOP = GAME_HEIGHT / 8;
	const float SHIP_LIMIT_BOTTOM = GAME_HEIGHT - GAME_HEIGHT / 8 - playershipNS::HEIGHT;
	*/
	/*int cameraX = 0;    // camera x position
	int cameraY = 0;     // camera y position

	//camera size
	const int cameraWidth = 640;
	const int cameraHeight = 480;
	const float scroll_rate = 10;
	*/
}


//=============================================================================
// This class is the core of the game
//=============================================================================
class Drachen : public Game
{
private:
	// game items
	TextureManager backgroundTexture;   // Background texture
										//TextureManager gameTextures;    // game texture
	TextureManager playershipTextures;
	TextureManager bulletTextures;
	TextureManager enemyTextures;
	TextureManager missileTextures;
	TextureManager reflectorTextures;
	TextureManager specialTextures;
	TextureManager menuTexture;
	TextureManager instructionTexture;
	TextureManager creditTexture;
	TextureManager cursorTexture;

	Image menu;
	Image instruction;
	Image credit;
	Image cursor;
	playership    playership1;           // spaceships
	Image   background;         // backdrop image
	Enemy enemy0;
	Bullet bullet;
	Missile missile;
	Reflector reflector;
	Special special;
	vector<Bullet>Pbulletv = {};
	vector<Bullet>Ebulletv = {};
	vector<Missile>Pmissilev = {};
	vector<Missile>Emissilev = {};
	vector<Reflector>Preflectorv = {};
	vector<Special>Pspecialv = {};
	vector<Enemy>Enemyv = {};
	//Image   background;         // backdrop image
	//int cameraX;
	//int cameraY;
	//int screenWidth;
	//int screenHeight;



public:
	// Constructor
	Drachen();

	// Destructor
	virtual ~Drachen();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
