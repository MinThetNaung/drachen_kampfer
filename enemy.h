//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#pragma once

#ifndef _ENEMY_H            // Prevent multiple definitions if this 
#define _ENEMY_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "Movementcomponent.h"
#include "Healthcomponent.h"
#include "Bullet.h"

namespace enemyNS
{
	const int   WIDTH = 192;                // image width (each frame)
	const int   HEIGHT = 192;               // image height
	const int   X = GAME_WIDTH / 2 - WIDTH / 2;    // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int   EDGE_TOP = -60;             // For BOX and ROTATE_BOX collison.
	const int   EDGE_BOTTOM = 60;           // "   relative to center
	const int   EDGE_LEFT = -60;            // "
	const int   EDGE_RIGHT = 60;            // "
	const float ROTATION_RATE = (float)2 * PI; // radians per second
	const float SPEED = 50;                 // pixels per second
	const float MAX_SPEED = 100;
	const float MASS = 300.0f;                // mass
	const int   TEXTURE_COLS = 1;			// texture has 1 columns
	const int   ENEMY_START_FRAME = 0;     // animation starting frame
	const int   ENEMY_END_FRAME = 0;       // animation ending frame
	const float ENEMY_ANIMATION_DELAY = 0.1f;    // time between frames
	const int BULLETCOOLDOWN = 100;
	const float angle = 0;
}

// inherits from Entity class
class Enemy : public Entity
{
private:
	MovementComponent movecomponent;
	HealthComponent healthcomponent;
	float   oldX, oldY, oldAngle;
	float   rotation;                       // current rotation rate (radians/second)
	bool bulletcool = false;
	int bulletcooldown = 0;

public:
	// constructor
	Enemy();
	bool isbulletcool();
	void bulletfired(bool t);

	void draw();

	// inherited member functions
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	// new functions
	void setVelocityX(float v) { velocity.x = v; }
};
#endif