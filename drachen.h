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

	const float SHIP_LIMIT_LEFT = GAME_WIDTH / 8;
	const float SHIP_LIMIT_RIGHT = GAME_WIDTH - GAME_WIDTH / 8 - playershipNS::WIDTH;
	const float SHIP_LIMIT_TOP = GAME_HEIGHT / 8;
	const float SHIP_LIMIT_BOTTOM = GAME_HEIGHT - GAME_HEIGHT / 8 - playershipNS::HEIGHT;

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
	playership    playership1;           // spaceships
	Image   background;         // backdrop image
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
	//=============================================================================
	// Update all game items
	//=============================================================================
	void update()
	{
		/*float playership1X;
		float playership1Y;

		playership1X = playership1.getX(); //get player location
		playership1Y = playership1.getY();
		*/

		//planet.update(frameTime);
		playership1.update(frameTime);
		enemy.update(frameTime);
		//Player skills
		if (input->isKeyDown(VK_KEY_I))  //I         // if move right FSM forward declaration
		{
			if (playership1.state == STATE_NORMAL || playership1.state == STATE_BULLET)
			{
				if (playership1.isbulletcool() == false)
				{
					if (!bullet.initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &bulletTextures))
						throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
					bullet.setFrames(BulletNS::BULLET_START_FRAME, BulletNS::BULLET_END_FRAME);
					bullet.setCurrentFrame(BulletNS::BULLET_START_FRAME);
					bullet.setX(playership1.getCenterX() - bullet.getWidth() / 2 * bullet.getScale());
					bullet.setY(playership1.getCenterY() - bullet.getHeight() / 2 * bullet.getScale());
					bullet.setdamage(playershipNS::BULLETDAMAGE);
					bullet.setSpeed(playershipNS::BULLETSPEED);
					bullet.setRadians(playership1.getRadians());
					bullet.isreflectable(true);
					Pbulletv.push_back(bullet);
					playership1.bulletfired(true);
					playership1.state = STATE_BULLET;
				}
			}
		}
		if (input->isKeyDown(VK_KEY_O))  //I         // if move right FSM forward declaration
		{
			if (playership1.state == STATE_NORMAL || playership1.state == STATE_MISSILE)
			{
				if (playership1.ismissilecool() == false)
				{
					if (!missile.initialize(this, MissileNS::WIDTH, MissileNS::HEIGHT, MissileNS::TEXTURE_COLS, &missileTextures))
						throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
					missile.setFrames(MissileNS::MISSILE_START_FRAME, MissileNS::MISSILE_END_FRAME);
					missile.setCurrentFrame(MissileNS::MISSILE_START_FRAME);
					missile.setX(playership1.getCenterX() - missile.getWidth() / 2 * missile.getScale());
					missile.setY(playership1.getCenterY() - missile.getHeight() / 2 * missile.getScale());
					missile.setdamage(playershipNS::MISSILEDAMAGE);
					missile.setSpeed(playershipNS::MISSILESPEED);
					missile.setRadians(playership1.getRadians());
					missile.isreflectable(false);
					Pmissilev.push_back(missile);
					playership1.missilefired(true);
					playership1.state = STATE_MISSILE;
				}
			}
		}
		if (input->isKeyDown(VK_KEY_P))  //I         // if move right FSM forward declaration
		{
			if (playership1.isreflectorcool() == false)
			{
				if (!reflector.initialize(this, ReflectorNS::WIDTH, ReflectorNS::HEIGHT, ReflectorNS::TEXTURE_COLS, &reflectorTextures))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing reflector"));
				//missile.setFrames(MissileNS::MISSILE_START_FRAME, MissileNS::MISSILE_END_FRAME);
				reflector.setCurrentFrame(ReflectorNS::REFLECTOR_START_FRAME);
				reflector.setX(playership1.getCenterX() - reflector.getWidth() / 2 * reflector.getScale());
				reflector.setY(playership1.getCenterY() - reflector.getHeight() / 2 * reflector.getScale());
				//missile.setSpeed(30);
				//missile.setRadians(playership1.getRadians());
				//missile.isreflectable(false);
				Preflectorv.push_back(reflector);
				playership1.reflectorfired(true);
			}
		}
		if (input->isKeyDown(VK_KEY_L))  //I         // if move right FSM forward declaration
		{
			if (playership1.state == STATE_NORMAL || playership1.state == STATE_SPECIAL)
			{
				if (playership1.isspecialcool() == false)
				{
					if (!special.initialize(this, SpecialNS::WIDTH, SpecialNS::HEIGHT, SpecialNS::TEXTURE_COLS, &specialTextures))
						throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing special"));
					special.setFrames(SpecialNS::SPECIAL_START_FRAME, SpecialNS::SPECIAL_END_FRAME);
					special.setCurrentFrame(ReflectorNS::REFLECTOR_START_FRAME);
					special.setX(playership1.getCenterX() - special.getWidth() / 2 * special.getScale());
					special.setY(playership1.getCenterY() - special.getHeight() / 2 * special.getScale());
					special.setdamage(playershipNS::SPECIALDAMAGE);
					special.setSpeed(playershipNS::SPECIALSPEED);
					special.setRadians(playership1.getRadians());
					special.isreflectable(false);
					Pspecialv.push_back(special);
					playership1.specialfired(true);
					playership1.setpmhealth(playership1.getpmhealth() - 1);
					playership1.state = STATE_SPECIAL;
				}
			}
		}
		if (input->isKeyDown(VK_KEY_I) == false && playership1.state == STATE_BULLET)
		{
			playership1.state = STATE_NORMAL;
		}
		if (input->isKeyDown(VK_KEY_O) == false && playership1.state == STATE_MISSILE)
		{
			playership1.state = STATE_NORMAL;
		}
		if (input->isKeyDown(VK_KEY_L) == false && playership1.state == STATE_SPECIAL)
		{
			playership1.state = STATE_NORMAL;
		}
		//Player skills
		for (unsigned d = 0; d < Pbulletv.size(); d++)
		{
			Bullet &tempbullet = Pbulletv[d];
			tempbullet.update(frameTime);
		}
		for (unsigned d = 0; d < Pmissilev.size(); d++)
		{
			Missile &tempmissile = Pmissilev[d];
			tempmissile.update(frameTime);
		}
		for (unsigned d = 0; d < Preflectorv.size(); d++)
		{
			Reflector &tempreflector = Preflectorv[d];
			tempreflector.update(frameTime);
		}
		for (unsigned d = 0; d < Pspecialv.size(); d++)
		{
			Special &tempspecial = Pspecialv[d];
			tempspecial.update(frameTime);
		}

		/*
		if (playership1X < 0)
		{
		cameraX -= playership1.getVelocity().x * frameTime; //scroll map right
		playership1.setX(0); //put the playership at left edge

		}

		else if (playership1X > (GAME_WIDTH - playership1.getWidth()))
		{
		cameraX -= playership1.getVelocity().x * frameTime; // scroll map left
		playership1.setX((float)(GAME_WIDTH - playership1.getWidth())); // put the player at right edge


		}

		else if (playership1Y < 0)
		{
		cameraY -= playership1.getVelocity().y * frameTime;
		playership1.setY(0);
		}

		else if (playership1Y > ( GAME_HEIGHT - playership1.getHeight()))
		{
		cameraY -= playership1.getVelocity().y * frameTime; // scroll map left
		playership1.setY((float)(GAME_HEIGHT - playership1.getHeight())); // put the player at right edge

		}

		if (cameraX > 0) // if the camera past left edge
		{
		cameraX = 0; // stop at left edge of map

		}
		else if (cameraY < 0)
		{
		cameraY = 0;
		}

		else if (cameraX > GAME_WIDTH - cameraWidth)
		{
		cameraX = GAME_WIDTH - cameraWidth;
		}

		else if (cameraY > GAME_HEIGHT - cameraHeight)
		{
		cameraY = GAME_HEIGHT - cameraHeight;
		}*/
		/*
		//camera
		int x = playership1.getX() - cameraX;
		int y = playership1.getY() - cameraY;

		//moving the camera
		if (cameraX < 0)
		cameraY = 0;
		if (cameraY < 0)
		cameraY = 0;
		if (cameraX > GAME_WIDTH - screenWidth)
		cameraX = GAME_WIDTH - screenWidth;

		if (cameraY > GAME_HEIGHT - screenHeight)
		cameraY = GAME_HEIGHT - screenHeight;

		//making the camera follow the player
		cameraX = playership1.getX() - screenWidth / 2;
		cameraY = playership1.getY() - screenHeight / 2;
		*/

		//enemy skills

		/*if (playership1.activate == true)
		{
		enemy.getX += frameTime * enemyNS::X - playershipNS::X;
		enemy.getY += frameTime * enemyNS::Y - playershipNS::Y;

		if (enemy.isbulletcool() == false)
		{
		if (!bullet.initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &bulletTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
		bullet.setFrames(BulletNS::BULLET_START_FRAME, BulletNS::BULLET_END_FRAME);
		bullet.setCurrentFrame(BulletNS::BULLET_START_FRAME);
		bullet.setX(enemy.getCenterX() - bullet.getWidth() / 2 * bullet.getScale());
		bullet.setY(enemy.getCenterY() - bullet.getHeight() / 2 * bullet.getScale());
		bullet.setdamage(2);
		bullet.setSpeed(30);
		bullet.setRadians(enemy.getRadians());
		bullet.isreflectable(true);
		Pbulletv.push_back(bullet);
		enemy.bulletfired(true);
		}
		}
		*/

		//if the playership at screen edge
		if ((playership1.getX() < SHIP_LIMIT_LEFT) || (playership1.getX() > SHIP_LIMIT_RIGHT))
		{
			// move background
			background.setX(background.getX() - frameTime * playership1.getVelocity().x);

			// keep playership on screen
			if (playership1.getX() < SHIP_LIMIT_LEFT)
				playership1.setX(SHIP_LIMIT_LEFT);
			if (playership1.getX() > SHIP_LIMIT_RIGHT)
				playership1.setX(SHIP_LIMIT_RIGHT);
		}
		if ((playership1.getY() < SHIP_LIMIT_TOP) || (playership1.getY() > SHIP_LIMIT_BOTTOM))
		{
			// move background
			background.setY(background.getY() - frameTime * playership1.getVelocity().y);
			// keep playership on screen
			if (playership1.getY() < SHIP_LIMIT_TOP)
				playership1.setY(SHIP_LIMIT_TOP);
			if (playership1.getY() > SHIP_LIMIT_BOTTOM)
				playership1.setY(SHIP_LIMIT_BOTTOM);
		}

		// Wrap space image around at edge
		// if left edge of background > screen left edge
		if (background.getX() > 0)
			// move background image left by SCREEN_WIDTH
			background.setX(background.getX() - ::SCREEN_WIDTH);
		// if background image off screen left
		if (background.getX() < -::SCREEN_WIDTH)
			// move background image right by SCREEN_WIDTH
			background.setX(background.getX() + ::SCREEN_WIDTH);
		// if top edge of background > screen top edge
		if (background.getY() > 0)
			// move background image up by SCREEN_HEIGHT
			background.setY(background.getY() - ::SCREEN_HEIGHT);
		// if background image off screen top
		if (background.getY() < -::SCREEN_HEIGHT)
			// move background image down by SCREEN_IMAGE
			background.setY(background.getY() + ::SCREEN_HEIGHT);
	}      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
