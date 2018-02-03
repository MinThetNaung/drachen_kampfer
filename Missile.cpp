#include"Missile.h"

Missile::Missile()
{
	//spriteData.scale = 0.5;
	spriteData.width = MissileNS::WIDTH;           // size of Ship1
	spriteData.height = MissileNS::HEIGHT;
	spriteData.x = MissileNS::X;                   // location on screen
	spriteData.y = MissileNS::Y;
	spriteData.rect.bottom = MissileNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = MissileNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;
	collisionType = entityNS::ROTATED_BOX;
}

void Missile::draw()
{
	Image::draw();
}

bool Missile::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Missile::update(float frameTime)
{

	velocity.y += sin(spriteData.angle)*Speed;
	velocity.x += cos(spriteData.angle)*Speed;
	spriteData.x += frameTime *velocity.x;         // move bullet along X 
	spriteData.y += frameTime *velocity.y;
}
