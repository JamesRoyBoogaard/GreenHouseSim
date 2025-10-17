#pragma once
#include <SFML/Graphics.hpp>

class Airflow {
    public:
        Airflow();
        struct Origin
        {
            int fan_rate;
            sf::Vector2f position;
        };

        struct Line
        {
            float velocity;
            sf::Vector2f position;
            float rate_of_slowing;
        };

        struct Outlet
        {
            float reach;
            float strength; 
            sf::Vector2f position;
        };

        struct Directional_line: public Line
        {
            
        };

        struct Offshoot_line: public Line
        { 
            float tightness_of_curve;
        };

    private:



};