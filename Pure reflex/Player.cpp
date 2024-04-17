#include "Player.h"
#include "Map.h"
Player::Player()
{
	sprite.setSize({ 15,15 });
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition({ WIDTH/2,HEIGHT/2 });
	target={ WIDTH / 2,HEIGHT / 2 };
}


void Player::update(float time,Map &map,sf::RenderWindow &window)
{
	static int teamId = 0;
	team = teamId;
	teamId++;
	float speed_y=0,speed_x=0;
	for (auto iter = allSkills.begin(); iter != allSkills.end();) {
		
		if (!(*iter)->update(*this, time))
			iter = allSkills.erase(iter);
		else {
			iter++;
		}
	}
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	target = sf::Vector2f(sf::Mouse::getPosition(window));
	//}
	/*sf::Vector2f dif = target - sprite.getPosition();
	if (dif != sf::Vector2f{ 0,0 }) {
		dif = dif / sqrtf(pow(dif.x, 2) + pow(dif.y, 2));
		speed_x = dif.x;
		speed_y = dif.y;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ){
		sf::Vector2f mouse = sf::Vector2f( sf::Mouse::getPosition(window))-sprite.getPosition();
		allSkills.push_back(new Spliter(*this,mouse));
	}
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
	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		 speed_y = 1;
	 }
		//sprite.move({ 0* time,1 * time });

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
