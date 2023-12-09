#include "WorldGen.h"

int** worldMap = new int* [worldMapHeight];
int** worldMapDupe = new int* [worldMapHeight];
int** worldTreeMap = new int* [worldMapHeight];

void innitWorldArray() {
	for (int i = 0; i < worldMapHeight; i++) {
		worldMap[i] = new int[worldMapWidth];
		worldMapDupe[i] = new int[worldMapWidth];
		worldTreeMap[i] = new int[worldMapWidth];
	};
};

void mapNoiseGenerator(int density) { // Density = percent of 1's (alive cells)
	srand(seed); // sets a random value for rand()
	for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
		int h = iters / worldMapWidth;
		int w = iters - (h * worldMapWidth);

		if (rand() % 100 > density) { worldMap[h][w] = 0; }
		else { worldMap[h][w] = gP; }
	};
};

int neighbour(int y, int x, bool dupe) {	// Finds surounding tiles
	
	int count = 0;
	int tempw = 0; //temporary width
	int temph = 0; //temporary height

	for (int h = y - 1; h <= y + 1; h++) {

		if (h == -1) { h = 0; }
		if((h == y + 1) && (y + 1 > worldMapHeight - 1)) { break; }			//stop from reaching too far (height)

		for (int w = x - 1;  w <= x + 1; w++) {

			if (w == -1) { w = 0; }
			if ((w == x + 1) && (x + 1 > worldMapWidth - 1)) { break; }	//stop from reaching too far (width)

			if (dupe) { // Check if you want to use the duplicated worldMap
				int num = worldMapDupe[h][w];
				tempArr[temph][tempw] = num; // 3 wide, 3 high array
				count += num;
				//cout << tempArr[th][tw];
			}

			else {
				count += worldMap[h][w]; // tells us number of grass tiles
			};
			tempw += 1;
		};
		tempw = 0;
		temph += 1;
	};
	//cout << count << endl;
	return count;
};

void displayMap() {
	for (int h = 0; h < worldMapHeight; h++) {
		for (int w = 0; w < worldMapWidth; w++) {
			if (worldMap[h][w] == gP || worldMap[h][w] == gG || worldMap[h][w] == gF) {
				cout << ".";
			}
			else {
				cout << worldMap[h][w];
			}
		};
		cout << "\n";
	};
	cout << "\n";
};

void displayTreeMap() {
	for (int h = 0; h < worldMapHeight; h++) {
		for (int w = 0; w < worldMapWidth; w++) {
			if (worldTreeMap[h][w] == 0) {
				cout << ".";
			}
			else {
				cout << worldTreeMap[h][w];
			}
		};
		cout << "\n";
	};
};

void copyMap() {
	for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
		int h = iters / worldMapWidth;
		int w = iters - (h * worldMapWidth);

		int num = worldMap[h][w];
		worldMapDupe[h][w] = num;
	};
};

void randomGrass() {
	srand(seed);
	for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
		int h = iters / worldMapWidth;
		int w = iters - (h * worldMapWidth);

		if (worldMap[h][w] == 1) {	// If cell = grass, make grass more random looking
			int r = (rand() % 100);
			if (r < 50) { worldMap[h][w] = gP; }
			else if (r >= 50 && r < 90) { worldMap[h][w] = gG; }
			else if (r >= 90) { worldMap[h][w] = gF; }
			//cout << r << " ";
		};
	};
};

