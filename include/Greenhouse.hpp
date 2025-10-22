#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Greenhouse {
public:
    Greenhouse();
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape background;
    sf::RectangleShape greenhouse;
    sf::RectangleShape upper_air_intake;
    sf::RectangleShape upper_air_outlet;
    sf::RectangleShape lower_air_intake;
    sf::RectangleShape lower_air_outlet;

    std::vector<sf::Sprite> plants;
    sf::Texture grassTexture;
    sf::Texture plantTexture;
};



