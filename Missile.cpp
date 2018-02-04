//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
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
	edge.top = MissileNS::HEIGHT / 2 * -1;             // ROTATED_BOX collision edges
	edge.bottom = MissileNS::HEIGHT / 2;
	edge.left = MissileNS::WIDTH / 2 * -1;
	edge.right = MissileNS::WIDTH / 2;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;
	collisionType = entityNS::BOX;
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
	Entity::update(frameTime);
	velocity.y += sin(spriteData.angle)*Speed;
	velocity.x += cos(spriteData.angle)*Speed;
	spriteData.x += frameTime *velocity.x;         // move bullet along X 
	spriteData.y += frameTime *velocity.y;
}
