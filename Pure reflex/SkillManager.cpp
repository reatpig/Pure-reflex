#include "SkillManager.h"
#include "Skills.h"

bool TimeManager::isOnCooldown()
{
    auto time = cooldown.getElapsedTime();
    if (time > cooldownTime)
        return false;
    return true;
}

inline void SkillFactory::initialization()
{   //Spliter
    TimeManager timeManager;
    timeManager.button = sf::Keyboard::W;
    timeManager.cooldownTime = sf::seconds(1);
    allCooldown.push_back(timeManager);
    //Knife
    timeManager.button = sf::Keyboard::F;
    timeManager.cooldownTime = sf::seconds(1);
    allCooldown.push_back(timeManager);
    isInit = true;
}

AttackSkill * SkillFactory::createSkill(Player* player, Target target)
{
    if (!isInit)
        initialization();
    //Spliter
    auto iter = allCooldown.begin();
    if (sf::Keyboard::isKeyPressed(Spliter::button)) {
        if (!iter->isOnCooldown()) {
            iter->cooldown.restart();
            return new Spliter(*player, target.target);
        }
        else return nullptr;

    }

    //Knife
    iter++;
    if (sf::Keyboard::isKeyPressed(Knife::button)) {
        if (!iter->isOnCooldown()) {
            iter->cooldown.restart();
            return new Knife(*player);
        }
        else return nullptr;
      
    }
    return nullptr;
}


SkillFactory::SkillFactory()
{
    //Spliter
    TimeManager timeManager;
    timeManager.button = sf::Keyboard::W;
    timeManager.cooldownTime = sf::seconds(10);
    allCooldown.push_back(timeManager);
    timeManager.button = sf::Keyboard::F;
    timeManager.cooldownTime = sf::seconds(10);
    allCooldown.push_back(timeManager);
}

void SkillManager::updateAllSkills(float time)
{
    for (auto iter = allSkills.begin(); iter != allSkills.end();++iter) {
        if (!(*iter)->update(time)) {
            iter = allSkills.erase(iter);
            if (iter == allSkills.end())
                return;
        }
    }
}

void SkillManager::drawAllSkills(sf::RenderWindow& window)
{
    for (auto iter = allSkills.begin(); iter != allSkills.end(); ++iter) {
        window.draw((*iter)->draw());
    }
}

void SkillManager::addSkills(sf::Vector2f mousePos, Player* caster)
{
    auto skill = SkillFactory::createSkill(caster, { mousePos, caster });
    if (skill != nullptr) {
        allSkills.push_back(skill);
    }
}
#include <iostream>

void SkillManager::skillKill(std::vector<std::shared_ptr<Player>> &allPlayers)
{
    for (auto skill : allSkills) {
        for (auto player : allPlayers) {
            if (player != skill->getCaster())
                if (skill->kill(*player)) {
                    player->setBlue();
                    std::cout << "Kill"<< std::endl;
                }
        }
    }
}
