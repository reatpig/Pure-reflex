#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
class Player;
class AttackSkill {
protected:
	char button;
	sf::RectangleShape sprite;
	float speed;
	sf::Vector2f target;
	sf::Time cooldown;
public:
	AttackSkill(Player& player);
	sf::RectangleShape& draw();
	bool kill(Player&);
	virtual bool update(Player&, float time) = 0;
};

class Knife :public AttackSkill {
public:
	Knife(Player& player);

};

class Spliter :public AttackSkill {
	float maxLeng;
	float currLeng;
public:
	Spliter(Player& player,sf::Vector2f target);
	bool update(Player&, float time) override;
};