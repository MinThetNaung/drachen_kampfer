// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 Drachen.h v1.0

#ifndef _Drachen_H             // Prevent multiple definitions if this 
#define _Drachen_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "playership.h"
#include "enemy.h"
#include "Bullet.h"
#include "Missile.h"
#include "reflector.h"
#include "special.h"
namespace drachenNS
{
	const char FONT[] = "Arial Bold";  // font
	const int FONT_BIG_SIZE = 256;     // font height
	const int FONT_SCORE_SIZE = 48;
	const COLOR_ARGB FONT_COLOR = graphicsNS::YELLOW;
	const COLOR_ARGB SHIP1_COLOR = graphicsNS::BLUE;

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
    TextureManager gameTextures;    // game texture
	TextureManager playershipTextures;
	TextureManager bulletTextures;
	TextureManager enemyTextures;
	TextureManager missileTextures;
	TextureManager reflectorTextures;
	TextureManager specialTextures;
    playership    playership1;           // spaceships
    Planet  planet;         // the planet
    Image   nebula;         // backdrop image
	Enemy enemy;
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
    Image   background;         // backdrop image
	int cameraX;
	int cameraY;
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
