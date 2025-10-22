#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Airflow {
    public:
        Airflow();
        void draw(sf::RenderWindow& window);
        sf::CircleShape Create_Directional_Line(sf::Vector2f initial_position, sf::RenderWindow& window);
        void Move_Directional_Line(sf::Vector2f dir, sf::CircleShape& directional_dot, sf::RenderWindow& window);
        float Decay_Method(float initial_velocity, sf::CircleShape& directional_dot, sf::RenderWindow& window);
        
        struct Line
        {
            sf::Vector2f velocity = {-.1f,0.f};
            sf::CircleShape dot;
            sf::Vector2f position;
            float rate_of_slowing = 0.80f;

        };

        struct Directional_line: public Line
        {
            std::vector<sf::Vector2f> trail;        

            Directional_line(sf::Vector2f initial_position,sf::RenderWindow& window)
            {
                Line::dot.setRadius(2.f);
                Line::dot.setFillColor(sf::Color::Black);
                Line::dot.setPosition(initial_position);
                Line::position = initial_position;
                trail.push_back(initial_position);
            }

            void Move(sf::RenderWindow& window)
            {
                dot.move(velocity);
                sf::Vector2f position = dot.getPosition();
                trail.push_back(position);

                std::vector<sf::Vertex> vert;
                for (auto& p: trail){
                    vert.push_back(sf::Vertex(p,sf::Color::Black));
                }

                window.draw(vert.data(), vert.size(), sf::PrimitiveType::LineStrip);
                window.draw(dot);
            }
        };

        struct Offshoot_line: public Line
        { 
            float tightness_of_curve;
            void Move_Spiral();
        };

    private:
    


};