
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 850), "The Simulation");

    sf::RectangleShape background(sf::Vector2f(1400, 500));
    sf::RectangleShape garden(sf::Vector2f(800, 300));

    std::vector<sf::Sprite> plants;

    sf::Texture grassTexture;
    sf::Texture plantTexture;

    if (!grassTexture.loadFromFile("../Textures/grass.png", sf::IntRect(0, 0, 1400, 850)))
    {
        
    }
    if (!plantTexture.loadFromFile("../Textures/plant_no_bg.png"))
    {

    }

    background.setTexture(&grassTexture);
    background.setPosition(0.f,0.f); 

    garden.setFillColor(sf::Color(192, 192, 192));    
    garden.setOutlineThickness(10.f);
    garden.setOutlineColor(sf::Color(200, 200, 200)); 
    garden.setPosition(300.f, 110.f);


    float top_row[2] = {385.f,188.f};
    float bottom_row[2] = {435.f,288.f};

    for(int i = 0; i < 12; i++){

        sf::Sprite plant;
        plant.setTexture(plantTexture);
        plant.setScale(0.2,0.2);

        if(i%2){
            plant.setPosition(top_row[0] + i*50, top_row[1]);
        }else{
            plant.setPosition(bottom_row[0] + i*50, bottom_row[1]);
        }

        plants.push_back(plant);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        std::cout << "Mouse: " << mousePos.x << ", " << mousePos.y << "\n";

        window.clear();
        window.draw(background);
        window.draw(garden);
        for(sf::Sprite plant: plants){
            window.draw(plant);
        }
        window.display();
    }

    return 0;
}
