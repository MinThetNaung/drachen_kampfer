//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

#include "enemy.h"
#include "playership.h"

//=============================================================================
// default constructor
//=============================================================================
Enemy::Enemy(/*int in_x, int in_y, int in_vx, int in_vy*/) : Entity()

{
	spriteData.scale = 0.5;
	spriteData.width = EnemyNS::WIDTH;           // size of Ship1
	spriteData.height = EnemyNS::HEIGHT;
	spriteData.x = EnemyNS::X;                   // location on screen
	spriteData.y = EnemyNS::Y;
	spriteData.rect.bottom = EnemyNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = EnemyNS::WIDTH;
	oldX = EnemyNS::X;
	oldY = EnemyNS::Y;
	oldAngle = 0.0f;
	rotation = 0.0f;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	currentFrame = startFrame;
	mass = EnemyNS::MASS;
	collisionType = entityNS::CIRCLE;
	radius = EnemyNS::WIDTH / 2.0;
}



//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ENEMY
//=============================================================================
void Enemy::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Enemy::update(float frameTime)
{

	Entity::update(frameTime);
	//oldX = spriteData.x;                        // save current position
	//oldY = spriteData.y;
	//oldAngle = spriteData.angle;

	dx = playershipNS::X - EnemyNS::X;
	dy = playershipNS::Y - EnemyNS::Y;
	angle = atan2(dy, dx);

	vx = cos(angle) * EnemyNS::SPEED;
	vy = sin(angle) * EnemyNS::SPEED;

	/*while (spriteData.angle != angle)
	{
	spriteData.angle += frameTime * EnemyNS::ROTATION_RATE;  // rotate the ship
	}*/
	spriteData.angle += frameTime * EnemyNS::ROTATION_RATE;
	spriteData.x += frameTime * vx;         // move ship along X 
	spriteData.y += frameTime * vy;         // move ship along Y   

											/*velocity.y += sin(spriteData.angle)*playershipNS::SPEED;
											velocity.x += cos(spriteData.angle)*playershipNS::SPEED;
											spriteData.x += frameTime *velocity.x;         // move ship along X
											spriteData.y += frameTime *velocity.y;         // move ship along Y*/

											// Wrap around screen edge
	if (spriteData.x > GAME_WIDTH)              // if off right screen edge
		spriteData.x = -EnemyNS::WIDTH;          // position off left screen edge
	else if (spriteData.x < -EnemyNS::WIDTH)     // else if off left screen edge
		spriteData.x = GAME_WIDTH;              // position off right screen edge
	if (spriteData.y > GAME_HEIGHT)             // if off bottom screen edge
		spriteData.y = -EnemyNS::HEIGHT;         // position off top screen edge
	else if (spriteData.y < -EnemyNS::HEIGHT)    // else if off top screen edge
		spriteData.y = GAME_HEIGHT;             // position off bottom screen edge

}

//=============================================================================
// damage
//=============================================================================
//void Ship::damage(WEAPON weapon)
//{
//shieldOn = true;
//}


// constructor

/*inline Enemy::Enemy(/*int in_x, int in_y, int in_vx, int in_vy)
{
x = in_x;
y = in_y;
vx = in_vx;
vy = in_vy;
}*/

bool Enemy::IsInitialized()
{
	//Are we initialized (have a texture and sprite)
	return initialized;
}
