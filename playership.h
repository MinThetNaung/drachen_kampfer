//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

#ifndef _PLAYERSHIP_H                 // Prevent multiple definitions if this 
#define _PLAYERSHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "Movementcomponent.h"
#include "Healthcomponent.h"
#include "Bullet.h"

using namespace std;
namespace playershipNS
{
	const int WIDTH = 160;                   // image width
	const int HEIGHT = 160;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)2 * PI; // radians per second
	const float SPEED = 10;                // 100 pixels per second
	const float MAXSPEED = 200;
	const float MINSPEED = -200;
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
	const int   SHIP1_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
	const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
	const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
	const int   SHIELD_START_FRAME = 24;    // shield start frame
	const int   SHIELD_END_FRAME = 27;      // shield end frame
	const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
	const int BULLETCOOLDOWN = 50;
	const int MISSILECOOLDOWN = 500;
	const int REFLECTORCOOLDOWN = 10000;
	const int SPECIALCOOLDOWN = 50000;
	const float BULLETDAMAGE = 5;
	const float BULLETSPEED = 500;
	const float MISSILEDAMAGE = 10;
	const float MISSILESPEED = 30;
	const float SPECIALDAMAGE = 50;
	const float SPECIALSPEED = 50;


}

// inherits from Entity class
class playership : public Entity
{
private:
	MovementComponent movecomponent;
	HealthComponent healthcomponent;

	float   oldX, oldY, oldAngle;
	float   rotation;
	bool bulletcool = false;
	int bulletcooldown = 0;
	bool missilecool = false;
	int missilecooldown = 0;
	bool reflectorcool = false;
	int reflectorcooldown = 0;
	bool specialcool = false;
	int specialcooldown = 0;
	//TextureManager bulletTextures;

	//bool    shieldOn;
	//Image   shield;
public:
	// constructor
	playership();
	bool isbulletcool();
	void bulletfired(bool t);
	bool ismissilecool();
	void missilefired(bool t);
	bool isreflectorcool();
	void reflectorfired(bool t);
	State state;
	D3DXVECTOR3 position;
	bool IsInitialized();
	int regencount = 0;
	bool isspecialcool();
	void specialfired(bool t);
	int getpchealth();
	void setpchealth(int i);
	int getpmhealth();
	void setpmhealth(int i);


	// move ship out of collision
	void toOldPosition()
	{
		spriteData.x = oldX;
		spriteData.y = oldY,
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

