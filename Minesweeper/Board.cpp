#include "Board.h"
#include "Random.h"

/* TILE FUNCTIONS */
Tile::Tile(int x, int y)
{
	numMines = 0;
	xPos = x;
	yPos = y;

	isRevealed = false;
	isFlagged = false;
	isMine = false;
	tileType = 11; //All tiles are hidden by default

	tileSprite.setTexture(Textures::getTexture("tile_hidden"));
	overlayedSprite.setTexture(Textures::getTexture("tile_hidden"));
}
Tile::~Tile()
{

}

//GETTERS
bool Tile::getRevealed()
{
	return isRevealed;
}
bool Tile::getFlagged()
{
	return isFlagged;
}
bool Tile::getMine()
{
	return isMine;
}
int Tile::getAdjacentMines()
{
	return numMines;
}
sf::Sprite Tile::getTileSprite()
{
	return tileSprite;
}
sf::Sprite Tile::getOverlaySprite()
{
	return overlayedSprite;
}
int Tile::getXPos()
{
	return xPos;
}
int Tile::getYPos()
{
	return yPos;
}

//SETTERS
void Tile::setRevealed(bool revealed)
{
	isRevealed = revealed;
}
void Tile::setFlagged(bool flagged)
{
	isFlagged = flagged;
}
void Tile::setMine(bool mine)
{
	isMine = mine;
}
void Tile::setTileType(int type)
{
	this->tileType = type;
}
void Tile::setTileSprite()
{
	//Left clicks
	if (tileType <= 9)
	{
		tileSprite.setTexture(Textures::getTexture("tile_revealed"));
		if (tileType == 0)
		{
			overlayedSprite.setTexture(Textures::getTexture("tile_revealed"));
		}
		else if (tileType == 9)
		{
			overlayedSprite.setTexture(Textures::getTexture("mine"));
		}
		else if (tileType == 1)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_1"));
		}
		else if (tileType == 2)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_2"));
		}
		else if (tileType == 3)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_3"));
		}
		else if (tileType == 4)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_4"));
		}
		else if (tileType == 5)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_5"));
		}
		else if (tileType == 6)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_6"));
		}
		else if (tileType == 7)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_7"));
		}
		else if (tileType == 8)
		{
			overlayedSprite.setTexture(Textures::getTexture("number_8"));
		}
	}

	//Right clicks
	else if (tileType > 9)
	{
		if (isRevealed == false && isFlagged == false && tileType == 10)
		{
			tileSprite.setTexture(Textures::getTexture("tile_hidden"));
			overlayedSprite.setTexture(Textures::getTexture("flag"));
			isFlagged = true;
		}
		else if (isRevealed == false && isFlagged == true && tileType == 11)
		{
			tileSprite.setTexture(Textures::getTexture("tile_hidden"));
			overlayedSprite.setTexture(Textures::getTexture("tile_hidden"));
			isFlagged = false;
		}
	}

}
void Tile::updateTile(int x, int y, sf::RenderWindow& window)
{
	setTileSprite();
	tileSprite.setPosition(x * IMAGESIZE, y * IMAGESIZE);
	overlayedSprite.setPosition(x * IMAGESIZE, y * IMAGESIZE);
	window.draw(tileSprite);
	window.draw(overlayedSprite);
}

void Tile::setNumMines(int mines)
{
	numMines = mines;
}


