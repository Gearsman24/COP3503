#pragma once
#include<iostream>
#include<iomanip>
#include <string>
#include <vector>
#include<fstream>
#include <SFML/Graphics.hpp>
#include "Textures.h"

/*
Tile count: 25 x 16 (400 Tiles total)
Mine count: 50 randomly generated mines
*/
#define LENGTH 25
#define WIDTH 16
#define MINES 50
#define IMAGESIZE 32

using namespace std;

class Tile
{
private:
	/* TILE TYPE REPRESENTED BY A NUMBER
	0 = Empty Tile
	1-8 = Number Tile
	9 = Mine Tile
	10 = Flagged Tile
	11 = Unrevealed Tile
	*/

	//A space can be...
	bool isRevealed; //Revealed or unrevealed, 
	bool isFlagged; //Flagged or unflagged
	bool isMine; //Mine or empty
	int tileType; //Empty, a number, or a mine
	int numMines; //A # of adjacent mines

	//A space has...
	sf::Sprite tileSprite; //A sprite for the tile
	sf::Sprite overlayedSprite; //A sprite for flagging and debug
	int xPos;
	int yPos;
	

public:

	Tile(int x, int y);
	~Tile();

	/* TILE FUNCTIONS */
	bool getRevealed();
	bool getFlagged();
	bool getMine();
	int getAdjacentMines();
	sf::Sprite getTileSprite();
	sf::Sprite getOverlaySprite();
	int getXPos();
	int getYPos();


	void setRevealed(bool revealed);
	void setFlagged(bool flagged);
	void setMine(bool mine);

	void setTileType(int type);
	void setTileSprite();
	
	void updateTile(int x, int y, sf::RenderWindow& window);


	void setNumMines(int mines);
};

class Board
{
private:
	vector<vector<Tile*>> tiles; //2D Vector for the tiles in the grid

	int tilesLeft; //Number of empty/number tiles unrevealed
	int totalMines; //For test boards
	int minesLeft; //Number of mines left
	int flagsPlaced; //Number of flags placed
	int faceType; //Type of face

	sf::Sprite digit; //Counter for number of bombs left
	sf::Sprite face; //Face that can change emotion
	sf::Sprite button; //Buttons for debug and tests
	sf::Sprite debug; //Debug shows all mines

	bool debugMode;

public:
	
	Board(); //Default constructor, randomly generated
	Board(int testNumber); //Test board constructors
	void loadData(ifstream& file, string& data, vector<string>& dataSet); //Loading testboard data

	/* BOARD FUNCTIONS */
	vector<vector<Tile*>> getTiles();
	vector<Tile*> getAdjacentTiles(int x, int y);
	bool inBounds(int x, int y);


	//GETTERS AND SETTERS
	int getFaceType();
	void setFaceType(int type);
	int getFlagsPlaced();
	void increaseFlags();
	void decreaseFlags();
	int getTilesLeft();
	void decreaseTilesLeft();
	bool getDebug();
	void setDebug();

	//BOARD IMAGE UPDATES
	void updateTiles(sf::RenderWindow& window);
	void updateCounter(sf::RenderWindow& window);
	void updateFace(sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
	void flagMines(sf::RenderWindow& window);
	void updateDebug(sf::RenderWindow& window);

	//GAME UPDATES
	void revealTile(int x, int y);
	void revealMine(int x, int y);


};