void wallGeneration() {
	for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
		int h = iters / worldMapWidth;
		int w = iters - (h * worldMapWidth);

		int count = neighbour(h, w, true);
		if (tempArr[1][1] == 0) {
			if (tempArr[1][1] == 0) {
				// represent if it should be horizontal Top
				if (tempArr[0][1] == !0 && tempArr[1][0] == 0 && tempArr[1][2] == 0 && tempArr[2][1] == 0) {
					if (tempArr[1][0] == 0 && tempArr[2][0] == !0 && tempArr[2][2] == 0) {
						worldMap[h][w] = -wBA;
					}
					else if (tempArr[1][2] == 0 && tempArr[2][2] == !0 && tempArr[2][0] == 0) {
						worldMap[h][w] = wBA;
					}
					else {
						worldMap[h][w] = wHT;
					}
				}

				/*if (tempArr[0][1] == 0 && tempArr[1][0] == 0 && tempArr[1][2] == 0 && (~tempArr[0][0] != ~tempArr[0][2])) {
					worldMap[h][w] = wHT;
				}*/

				// represent if it should be horizontal
				if (tempArr[0][1] == 0 && tempArr[1][0] == 0 && tempArr[1][2] == 0 && tempArr[2][1] == !0) { // works
					if (tempArr[1][0] == 0 && tempArr[0][0] == !0) {
						worldMap[h][w] = -wBU;
					}
					else if (tempArr[1][2] == 0 && tempArr[0][2] == !0) {
						worldMap[h][w] = wBU;
					}
					else {
						worldMap[h][w] = wH;
					}
				}

				// if vertical
				if (tempArr[0][1] == 0 && ((tempArr[1][0] == !0 && tempArr[1][2] == 0) || (tempArr[1][0] == 0 && tempArr[1][2] == !0)) && tempArr[2][1] == 0) { // works

					// if vertical but should be bent up
					if (tempArr[2][1] == 0 && tempArr[2][2] == !0 && tempArr[1][0] == !0) {
						worldMap[h][w] = -wBU;
					}
					else if (tempArr[2][1] == 0 && tempArr[2][0] == !0 && tempArr[1][2] == !0) {
						worldMap[h][w] = wBU;
					}

					// if vertical but should be bent away
					else if (tempArr[0][1] == 0 && tempArr[0][2] == !0 && tempArr[1][0] == !0) {
						worldMap[h][w] = -wBA;
					}
					else if (tempArr[0][1] == 0 && tempArr[0][0] == !0 && tempArr[1][2] == !0) {
						worldMap[h][w] = wBA;
					}

					// should it even exist?
					else if (tempArr[1][0] == 0 && tempArr[0][0] == !0 && tempArr[2][0] == !0) {
						worldMap[h][w] = gG; // left
					}
					else if (tempArr[1][2] == 0 && tempArr[0][2] == !0 && tempArr[2][2] == !0) {
						worldMap[h][w] = gG; // right
					}

					else {
						if (tempArr[1][0] == !0 && tempArr[1][2] == 0) { worldMap[h][w] = -wV; } // Vertical flipped
						else { worldMap[h][w] = wV; } // represent if it should be vertical
					};
				}

				// represent if it should be bent up
				if (tempArr[0][1] == 0 && ((tempArr[1][0] == !0 && tempArr[1][2] == 0) || (tempArr[1][0] == 0 && tempArr[1][2] == !0)) && tempArr[2][1] == !0) { // works
					if ((tempArr[0][0] == !0 && tempArr[1][0] == 0) || (tempArr[0][2] == !0 && tempArr[1][2] == 0)) {
						worldMap[h][w] = gG;
					}
					else {
						if (tempArr[1][0] == !0 && tempArr[1][2] == 0) { worldMap[h][w] = -wBU; } // Bent up flipped
						else { worldMap[h][w] = wBU; }
					}
				}

				// represent if it should be bent Away
				if (tempArr[0][1] == !0 && ((tempArr[1][0] == !0 && tempArr[1][2] == 0) || (tempArr[1][0] == 0 && tempArr[1][2] == !0)) && tempArr[2][1] == 0) { // works
					if ((tempArr[2][0] == !0 && tempArr[1][0] == 0) || (tempArr[2][2] == !0 && tempArr[1][2] == 0)) {
						worldMap[h][w] = gG;
					}
					else {
						if (tempArr[1][0] == !0 && tempArr[1][2] == 0) { worldMap[h][w] = -wBA; } // Bent away flipped
						else { worldMap[h][w] = wBA; }
					}
				}

				// represents if it should be an inner join						
				if (tempArr[0][1] == 0 && tempArr[1][0] == 0 && tempArr[1][2] == 0 && tempArr[2][1] == 0 && (tempArr[2][2] == !0 || tempArr[2][0] == !0)) {

					// should be a vertical wall
					if (tempArr[0][0] == !0 && tempArr[0][2] == !0) {
						worldMap[h][w] = -wV;
					}
					else if (tempArr[0][2] == !0 && tempArr[2][2] == !0) {
						worldMap[h][w] = wV;
					}

					// if it should be a horizontal
					if (tempArr[2][0] == !0 && tempArr[2][2] == !0) {
						worldMap[h][w] = wH;
					}

					else {
						if (tempArr[2][0] == !0) {
							worldMap[h][w] = -wIJ;
						}
						else {
							worldMap[h][w] = wIJ;
						}
					}
				}

			}
			else {
				worldMap[h][w] = gP;
			};
		};
	};
};

