// //
// // Created by Diya Patel on 10/28/25.
// //
//
// #ifndef DSA_PROJECT_2_DISPLAY_H
// #define DSA_PROJECT_2_DISPLAY_H
//
// #pragma once
// #include <SFML/Graphics.hpp>
// #include <vector>
// #include <cmath>
// #include <cstdlib>
// #include <ctime>
// #include <optional>
// #include <cstdint>
//
// class Display {
// public:
//     //Display();
//     Display(const std::vector<Star>& dataStars);
//     // renamed to feel like a visual loop
//     void start();
//
//     void setPath(const std::vector<int>& indices);
//
// private:
//     struct Star {
//         sf::ConvexShape shape;
//         sf::CircleShape shadow;
//         sf::Vector2f position;
//         float twinklePhase;
//         float twinkleSpeed;
//     };
//
//     sf::RenderWindow window;
//     sf::Clock clock;
//     std::vector<Star> stars;
//
//     // Sidebar UI
//     sf::Font font;
//     sf::RectangleShape sidebar;
//     sf::Text title;
//     sf::RectangleShape algo1Btn, algo2Btn, rand1Btn, rand2Btn, generateBtn;
//     sf::Text algo1Label, algo2Label, rand1Text, rand2Text, generateLabel, infoBox;
//
//     // The visualized path
//     sf::VertexArray path;
//
//     std::string selectedAlgorithm;
//     bool generateActive = false;
//
//
//     // void setupStars();
//     void setupStars(const std::vector<Star>& dataStars);
//     void setupSidebar();
//     void drawSidebar();
//     void drawStars();
// };
//
// #endif //DSA_PROJECT_2_DISPLAY_H

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
#include "star.h"   // ⭐ Include your teammate’s real Star class

class Display {
public:
    Display(const std::vector<Star>& dataStars);
    void start();
    void setPath(const std::vector<int>& indices);

private:
    // Internal struct for how each star looks on-screen
    struct VisualStar {
        sf::ConvexShape shape;
        sf::CircleShape shadow;
        sf::Vector2f position;
        float twinklePhase;
        float twinkleSpeed;
    };

    // --- Data ---
    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<VisualStar> stars;
    sf::VertexArray path;

    // --- Sidebar UI ---
    sf::Font font;
    sf::RectangleShape sidebar;
    sf::Text title;
    sf::RectangleShape algo1Btn, algo2Btn, rand1Btn, rand2Btn, generateBtn;
    sf::Text algo1Label, algo2Label, rand1Text, rand2Text, generateLabel;
    sf::RectangleShape infoBox;

    std::string selectedAlgorithm;
    bool generateActive = false;

    // --- Internal helpers ---
    void setupStars(const std::vector<Star>& dataStars);
    void setupSidebar();
    void drawSidebar();
    void drawStars();

    // Helper to make star shape
    sf::ConvexShape makeStar(float radius, int points = 5);
};

#endif // DSA_PROJECT_2_DISPLAY_H
