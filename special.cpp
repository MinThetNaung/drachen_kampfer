//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#include"special.h"

Special::Special()
{
	//spriteData.scale = 0.5;
	spriteData.width = SpecialNS::WIDTH;           // size of Ship1
	spriteData.height = SpecialNS::HEIGHT;
	spriteData.x = SpecialNS::X;                   // location on screen
	spriteData.y = SpecialNS::Y;
	spriteData.rect.bottom = SpecialNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = SpecialNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;
	collisionType = entityNS::ROTATED_BOX;
}

void Special::draw()
{
	Image::draw();
}

bool Special::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Special::update(float frameTime)
{
	Entity::update(frameTime);
	velocity.y += sin(spriteData.angle)*Speed;
	velocity.x += cos(spriteData.angle)*Speed;
	spriteData.x += frameTime *velocity.x;         // move bullet along X 
	spriteData.y += frameTime *velocity.y;
}