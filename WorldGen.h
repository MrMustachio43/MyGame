#pragma once
#ifndef WorldGen
#define WorldGen

#include <map>
#include <process.h>
#include <iostream>
#include <fstream>

using namespace std;

static int worldMapWidth = 100;
static int worldMapHeight = 60;
extern int** worldMap;
extern int** worldMapDupe;
extern int** worldTreeMap;
static int tempArr[3][3];

static struct mapLoc {
	int vLN[2]; // valid Location Number
};

static map<int, mapLoc> validLocation;
static map<int, mapLoc> treeTransparency;

static enum Tiles {
	gP = 1,		// Grass Plain
	gG,			// Grass Grass
	gF,			// Grass Flowers
	wHT,		// Wall Horizontal top
	wH,			// Wall Horizontal
	wV,			// Wall Vertical
	wBU,		// Wall Bent Up
	wBA,		// Wall Bent Away
	wIJ,		// Wall Inner Joint
	t1,			// Tree 1
	tT			// Tree Transparency
};

//map<int, int> testMap = { 
//	{0, 0},
//	{1, 16},
//	{2, 96},
//	{3, 144}
//};

//int worldMap[5][5] = { 
//{5 ,5, 5, 5, 5},
//{5,-4, 8, 4, 5},
//{5,-2, 5, 2, 5},
//{5,-3, 9, 3, 5},
//{5, 5, 5, 5, 5},
//};

// Passing NULL gives current time
// times proccess id to get random value
static int seed = time(NULL) * _getpid();


void mapNoiseGenerator(int density);

int neighbour(int y, int x, bool dupe);

void displayMap();

void displayTreeMap();

void copyMap();

void randomGrass();

void wallGeneration();

void getRidOfOuties(); //Smooths Noise for easier wall generation

void storeValidLocation();

void generateTrees(int numTrees);

bool isWall(int h, int w);

bool shouldBeTransparent(int h, int w);

void generateWorldMap();

void innitWorldArray();

#endif