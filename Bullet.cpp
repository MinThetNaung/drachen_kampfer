#include"Bullet.h"

Bullet::Bullet()
{
	spriteData.scale = 0.5;
	spriteData.width = BulletNS::WIDTH;           // size of Ship1
	spriteData.height = BulletNS::HEIGHT;
	spriteData.x = BulletNS::X;                   // location on screen
	spriteData.y = BulletNS::Y;
	spriteData.rect.bottom = BulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = BulletNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;
	collisionType = entityNS::ROTATED_BOX;
}

void Bullet::draw()
{
	Image::draw();
}

bool Bullet::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Bullet::update(float frameTime)
{
	
	velocity.y += sin(spriteData.angle)*Speed;
	velocity.x += cos(spriteData.angle)*Speed;
	spriteData.x += frameTime *velocity.x;         // move bullet along X 
	spriteData.y += frameTime *velocity.y;
}
