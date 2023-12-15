#include "raylib.h"	// anything ray-X is game engine help
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <process.h>
#include <iostream>
#include <map>     // Allows me to create maps
#include <fstream> // helps with files
#include <string>

#include "Player.h"
#include "WorldGen.h"

using namespace std;

int screenWidth = 1920;
int screenHeight = 1080;

enum gameStates {
	stateExit = -1,
	stateTitleScreen,
	stateNewGame,
	statePause,
	stateLoad,
	stateLoaded,
	stateSaving
};

Color transparent = { 0, 0, 0, 0 };
Color opacity50 = { 255, 255, 255, 255 / 2 };

Texture2D title;
Texture2D menuBackground;
Texture2D titleBackground;

// ----- Menu Functions -----
string saveGamePath = "";

bool gameLoaded = false;
int gameState = 0;

string saveGameWorldMap;
string saveGameWorldTreeMap;
string saveGamePlayerAttributes;

void Settings() {
	// TODO: Implement control logic
}

bool loadGame(string saveGame) {

	innitWorldArray();

	saveGameWorldMap = saveGame;
	saveGameWorldTreeMap = saveGame;
	saveGamePlayerAttributes = saveGame;

	saveGameWorldMap = saveGameWorldMap.append("/worldMap.txt");
	saveGameWorldTreeMap = saveGameWorldTreeMap.append("/worldTreeMap.txt");
	saveGamePlayerAttributes = saveGamePlayerAttributes.append("/playerAttributes.txt");

	int num = 0;
	int num2 = 0;
	ifstream worldMapFile(saveGameWorldMap); // Input-fstream, Reading the file
	ifstream worldTreeMapFile(saveGameWorldTreeMap);
	for (int h = 0; h < worldMapHeight; h++) {
		for (int w = 0; w < worldMapWidth; w++) {
			worldMapFile >> num; // Read the number
			worldMap[h][w] = num; // asign number to map

			worldTreeMapFile >> num2;
			worldTreeMap[h][w] = num2;
		};
	};
	worldMapFile.close();
	worldTreeMapFile.close();

	return true;
}

void loadGameMenu() {
	Texture2D title = LoadTexture("./Images/title.png");
	Texture2D menuBackground = LoadTexture("./Images/menuBackground.png");
	Texture2D titleBackground = LoadTexture("./Images/titleBackground.png");

	while (gameState == stateLoad) {
		BeginDrawing();
		DrawTexture(menuBackground, 696, 168, WHITE);		// Reloading textures
		DrawTextureEx(title, { 768, 225 }, 0, 1.02, BLACK);
		DrawTexture(title, 770, 225, WHITE);

		if (GuiButton({ 859, 392, 202, 76 }, "Save Game 1")) {
			saveGamePath = "./SaveGames/SaveGame1";
			gameLoaded = loadGame(saveGamePath); // Returns true once finished
		}
		if (GuiButton({ 859, 492, 202, 76 }, "Save Game 2")) {
			saveGamePath = "./SaveGames/SaveGame2";
			gameLoaded = loadGame(saveGamePath);
		}
		if (GuiButton({ 859, 592, 202, 76 }, "Save Game 3")) {
			saveGamePath = "./SaveGames/SaveGame3";
			gameLoaded = loadGame(saveGamePath);
		}
		if (GuiButton({ 859, 692, 202, 76 }, "Save Game 4")) {
			saveGamePath = "./SaveGames/SaveGame4";
			gameLoaded = loadGame(saveGamePath);
		}
		if (GuiButton({ 859, 792, 202, 76 }, "Save Game 5")) {
			saveGamePath = "./SaveGames/SaveGame5";
			gameLoaded = loadGame(saveGamePath);
		}
		if (GuiButton({ 700, 925, 120, 24 }, "Back")) {
			UnloadTexture(menuBackground);		// Unloading textures
			UnloadTexture(titleBackground);
			UnloadTexture(title);

			EndDrawing();
			CloseWindow();
			gameState = stateTitleScreen; // quits menu to tile screen
		}
		EndDrawing();

		if (gameLoaded == true) {
			UnloadTexture(menuBackground);		// Unloading textures
			UnloadTexture(titleBackground);
			UnloadTexture(title);

			CloseWindow();

			gameState = 4;
		}
	};
	CloseWindow();
};

