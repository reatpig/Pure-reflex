#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>

const unsigned int WIDTH=800, HEIGHT = 800;
class Player;
class Map
{
	std::vector<std::vector<char>> map; 
	const unsigned int MAPX=20,MAPY=20;

	std::vector<std::shared_ptr<Player>> allPlayers;
public:

	Map();
	void createPlayer();
	void update(float time, sf::RenderWindow& window);
	void display(sf::RenderWindow & window);
	char get(int x, int y);

	
};

