#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Skills.h"
#include <list>
class Map;
class AttackSkill;


class Player
{
	bool isLife;
	//sf::Sprite sprite;
	sf::RectangleShape sprite;
	 int team;
	sf::Vector2f target;
public:
	std::list<AttackSkill*> allSkills;
	Player();
	void update(float time, Map& map, sf::RenderWindow& window);
	sf::RectangleShape& getSprite();
};

