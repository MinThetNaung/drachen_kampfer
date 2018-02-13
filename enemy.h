//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

#ifndef _ENEMY_H                 // Prevent multiple definitions if this 
#define _ENEMY_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <random>
#include <stdlib.h>

using namespace std;
namespace EnemyNS
{
	const int WIDTH = 160;                   // image width
	const int HEIGHT = 160;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)2 * PI; // radians per second
	const float SPEED = rand() % 300 + 1;             // 1 < spd < 300 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   ENEMY_START_FRAME = 0;      // ship1 starts at frame 0
	const int   ENEMY_END_FRAME = 0;        // ship1 animation frames 0,1,2,3
}

// inherits from Entity class
class Enemy : public Entity
{
private:
	float   oldX, oldY, oldAngle;
	float   rotation;
	float dx;
	float dy;
	float angle;
	float x, y, vx, vy;

	//bool    shieldOn;
	//Image   shield;
public:
	// constructor
	Enemy(/*int in_x, int in_y, int in_vx, int in_vy*/);
	State state;
	D3DXVECTOR3 position;
	bool IsInitialized();

	// move ENEMY out of collision
	void toOldPosition()
	{
		spriteData.x = oldX;
		spriteData.y = oldY;
		spriteData.angle = oldAngle;
		rotation = 0.0f;
	}

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	//void damage(WEAPON);
};
#endif

