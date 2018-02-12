//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
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
	edge.top = BulletNS::HEIGHT / 2 * -1;             // ROTATED_BOX collision edges
	edge.bottom = BulletNS::HEIGHT / 2;
	edge.left = BulletNS::WIDTH / 2 * -1;
	edge.right = BulletNS::WIDTH / 2;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;
	currentFrame = startFrame;
	collisionType = entityNS::ROTATED_BOX;
	reflectable = true;
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
	Entity::update(frameTime);
	velocity.y = sin(spriteData.angle)*Speed;
	velocity.x = cos(spriteData.angle)*Speed;
	spriteData.x += frameTime *velocity.x;         // move bullet along X 
	spriteData.y += frameTime *velocity.y;
}

