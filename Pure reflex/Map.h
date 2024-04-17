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
public:
	Map();
	void display(sf::RenderWindow & window,Player & player);
	char get(int x, int y);
};

