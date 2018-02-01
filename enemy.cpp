#include "enemy.h"
using namespace enemyNS;

//=============================================================================
// default constructor
//=============================================================================
Enemy::Enemy() : Entity()
{
	spriteData.width = WIDTH;           // size of butterfly
	spriteData.height = HEIGHT;
	spriteData.x = X;                   // location on screen
	spriteData.y = Y;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
	edge.top = EDGE_TOP;             // ROTATED_BOX collision edges
	edge.bottom = EDGE_BOTTOM;
	edge.left = EDGE_LEFT;
	edge.right = EDGE_RIGHT;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = ENEMY_ANIMATION_DELAY;
	startFrame = ENEMY_START_FRAME;     // first frame of animation
	endFrame = ENEMY_END_FRAME;     // last frame of animationaa
	currentFrame = startFrame;
	radius = WIDTH / 2.0;
	collisionType = entityNS::ROTATED_BOX;
	mass = enemyNS::MASS;
}

//=============================================================================
// Initialize the Enemy.
// Post: returns true if successful, false if failed
//=============================================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the enemy
//=============================================================================
void Enemy::draw()
{
	Image::draw();              // draw enemy
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move player along X 

													// Bounce off walls
	if (spriteData.x > GAME_WIDTH - enemyNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - enemyNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	spriteData.x += velocity.x * frameTime;
}
