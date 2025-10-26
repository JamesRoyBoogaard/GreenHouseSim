#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <chrono>

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
            float rate_of_slowing = 0.98f;
        };

        struct Directional_line: public Line
        {
            std::vector<sf::Vector2f> trail;   
            std::chrono::steady_clock::time_point initial_time;     

            Directional_line(sf::Vector2f initial_position,sf::RenderWindow& window)
            {
                Line::dot.setRadius(2.f);
                Line::dot.setFillColor(sf::Color::Black);
                Line::dot.setPosition(initial_position);
                Line::position = initial_position;
                Line::velocity = {-8.f,0.f};// This will later be culculated based off the aircon the partcle was produced from and the dir it points.
                trail.push_back(initial_position);
                initial_time = std::chrono::steady_clock::now();

            }

            void Move(sf::RenderWindow& window)
            {
                auto current_time = std::chrono::steady_clock::now();
                // current_time check against initial_time
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);


                if(elapsed.count()>=1000){
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
                initial_time = std::chrono::steady_clock::now();
                }
                
            }
        };

        struct Offshoot_line: public Line
        { 
            float tightness_of_curve;
            std::vector<sf::Vector2f> trail;

            Offshoot_line(Directional_line dl, sf::RenderWindow& window, float y_offset){
                float tightness_of_curve = 4.f;
                Line::dot.setRadius(2.f);
                auto& position = dl.dot.getPosition();
                Line::dot.setPosition(position);
                Line::dot.setFillColor(sf::Color::Green);
                Line::velocity = {dl.velocity.x , dl.velocity.y + y_offset};
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