#include "Skills.h"
#include "Common.h"
sf::RectangleShape& Player::getSprite()
{
	return sprite;
}



Knife::Knife(Player& player) :AttackSkill(player)
{
	sprite.setFillColor(sf::Color::Red);
	sprite.setSize(sf::Vector2f(20, 10));
}

bool Knife::kill(Player&)
{
    return false;
}

bool Knife::update( float time)
{
	return false;
}

AttackSkill::AttackSkill(Player& player):
	caster(&player)
{
	speed = 0;
	sprite.setPosition(player.getSprite().getPosition());
}

sf::RectangleShape& AttackSkill::draw()
{
	return sprite;
}

bool lineRectIntersection(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd,
    const sf::FloatRect& rect) {

    // Check if any of the line endpoints are inside the rectangle
    if (rect.contains(lineStart) || rect.contains(lineEnd)) {
        return true;
    }

    // Calculate the line's direction vector
    sf::Vector2f lineDir = lineEnd - lineStart;

    // Check for intersection with each of the rectangle's edges
    for (int i = 0; i < 4; i++) {
        // Get the edge's start and end points
        sf::Vector2f edgeStart;
        sf::Vector2f edgeEnd;

        switch (i) {
        case 0: // Top edge
            edgeStart = sf::Vector2f(rect.left, rect.top);
            edgeEnd = sf::Vector2f(rect.left + rect.width, rect.top);
            break;
        case 1: // Right edge
            edgeStart = sf::Vector2f(rect.left + rect.width, rect.top);
            edgeEnd = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
            break;
        case 2: // Bottom edge
            edgeStart = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
            edgeEnd = sf::Vector2f(rect.left, rect.top + rect.height);
            break;
        case 3: // Left edge
            edgeStart = sf::Vector2f(rect.left, rect.top + rect.height);
            edgeEnd = sf::Vector2f(rect.left, rect.top);
            break;
        }

        // Calculate the edge's direction vector
        sf::Vector2f edgeDir = edgeEnd - edgeStart;

        // Calculate the cross product of the line and edge direction vectors
        float crossProduct = lineDir.x * edgeDir.y - lineDir.y * edgeDir.x;

        // If the cross product is zero, the line and edge are parallel
        if (crossProduct != 0) {
            // Calculate the line's parametric equation
            float t = ((edgeStart.x - lineStart.x) * edgeDir.y - (edgeStart.y - lineStart.y) * edgeDir.x) / crossProduct;

            // Check if the intersection point is on the line segment
            if (t >= 0 && t <= 1) {
                // Calculate the intersection point
                sf::Vector2f intersectionPoint = lineStart + t * lineDir;

                // Check if the intersection point is on the edge segment
                float u = ((intersectionPoint.x - edgeStart.x) * edgeDir.x + (intersectionPoint.y - edgeStart.y) * edgeDir.y) / (edgeDir.x * edgeDir.x + edgeDir.y * edgeDir.y);
                if (u >= 0 && u <= 1) {
                    return true;
                }
            }
        }
    }

    // No intersection found
    return false;
}

std::shared_ptr<Player> AttackSkill::getCaster()
{
	return caster;
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
	this->target = normalize(target);
    startPoint = player.getSprite().getPosition();
	auto angle =atan2(target.y, target.x) * 180 / PI-90;
	sprite.setRotation(angle);

	sprite.setFillColor(sf::Color::Blue);
	//sprite.setSize({ 1,1 });
	//sprite.setScale({ 5,5 });

	maxLeng = 200;
	currLeng = 0;
	speed = 1.5;
}

bool Spliter::kill(Player& player)
{
   sf::Vector2f endPoint= startPoint+  currLeng* target;
    return lineRectIntersection(startPoint,endPoint, player.getSprite().getGlobalBounds());
}

bool Spliter::update(float time) {
	currLeng += vectorLeng( target * speed * time);
	if (currLeng >= maxLeng) {
		//sprite.move(target * speed * time*maxLeng/currLeng);
		currLeng = maxLeng;
	
		return false;
	}
	sprite.setSize({ 5, currLeng });
	
	//sprite.move(target * speed * time);
	
	return true;
}