/* BOARD FUNCTIONS */
Board::Board()
{
	tilesLeft = (LENGTH * WIDTH) - MINES;
	minesLeft = MINES;
	flagsPlaced = 0;
	digit.setTexture(Textures::getTexture("digits"));
	face.setTexture(Textures::getTexture("face_happy"));
	debug.setTexture(Textures::getTexture("mine"));
	debugMode = false;
	faceType = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		vector<Tile*> tileCol;
		for (int j = 0; j < WIDTH; j++)
		{
			//Initialize each space in the grid with a tile
			Tile* newTile = new Tile(i, j);
			tileCol.push_back(newTile);
		}
		tiles.push_back(tileCol);
	}

	//Initialize position of mines in the grid
	totalMines = 0;
	while (totalMines < MINES)
	{
		int x = Random::randNum(0, LENGTH - 1); //xth row
		int y = Random::randNum(0, WIDTH - 1); //yth column
		if (tiles.at(x).at(y)->getMine() == false)
		{
			tiles.at(x).at(y)->setMine(true);
			totalMines++;
		}
	}

	//Get adjacent mines for each tile (except bombs), taking edges into account
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			vector<Tile*> adjacents = getAdjacentTiles(i, j);
			
			int mine = 0;
			for (int k = 0; k < (int)adjacents.size(); k++)
			{
				if (adjacents.at(k)->getMine() == true)
				{
					mine++;
				}
			}
			tiles.at(i).at(j)->setNumMines(mine);
		}
	}
}
void Board::loadData(ifstream& file, string& data, vector<string>& dataSet)
{
	getline(file, data);
	dataSet.push_back(data);
}
Board::Board(int testNumber)
{
	totalMines = 0;
	flagsPlaced = 0;
	minesLeft = 0;
	digit.setTexture(Textures::getTexture("digits"));
	face.setTexture(Textures::getTexture("face_happy"));
	debug.setTexture(Textures::getTexture("mine"));
	debugMode = false;
	faceType = 0;

	for (int i = 0; i < LENGTH; i++)
	{
		vector<Tile*> tileCol;
		for (int j = 0; j < WIDTH; j++)
		{
			//Initialize each space in the grid with a tile

			Tile* newTile = new Tile(i, j);
			tileCol.push_back(newTile);
		}
		tiles.push_back(tileCol);
	}

	//Open file
	ifstream file;
	string fileName = "boards\\testboard" + to_string(testNumber) + ".brd";
	file.open(fileName);

	vector<string> rowStrings;

	string line;
	while (file.good())
	{
		loadData(file, line, rowStrings);
	}
	file.close();

	char type;
	//Initialize position of mines in the grid
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			type = rowStrings.at(i).at(j);
			if (type == '1')
			{
				tiles.at(j).at(i)->setMine(true);
				totalMines++;
				minesLeft++;
			}
		}
	}
	tilesLeft = (LENGTH * WIDTH) - totalMines;

	//Get adjacent mines for each tile (except bombs), taking edges into account
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			vector<Tile*> adjacents = getAdjacentTiles(i, j);

			int mine = 0;
			for (int k = 0; k < (int)adjacents.size(); k++)
			{
				if (adjacents.at(k)->getMine() == true)
				{
					mine++;
				}
			}
			tiles.at(i).at(j)->setNumMines(mine);
		}
	}
}

//GETTERS
int Board::getFaceType()
{
	return faceType;
}
void Board::setFaceType(int type)
{
	faceType = type;
}
int Board::getFlagsPlaced()
{
	return flagsPlaced;
}
int Board::getTilesLeft()
{
	return tilesLeft;
}
bool Board::getDebug()
{
	return debugMode;
}

//SETTERS
void Board::increaseFlags()
{
	flagsPlaced++;
	minesLeft--;
}
void Board::decreaseFlags()
{
	flagsPlaced--;
	minesLeft++;
}
void Board::decreaseTilesLeft()
{
	tilesLeft--;
}
void Board::setDebug()
{
	if (debugMode == false)
	{
		debugMode = true;
	}
	else
	{
		debugMode = false;
	}
}



