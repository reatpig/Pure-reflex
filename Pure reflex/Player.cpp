#include "Player.h"
#include "Map.h"
#include "SkillManager.h"
Player::Player(bool isControllable)
{
	this->isControllable = isControllable;

	sprite.setSize({ 15,15 });
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition({ WIDTH/2,HEIGHT/2 });

	target={ WIDTH / 2,HEIGHT / 2 };

}
void Player::setBlue()
{
	sprite.setFillColor(sf::Color::Blue);
}
//TODO send to map
void Player::update(float time,Map &map,sf::RenderWindow &window)
{
	static int teamId = 0;
	team = teamId;
	teamId++;
	float speed_y=0,speed_x=0;
	if (isControllable) {
		sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window)) - sprite.getPosition();
		SkillManager::addSkills(mouse, this);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			speed_x = -1;

		}
		//sprite.move({ -1 * time,0 * time });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			speed_x = 1;

		}
		//sprite.move({ 1 * time,0 * time });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			speed_y = -1;
		}
		//	sprite.move({ 0 * time,-1 * time });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

			speed_y = 1;
		}
		//sprite.move({ 0* time,1 * time });

	}
	 auto rect_hero = sprite.getPosition();
	 auto top = sprite.getPosition().y ;
	 auto left = sprite.getPosition().x ;
	 auto height =  sprite.getSize().y;
	 auto width =  sprite.getSize().x;

	 int down2 = ( top +  height + speed_y * time) / 32 ;
	 int right2 = ( left +  width + speed_x * time) / 32;
	 int top2 = (top  + speed_y * time) / 32 ;
	 int left2 = (left  + speed_x * time) / 32;
	 if (map.get(left2, top2) != '0') {
		 speed_x = 0;
		 speed_y = 0;
	 }
	 if (map.get(right2, down2) != '0') {
		 speed_x = 0;
		 speed_y = 0;
	 }
	 sprite.setPosition(sprite.getPosition().x + speed_x * time,
		 sprite.getPosition().y + speed_y * time);

}
