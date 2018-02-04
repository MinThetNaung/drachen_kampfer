// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 Drachen.cpp v1.0
// This class is the core of the game

#include "Drachen.h"
using namespace drachenNS;

//=============================================================================
// Constructor
//=============================================================================
Drachen::Drachen()
{
	//The actual size of the display screen
	//screenWidth = 300;
	//screenHeight = 400;

	//camera position
	//cameraX = 0; 
	//cameraY = 0;


}

//=============================================================================
// Destructor
//=============================================================================
Drachen::~Drachen()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Drachen::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError
	if (!playershipTextures.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing characters textures"));
	// nebula texture
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// main game textures
	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// enemy textures
	if (!enemyTextures.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));

	// nebula image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// enemy image
	if (!enemy.initialize(this, 0, 0, 0, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));

	if (!bulletTextures.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet textures"));

	if (!missileTextures.initialize(graphics, MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile textures"));

	if (!reflectorTextures.initialize(graphics, REFLECTOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing reflector textures"));
	if (!specialTextures.initialize(graphics, SPECIAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing special textures"));
	// planet
	//if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
	//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// ship
	if (!playership1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, 0, &playershipTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	//playership1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	playership1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	//playership1.setX(GAME_WIDTH /4);
	//playership1.setY(GAME_HEIGHT/4);
	//To set the player ship in the center
	playership1.setX(GAME_WIDTH / 2 - shipNS::WIDTH / 2);
	playership1.setY(GAME_HEIGHT / 2 - shipNS::HEIGHT / 2);
	//ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
	// ship2

	// enemy
	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, 0, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	// Start enemy in the middle of left
	enemy.setX(GAME_WIDTH / 4 - enemyNS::WIDTH);
	enemy.setY(GAME_HEIGHT / 4 - enemyNS::HEIGHT);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Drachen::update()
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
		if (playership1.isbulletcool() == false)
		{
			if (!bullet.initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &bulletTextures))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
			bullet.setFrames(BulletNS::BULLET_START_FRAME, BulletNS::BULLET_END_FRAME);
			bullet.setCurrentFrame(BulletNS::BULLET_START_FRAME);
			bullet.setX(playership1.getCenterX() - bullet.getWidth() / 2 * bullet.getScale());
			bullet.setY(playership1.getCenterY() - bullet.getHeight() / 2 * bullet.getScale());
			bullet.setdamage(2);
			bullet.setSpeed(30);
			bullet.setRadians(playership1.getRadians());
			bullet.isreflectable(true);
			Pbulletv.push_back(bullet);
			playership1.bulletfired(true);
		}
	}
	if (input->isKeyDown(VK_KEY_O))  //I         // if move right FSM forward declaration
	{
		if (playership1.ismissilecool() == false)
		{
			if (!missile.initialize(this, MissileNS::WIDTH, MissileNS::HEIGHT, MissileNS::TEXTURE_COLS, &missileTextures))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
			missile.setFrames(MissileNS::MISSILE_START_FRAME, MissileNS::MISSILE_END_FRAME);
			missile.setCurrentFrame(MissileNS::MISSILE_START_FRAME);
			missile.setX(playership1.getCenterX() - missile.getWidth() / 2 * missile.getScale());
			missile.setY(playership1.getCenterY() - missile.getHeight() / 2 * missile.getScale());
			missile.setdamage(5);
			missile.setSpeed(20);
			missile.setRadians(playership1.getRadians());
			missile.isreflectable(false);
			Pmissilev.push_back(missile);
			playership1.missilefired(true);
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
		if (playership1.isspecialcool() == false)
		{
			if (!special.initialize(this, SpecialNS::WIDTH, SpecialNS::HEIGHT, SpecialNS::TEXTURE_COLS, &specialTextures))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing special"));
			special.setFrames(SpecialNS::SPECIAL_START_FRAME, SpecialNS::SPECIAL_END_FRAME);
			special.setCurrentFrame(ReflectorNS::REFLECTOR_START_FRAME);
			special.setX(playership1.getCenterX() - special.getWidth() / 2 * special.getScale());
			special.setY(playership1.getCenterY() - special.getHeight() / 2 * special.getScale());
			special.setdamage(50);
			special.setSpeed(30);
			special.setRadians(playership1.getRadians());
			special.isreflectable(false);
			Pspecialv.push_back(special);
			playership1.specialfired(true);
			playership1.setpmhealth(playership1.getpmhealth() - 1);

		}
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

	if (playership1.activate == true)
	{
		enemy.getX += frameTime * enemyNS::X - shipNS::X;
		enemy.getY += frameTime * enemyNS::Y - shipNS::Y;

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
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Drachen::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Drachen::collisions()
{

	VECTOR2 collisionVector;
	for (unsigned d = 0; d < Pbulletv.size(); d++)
	{
		Bullet &tempbullet = Pbulletv[d];
		Bullet *tmpBulletPointer = &tempbullet;
		// enemy collide
		for (unsigned e = 0; e < Enemyv.size(); e++)
		{
			Enemy &tempenemy = Enemyv[e];
			Enemy *tmpEnemyPointer = &tempenemy;
			if (tempbullet.collidesWith(tempenemy, collisionVector))
			{
				//tempenemy.setchealth() = tempenemy.getchealth() - tempbullet.getdamage()
				Pbulletv.erase(Pbulletv.begin() + d);
				tmpBulletPointer = NULL;
			}

		}
		//reflect collide
		for (unsigned e = 0; e < Preflectorv.size(); e++)
		{
			Reflector &tempreflector = Preflectorv[e];
			Reflector *tmpReflectorPointer = &tempreflector;
			if (tempbullet.collidesWith(tempreflector, collisionVector))
			{
				tempbullet.bounce(collisionVector, tempreflector);
			}
		}
	}
	for (unsigned d = 0; d < Pmissilev.size(); d++)
	{
		Missile &tempmissile = Pmissilev[d];
		Missile *tmpMissilePointer = &tempmissile;
		for (unsigned e = 0; e < Enemyv.size(); e++)
		{
			Enemy &tempenemy = Enemyv[e];
			Enemy *tmpEnemyPointer = &tempenemy;
			if (tempmissile.collidesWith(tempenemy, collisionVector))
			{
				//tempenemy.setchealth() = tempenemy.getchealth() - tempmissile.getdamage()
				Pmissilev.erase(Pmissilev.begin() + d);
				tmpMissilePointer = NULL;
			}
		}
		for (unsigned e = 0; e < Preflectorv.size(); e++)
		{
			Reflector &tempreflector = Preflectorv[e];
			Reflector *tmpReflectorPointer = &tempreflector;
			if (tempmissile.collidesWith(tempreflector, collisionVector))
			{
				Pmissilev.erase(Pmissilev.begin() + d);
				tmpMissilePointer = NULL;
				Preflectorv.erase(Preflectorv.begin() + e);
				tmpReflectorPointer = NULL;
			}
		}
	}
	for (unsigned d = 0; d < Pspecialv.size(); d++)
	{
		Special &tempspecial = Pspecialv[d];
		Special *tmpSpecialPointer = &tempspecial;
		for (unsigned e = 0; e < Enemyv.size(); e++)
		{
			Enemy &tempenemy = Enemyv[e];
			Enemy *tmpEnemyPointer = &tempenemy;
			if (tempspecial.collidesWith(tempenemy, collisionVector))
			{
				//tempenemy.setchealth() = tempenemy.getchealth() - tempspecial.getdamage()
				Pspecialv.erase(Pspecialv.begin() + d);
				tmpSpecialPointer = NULL;
			}
		}
		for (unsigned e = 0; e < Preflectorv.size(); e++)
		{
			Reflector &tempreflector = Preflectorv[e];
			Reflector *tmpReflectorPointer = &tempreflector;
			if (tempspecial.collidesWith(tempreflector, collisionVector))
			{
				Pspecialv.erase(Pspecialv.begin() + d);
				tmpSpecialPointer = NULL;
				Preflectorv.erase(Preflectorv.begin() + e);
				tmpReflectorPointer = NULL;
			}
		}
	}

	// if collision between ship and planet
	/*if(ship1.collidesWith(planet, collisionVector))
	{
	// bounce off planet
	ship1.bounce(collisionVector, planet);
	ship1.damage(PLANET);
	}*/

	// if collision between ships
	/*if(ship1.collidesWith(ship2, collisionVector))
	{
	// bounce off ship
	ship1.bounce(collisionVector, ship2);
	ship1.damage(SHIP);
	// change the direction of the collisionVector for ship2
	ship2.bounce(collisionVector*-1, ship1);
	ship2.damage(SHIP);
	}*/
}

//=============================================================================
// Render game items
//=============================================================================
void Drachen::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	playership1.draw();                           // add the spaceship to the scene
	enemy.draw();
	for (unsigned d = 0; d < Pbulletv.size(); d++)
	{
		Bullet &tempbullet = Pbulletv[d];
		tempbullet.draw();
	}
	//ship2.draw();                           // add the spaceship to the scene
	for (unsigned d = 0; d < Pmissilev.size(); d++)
	{
		Missile &tempmissile = Pmissilev[d];
		tempmissile.draw();
	}
	for (unsigned d = 0; d < Preflectorv.size(); d++)
	{
		Reflector &tempreflector = Preflectorv[d];
		tempreflector.draw();
	}
	for (unsigned d = 0; d < Pspecialv.size(); d++)
	{
		Special &tempspecial = Pspecialv[d];
		tempspecial.draw();
	}
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Drachen::releaseAll()
{
	backgroundTexture.onLostDevice();
	gameTextures.onLostDevice();
	enemyTextures.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Drachen::resetAll()
{
	gameTextures.onResetDevice();

	enemyTextures.onResetDevice();
	backgroundTexture.onResetDevice();
	Game::resetAll();
	return;
}