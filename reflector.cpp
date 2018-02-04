//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#include"Reflector.h"

Reflector::Reflector()
{
	spriteData.scale = 0.1;
	spriteData.width = ReflectorNS::WIDTH;           // size of Ship1
	spriteData.height = ReflectorNS::HEIGHT;
	spriteData.x = ReflectorNS::X;                   // location on screen
	spriteData.y = ReflectorNS::Y;
	spriteData.rect.bottom = ReflectorNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = ReflectorNS::WIDTH;
	radius = ReflectorNS::WIDTH*spriteData.scale;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;
	collisionType = entityNS::CIRCLE;
}

void Reflector::draw()
{
	Image::draw();
}

bool Reflector::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Reflector::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * ReflectorNS::ROTATION_RATE;
}