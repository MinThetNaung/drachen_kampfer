// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	if (!playershipTextures.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing characters textures"));
    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

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
    

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
    //planet.update(frameTime);
	playership1.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
    VECTOR2 collisionVector;
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
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    nebula.draw();                          // add the orion nebula to the scene
    planet.draw();                          // add the planet to the scene
    playership1.draw();                           // add the spaceship to the scene
    //ship2.draw();                           // add the spaceship to the scene

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    nebulaTexture.onLostDevice();
    gameTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
    nebulaTexture.onResetDevice();
    Game::resetAll();
    return;
}