void Credits() {
	// TODO: Implement control logic
}

void saveGame(string saveGame, Player* player) {
	string saveGameWorldMap = saveGame;
	string saveGameWorldTreeMap = saveGame;
	string saveGamePlayerAttributes = saveGame;

	saveGameWorldMap = saveGameWorldMap.append("/worldMap.txt");
	saveGameWorldTreeMap = saveGameWorldTreeMap.append("/worldTreeMap.txt");
	saveGamePlayerAttributes = saveGamePlayerAttributes.append("/playerAttributes.txt");

	ofstream worldMapFile(saveGameWorldMap); // Output-fstream, writing to the file
	ofstream worldTreeMapFile(saveGameWorldTreeMap);
	for (int h = 0; h < worldMapHeight; h++) {
		for (int w = 0; w < worldMapWidth; w++) {
			if (w == worldMapWidth - 1) {
				worldMapFile << worldMap[h][w];			// Writing end line array num to the file
				worldTreeMapFile << worldTreeMap[h][w]; // if last num has a comma, it will think theres another value
			}
			else {
				worldMapFile << worldMap[h][w] << " "; // Writing the array to the file
				worldTreeMapFile << worldTreeMap[h][w] << " ";
			};
		};
		worldMapFile << "\n"; //After every line in the 2d array add a \n
		worldTreeMapFile << "\n";
	};
	worldMapFile.close();
	worldTreeMapFile.close();

	ofstream playerAtrributes(saveGamePlayerAttributes);
	playerAtrributes << player->get_playerPos().x << " " << player->get_playerPos().y << endl;
	playerAtrributes << player->get_playerCollisionPos().x << " " << player->get_playerCollisionPos().y << endl;

	playerAtrributes.close();
};

void saveGameMenu(Player* player) {
	Texture2D title = LoadTexture("./Images/title.png");
	Texture2D menuBackground = LoadTexture("./Images/menuBackground.png");
	Texture2D titleBackground = LoadTexture("./Images/titleBackground.png");
	gameState = stateSaving;

	while (gameState == stateSaving) {
		BeginDrawing();
		DrawTexture(menuBackground, 696, 168, WHITE);
		DrawTextureEx(title, { 768, 225 }, 0, 1.02, BLACK);
		DrawTexture(title, 770, 225, WHITE);

		if (GuiButton({ 859, 392, 202, 76 }, "Save Game 1")) {
			saveGamePath = "./SaveGames/SaveGame1";
			saveGame(saveGamePath, player);
		}
		if (GuiButton({ 859, 492, 202, 76 }, "Save Game 2")) {
			saveGamePath = "./SaveGames/SaveGame2";
			saveGame(saveGamePath, player);
		}
		if (GuiButton({ 859, 592, 202, 76 }, "Save Game 3")) {
			saveGamePath = "./SaveGames/SaveGame3";
			saveGame(saveGamePath, player);
		}
		if (GuiButton({ 859, 692, 202, 76 }, "Save Game 4")) {
			saveGamePath = "./SaveGames/SaveGame4";
			saveGame(saveGamePath, player);
		}
		if (GuiButton({ 859, 792, 202, 76 }, "Save Game 5")) {
			saveGamePath = "./SaveGames/SaveGame5";
			saveGame(saveGamePath, player);
		}
		if (GuiButton({ 700, 925, 120, 24 }, "Back")) { //Ends drawing early, changes menu
			EndDrawing();
			CloseWindow();

			UnloadTexture(menuBackground);
			UnloadTexture(titleBackground);
			UnloadTexture(title);

			gameState = statePause; // Goes back to pause menu
		}
		EndDrawing();
	};
};

