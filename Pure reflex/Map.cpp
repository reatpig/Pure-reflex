#include "Map.h"

Map::Map()
{
	map.resize(MAPY);
	for (int i = 0; i < MAPY; ++i)
		map[i].resize(MAPX);
	for (int i = 0; i < MAPY; ++i)
		for (int r = 0; r < MAPX; ++r)
			if (i == 0 || r == 0 || MAPX-1 ==r || MAPY-1 == i)
				map[i][r] = '1';
			else map[i][r] = '0';

}

void Map::display(sf::RenderWindow& window, Player& player)
{
	window.clear(sf::Color::White);
	sf::RectangleShape rectangle;
	rectangle.setSize( sf::Vector2f(32, 32));
	for (int i = 0; i < MAPX; ++i)
		for (int r = 0; r < MAPY; ++r) {

			if (map[i][r] == '0')
				continue;
			else 
				rectangle.setFillColor(sf::Color::Black);
			rectangle.setPosition(r * 32, i * 32);
			window.draw(rectangle);
		}
	for (auto& skill : player.allSkills)
		window.draw(skill->draw());
	window.draw(player.getSprite());
	window.display();
}

char Map::get(int x, int y)
{
	return map[y][x];
}

