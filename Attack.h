//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#pragma once
#include "entity.h"
#include "constants.h"
namespace AttackNS
{
	const int WIDTH = 48;                   // image width
	const int HEIGHT = 48;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int   TEXTURE_COLS = 3;
	//const int   SWORD_START_FRAME = 0;      // sword start
	//const int   SWORD_END_FRAME = 4;
	//const float SWORD_ANIMATION_DELAY = 0.3f;
}
class Attack : public Entity
{
private:

public:
	// constructor
	Attack();
	float Damage;
	float Speed;
	bool reflectable;
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	//void damage(WEAPON);
	float setdamage(float d); // set the starting damage
	float getdamage();
	float setSpeed(float s);
	float getSpeed();
	bool isreflectable(bool t);
};