void getRidOfOuties() {
	for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
		int h = iters / worldMapWidth;
		int w = iters - (h * worldMapWidth);

		int count = neighbour(h, w, true);
		if (tempArr[1][1] == 0) {

			if (tempArr[0][0] == 0 && tempArr[0][1] == 0 && tempArr[0][2] == 0 && count >= 3) {
				worldMap[h][w] = 1; // top 
			}
			if (tempArr[0][0] == 0 && tempArr[1][0] == 0 && tempArr[2][0] == 0 && count >= 3) {
				worldMap[h][w] = 1; // left
			}
			if (tempArr[2][0] == 0 && tempArr[2][1] == 0 && tempArr[2][2] == 0 && count >= 3) {
				worldMap[h][w] = 1; // right
			}
			if (tempArr[0][2] == 0 && tempArr[1][2] == 0 && tempArr[2][2] == 0 && count >= 3) {
				worldMap[h][w] = 1; // bottom
			}
			//
		// top side or bottom == 0, with either side being 0 and rest 1's
			if (tempArr[0][1] == 0 && ((tempArr[0][0] == 0 && tempArr[0][2] == !0) || (tempArr[0][0] == !0 && tempArr[0][2] == 0)) && count >= 4) {
				worldMap[h][w] = 1; // Top
			}
			if (tempArr[2][1] == 0 && ((tempArr[2][0] == 0 && tempArr[2][2] == !0) || (tempArr[2][0] == !0 && tempArr[2][2] == 0)) && count >= 4) {
				worldMap[h][w] = 1; // Bottom
			}
			if (tempArr[1][0] == 0 && ((tempArr[0][0] == 0 && tempArr[2][0] == !0) || (tempArr[0][0] == !0 && tempArr[2][0] == 0)) && count >= 4) {
				worldMap[h][w] = 1; //left
			}
			if (tempArr[1][2] == 0 && ((tempArr[0][2] == 0 && tempArr[2][2] == !0) || (tempArr[0][2] == !0 && tempArr[2][2] == 0)) && count >= 4) {
				worldMap[h][w] = 1; // right
			}
			//
			//
			if (count >= 7) {
				worldMap[h][w] = 1;
			};
		};
	};
};

void storeValidLocation() {		//Needed to prevent spawning strees on wall tiles
	int count = 0;
	for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
		int h = iters / worldMapWidth;
		int w = iters - (h * worldMapWidth);

		if (worldMap[h][w] == gP || worldMap[h][w] == gG || worldMap[h][w] == gF) {
			mapLoc location = { h, w };
			pair<int, mapLoc> pair(count, location);
			validLocation.insert(pair);
			count++;
		}
	};
};

void generateTrees(int numTrees) {

	srand(seed);
	int size = validLocation.size();


	for (int i = 0; i < numTrees; i++) {

		int r = (rand() % size);
		mapLoc treeLocation = validLocation[r];
		int h = treeLocation.vLN[0];
		int w = treeLocation.vLN[1];

		worldTreeMap[h][w] = t1;

		for (int k = h - 2; k <= h; k++) {

			if (k == -1 || k == -2) { k = h; }
			//The height is always in bounds (going numerically up the array), so we dont need to check for it

			for (int j = w - 1; j <= w + 1; j++) {

				if (j == -1) { k = w; }
				if ((j == w + 1) && (w + 1 > worldMapWidth)) { break; }

				if (worldTreeMap[k][j] == t1) {
					worldTreeMap[h][w] = t1;
				}
				else {
					worldTreeMap[k][j] = tT;

					int arrNum = (k * worldMapHeight) + j;
					mapLoc location = { h, w };
					pair<int, mapLoc> pair(arrNum, location);
					treeTransparency.insert(pair);
				};
			};
		};
	};
};

bool isWall(int h, int w) {
	int num = worldMap[h][w];
	switch (num) {
	case wH:
		return true;
	case wHT:
		return true;
	case wV:
		return true;
	case -wV:
		return true;
	case wBU:
		return true;
	case -wBU:
		return true;
	case wBA:
		return true;
	case -wBA:
		return true;
	default:
		return false;
	};
};

bool shouldBeTransparent(int h, int w) {
	int num = worldTreeMap[h][w];
	switch (num) {
	case tT:
		return true;
	default:
		return false;
	};
};

void generateWorldMap() {

	innitWorldArray();

	mapNoiseGenerator(55);

	displayMap();
	cout << "------------^^Noise^^----------------" << endl << endl;

	int CAIterations = 1; // Cellular Automata

	for (int i = 0; i < CAIterations; i++) {
		for (int iters = 0; iters < worldMapHeight * worldMapWidth; iters++) {
			int h = iters / worldMapWidth;
			int w = iters - (h * worldMapWidth);
			int count = neighbour(h, w, false);
			if (worldMap[h][w] == 0 && count >= 6) { worldMap[h][w] = 1; }
			if (worldMap[h][w] == 1 && count <= 3) { worldMap[h][w] = 0; }
		};
	};

	displayMap();
	cout << "------------^^Cellular A^^----------------" << endl << endl;

	copyMap();
	getRidOfOuties();
	copyMap();

	displayMap();
	cout << "------------^^Outies^^----------------" << endl << endl;

	randomGrass();

	displayMap();
	cout << "------------^^Grass^^----------------" << endl << endl;

	wallGeneration();

	displayMap();
	cout << "------------^^Walls^^----------------" << endl << endl;

	storeValidLocation();
	int treeCount = validLocation.size() * 0.1; // 10% of the map (where not a wall) will be covered in trees
	generateTrees(treeCount);

	displayTreeMap();
	cout << "------------^^Trees^^----------------" << endl << endl;
}