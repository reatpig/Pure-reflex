#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Skills.h"
#include <list>
#include <memory>

#include "SkillManager.h"

class Map;
class AttackSkill;
class SkillManager;

class Player
{
	bool isLife;
	bool isControllable;
	//sf::Sprite sprite;
	sf::RectangleShape sprite;
	 int team;
	sf::Vector2f target;

public:

	std::shared_ptr< SkillManager> skillManager;
	Player(bool isControllable= true);
	void update(float time, Map& map, sf::RenderWindow& window);
	sf::RectangleShape& getSprite();

	//TODO erase
	void setBlue();
};

