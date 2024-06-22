#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
class Player;

class AttackSkill {
protected:
	sf::RectangleShape sprite;
	std::shared_ptr <Player> caster;
	float speed;
	sf::Vector2f target;

public:

	AttackSkill(Player& player);
	sf::RectangleShape& draw();
	virtual bool kill(Player&)=0;
	std::shared_ptr <Player> getCaster();
	virtual bool update( float time) = 0;
	
};


class Knife :public AttackSkill {
	
public:
	const static sf::Keyboard::Key button = sf::Keyboard::Z;
	Knife(Player& player);
	bool kill(Player&) override;
	bool update( float time) override;
	
};

class Spliter :public AttackSkill {
	
	float maxLeng;
	float currLeng;
	sf::Vector2f startPoint;

public:
	const static sf::Keyboard::Key button = sf::Keyboard::F;
	Spliter(Player& player, sf::Vector2f target);
	bool kill(Player&) override;
	bool update( float time) override;

};