// ----- Main Function -----
int main() {
	//initialisation
	SetTargetFPS(FLAG_VSYNC_HINT);  // Detects refresh rate and sets it to target FPS
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(screenWidth, screenHeight, "MyGame"); // Opens the window 1920 px wide, 1080 px length
	InitAudioDevice();
	SetExitKey(KEY_NULL);


	if (gameState == stateTitleScreen) {
		Texture2D title = LoadTexture("./Images/title.png");
		Texture2D menuBackground = LoadTexture("./Images/menuBackground.png");
		Texture2D titleBackground = LoadTexture("./Images/titleBackground.png");

		while (gameState == stateTitleScreen) {
			BeginDrawing();
			DrawTexture(titleBackground, 0, 0, WHITE);
			DrawTexture(menuBackground, 696, 168, WHITE);
			DrawTextureEx(title, { 768, 225 }, 0, 1.02, BLACK);
			DrawTexture(title, 770, 225, WHITE);

			if (WindowShouldClose()) { EndDrawing(); gameState = stateExit; }
			if (GuiButton({ 834, 442, 252, 96 }, "New Game")) { EndDrawing(); gameState = stateNewGame; }
			if (GuiButton({ 834, 562, 252, 96 }, "Settings")) { EndDrawing(); Settings(); }
			if (GuiButton({ 834, 682, 252, 96 }, "Load Game")) { EndDrawing(); gameState = stateLoad; }
			if (GuiButton({ 834, 827, 252, 96 }, "Quit")) { EndDrawing(); gameState = stateExit; }
			if (GuiButton({ 1093, 925, 120, 24 }, "Credits")) {EndDrawing(); Credits();}

			EndDrawing();
		};
		//CloseWindow();
	};

	if (gameState == stateNewGame || gameState == stateLoaded) { // 1 represents a new game, 2 represents loading a game

		// ----- worldMap Textures -----
		Texture2D grassTexture1 = LoadTexture("./Images/grassPlain.png");
		Texture2D grassTexture2 = LoadTexture("./Images/grassGrass.png");
		Texture2D grassTexture3 = LoadTexture("./Images/grassFlower1.png");


		Texture2D wallHorizontal = LoadTexture("./Images/wallHorizontal.png"); // 1
		Rectangle wallHorizontalRect = { 0, 0, 16, 16 };

		Texture2D wallVertical = LoadTexture("./Images/wallVertical.png"); // 2
		Rectangle wallVerticalRect = { 0, 0, 16, 16 };

		Texture2D wallHorizontalTop = LoadTexture("./Images/wallHorizontalTop.png");
		Rectangle wallHorizontalTopRect = { 0, 0, 16, 16 };

		Texture2D wallBendUp = LoadTexture("./Images/wallBendUp.png"); // 3 , -3
		Rectangle wallBendUpRect = { 0, 0, 16, 16 };

		Texture2D wallBendAway = LoadTexture("./Images/wallBendAway.png"); // 4, -4
		Rectangle wallBendAwayRect = { 0, 0, 16, 16 };

		Texture2D wallInnerJoin = LoadTexture("./Images/wallInnerJoint.png"); // 10, -10
		Rectangle wallInnerJoinRect = { 0, 0, 16, 16 };


		Texture2D tree1 = LoadTexture("./Images/tree1.png");
		Rectangle tree1Rect = { 0, 0, 48, 48 };

		// ----- worldMap Generation -----
		if (gameState == stateNewGame) {
			generateWorldMap();
		}

		if (gameState == stateLoad) {
			loadGameMenu();
		};

		// ----- Player Initilization -----
		Player* player; {
			Player* P = new Player();
			player = P;
		}

		player->set_playerPos(worldMapWidth / 2, worldMapHeight / 2);

		if (gameState == stateLoaded) {
			int num = 0;
			ifstream playerAtrributes(saveGamePlayerAttributes);
			for (int i = 0; i < 4; i++) {
				playerAtrributes >> num;
				switch (i) {
				case 0:
					player->load_playerPosX(num); break;
				case 1:
					player->load_playerPosY(num); break;
				case 2:
					player->load_playerCollisionPosX(num); break;
				case 3:
					player->load_playerCollisionPosY(num); break;
				}
			}
		}
		// --------------------------------

		// ----- Camera -----
		Camera2D camera = { 0 };
		float cameraZoom = 5;
		camera.zoom = cameraZoom;
		camera.target = player->get_playerPos();
		camera.offset = { (screenWidth / 2) - player->get_fw() * 2 , (screenHeight / 2) - player->get_fh() * 2 };
		// ------------------

		int frameIndex = 0;
		float frameUpdate = 1.0 / 14.0;  // Frame delay
		float frameRun = 0.0;

		float screenHeightBoundary = 0;
		float screenHeightBoundaryBottom = worldMapHeight * 16;
		float screenWidthBoundary = screenWidth / 2;
		float screenWidthBoundaryRight = (worldMapWidth * 16) - ((screenWidth / 2) + (player->get_fw() * 2)) / cameraZoom;

		bool canMove = true;
		bool attacking = false;
		int pauseCount = 0;

		// ----- Game Loop Start -----
		while (!WindowShouldClose()) {  // Closing window condition

			const float dT = GetFrameTime(); // Delta Time
			frameRun += dT;

			if (IsKeyPressed(KEY_E)) {				// Check Attacking
				frameIndex = 0;
				attacking = true;
			};

			if (IsKeyPressed(KEY_ESCAPE)) {
				pauseCount++;
				if (pauseCount % 2 == 0) {
					canMove = true;
				}
				else {
					canMove = false;
				};
			};

			// ----- Player Movement -----
			if (canMove == true) {
				if (frameRun >= frameUpdate) {
					frameRun = 0;

					if (attacking) {				// Attacking
						player->animationAttack(frameIndex);
						if (frameIndex > 3) { frameIndex = 0; attacking = false; }
						frameIndex++;
					};

					if (IsKeyDown(KEY_W)) {						// -- Move Up --
						player->moveUp();
						player->set_playerDirection('U');

						if (IsKeyDown(KEY_A)) {					// move up and left
							player->set_playerDirection('L');
							player->moveLeft();
						}
						else if (IsKeyDown(KEY_D)) {			// move up and right
							player->set_playerDirection('R');
							player->moveRight();
						}

						if (!attacking) {
							frameUpdate = 1.0 / 14.0;
							if (frameIndex > 5) { frameIndex = 0; }
							player->animationUp((float)frameIndex, 'U');
							if (IsKeyDown(KEY_A)) {					// move and left
								player->animationLeft((float)frameIndex, 'L');
							}
							else if (IsKeyDown(KEY_D)) {			// move and right
								player->animationRight((float)frameIndex, 'R');
							}
							frameIndex++;
						}
					}

					else if (IsKeyDown(KEY_S)) {				// -- Move Down --
						player->moveDown();
						player->set_playerDirection('D');

						if (IsKeyDown(KEY_A)) {					// move up and left
							player->set_playerDirection('L');
							player->moveLeft();
						}
						else if (IsKeyDown(KEY_D)) {			// move up and right
							player->set_playerDirection('R');
							player->moveRight();
						}

						if (attacking == false) {
							frameUpdate = 1.0 / 14.0;
							if (frameIndex > 5) { frameIndex = 0; }

							player->animationDown((float)frameIndex, 'D');
							if (IsKeyDown(KEY_A)) {					// Animate Down and Left
								player->animationLeft((float)frameIndex, 'L');
							}
							else if (IsKeyDown(KEY_D)) {			// Animate Down and Right
								player->animationRight((float)frameIndex, 'R');
							}
							frameIndex++;
						}
					}

					else if (IsKeyDown(KEY_A)) {				// -- Move Left --
						player->moveLeft();
						player->set_playerDirection('L');

						if (attacking == false) {
							frameUpdate = 1.0 / 14.0;
							if (frameIndex > 5) { frameIndex = 0; }
							player->animationLeft((float)frameIndex, 'L');
							if (IsKeyDown(KEY_S)) {
								player->animationDown((float)frameIndex, 'D');
							}
							else if (IsKeyDown(KEY_W)) {
								player->animationUp((float)frameIndex, 'L');
							}
							frameIndex++;
						}
					}

					else if (IsKeyDown(KEY_D)) {				// -- Move Right --
						player->moveRight();
						player->set_playerDirection('R');

						if (attacking == false) {
							frameUpdate = 1.0 / 14.0;
							if (frameIndex > 5) { frameIndex = 0; }
							player->animationRight((float)frameIndex, 'R');
							frameIndex++;
						}
					}

					else {										// -- Idle --
						if (!attacking) {
							frameUpdate = 1.0 / 7.0;
							if (frameIndex > 5) { frameIndex = 0; }
							player->playerIdle((float)frameIndex);
							frameIndex++;
						}
					};
				};
			}

			// Boundary stoppers
			if (player->get_playerCollisionPos().y <= 0) {
				player->set_playerPos(0, player->get_playerSpeed());
				player->set_playerCollisionPos(0, player->get_playerSpeed());
			}
			if (player->get_playerCollisionPos().y >= (worldMapHeight * 16)) {
				player->set_playerPos(0, -player->get_playerSpeed());
				player->set_playerCollisionPos(0, -player->get_playerSpeed());
			}

			if (player->get_playerCollisionPos().x <= 0) {
				player->set_playerPos(player->get_playerSpeed(), 0);
				player->set_playerCollisionPos(player->get_playerSpeed(), 0);
			}
			if (player->get_playerCollisionPos().x >= (worldMapWidth * 16)) {
				player->set_playerPos(-player->get_playerSpeed(), 0);
				player->set_playerCollisionPos(-player->get_playerSpeed(), 0);
			}

			// ----------End of Player Movement-------------
			// 
			// ----- Camera Boundary -----
			if (player->get_playerPos().y < screenHeightBoundary && player->get_playerPos().x > screenWidthBoundaryRight) {
				camera.target = Vector2{ screenWidthBoundaryRight , screenHeightBoundary };
			}
			else if (player->get_playerPos().y < screenHeightBoundary && player->get_playerPos().x < screenWidthBoundary) {
				camera.target = Vector2{ screenWidthBoundary , screenHeightBoundary };
			}
			else if (player->get_playerPos().y > screenHeightBoundaryBottom && (player->get_playerPos().x > screenWidthBoundaryRight)) {
				camera.target = Vector2{ screenWidthBoundaryRight , screenHeightBoundaryBottom };
			}
			else if (player->get_playerPos().y > screenHeightBoundaryBottom && (player->get_playerPos().x < screenWidthBoundary)) {
				camera.target = Vector2{ screenWidthBoundary , screenHeightBoundaryBottom };
			}

			else if (player->get_playerPos().y < screenHeightBoundary) {
				camera.target = Vector2{ player->get_playerPos().x, screenHeightBoundary };
			}
			else if (player->get_playerPos().y > screenHeightBoundaryBottom) {
				camera.target = Vector2{ player->get_playerPos().x, screenHeightBoundaryBottom };
			}
			else if (player->get_playerPos().x <= screenWidthBoundary) {
				camera.target = Vector2{ screenWidthBoundary, player->get_playerPos().y };
			}
			else if (player->get_playerPos().x > screenWidthBoundaryRight) {
				camera.target = Vector2{ screenWidthBoundaryRight, player->get_playerPos().y };
			}

			else {
				camera.target = player->get_playerPos();
			};
			//-----------------------------
			// 
			// ----- Drawing -----

			if (pauseCount % 2 == 1) {
				BeginDrawing();

				DrawTexture(menuBackground, 696, 168, WHITE);
				DrawTextureEx(title, { 768, 225 }, 0, 1.02, BLACK);
				DrawTexture(title, 770, 225, WHITE);

				if (GuiButton({ 834, 442, 252, 96 }, "Save")) { saveGameMenu(player); }
				if (GuiButton({ 834, 562, 252, 96 }, "Settings")) { Settings(); }
				if (GuiButton({ 834, 682, 252, 96 }, "Load Game")) { loadGameMenu(); }
				if (GuiButton({ 834, 827, 252, 96 }, "Quit")) { gameState = 0;  break; }
				if (GuiButton({ 1093, 925, 120, 24 }, "Credits")) Credits();

				EndDrawing();

			}
			else if (pauseCount % 2 == 0) {
				BeginDrawing();
				BeginMode2D(camera);

				int hIndexStart = (player->get_playerPos().y / 16) - 8;
				if (hIndexStart < 0) { hIndexStart = 0; }

				int hIndexEnd = hIndexStart + 22;
				if (hIndexEnd > worldMapHeight) { hIndexEnd = worldMapHeight; }

				int wIndexStart = (player->get_playerPos().x / 16) - (((GetMonitorWidth(0) / 16) / 2) / 2);
				if (wIndexStart < 0) { wIndexStart = 0; }

				int wIndexEnd = (player->get_playerPos().x / 16) + (((GetMonitorWidth(0) / 16) / 2) / 2);
				if (wIndexEnd > worldMapWidth) { wIndexEnd = worldMapWidth; }

				// Walls and Grass
				for (int h = hIndexStart; h < hIndexEnd; h++) {
					for (int w = wIndexStart; w < wIndexEnd; w++) {
						Vector2 pos = { w * 16, h * 16 };

						// Grass
						if (worldMap[h][w] == gP) {
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
						}
						else if (worldMap[h][w] == gG) {
							DrawTexture(grassTexture2, w * 16, h * 16, WHITE);
						}
						else if (worldMap[h][w] == gF) {
							DrawTexture(grassTexture3, w * 16, h * 16, WHITE);
						}

						// Walls
						else if (worldMap[h][w] == wHT) {
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallHorizontalTop, wallHorizontalTopRect, pos, WHITE);
							//placeCollision(pos, wallHorizontalTopRect);
						}
						else if (worldMap[h][w] == wH) {
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallHorizontal, wallHorizontalRect, pos, WHITE);
							//placeCollision(pos, wallHorizontalRect);
						}
						//cout << wallHorizontalRect.x << " " << wallHorizontalRect.y;
						else if (worldMap[h][w] == wV) {
							if (wallVerticalRect.width < 0) {
								wallVerticalRect.width = -wallVerticalRect.width;
							}
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallVertical, wallVerticalRect, pos, WHITE);
							//placeCollision(pos, wallVerticalRect);
						}
						else if (worldMap[h][w] == -wV) {
							if (wallVerticalRect.width > 0) {
								wallVerticalRect.width = -wallVerticalRect.width;
							}
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallVertical, wallVerticalRect, pos, WHITE);
							//placeCollision(pos, wallVerticalRect);
						}
						else if (worldMap[h][w] == wBU) {
							if (wallBendUpRect.width < 0) {
								wallBendUpRect.width = -wallBendUpRect.width;
							}
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallBendUp, wallBendUpRect, pos, WHITE);
							//placeCollision(pos, wallBendUpRect);
						}
						else if (worldMap[h][w] == -wBU) {
							if (wallBendUpRect.width > 0) {
								wallBendUpRect.width = -wallBendUpRect.width;
							}
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallBendUp, wallBendUpRect, pos, WHITE);
							//placeCollision(pos, wallBendUpRect);
						}
						else if (worldMap[h][w] == wBA) {
							if (wallBendAwayRect.width < 0) {
								wallBendAwayRect.width = -wallBendAwayRect.width;
							}
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallBendAway, wallBendAwayRect, pos, WHITE);
							//placeCollision(pos, wallBendAwayRect);
						}
						else if (worldMap[h][w] == -wBA) {
							if (wallBendAwayRect.width > 0) {
								wallBendAwayRect.width = -wallBendAwayRect.width;
							}
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
							DrawTextureRec(wallBendAway, wallBendAwayRect, pos, WHITE);
							//placeCollision(pos, wallBendAwayRect);
						}
						else if (worldMap[h][w] == wIJ) {
							if (wallInnerJoinRect.width < 0) {
								wallInnerJoinRect.width = -wallInnerJoinRect.width;
							}
							DrawTextureRec(wallInnerJoin, wallInnerJoinRect, pos, WHITE);
						}
						else if (worldMap[h][w] == -wIJ) {
							if (wallInnerJoinRect.width > 0) {
								wallInnerJoinRect.width = -wallInnerJoinRect.width;
							}
							DrawTextureRec(wallInnerJoin, wallInnerJoinRect, pos, WHITE);
						}
						else {
							DrawTexture(grassTexture1, w * 16, h * 16, WHITE);
						};
					};
				};


				// Colisions
				int h = (player->get_playerCollisionPos().y / 16); // Position in array
				int w = (player->get_playerCollisionPos().x / 16);

				// Colliding >
				if ((isWall(h, w) || worldTreeMap[h][w] == 2) && (player->get_playerDirection() == 'U' || player->get_playerDirection() == 'R' || player->get_playerDirection() == 'L')) {
					player->set_playerPos(0, player->get_playerSpeed());
					player->set_playerCollisionPos(0, player->get_playerSpeed());
				}

				// Colliding V
				if ((isWall(h + 1, w) || worldTreeMap[h + 1][w] == 2) && player->get_playerCollisionPos().y >= ((h * 16) + 12)) {
					player->set_playerPos(0, -player->get_playerSpeed());
					player->set_playerCollisionPos(0, -player->get_playerSpeed());
				}

				// Colliding >
				if ((isWall(h, w + 1) || worldTreeMap[h][w + 1] == 2) && player->get_playerCollisionPos().x >= ((w * 16) + 12)) {
					player->set_playerPos(-player->get_playerSpeed(), 0);
					player->set_playerCollisionPos(-player->get_playerSpeed(), 0);
				}

				// Colliding <
				if ((isWall(h, w - 1) || worldTreeMap[h][w - 1] == 2) && player->get_playerCollisionPos().x <= w * 16) {
					player->set_playerPos(player->get_playerSpeed(), 0);
					player->set_playerCollisionPos(player->get_playerSpeed(), 0);
				}

				// Drawing Trees + player
				if (shouldBeTransparent(h, w)) {
					DrawTextureRec(player->get_player(), player->get_frameRec(), player->get_playerPos(), WHITE);
					//DrawRectangleRec(player->get_playerCollisionPos(), BLACK);

					// Trees
					for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
						int h = iters / worldMapWidth;
						int w = iters - (h * worldMapWidth);

						int ph = (player->get_playerCollisionPos().y / 16); // Player position in array
						int pw = (player->get_playerCollisionPos().x / 16);
						int arrNum = (ph * worldMapHeight) + pw;
						mapLoc treeLoc = treeTransparency[arrNum];
						int tLH = treeLoc.vLN[0];
						int tLW = treeLoc.vLN[1];

						Vector2 pos = { (tLW - 0.75) * 16, (tLH - 2) * 16 }; // Position of tree to see behind
						Vector2 pos2 = { (w - 0.75) * 16, (h - 2) * 16 }; // The rest of the trees

						if (pos.x == pos2.x && pos.y == pos2.y) {
							DrawTextureRec(tree1, tree1Rect, pos, opacity50);
						}
						else if (worldTreeMap[h][w] == t1) {
							DrawTextureRec(tree1, tree1Rect, pos2, WHITE);
						};
					};
				}
				else {
					// Trees
					for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
						int h = iters / worldMapWidth;
						int w = iters - (h * worldMapWidth);
						Vector2 pos = { (w - 0.75) * 16, (h - 2) * 16 };

						if (worldTreeMap[h][w] == t1) {
							DrawTextureRec(tree1, tree1Rect, pos, WHITE);
						};
					};
					DrawTextureRec(player->get_player(), player->get_frameRec(), player->get_playerPos(), WHITE);
					//DrawRectangleRec(player->get_playerCollisionPos(), BLACK);
				};

				EndMode2D();
				EndDrawing();
			};
		};
		// -------------------------
		// ----- Game Loop End -----
		delete player;
		UnloadTexture(grassTexture1);
		UnloadTexture(grassTexture2);
		UnloadTexture(grassTexture3);
		UnloadTexture(wallHorizontal);
		UnloadTexture(wallHorizontalTop);
		UnloadTexture(wallVertical);
		UnloadTexture(wallBendUp);
		UnloadTexture(wallBendAway);
		UnloadTexture(wallInnerJoin);
		UnloadTexture(tree1);
		UnloadTexture(menuBackground);
		UnloadTexture(titleBackground);
		UnloadTexture(title);

		for (int i = 0; i < worldMapHeight; i++) {
			delete[] worldMap[i];
			delete[] worldMapDupe[i];
			delete[] worldTreeMap[i];
		}

		delete[] worldMap;
		delete[] worldMapDupe;
		delete[] worldTreeMap;

		worldMap = NULL;
		worldMapDupe = NULL;
		worldTreeMap = NULL;
	}
	CloseAudioDevice();
	CloseWindow();

	if (gameState == 0) {
		main();
	}

	return 0;
};