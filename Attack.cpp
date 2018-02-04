//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#include "Attack.h"


Attack::Attack() : Entity()
{
	collisionType = entityNS::BOX;
	spriteData.width = AttackNS::WIDTH;        // size of sword
	spriteData.height = AttackNS::HEIGHT;
	spriteData.x = AttackNS::X;                   // location on screen
	spriteData.y = AttackNS::Y;
	spriteData.rect.bottom = AttackNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = AttackNS::WIDTH;
	//frameDelay = AttackNS::SWORD_ANIMATION_DELAY;
	//startFrame = AttackNS::SWORD_START_FRAME;     // first frame of sword animation
	//endFrame = AttackNS::SWORD_END_FRAME;     // last frame of sword animation
	currentFrame = startFrame;
}
float Attack::setdamage(float d)
{
	Damage = d;
	return Damage;
}
float Attack::getdamage()
{
	return Damage;
}
float Attack::setSpeed(float s)
{
	Speed = s;
	return Speed;
}
float Attack::getSpeed()
{
	return Speed;
}
bool Attack::isreflectable(bool t)
{
	reflectable = t;
	return t;
}
void Attack::update(float frameTime)
{
	Entity::update(frameTime);

}
/*void Attack::damage(WEAPON)
{
}*/
void Attack::draw()
{
	Image::draw();
}
bool Attack::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