vector<vector<Tile*>> Board::getTiles()
{
	return tiles;
}
bool Board::inBounds(int x, int y)
{
	if (x < 0 || x >= LENGTH)
		return false;
	if (y < 0 || y >= WIDTH)
		return false;
	return true;
}
vector<Tile*> Board::getAdjacentTiles(int x, int y)
{
	vector<Tile*> adjacentTiles;

	const int row[] = { -1, -1, -1, 1, 1, 1, 0, 0 };
	const int column[] = { -1, 0, 1, -1, 0, 1, -1, 1 };

	for (int i = 0; i < 8; i++)
	{
		if (inBounds(x + row[i], y + column[i]))
		{
			adjacentTiles.push_back(tiles.at(x + row[i]).at(y + column[i]));
		}
	}
	return adjacentTiles;
}
void Board::updateTiles(sf::RenderWindow& window)
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			tiles.at(i).at(j)->updateTile(i, j, window);
		}
	}
}
void Board::updateCounter(sf::RenderWindow& window)
{
	int mines = totalMines - flagsPlaced;
	int ones = abs(mines) % 10;
	int tens = (abs(mines) / 10) % 10;
	int hundreds = (abs(mines) / 100) % 10;

	int position = 0;
	//If game is not won
	if(faceType != 2)
	{ 
		if (mines < 0)
		{
			digit.setTextureRect(sf::IntRect(21 * 10, 0, 21, IMAGESIZE));
			digit.setPosition(position, WIDTH * IMAGESIZE);
			window.draw(digit);
			position += 21;
		}

		if (hundreds != 0) //I think it looks nicer this way with two digits showing
		{
			digit.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, IMAGESIZE));
			digit.setPosition(position, WIDTH * IMAGESIZE);
			window.draw(digit);
			position += 21;
		}

		
		digit.setTextureRect(sf::IntRect(21 * tens, 0, 21, IMAGESIZE));
		digit.setPosition(position, WIDTH * IMAGESIZE);
		window.draw(digit);
		position += 21;

		digit.setTextureRect(sf::IntRect(21 * ones, 0, 21, IMAGESIZE));
		digit.setPosition(position, WIDTH * IMAGESIZE);
		window.draw(digit);
	}
	//If game is won
	else if (faceType == 2)
	{
		digit.setTextureRect(sf::IntRect(0, 0, 21, IMAGESIZE));
		digit.setPosition(position, WIDTH * IMAGESIZE);
		window.draw(digit);
		position += 21;
		digit.setPosition(position, WIDTH * IMAGESIZE);
		window.draw(digit);
	}
	
}
void Board::updateFace(sf::RenderWindow& window)
{
	switch (faceType)
	{
	case 0:
		face.setTexture(Textures::getTexture("face_happy"));
		break;
	case 1:
		face.setTexture(Textures::getTexture("face_lose"));
		break;
	case 2:
		face.setTexture(Textures::getTexture("face_win"));
		break;
	}

	face.setPosition(((LENGTH * IMAGESIZE) / 2) - IMAGESIZE, WIDTH * IMAGESIZE);
	window.draw(face);
}
void Board::updateDebug(sf::RenderWindow& window)
{
	if (debugMode == true)
	{
		for (int i = 0; i < LENGTH; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (tiles.at(i).at(j)->getMine() == true)
				{
					debug.setPosition(i * IMAGESIZE, j * IMAGESIZE);
					window.draw(debug);
				}
			}
		}
	}
}
void Board::drawButtons(sf::RenderWindow& window)
{
	//Debug
	button.setTexture(Textures::getTexture("debug"));
	button.setPosition((LENGTH * IMAGESIZE) - (10 * IMAGESIZE), WIDTH * IMAGESIZE);
	window.draw(button);

	//Buttons
	button.setTexture(Textures::getTexture("test_1"));
	button.setPosition((LENGTH * IMAGESIZE) - (8 * IMAGESIZE), WIDTH * IMAGESIZE);
	window.draw(button);

	button.setTexture(Textures::getTexture("test_2"));
	button.setPosition((LENGTH * IMAGESIZE) - (6 * IMAGESIZE), WIDTH * IMAGESIZE);
	window.draw(button);

	button.setTexture(Textures::getTexture("test_3"));
	button.setPosition((LENGTH * IMAGESIZE) - (4 * IMAGESIZE), WIDTH * IMAGESIZE);
	window.draw(button);
}

void Board::flagMines(sf::RenderWindow& window)
{
	flagsPlaced = MINES;
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (tiles.at(i).at(j)->getMine() == true)
			{
				tiles.at(i).at(j)->setTileType(10);
				tiles.at(i).at(j)->setTileSprite();
			}
		}
	}
}


void Board::revealTile(int x, int y)
{
	if (tiles.at(x).at(y)->getMine() == false && tiles.at(x).at(y)->getFlagged() == false && tiles.at(x).at(y)->getRevealed() == false)
	{
		decreaseTilesLeft();
		tiles.at(x).at(y)->setFlagged(false);
		tiles.at(x).at(y)->setRevealed(true);
		tiles.at(x).at(y)->setTileType(tiles.at(x).at(y)->getAdjacentMines());
		tiles.at(x).at(y)->setTileSprite();
	}

	if (tiles.at(x).at(y)->getAdjacentMines() == 0 && tiles.at(x).at(y)->getFlagged() == false)
	{
		vector<Tile*> reveals = getAdjacentTiles(x, y);
		for (int i = 0; i < (int)reveals.size(); i++)
		{
			if (reveals.at(i)->getMine() == false)
			{
				int xReveal = reveals.at(i)->getXPos();
				int yReveal = reveals.at(i)->getYPos();
				if(tiles.at(xReveal).at(yReveal)->getRevealed() == false)
					revealTile(reveals.at(i)->getXPos(), reveals.at(i)->getYPos());
			}
		}
	}
}
void Board::revealMine(int x, int y)
{
	if(tiles.at(x).at(y)->getFlagged() == false)
	{ 
		tiles.at(x).at(y)->setRevealed(true);
		tiles.at(x).at(y)->setTileType(9);
		tiles.at(x).at(y)->setTileSprite();
	}
	
}

