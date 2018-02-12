//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

#include "playership.h"

//=============================================================================
// default constructor
//=============================================================================
playership::playership() : Entity()
{
	spriteData.scale = 0.5;
	spriteData.width = playershipNS::WIDTH;           // size of Ship1
	spriteData.height = playershipNS::HEIGHT;
	spriteData.x = playershipNS::X;                   // location on screen
	spriteData.y = playershipNS::Y;
	spriteData.rect.bottom = playershipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playershipNS::WIDTH;

	oldX = playershipNS::X;
	oldY = playershipNS::Y;
	oldAngle = 0.0f;
	rotation = 0.0f;


	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = playershipNS::SHIP_ANIMATION_DELAY;
	edge.top = playershipNS::HEIGHT / 2 * -1;             // ROTATED_BOX collision edges
	edge.bottom = playershipNS::HEIGHT / 2;
	edge.left = playershipNS::WIDTH / 2 * -1;
	edge.right = playershipNS::WIDTH / 2;


	// startFrame = playershipNS::SHIP1_START_FRAME;     // first frame of ship animation
	//  endFrame     = playershipNS::SHIP1_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = playershipNS::WIDTH / 2.0;
	//shieldOn = false;
	mass = playershipNS::MASS;
	collisionType = entityNS::ROTATED_BOX;
	healthcomponent.setmhealth(5);
	healthcomponent.setchealth(healthcomponent.getmhealth());
}

bool playership::isbulletcool()
{
	return bulletcool;
}

void playership::bulletfired(bool t)
{
	bulletcool = t;
	bulletcooldown = playershipNS::BULLETCOOLDOWN;
}

bool playership::ismissilecool()
{
	return missilecool;
}

void playership::missilefired(bool t)
{
	missilecool = t;
	missilecooldown = playershipNS::MISSILECOOLDOWN;
}

bool playership::isreflectorcool()
{
	return reflectorcool;
}

void playership::reflectorfired(bool t)
{
	reflectorcool = t;
	reflectorcooldown = playershipNS::REFLECTORCOOLDOWN;
}

bool playership::isspecialcool()
{
	return specialcool;
}

void playership::specialfired(bool t)
{
	specialcool = t;
	specialcooldown = playershipNS::SPECIALCOOLDOWN;
}

int playership::getpchealth()
{
	return healthcomponent.getchealth();
}

void playership::setpchealth(int i)
{
	healthcomponent.setchealth(i);
}

int playership::getpmhealth()
{
	return healthcomponent.getmhealth();
}

void playership::setpmhealth(int i)
{
	healthcomponent.setmhealth(i);
}



//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool playership::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	/*shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
	shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);                  // do not loop animation*/
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void playership::draw()
{

	Image::draw();              // draw ship
								//if(shieldOn)
								// draw shield using colorFilter 50% alpha
								//shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void playership::update(float frameTime)
{

	Entity::update(frameTime);
	oldX = spriteData.x;                        // save current position
	oldY = spriteData.y;
	oldAngle = spriteData.angle;


	healthcomponent.update();
	// Health regen
	if (healthcomponent.getchealth() <= healthcomponent.getmhealth())
	{
		regencount++;
		if (regencount >= playerregen)
		{
			healthcomponent.setchealth(healthcomponent.getchealth() + 1);
			regencount = 0;
		}

	}
	// health check
	if (healthcomponent.getchealth() > healthcomponent.getmhealth())
	{
		healthcomponent.setchealth(healthcomponent.getmhealth());
	}
	//skill cool down
	if (bulletcool == true)
	{
		bulletcooldown--;
		if (bulletcooldown <= 0)
		{
			bulletcool = false;
		}
	}
	if (missilecool == true)
	{
		missilecooldown--;
		if (missilecooldown <= 0)
		{
			missilecool = false;
		}
	}
	if (reflectorcool == true)
	{
		reflectorcooldown--;
		if (reflectorcooldown <= 0)
		{
			reflectorcool = false;
		}
	}
	if (specialcool == true)
	{
		specialcooldown--;
		if (specialcooldown <= 0)
		{
			specialcool = false;
		}
	}
	if (input->isKeyDown(VK_KEY_L))           // if move right front os 0
	{
		if (specialcool == false)
		{

		}
	}
	//movement rotate
	if (input->isKeyDown(VK_KEY_D))           // if move right front os 0
	{
		spriteData.angle += frameTime * playershipNS::ROTATION_RATE;
		//velocity.y = sin(spriteData.angle)*velocity.y;
		//velocity.x = cos(spriteData.angle)*velocity.x;
	}
	else if (input->isKeyDown(VK_KEY_A))           // if move left
	{
		spriteData.angle -= frameTime * playershipNS::ROTATION_RATE;
		//velocity.y = sin(spriteData.angle)*velocity.y;
		//velocity.x = cos(spriteData.angle)*velocity.x;
	}
	else if (input->isKeyDown(VK_KEY_W))           // if move up
	{

		velocity.y += sin(spriteData.angle)*playershipNS::SPEED;
		velocity.x += cos(spriteData.angle)*playershipNS::SPEED;
		if (velocity.y > playershipNS::MAXSPEED)
		{
			velocity.y = playershipNS::MAXSPEED;
		}
		if (velocity.x > playershipNS::MAXSPEED)
		{
			velocity.x = playershipNS::MAXSPEED;
		}
	}
	else if (input->isKeyDown(VK_KEY_S))           // if move down
	{
		velocity.y -= sin(spriteData.angle)*playershipNS::SPEED;
		velocity.x -= cos(spriteData.angle)*playershipNS::SPEED;
		if (velocity.y < playershipNS::MINSPEED)
		{
			velocity.y = playershipNS::MINSPEED;
		}
		if (velocity.x < playershipNS::MINSPEED)
		{
			velocity.x = playershipNS::MINSPEED;
		}
	}
	spriteData.x += frameTime *velocity.x;         // move ship along X 
	spriteData.y += frameTime *velocity.y;         // move ship along Y


												   // Bounce off walls
												   /*  if (spriteData.x > GAME_WIDTH-spriteData.width*spriteData.scale)    // if hit right screen edge
												   {
												   spriteData.x = GAME_WIDTH- spriteData.width*spriteData.scale;    // position at right screen edge
												   // velocity.x = 0;                   // reverse X direction
												   } else if (spriteData.x < 0)                    // else if hit left screen edge
												   {
												   spriteData.x = 0;                           // position at left screen edge
												   //  velocity.x = 0;                   // reverse X direction
												   }
												   if (spriteData.y > GAME_HEIGHT- spriteData.height*spriteData.scale)  // if hit bottom screen edge
												   {
												   spriteData.y = GAME_HEIGHT- spriteData.height*spriteData.scale;  // position at bottom screen edge
												   //  velocity.y = 0;                   // reverse Y direction
												   } else if (spriteData.y < 0)                    // else if hit top screen edge
												   {
												   spriteData.y = 0;                           // position at top screen edge
												   //  velocity.y = 0;                   // reverse Y direction
												   }*/
												   /*if(shieldOn)
												   {
												   shield.update(frameTime);
												   if(shield.getAnimationComplete())
												   {
												   shieldOn = false;
												   shield.setAnimationComplete(false);
												   }
												   }*/
}

//=============================================================================
// damage
//=============================================================================
//void Ship::damage(WEAPON weapon)
//{
//shieldOn = true;
//}

bool playership::IsInitialized()
{
	//Are we initialized (have a texture and sprite)
	return initialized;
}