//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B

#include "Drachen.h"
using namespace drachenNS;

//=============================================================================
// Constructor
//=============================================================================
Drachen::Drachen()
{
	//The actual size of the display screen
	//screenWidth = 300;
	//screenHeight = 400;

	//camera position
	//cameraX = 0; 
	//cameraY = 0;


}

//=============================================================================
// Destructor
//=============================================================================
Drachen::~Drachen()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Drachen::initialize(HWND hwnd)
{
	//int randX, randY;
	Game::initialize(hwnd); // throws GameError
	if (!playershipTextures.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing characters textures"));
	// background texture
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// menu texture
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	// instruction texture
	if (!instructionTexture.initialize(graphics, INSTRUCTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction texture"));

	// credit texture
	if (!creditTexture.initialize(graphics, CREDIT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credit texture"));

	// cursor texture
	if (!cursorTexture.initialize(graphics, CURSOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cursor texture"));
	// main game textures
	//	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
	//      throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// enemy textures
	if (!enemyTextures.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));




	// background image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	background.setScale((float)::SCREEN_SCALE);

	//Menu image
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu textures"));

	//Instruction image
	if (!instructionTexture.initialize(graphics, INSTRUCTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction textures"));

	//credit image
	if (!creditTexture.initialize(graphics, CREDIT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credit textures"));

	//cursor image
	if (!cursorTexture.initialize(graphics, CURSOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cursor textures"));


	// enemy image
	//if (!enemy.initialize(this, 0, 0, 0, &enemyTextures))
	//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));

	if (!bulletTextures.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet textures"));

	if (!missileTextures.initialize(graphics, MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile textures"));

	if (!reflectorTextures.initialize(graphics, REFLECTOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing reflector textures"));
	if (!specialTextures.initialize(graphics, SPECIAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing special textures"));
	// planet
	//if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
	//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// ship
	if (!playership1.initialize(this, playershipNS::WIDTH, playershipNS::HEIGHT, 0, &playershipTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	//playership1.setFrames(playershipNS::SHIP1_START_FRAME, playershipNS::SHIP1_END_FRAME);
	playership1.setCurrentFrame(playershipNS::SHIP1_START_FRAME);
	//playership1.setX(GAME_WIDTH /4);
	//playership1.setY(GAME_HEIGHT/4);
	//To set the player ship in the center
	playership1.setX(GAME_WIDTH / 2 - playershipNS::WIDTH / 2);
	playership1.setY(GAME_HEIGHT / 2 - playershipNS::HEIGHT / 2);
	playership1.state = STATE_NORMAL;
	playership1.setMass(playershipNS::MASS);

	playership1.setVelocity(VECTOR2(playershipNS::SPEED, -playershipNS::SPEED)); // VECTOR2(X, Y)
																				 // ship2

																				 // enemy
																				 // enemy
	if (!enemy0.initialize(this, EnemyNS::WIDTH, EnemyNS::HEIGHT, 0, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy0.setFrames(EnemyNS::ENEMY_START_FRAME, EnemyNS::ENEMY_END_FRAME);
	enemy0.setCurrentFrame(EnemyNS::ENEMY_START_FRAME);
	// Start enemy in the middle of left
	enemy0.setX(GAME_WIDTH - EnemyNS::WIDTH);
	enemy0.setY(GAME_HEIGHT - EnemyNS::HEIGHT);
	enemy0.setVelocity(VECTOR2(-EnemyNS::SPEED, -EnemyNS::SPEED)); // VECTOR2(X, Y)

	if (!enemy1.initialize(this, EnemyNS::WIDTH, EnemyNS::HEIGHT, 0, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy1.setFrames(EnemyNS::ENEMY_START_FRAME, EnemyNS::ENEMY_END_FRAME);
	enemy1.setCurrentFrame(EnemyNS::ENEMY_START_FRAME);
	// Start enemy in the middle of left
	enemy1.setX(GAME_WIDTH / 2 - EnemyNS::WIDTH);
	enemy1.setY(GAME_HEIGHT / 2 - EnemyNS::HEIGHT);
	enemy1.setVelocity(VECTOR2(-EnemyNS::SPEED, -EnemyNS::SPEED)); // VECTOR2(X, Y)

	if (!enemy2.initialize(this, EnemyNS::WIDTH, EnemyNS::HEIGHT, 0, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy2.setFrames(EnemyNS::ENEMY_START_FRAME, EnemyNS::ENEMY_END_FRAME);
	enemy2.setCurrentFrame(EnemyNS::ENEMY_START_FRAME);
	// Start enemy in the middle of left
	enemy2.setX(GAME_WIDTH / 3 - EnemyNS::WIDTH);
	enemy2.setY(GAME_HEIGHT / 3 - EnemyNS::HEIGHT);
	enemy2.setVelocity(VECTOR2(-EnemyNS::SPEED, -EnemyNS::SPEED)); // VECTOR2(X, Y)

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Drachen::update()
{
	/*float playership1X;
	float playership1Y;

	playership1X = playership1.getX(); //get player location
	playership1Y = playership1.getY();
	*/

	//planet.update(frameTime);
	playership1.update(frameTime);

	//Player skills
	if (input->isKeyDown(VK_KEY_I))  //I         // if move right FSM forward declaration
	{
		if (playership1.state == STATE_NORMAL || playership1.state == STATE_BULLET)
		{
			if (playership1.isbulletcool() == false)
			{
				if (!bullet.initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &bulletTextures))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
				bullet.setFrames(BulletNS::BULLET_START_FRAME, BulletNS::BULLET_END_FRAME);
				bullet.setCurrentFrame(BulletNS::BULLET_START_FRAME);
				bullet.setX(playership1.getCenterX() - bullet.getWidth() / 2 * bullet.getScale());
				bullet.setY(playership1.getCenterY() - bullet.getHeight() / 2 * bullet.getScale());
				bullet.setdamage(playershipNS::BULLETDAMAGE);
				bullet.setSpeed(playershipNS::BULLETSPEED);
				bullet.setRadians(playership1.getRadians());
				bullet.isreflectable(true);
				Pbulletv.push_back(bullet);
				playership1.bulletfired(true);
				playership1.state = STATE_BULLET;
			}
		}
	}
	if (input->isKeyDown(VK_KEY_O))  //I         // if move right FSM forward declaration
	{
		if (playership1.state == STATE_NORMAL || playership1.state == STATE_MISSILE)
		{
			if (playership1.ismissilecool() == false)
			{
				if (!missile.initialize(this, MissileNS::WIDTH, MissileNS::HEIGHT, MissileNS::TEXTURE_COLS, &missileTextures))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
				missile.setFrames(MissileNS::MISSILE_START_FRAME, MissileNS::MISSILE_END_FRAME);
				missile.setCurrentFrame(MissileNS::MISSILE_START_FRAME);
				missile.setX(playership1.getCenterX() - missile.getWidth() / 2 * missile.getScale());
				missile.setY(playership1.getCenterY() - missile.getHeight() / 2 * missile.getScale());
				missile.setdamage(playershipNS::MISSILEDAMAGE);
				missile.setSpeed(playershipNS::MISSILESPEED);
				missile.setRadians(playership1.getRadians());
				missile.isreflectable(false);
				Pmissilev.push_back(missile);
				playership1.missilefired(true);
				playership1.state = STATE_MISSILE;
			}
		}
	}
	if (input->isKeyDown(VK_KEY_P))  //I         // if move right FSM forward declaration
	{
		if (playership1.isreflectorcool() == false)
		{
			if (!reflector.initialize(this, ReflectorNS::WIDTH, ReflectorNS::HEIGHT, ReflectorNS::TEXTURE_COLS, &reflectorTextures))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing reflector"));
			//missile.setFrames(MissileNS::MISSILE_START_FRAME, MissileNS::MISSILE_END_FRAME);
			reflector.setCurrentFrame(ReflectorNS::REFLECTOR_START_FRAME);
			reflector.setX(playership1.getCenterX() - reflector.getWidth() / 2 * reflector.getScale());
			reflector.setY(playership1.getCenterY() - reflector.getHeight() / 2 * reflector.getScale());
			//missile.setSpeed(30);
			//missile.setRadians(playership1.getRadians());
			//missile.isreflectable(false);
			Preflectorv.push_back(reflector);
			playership1.reflectorfired(true);
		}
	}
	if (input->isKeyDown(VK_KEY_L))  //I         // if move right FSM forward declaration
	{
		if (playership1.state == STATE_NORMAL || playership1.state == STATE_SPECIAL)
		{
			if (playership1.isspecialcool() == false)
			{
				if (!special.initialize(this, SpecialNS::WIDTH, SpecialNS::HEIGHT, SpecialNS::TEXTURE_COLS, &specialTextures))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing special"));
				special.setFrames(SpecialNS::SPECIAL_START_FRAME, SpecialNS::SPECIAL_END_FRAME);
				special.setCurrentFrame(ReflectorNS::REFLECTOR_START_FRAME);
				special.setX(playership1.getCenterX() - special.getWidth() / 2 * special.getScale());
				special.setY(playership1.getCenterY() - special.getHeight() / 2 * special.getScale());
				special.setdamage(playershipNS::SPECIALDAMAGE);
				special.setSpeed(playershipNS::SPECIALSPEED);
				special.setRadians(playership1.getRadians());
				special.isreflectable(false);
				Pspecialv.push_back(special);
				playership1.specialfired(true);
				playership1.setpmhealth(playership1.getpmhealth() - 1);
				playership1.state = STATE_SPECIAL;
			}
		}
	}
	if (input->isKeyDown(VK_KEY_I) == false && playership1.state == STATE_BULLET)
	{
		playership1.state = STATE_NORMAL;
	}
	if (input->isKeyDown(VK_KEY_O) == false && playership1.state == STATE_MISSILE)
	{
		playership1.state = STATE_NORMAL;
	}
	if (input->isKeyDown(VK_KEY_L) == false && playership1.state == STATE_SPECIAL)
	{
		playership1.state = STATE_NORMAL;
	}
	if (playership1.state == STATE_REFLECT)
	{
		playership1.state = STATE_NORMAL;
	}

	//enemy movement
	enemy0.update(frameTime);
	enemy1.update(frameTime);
	enemy2.update(frameTime);


	//Player skills
	for (unsigned d = 0; d < Pbulletv.size(); d++)
	{
		Bullet &tempbullet = Pbulletv[d];
		tempbullet.update(frameTime);
	}
	for (unsigned d = 0; d < Pmissilev.size(); d++)
	{
		Missile &tempmissile = Pmissilev[d];
		tempmissile.update(frameTime);
	}
	for (unsigned d = 0; d < Preflectorv.size(); d++)
	{
		Reflector &tempreflector = Preflectorv[d];
		tempreflector.update(frameTime);
	}
	for (unsigned d = 0; d < Pspecialv.size(); d++)
	{
		Special &tempspecial = Pspecialv[d];
		tempspecial.update(frameTime);
	}

	/*
	if (playership1X < 0)
	{
	cameraX -= playership1.getVelocity().x * frameTime; //scroll map right
	playership1.setX(0); //put the playership at left edge

	}

	else if (playership1X > (GAME_WIDTH - playership1.getWidth()))
	{
	cameraX -= playership1.getVelocity().x * frameTime; // scroll map left
	playership1.setX((float)(GAME_WIDTH - playership1.getWidth())); // put the player at right edge


	}

	else if (playership1Y < 0)
	{
	cameraY -= playership1.getVelocity().y * frameTime;
	playership1.setY(0);
	}

	else if (playership1Y > ( GAME_HEIGHT - playership1.getHeight()))
	{
	cameraY -= playership1.getVelocity().y * frameTime; // scroll map left
	playership1.setY((float)(GAME_HEIGHT - playership1.getHeight())); // put the player at right edge

	}

	if (cameraX > 0) // if the camera past left edge
	{
	cameraX = 0; // stop at left edge of map

	}
	else if (cameraY < 0)
	{
	cameraY = 0;
	}

	else if (cameraX > GAME_WIDTH - cameraWidth)
	{
	cameraX = GAME_WIDTH - cameraWidth;
	}

	else if (cameraY > GAME_HEIGHT - cameraHeight)
	{
	cameraY = GAME_HEIGHT - cameraHeight;
	}*/
	/*
	//camera
	int x = playership1.getX() - cameraX;
	int y = playership1.getY() - cameraY;

	//moving the camera
	if (cameraX < 0)
	cameraY = 0;
	if (cameraY < 0)
	cameraY = 0;
	if (cameraX > GAME_WIDTH - screenWidth)
	cameraX = GAME_WIDTH - screenWidth;

	if (cameraY > GAME_HEIGHT - screenHeight)
	cameraY = GAME_HEIGHT - screenHeight;

	//making the camera follow the player
	cameraX = playership1.getX() - screenWidth / 2;
	cameraY = playership1.getY() - screenHeight / 2;
	*/

	//enemy skills

	/*if (playership1.activate == true)
	{
	enemy.getX += frameTime * enemyNS::X - playershipNS::X;
	enemy.getY += frameTime * enemyNS::Y - playershipNS::Y;

	if (enemy.isbulletcool() == false)
	{
	if (!bullet.initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &bulletTextures))
	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	bullet.setFrames(BulletNS::BULLET_START_FRAME, BulletNS::BULLET_END_FRAME);
	bullet.setCurrentFrame(BulletNS::BULLET_START_FRAME);
	bullet.setX(enemy.getCenterX() - bullet.getWidth() / 2 * bullet.getScale());
	bullet.setY(enemy.getCenterY() - bullet.getHeight() / 2 * bullet.getScale());
	bullet.setdamage(2);
	bullet.setSpeed(30);
	bullet.setRadians(enemy.getRadians());
	bullet.isreflectable(true);
	Pbulletv.push_back(bullet);
	enemy.bulletfired(true);
	}
	}
	*/

	//if the playership at screen edge
	if ((playership1.getX() < SHIP_LIMIT_LEFT) || (playership1.getX() > SHIP_LIMIT_RIGHT))
	{
		// move background
		background.setX(background.getX() - frameTime * playership1.getVelocity().x);


		/*if ((reflector.getX() < SHIP_LIMIT_LEFT) || (reflector.getX() > SHIP_LIMIT_RIGHT))
		{
		reflector.setVisible(false);
		}*/
		// keep playership on screen
		if (playership1.getX() < SHIP_LIMIT_LEFT)
			playership1.setX(SHIP_LIMIT_LEFT);
		if (playership1.getX() > SHIP_LIMIT_RIGHT)
			playership1.setX(SHIP_LIMIT_RIGHT);
	}
	if ((playership1.getY() < SHIP_LIMIT_TOP) || (playership1.getY() > SHIP_LIMIT_BOTTOM))
	{
		// move background
		background.setY(background.getY() - frameTime * playership1.getVelocity().y);

		/*if ((reflector.getY() < SHIP_LIMIT_TOP) || (reflector.getY() > SHIP_LIMIT_BOTTOM))
		{
		reflector.setVisible(false);
		}*/
		// keep playership on screen
		if (playership1.getY() < SHIP_LIMIT_TOP)
			playership1.setY(SHIP_LIMIT_TOP);
		if (playership1.getY() > SHIP_LIMIT_BOTTOM)
			playership1.setY(SHIP_LIMIT_BOTTOM);
	}

	// Wrap space image around at edge
	// if left edge of background > screen left edge
	if (background.getX() > 0)
	{

		// move background image left by SCREEN_WIDTH
		background.setX(background.getX() - ::SCREEN_WIDTH);
		if (playership1.getX() > background.getX())
		{
			for (unsigned d = 0; d < Preflectorv.size(); d++)
			{


				Reflector &tempreflector = Preflectorv[d];
				Reflector *tmpReflectorPointer = &tempreflector;
				Preflectorv.erase(Preflectorv.begin() + d);
				tmpReflectorPointer = NULL;
			}
			return;
		}

	}
	// if background image off screen left
	if (background.getX() < -::SCREEN_WIDTH)
	{

		// move background image right by SCREEN_WIDTH
		background.setX(background.getX() + ::SCREEN_WIDTH);
		if (playership1.getX() > background.getX())
		{
			for (unsigned d = 0; d < Preflectorv.size(); d++)
			{


				Reflector &tempreflector = Preflectorv[d];
				Reflector *tmpReflectorPointer = &tempreflector;
				Preflectorv.erase(Preflectorv.begin() + d);
				tmpReflectorPointer = NULL;
			}
			return;

		}

	}
	// if top edge of background > screen top edge
	if (background.getY() > 0)
	{	// move background image up by SCREEN_HEIGHT
		background.setY(background.getY() - ::SCREEN_HEIGHT);

		if (playership1.getY() > background.getY())
		{
			for (unsigned d = 0; d < Preflectorv.size(); d++)
			{


				Reflector &tempreflector = Preflectorv[d];
				Reflector *tmpReflectorPointer = &tempreflector;
				Preflectorv.erase(Preflectorv.begin() + d);
				tmpReflectorPointer = NULL;
			}
			return;
		}
	}
	// if background image off screen top
	if (background.getY() < -::SCREEN_HEIGHT)
	{	// move background image down by SCREEN_IMAGE
		background.setY(background.getY() + ::SCREEN_HEIGHT);
		if (playership1.getY() < background.getY())
		{
			for (unsigned d = 0; d < Preflectorv.size(); d++)
			{


				Reflector &tempreflector = Preflectorv[d];
				Reflector *tmpReflectorPointer = &tempreflector;
				Preflectorv.erase(Preflectorv.begin() + d);
				tmpReflectorPointer = NULL;
			}
			return;
			/*	for (unsigned d = 0; d < Pbulletv.size(); d++)
			{


			Bullet &tempbullet = Pbulletv[d];
			Bullet *tmpBulletPointer = &tempbullet;
			Pbulletv.erase(Pbulletv.begin() + d);
			tmpBulletPointer = NULL;
			}*/
		}
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Drachen::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Drachen::collisions()
{

	VECTOR2 collisionVector;
	for (unsigned e = 0; e < Preflectorv.size(); e++)
	{
		Reflector &tempreflector = Preflectorv[e];
		Reflector *tmpReflectorPointer = &tempreflector;
		if (playership1.collidesWith(tempreflector, collisionVector))
		{
			playership1.state = STATE_REFLECT;
		}
	}
	for (unsigned d = 0; d < Pbulletv.size(); d++)
	{
		Bullet &tempbullet = Pbulletv[d];
		Bullet *tmpBulletPointer = &tempbullet;
		// enemy collide
		for (unsigned e = 0; e < Enemyv.size(); e++)
		{
			Enemy &tempenemy = Enemyv[e];
			Enemy *tmpEnemyPointer = &tempenemy;
			if (tempbullet.collidesWith(tempenemy, collisionVector))
			{
				//tempenemy.setchealth() = tempenemy.getchealth() - tempbullet.getdamage()
				Pbulletv.erase(Pbulletv.begin() + d);
				tmpBulletPointer = NULL;
			}

		}


		//reflect collide
		for (unsigned e = 0; e < Preflectorv.size(); e++)
		{
			Reflector &tempreflector = Preflectorv[e];
			Reflector *tmpReflectorPointer = &tempreflector;
			if (tempbullet.collidesWith(tempreflector, collisionVector))
			{

				float angle = atan2(tempreflector.getCenterY() - tempbullet.getCenterY(), tempreflector.getCenterX() - tempbullet.getCenterX());
				tempbullet.setRadians(tempbullet.getRadians() + angle);
				//tempbullet.setVelocity();
				/*tempbullet.flipHorizontal(true);
				tempbullet.flipVertical(true);*/
				//tempbullet.setVelocity(tempbullet.getVelocity());
				//tempbullet.setSpeed(tempbullet.getSpeed() *-1);

				/*double distPerpWall = (tempbullet.getCenterX() * tempreflector.getCenterX() + tempbullet.getCenterY * tempreflector.getCenterY()) / hypot(tempreflector.getCenterX(), tempreflector.getCenterY());
				double distParWall = (tempbullet.getCenterX() * tempreflector.getCenterX() + tempbullet.getCenterY * tempreflector.getCenterY()) / hypot(tempreflector.getCenterX(), -tempreflector.getCenterY());
				distPerpWall = -distPerpWall;

				tempbullet.setDeltaV =distParWall * tempreflector.getCenterY() + distPerpWall * tempreflector.getCenterX();
				tempbullet.setDeltaV = distParWall * -tempreflector.getCenterX() + distPerpWall * tempreflector.getCenterY();*/
				//tempbullet.bounce(collisionVector, tempreflector);
			}
		}
	}
	for (unsigned d = 0; d < Pmissilev.size(); d++)
	{
		Missile &tempmissile = Pmissilev[d];
		Missile *tmpMissilePointer = &tempmissile;
		for (unsigned e = 0; e < Enemyv.size(); e++)
		{
			Enemy &tempenemy = Enemyv[e];
			Enemy *tmpEnemyPointer = &tempenemy;
			if (tempmissile.collidesWith(tempenemy, collisionVector))
			{
				//tempenemy.setchealth() = tempenemy.getchealth() - tempmissile.getdamage()
				Pmissilev.erase(Pmissilev.begin() + d);
				tmpMissilePointer = NULL;
			}
		}
		for (unsigned e = 0; e < Preflectorv.size(); e++)
		{
			Reflector &tempreflector = Preflectorv[e];
			Reflector *tmpReflectorPointer = &tempreflector;
			if (tempmissile.collidesWith(tempreflector, collisionVector))
			{
				Pmissilev.erase(Pmissilev.begin() + d);
				tmpMissilePointer = NULL;
				Preflectorv.erase(Preflectorv.begin() + e);
				tmpReflectorPointer = NULL;
			}
		}
	}
	for (unsigned d = 0; d < Pspecialv.size(); d++)
	{
		Special &tempspecial = Pspecialv[d];
		Special *tmpSpecialPointer = &tempspecial;
		for (unsigned e = 0; e < Enemyv.size(); e++)
		{
			Enemy &tempenemy = Enemyv[e];
			Enemy *tmpEnemyPointer = &tempenemy;
			if (tempspecial.collidesWith(tempenemy, collisionVector))
			{
				//tempenemy.setchealth() = tempenemy.getchealth() - tempspecial.getdamage()
				Pspecialv.erase(Pspecialv.begin() + d);
				tmpSpecialPointer = NULL;
			}
		}
		for (unsigned e = 0; e < Preflectorv.size(); e++)
		{
			Reflector &tempreflector = Preflectorv[e];
			Reflector *tmpReflectorPointer = &tempreflector;
			if (tempspecial.collidesWith(tempreflector, collisionVector))
			{
				Pspecialv.erase(Pspecialv.begin() + d);
				tmpSpecialPointer = NULL;
				Preflectorv.erase(Preflectorv.begin() + e);
				tmpReflectorPointer = NULL;
			}
		}
	}
	for (unsigned e = 0; e < Enemyv.size(); e++)
	{
		Enemy &tempenemy = Enemyv[e];
		Enemy *tmpEnemyPointer = &tempenemy;
		if (playership1.collidesWith(tempenemy, collisionVector))
		{
			playership1.setpchealth(playership1.getpchealth() - 1);
			Enemyv.erase(Enemyv.begin() + e);
			tmpEnemyPointer = NULL;
		}
	}
	// if collision between ship and planet
	/*if(ship1.collidesWith(planet, collisionVector))
	{
	// bounce off planet
	ship1.bounce(collisionVector, planet);
	ship1.damage(PLANET);
	}*/

	// if collision between ships
	/*if(ship1.collidesWith(ship2, collisionVector))
	{
	// bounce off ship
	ship1.bounce(collisionVector, ship2);
	ship1.damage(SHIP);
	// change the direction of the collisionVector for ship2
	ship2.bounce(collisionVector*-1, ship1);
	ship2.damage(SHIP);
	}*/

	/*/enemy Collision
	VECTOR2 collisionVector;
	// if collision between player and enemy
	if (playership1.collidesWith(enemy0, collisionVector))
	{
	// player bounce off
	playership1.bounce(collisionVector, enemy0);
	playership1.damage(ENEMY);
	}
	// if collision between enemy and weapons
	if (enemy0.collidesWith(bullet, collisionVector))
	{
	delete &enemy0;
	delete &bullet;
	}
	if (enemy0.collidesWith(missile, collisionVector))
	{
	delete &enemy0;
	}
	if (enemy0.collidesWith(reflector, collisionVector))
	{
	enemy0.bounce(collisionVector, reflector);
	}
	if (enemy0.collidesWith(special, collisionVector))
	{
	delete &enemy0;
	}*/
}

//=============================================================================
// Render game items
//=============================================================================
void Drachen::render()
{


	graphics->spriteBegin();                // begin drawing sprites

	float x = background.getX();
	float y = background.getY();
	//wrap image around at edges
	background.draw();                          // add the orion nebula to the scene                       // add the planet to the scene
												// if background image right edge visible
	if (background.getX() < -::SCREEN_WIDTH + (int)GAME_WIDTH)
	{
		background.setX(background.getX() + ::SCREEN_WIDTH); // wrap around to left edge
		background.draw();                           // draw again
	}
	// if background image bottom edge visible
	if (background.getY() < -::SCREEN_HEIGHT + (int)GAME_HEIGHT)
	{
		background.setY(background.getY() + ::SCREEN_HEIGHT); // wrap around to top edge
		background.draw();                           // draw again
		background.setX(x);                          // restore x position
													 // if background image right edge visible
													 // wrap around to left edge
		if (background.getX() < -::SCREEN_WIDTH + (int)GAME_WIDTH)
			background.draw();                       // draw again
	}
	background.setY(y);      // restore y position



	for (unsigned d = 0; d < Pbulletv.size(); d++)
	{
		Bullet &tempbullet = Pbulletv[d];
		tempbullet.draw();
	}
	//ship2.draw();                           // add the spaceship to the scene
	for (unsigned d = 0; d < Pmissilev.size(); d++)
	{
		Missile &tempmissile = Pmissilev[d];
		tempmissile.draw();
	}
	for (unsigned d = 0; d < Preflectorv.size(); d++)
	{
		Reflector &tempreflector = Preflectorv[d];
		tempreflector.draw();
	}
	for (unsigned d = 0; d < Pspecialv.size(); d++)
	{
		Special &tempspecial = Pspecialv[d];
		tempspecial.draw();
	}

	enemy0.draw();
	enemy1.draw();
	enemy2.draw();
	playership1.draw();
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Drachen::releaseAll()
{
	menuTexture.onLostDevice();
	instructionTexture.onLostDevice();
	creditTexture.onLostDevice();
	cursorTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	playershipTextures.onLostDevice();
	enemyTextures.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Drachen::resetAll()
{

	menuTexture.onResetDevice();
	instructionTexture.onResetDevice();
	creditTexture.onResetDevice();
	cursorTexture.onResetDevice();
	playershipTextures.onResetDevice();

	enemyTextures.onResetDevice();
	backgroundTexture.onResetDevice();
	Game::resetAll();
	return;
}
