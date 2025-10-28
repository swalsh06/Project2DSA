//
// Created by Diya Patel on 10/28/25.
//

#ifndef DSA_PROJECT_2_DISPLAY_H
#define DSA_PROJECT_2_DISPLAY_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <cstdint>

class Display {
public:
    Display();

    // renamed to feel like a visual loop
    void start();

    // 💡 New: this will be called by your backend to send you the path
    void setPath(const std::vector<int>& indices);

private:
    struct Star {
        sf::ConvexShape shape;
        sf::CircleShape shadow;
        sf::Vector2f position;
        float twinklePhase;
        float twinkleSpeed;
    };

    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<Star> stars;

    // Sidebar UI
    sf::Font font;
    sf::RectangleShape sidebar;
    sf::Text title;
    sf::RectangleShape algo1Btn, algo2Btn, rand1Btn, rand2Btn, generateBtn;
    sf::Text algo1Label, algo2Label, rand1Text, rand2Text, generateLabel;

    // The visualized path
    sf::VertexArray path;

    void setupStars();
    void setupSidebar();
    void drawSidebar();
    void drawStars();
};

#endif //DSA_PROJECT_2_DISPLAY_H