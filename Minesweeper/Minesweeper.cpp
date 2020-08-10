#include "Board.h"
#include <SFML/OpenGL.hpp>
#include <unordered_map>
#include <cmath>

bool clicked(sf::Sprite sprite, sf::Vector2i &mousePosition)
{
	sf::IntRect rect((int)sprite.getPosition().x, (int)sprite.getPosition().y, (int)sprite.getGlobalBounds().width, (int)sprite.getGlobalBounds().height);

	if (rect.contains(mousePosition.x, mousePosition.y))
		return true;
	else
		return false;
}

int main()
{
	/*==INITIALIZATION==*/

	/* THE WINDOW
	Window of size 800 x 600
	Title of window is "Minesweeper"
	*/
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	/* THE BOARD
	Load a randomly generated Minesweeper game on startup
	*/
	Board board = Board();
	int restart = 0;


	/*==PROGRAM EXECUTION==*/
	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		//WIN!
		if (board.getTilesLeft() == 0)
		{
			board.setFaceType(2);
			//Set all mines to flagged
			board.flagMines(window);
		}

		//LOSE!
		for (int i = 0; i < LENGTH; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (board.getTiles().at(i).at(j)->getMine() == true && board.getTiles().at(i).at(j)->getRevealed() == true)
				{
					board.setFaceType(1);
				}
			}
		}
		if (board.getFaceType() == 1)
		{
			for (int i = 0; i < LENGTH; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					if (board.getTiles().at(i).at(j)->getMine() == true)
					{
						board.getTiles().at(i).at(j)->setFlagged(false);
						board.getTiles().at(i).at(j)->setTileType(9);
						board.getTiles().at(i).at(j)->setTileSprite();
					}
				}
			}
		}

		//Draw and update tiles
		board.updateTiles(window);

		//Draw and update counter
		board.updateCounter(window);

		//Draw and update face
		board.updateFace(window);

		//Draw the buttons
		board.drawButtons(window);

		//Draw and update debug
		if (board.getDebug() == true)
		{
			board.updateDebug(window);
		}

		sf::Event event;
		//Check for an event
		while (window.pollEvent(event))
		{
			//Check for resize (prevents wrong mouse to sprite position)
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

			switch (event.type)
			{
			//Check for exit
			case sf::Event::Closed:
				window.close();
				break;

			//Check for Mouse Click
			case sf::Event::MouseButtonReleased:
				//Get mouse position
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				bool spriteClicked;
				
				//Right click (FLAGGING)
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//Check if a tile is pressed
					if (board.getFaceType() == 0 && mousePosition.x >= 0 && mousePosition.x < LENGTH * IMAGESIZE && mousePosition.y >= 0 && mousePosition.y < WIDTH * IMAGESIZE)
					{
						int x = mousePosition.x / IMAGESIZE;
						int y = mousePosition.y / IMAGESIZE;

						spriteClicked = clicked(board.getTiles().at(x).at(y)->getTileSprite(), mousePosition);
						if (spriteClicked)
						{
							Tile* clickedTile = board.getTiles().at(x).at(y);

							//Flag or unflag
							if (clickedTile->getFlagged() == false && clickedTile->getRevealed() == false)
							{
								board.increaseFlags();
								clickedTile->setTileType(10);
								clickedTile->setTileSprite();
							}
							else if(clickedTile->getRevealed() == false)
							{
								board.decreaseFlags();
								clickedTile->setTileType(11);
								clickedTile->setTileSprite();
							}
						}
					}
				}

				//Left click
				else if (event.mouseButton.button == sf::Mouse::Left)
				{
					//Chcke if a tile is pressed (REVEALING)
					if (board.getFaceType() == 0 && mousePosition.x >= 0 && mousePosition.x < LENGTH * IMAGESIZE && mousePosition.y >= 0 && mousePosition.y < WIDTH * IMAGESIZE)
					{
						int x = mousePosition.x / IMAGESIZE;
						int y = mousePosition.y / IMAGESIZE;

						spriteClicked = clicked(board.getTiles().at(x).at(y)->getTileSprite(), mousePosition);
						if (spriteClicked)
						{
							Tile* clickedTile = board.getTiles().at(x).at(y);
								
							//Reveal mine
							if (clickedTile->getMine() == true)
							{
								board.revealMine(x, y);
							}
							//Reveal tile, and adjacent tiles
							else
							{
								board.revealTile(x, y);
							}
						}
					}


					//DEBUG BUTTON
					if (mousePosition.x > (LENGTH * IMAGESIZE) - (10 * IMAGESIZE) && mousePosition.x < (LENGTH * IMAGESIZE) - (10 * IMAGESIZE) + 64)
					{
						if (mousePosition.y > WIDTH * IMAGESIZE && mousePosition.y < WIDTH * IMAGESIZE + 64)
						{
							board.setDebug();
						}
					}

					//FACE BUTTON (RESTART)
					if (mousePosition.x > ((LENGTH * IMAGESIZE) / 2) - IMAGESIZE && mousePosition.x < ((LENGTH * IMAGESIZE) / 2) - IMAGESIZE + 64)
					{
						if (mousePosition.y > WIDTH * IMAGESIZE && mousePosition.y < WIDTH * IMAGESIZE + 64)
						{
							for (int i = 0; i < LENGTH; i++)
							{
								for (int j = 0; j < WIDTH; j++)
								{
									delete board.getTiles().at(i).at(j);
								}
							}
							board = Board();
						}
					}

					//TEST BUTTONS
					for(int k = 8; k >= 4; k-= 2)
					{
						if (mousePosition.x > (LENGTH * IMAGESIZE) - (k * IMAGESIZE) && mousePosition.x < (LENGTH * IMAGESIZE) - (k * IMAGESIZE) + 64)
						{
							if (mousePosition.y > WIDTH * IMAGESIZE && mousePosition.y < WIDTH * IMAGESIZE + 64)
							{
								if (k == 8)
								{
									board = Board(1);
									break;
								}
								else if (k == 6)
								{
									board = Board(2);
									break;
								}
								else if (k == 4)
								{
									board = Board(3);
									break;
								}
							}
						}
					}
					



				}

				

				break;
				
			}
		}
		
		

		window.display();
	}

	/* Clean up */
	Textures::Clear();
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; i++)
		{
			delete board.getTiles().at(i).at(j);
		}
	}

	return 0;
}