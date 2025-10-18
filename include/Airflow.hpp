#pragma once
#include <SFML/Graphics.hpp>

class Airflow {
    public:
        Airflow();
        void draw(sf::RenderWindow& window);
        sf::CircleShape Create_Directional_Line(sf::Vector2f initial_position, sf::RenderWindow& window);
        void Move_Directional_Line(sf::Vector2f dir, sf::CircleShape& directional_dot, sf::RenderWindow& window);
        // struct Origin
        // {
        //     int fan_rate;
        //     sf::Vector2f position;
        // };

        // struct Line
        // {
        //     float velocity;
        //     sf::CircleShape dot;
        //     sf::Vector2f position;
        //     float rate_of_slowing;
        // };

        // struct Outlet
        // {
        //     float reach;
        //     float strength; 
        //     sf::Vector2f position;
        // };

        // struct Directional_line: public Line
        // {
            
        // };

        // struct Offshoot_line: public Line
        // { 
        //     float tightness_of_curve;
        // };

    private:
    


};