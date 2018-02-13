//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

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
	//int randX, randY;
    Game::initialize(hwnd); // throws GameError
	if (!playershipTextures.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing characters textures"));
	// background texture
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
	//	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
	//      throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// enemy textures
	if (!enemyTextures.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));




	// background image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	background.setScale((float)::SCREEN_SCALE);

	// enemy image
	//if (!enemy.initialize(this, 0, 0, 0, &enemyTextures))
	//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));

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
    if (!playership1.initialize(this, playershipNS::WIDTH, playershipNS::HEIGHT, 0, &playershipTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	//playership1.setFrames(playershipNS::SHIP1_START_FRAME, playershipNS::SHIP1_END_FRAME);
	playership1.setCurrentFrame(playershipNS::SHIP1_START_FRAME);
	//playership1.setX(GAME_WIDTH /4);
	//playership1.setY(GAME_HEIGHT/4);
	//To set the player ship in the center
	playership1.setX(GAME_WIDTH / 2 - playershipNS::WIDTH / 2);
	playership1.setY(GAME_HEIGHT / 2 - playershipNS::HEIGHT / 2);
	playership1.state = STATE_NORMAL;
	playership1.setMass(playershipNS::MASS);

	playership1.setVelocity(VECTOR2(playershipNS::SPEED, -playershipNS::SPEED)); // VECTOR2(X, Y)
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

				float angle = atan2(tempreflector.getCenterY() - tempbullet.getCenterY(), tempreflector.getCenterX() - tempbullet.getCenterX());
				tempbullet.setRadians(tempbullet.getRadians() + angle);
				//tempbullet.setVelocity();
				/*tempbullet.flipHorizontal(true);
				tempbullet.flipVertical(true);*/
				//tempbullet.setVelocity(tempbullet.getVelocity());
				//tempbullet.setSpeed(tempbullet.getSpeed() *-1);

				/*double distPerpWall = (tempbullet.getCenterX() * tempreflector.getCenterX() + tempbullet.getCenterY * tempreflector.getCenterY()) / hypot(tempreflector.getCenterX(), tempreflector.getCenterY());
				double distParWall = (tempbullet.getCenterX() * tempreflector.getCenterX() + tempbullet.getCenterY * tempreflector.getCenterY()) / hypot(tempreflector.getCenterX(), -tempreflector.getCenterY());
				distPerpWall = -distPerpWall;

				tempbullet.setDeltaV =distParWall * tempreflector.getCenterY() + distPerpWall * tempreflector.getCenterX();
				tempbullet.setDeltaV = distParWall * -tempreflector.getCenterX() + distPerpWall * tempreflector.getCenterY();*/
				//tempbullet.bounce(collisionVector, tempreflector);
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
	for (unsigned e = 0; e < Enemyv.size(); e++)
	{
		Enemy &tempenemy = Enemyv[e];
		Enemy *tmpEnemyPointer = &tempenemy;
		if (playership1.collidesWith(tempenemy, collisionVector))
		{
			playership1.setpchealth(playership1.getpchealth() - 1);
			Enemyv.erase(Enemyv.begin() + e);
			tmpEnemyPointer = NULL;
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




	float x = background.getX();
	float y = background.getY();
	//wrap image around at edges
    background.draw();                          // add the orion nebula to the scene                       // add the planet to the scene
												// if background image right edge visible
	if (background.getX() < -::SCREEN_WIDTH + (int)GAME_WIDTH)
	{
		background.setX(background.getX() + ::SCREEN_WIDTH); // wrap around to left edge
		background.draw();                           // draw again
	}
	// if background image bottom edge visible
	if (background.getY() < -::SCREEN_HEIGHT + (int)GAME_HEIGHT)
	{
		background.setY(background.getY() + ::SCREEN_HEIGHT); // wrap around to top edge
		background.draw();                           // draw again
		background.setX(x);                          // restore x position
													 // if background image right edge visible
													 // wrap around to left edge
		if (background.getX() < -::SCREEN_WIDTH + (int)GAME_WIDTH)
			background.draw();                       // draw again
	}
	background.setY(y);      // restore y position


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

	playership1.draw();
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Drachen::releaseAll()
{
    backgroundTexture.onLostDevice();
	playershipTextures.onLostDevice();
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
	playershipTextures.onResetDevice();
   
	enemyTextures.onResetDevice();
    backgroundTexture.onResetDevice();
    Game::resetAll();
    return;
}
