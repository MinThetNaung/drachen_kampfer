#pragma once
#include "Attack.h"
#include "constants.h"
namespace BulletNS
{
	const int WIDTH = 177;                   // image width
	const int HEIGHT = 164;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int   TEXTURE_COLS = 3;
	const int   BULLET_START_FRAME = 0;      // ship1 starts at frame 0
	const int   BULLET_END_FRAME = 2;
	//const int   SWORD_START_FRAME = 0;      // sword start
	//const int   SWORD_END_FRAME = 4;
	//const float SWORD_ANIMATION_DELAY = 0.3f;
}
class Bullet : public Attack
{
private:
	
	//bool    shieldOn;
	//Image   shield;
public:
	// constructor
	Bullet();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	//void damage(WEAPON);
};
