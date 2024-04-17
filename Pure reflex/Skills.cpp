#include "Skills.h"

sf::RectangleShape& Player::getSprite()
{
	return sprite;
}

Knife::Knife(Player& player) :AttackSkill(player)
{
	button = 'Q';

	sprite.setFillColor(sf::Color::Red);
	sprite.setSize(sf::Vector2f(20, 10));
}

AttackSkill::AttackSkill(Player& player)
{
	sprite.setPosition(player.getSprite().getPosition());
}

sf::RectangleShape& AttackSkill::draw()
{
	return sprite;
}

bool AttackSkill::kill(Player& player)
{
	//sf::Rect<float> playerRect(player.getSprite().getPosition(), player.getSprite().getSize());
	//sf::Rect<float> playerRect(sprite.getPosition(), playe.getSize());
	return	player.getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds());
}
float vectorLeng(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}
sf::Vector2f& normalize(sf::Vector2f &vector) {
	float leng = vectorLeng(vector);
	vector /= leng;
	return vector;
   
}
Spliter::Spliter(Player& player, sf::Vector2f target) :AttackSkill(player)
{
	button = 'W';
	sprite.setFillColor(sf::Color::Blue);
	sprite.setSize({ 1,1 });
	sprite.setScale({ 5,5 });
	this->target = normalize(target);
	maxLeng = 200;
	currLeng = 0;
	speed = 1.5;
}

bool Spliter::update(Player& player, float time) {
	currLeng += vectorLeng( target * speed * time);
	if (currLeng >= maxLeng) {
		sprite.move(target * speed * time*maxLeng/currLeng);
		
		return false;
	}
	sprite.move(target * speed * time);
	return true;
}