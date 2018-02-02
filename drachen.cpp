// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 Drachen.cpp v1.0
// This class is the core of the game

#include "Drachen.h"

//=============================================================================
// Constructor
//=============================================================================
Drachen::Drachen()
{}

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
    if (!backgroundTexture.initialize(graphics,BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// enemy textures
	if (!enemyTextures.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));

    // nebula image
    if (!background.initialize(graphics,0,0,0,&backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// enemy image
	if (!enemy.initialize(this, 0, 0, 0, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));

	if (!bulletTextures.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet textures"));
	
	if (!missileTextures.initialize(graphics, MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile textures"));
    // planet
    //if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
        //throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

    // ship
    if (!playership1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, 0, &playershipTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	//playership1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	playership1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	playership1.setX(GAME_WIDTH/4);
	playership1.setY(GAME_HEIGHT/4);
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
    //planet.update(frameTime);
	playership1.update(frameTime,this);
	enemy.update(frameTime);
	//Player skills
	if (input->isKeyDown(VK_KEY_I))  //I         // if move right FSM forward declaration
	{

		if (!bullet.initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, 0, &bulletTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
		bullet.setCurrentFrame(BulletNS::BULLET_START_FRAME);
		bullet.setX(playership1.getX());
		bullet.setY(playership1.getY());
		bullet.setdamage(2);
		bullet.setSpeed(100);
		bullet.setRadians(playership1.getRadians());
		bullet.isreflectable(true);
		Pbulletv.push_back(bullet);
	}
	if (input->isKeyDown(VK_KEY_O))  //I         // if move right FSM forward declaration
	{
		if (!missile.initialize(this, MissileNS::WIDTH, MissileNS::HEIGHT, 0, &missileTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
		missile.setCurrentFrame(MissileNS::MISSILE_START_FRAME);
		missile.setX(playership1.getX());
		missile.setY(playership1.getY());
		missile.setdamage(2);
		missile.setSpeed(100);
		missile.setRadians(playership1.getRadians());
		missile.isreflectable(true);
		Pmissilev.push_back(missile);
	}
	//Player skills
	for (unsigned d = 0; d < Pbulletv.size(); d++)
	{
		Bullet &tempbullet = Pbulletv[d];
		tempbullet.update(frameTime);
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
		if (bullet.collidesWith(enemy, collisionVector))
		{
				// if bullet collideswith	 tempbullet.collidesWith(enemy, collisionVector) {
			Pbulletv.erase(Pbulletv.begin() + d);
			tmpBulletPointer = NULL;
		}
	}
	for (unsigned d = 0; d < Pmissilev.size(); d++)
	{
		Missile &tempmissile = Pmissilev[d];
		Missile *tmpMissilePointer = &tempmissile;
		if (bullet.collidesWith(enemy, collisionVector))
		{
			// if bullet collideswith	 tempbullet.collidesWith(enemy, collisionVector) {
			Pmissilev.erase(Pmissilev.begin() + d);
			tmpMissilePointer = NULL;
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
