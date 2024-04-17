#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    Player player;
    sf::Clock clock;
    Map map;
    while (window.isOpen())
    {
       
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
        float time = clock.restart().asMicroseconds()/2000.;
        if (time > 1000)
            time = 1000;
        player.update(time,map,window);
        map.display(window,player);
      
    }

    return 0;
}