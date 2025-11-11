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
            float rate_of_slowing = 0.99f;
        };

        struct Offshoot_line: public Line
        { 
            float tightness_of_curve;
            std::vector<sf::Vector2f> trail;

            Offshoot_line(sf::Vector2f p_position, sf::Vector2f velocity, float y_offset){
                float tightness_of_curve = 4.f;
                Line::dot.setRadius(2.f);
                auto position = p_position;
                Line::dot.setPosition(position);
                Line::dot.setFillColor(sf::Color::Green);
                Line::velocity = {velocity.x , velocity.y + y_offset};
                trail.push_back(position);
            }

            void Move_Spiral(sf::RenderWindow& window){
                dot.setPosition(velocity*=rate_of_slowing);
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

        struct Directional_line: public Line
        {
            std::vector<sf::Vertex> trail;   
            std::chrono::steady_clock::time_point initial_time;  
            std::chrono::steady_clock::time_point last_offshoot;
            std::vector<Airflow::Offshoot_line> offshoot_lines;

            Directional_line(sf::Vector2f initial_position,sf::RenderWindow& window, sf::Vector2f p_velocity)
            {
                Line::dot.setRadius(2.f);
                Line::dot.setFillColor(sf::Color::Black);
                Line::dot.setPosition(initial_position);
                Line::position = initial_position;
                Line::velocity = p_velocity;
                trail.emplace_back(initial_position, sf::Color::Black);
                initial_time = std::chrono::steady_clock::now();
                last_offshoot = initial_time;
            }

            void Move(sf::RenderWindow& window)
            {

                auto current_time = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
                auto ol_elapsted = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_offshoot);

                //Over here we are trying to move the dot a certain amount each time 10 milliseconds elapses XXX
                //Additionally the direction that the dots bo should not be diagonal as it currently is XXX
                if(elapsed.count()>=10){
                    dot.setPosition(velocity*=rate_of_slowing);
                    sf::Vector2f position = dot.getPosition();
                    trail.emplace_back(position, sf::Color::Black);
                    initial_time = current_time;
                }
                if(trail.size()>=20){
                    trail.erase(trail.begin());
                }
                if(ol_elapsted.count()>=250){
                    offshoot_lines.emplace_back(position,velocity,30);
                    offshoot_lines.emplace_back(position, velocity,-30);
                    last_offshoot = std::chrono::steady_clock::now();
                }
                 
                window.draw(trail.data(),trail.size(), sf::PrimitiveType::LineStrip);
                window.draw(dot);
            }
        };



    private:

    


};