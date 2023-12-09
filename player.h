#pragma once
#include "raylib.h"

class Player {
	Texture2D player = LoadTexture("./Images/player.png");
	float frameWidth = player.width / 6;
	float frameHeight = player.height / 10;
	Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
	Vector2 playerPos = { 0, 0 };
	Vector2 playerVelocity = { 0.0, 0.0 };
	char playerDirection = 'D';
	int playerSpeed = 4;

	Vector2 playerColliderInnit = { playerPos.x + 20, playerPos.y + 34 };
	Rectangle playerColliderPos = { playerColliderInnit.x , playerColliderInnit.y, 8, 8 };

public:
	//----- Get Methods -----
	Texture2D get_player();
	Rectangle get_frameRec();
	Vector2 get_playerPos();
	float get_fw();
	float get_fh();
	char get_playerDirection();
	int get_playerSpeed();
	Rectangle get_playerCollisionPos();
	//------------------------
	// 
	// ----- Set Methods -----
	void set_playerDirection(bool pd);
	void set_playerDirection(char dir);
	void set_playerVelocity(int x, int y);
	void set_playerPos(int x, int y);

	void load_playerPosX(int x);
	void load_playerPosY(int y);
	void load_playerCollisionPosX(int x);
	void load_playerCollisionPosY(int y);

	void set_playerCollisionPos(int x, int y);
	void set_playerSpeed(int s);
	//---------------------------
	//
	// ----- Player Animation -----
	void animationUp(float i, char dir);
	void animationDown(float i, char dir);
	void animationLeft(float i, char dir);
	void animationRight(float i, char dir);
	void animationAttack(int frameIndex);
	
	void playerIdle(float i);
	//----------------------------
	//
	// ----- Actual Movement -----
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
};

