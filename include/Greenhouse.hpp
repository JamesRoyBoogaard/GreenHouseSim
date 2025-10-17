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
    std::vector<sf::Sprite> plants;
    sf::Texture grassTexture;
    sf::Texture plantTexture;
};



