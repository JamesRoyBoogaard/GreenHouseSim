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
            sf::Vector2f velocity ;
            sf::CircleShape dot;
            sf::Vector2f position;
            float rate_of_slowing = 0.99f;
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
                Line::velocity = {-8.f,0.f};// This will later be culculated based off the aircon the partcle was produced from and the dir it points.
                trail.push_back(initial_position);
            }

            void Move(sf::RenderWindow& window)
            {
                dot.move(Line::velocity*=rate_of_slowing);
                sf::Vector2f position = dot.getPosition();
                trail.push_back(position);
                std::vector<sf::Vertex> vert;
                for (auto& p: trail){
                    if(trail.size()<=1000){
                        vert.push_back(sf::Vertex(p,sf::Color::Black));
                    }else{
                        trail.erase(trail.begin());
                }
            }
            window.draw(vert.data(), vert.size(), sf::PrimitiveType::LineStrip);
            window.draw(dot);
            }
        };

        struct Offshoot_line: public Line
        { 
            float tightness_of_curve;
            std::vector<sf::Vector2f> trail;

            Offshoot_line(Directional_line dl, sf::RenderWindow& window){
                float tightness_of_curve = 4.f;
                Line::dot.setRadius(2.f);
                auto& position = dl.dot.getPosition();
                Line::dot.setPosition(position);
                Line::dot.setFillColor(sf::Color::Green);
                Line::velocity = {dl.velocity.x , dl.velocity.y + 30};
                trail.push_back(position);
            }

            void Move_Spiral(sf::RenderWindow& window){
                dot.move(Line::velocity*=rate_of_slowing);
                sf::Vector2f position = dot.getPosition();
                trail.push_back(position);
                std::vector<sf::Vertex> vert;
                for (auto& p: trail){
                    if(trail.size()<=1000){
                        vert.push_back(sf::Vertex(p,sf::Color::Green));
                    }else{
                        trail.erase(trail.begin());
                }
            }
            window.draw(vert.data(), vert.size(), sf::PrimitiveType::LineStrip);
            window.draw(dot);
            }
        };

    private:
    


};