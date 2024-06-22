#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include <memory>

#include "Skills.h"

struct Target
{
    sf::Vector2f target;
    Player *playerTarget;

};
struct TimeManager {
    sf::Time cooldownTime;
    sf::Clock cooldown;
    sf::Keyboard::Key button;
    bool isOnCooldown();
};

class AttackSkill;
class SkillManager {
    inline static std::list<AttackSkill *> allSkills;
    SkillManager();
public:
    void static updateAllSkills(float time);
    void static drawAllSkills(sf::RenderWindow& window);
    void static addSkills(sf::Vector2f mousePos,Player * caster);
    void static skillKill(std::vector<std::shared_ptr<Player>> &allPlayers);
};
//Factory  
class SkillFactory
{
    inline static std::vector<TimeManager> allCooldown;
    inline static bool isInit=false;
    static void initialization();
    SkillFactory();
public:
    static AttackSkill* createSkill(Player* player, Target target);
 
  
};

