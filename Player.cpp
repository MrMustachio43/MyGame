#include "Player.h"
#include "raymath.h"

//----- Get Methods -----
Texture2D Player::get_player() {
	return player;
}
Rectangle Player::get_frameRec() {
	return frameRec;
}
Vector2 Player::get_playerPos() {
	return playerPos;
}
float Player::get_fw() {
	return frameWidth;
}
float Player::get_fh() {
	return frameHeight;
}
char Player::get_playerDirection() {
	return playerDirection;
}
int Player::get_playerSpeed() {
	return playerSpeed;
}
Rectangle Player::get_playerCollisionPos() {
	return playerColliderPos;
}
//------------------------
// 
// ----- Set Methods -----
void Player::set_playerDirection(bool pd) {
	playerDirection = pd;
}
void Player::set_playerDirection(char dir) {
	if (dir == 'U') { playerDirection = 'U'; }
	if (dir == 'D') { playerDirection = 'D'; }
	if (dir == 'L') { playerDirection = 'L'; }
	if (dir == 'R') { playerDirection = 'R'; }

}
void Player::set_playerVelocity(int x, int y) {
	if (playerDirection == 'U') {
		playerVelocity.y = -y;
		playerVelocity.x = x;
	}
	else if (playerDirection == 'L') {
		playerVelocity.x = -x;
		playerVelocity.y = y;
	}
	else {
		playerVelocity.x = x;
		playerVelocity.y = y;
	}
}
void Player::set_playerPos(int x, int y) {
	Vector2 vector = { x, y };
	playerPos = Vector2Add(playerPos, vector);
}

void Player::load_playerPosX(int x) {
	playerPos.x = x;
}
void Player::load_playerPosY(int y) {
	playerPos.y = y;
}
void Player::load_playerCollisionPosX(int x) {
	playerColliderPos.x = x;
}
void Player::load_playerCollisionPosY(int y) {
	playerColliderPos.y = y;
}

void Player::set_playerCollisionPos(int x, int y) {
	playerColliderPos.x += x;
	playerColliderPos.y += y;
}
void Player::set_playerSpeed(int s) {
	playerSpeed = s;
}
//---------------------------
//
// ----- Move animation -----
void Player::animationUp(float i, char dir) {
	int frameIndex = i;
	playerDirection = dir;
	frameRec.y = frameHeight * 5;			// Animation
	frameRec.x = frameWidth * frameIndex;

};
void Player::animationDown(float i, char dir) {
	int frameIndex = i;
	playerDirection = dir;
	frameRec.y = frameHeight * 3;			// Animation
	frameRec.x = frameWidth * frameIndex;
};
void Player::animationLeft(float i, char dir) {
	int frameIndex = i;
	playerDirection = dir;
	if (frameRec.width > 0) {
		frameRec.width = -frameRec.width;
	}
	frameRec.y = frameHeight * 4;			// Animation
	frameRec.x = frameWidth * frameIndex;
};
void Player::animationRight(float i, char dir) {
	int frameIndex = i;
	playerDirection = dir;
	if (frameRec.width < 0) {
		frameRec.width = -frameRec.width;
	};
	frameRec.y = frameHeight * 4;			// Animation
	frameRec.x = frameWidth * frameIndex;
};
void Player::animationAttack(int frameIndex) {

	if (playerDirection == 'U') {
		frameRec.y = frameHeight * 8;			// Animation
		frameRec.x = frameWidth * frameIndex;
	}
	else if (playerDirection == 'D') {
		frameRec.y = frameHeight * 6;			// Animation
		frameRec.x = frameWidth * frameIndex;
	}
	else if (playerDirection == 'L') {
		if (frameRec.width > 0) {
			frameRec.width = -frameRec.width;
		}
		frameRec.y = frameHeight * 7;			// Animation
		frameRec.x = frameWidth * frameIndex;
	}
	else if (playerDirection == 'R') {
		if (frameRec.width < 0) {
			frameRec.width = -frameRec.width;
		};
		frameRec.y = frameHeight * 7;			// Animation
		frameRec.x = frameWidth * frameIndex;
	};
};

//---------------------------
//
// ----- Idle Animation -----
void Player::playerIdle(float i) {
	int frameIndex = i;
	if (playerDirection == 'U') {
		frameRec.y = frameHeight * 2;
		frameRec.x = (frameWidth)*frameIndex;
	}
	else if (playerDirection == 'D') {
		frameRec.y = frameHeight * 0;
		frameRec.x = (frameWidth)*frameIndex;
	}
	else if (playerDirection == 'L') {
		frameRec.y = frameHeight * 1;
		frameRec.x = (frameWidth)*frameIndex;
	}
	else if (playerDirection == 'R') {
		frameRec.y = frameHeight * 1;
		frameRec.x = (frameWidth)*frameIndex;
	};
};
//----------------------------
//
// ----- Actual Movement -----
void Player::moveUp() {
	playerVelocity = { 0, -(float)playerSpeed };
	playerPos = Vector2Add(playerPos, playerVelocity);
	playerColliderPos.y += -playerSpeed;
};

void Player::moveDown() {
	playerVelocity = { 0, (float)playerSpeed };
	playerPos = Vector2Add(playerPos, playerVelocity);
	playerColliderPos.y += playerSpeed;
};

void Player::moveRight() {
	playerVelocity = { (float)playerSpeed, 0 };
	playerPos = Vector2Add(playerPos, playerVelocity);
	playerColliderPos.x += playerSpeed;
}

void Player::moveLeft() {
	playerVelocity = { -(float)playerSpeed, 0 };
	playerPos = Vector2Add(playerPos, playerVelocity);
	playerColliderPos.x += -playerSpeed;
}

