
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 850), "The Simulation");
    sf::RectangleShape background(sf::Vector2f(1300.f, 500.f));
    sf::Sprite plant;
    sf::Sprite soil;

    sf::Texture grassTexture;
    sf::Texture plantTexture;
    sf::Texture soilTexture;

    if (!grassTexture.loadFromFile("../Textures/grass.png", sf::IntRect(0, 0, 1400, 850)))
    {
        
    }
    if (!plantTexture.loadFromFile("../Textures/plant_no_bg.png"))
    {

    }
    if (!plantTexture.loadFromFile("../Textures/dirt.png"))
    {

    }


    background.setTexture(&grassTexture);
    background.setOutlineThickness(10.f);
    background.setOutlineColor(sf::Color(192, 192, 192)); // steel-like gray  
    background.setPosition(10.f,10.f);  
    plant.setTexture(plantTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(plant);
        window.display();
    }

    return 0;
}
