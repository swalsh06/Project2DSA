// #include "display.h"
// #include <iostream>
//
// //Create a 5-pointed star
// sf::ConvexShape makeStar(float radius, int points = 5) {
//     sf::ConvexShape star(points * 2);
//     float innerRadius = radius * 0.5f;
//     float angleStep = static_cast<float>(M_PI) / points;
//
//     for (int i = 0; i < points * 2; ++i) {
//         float angle = i * angleStep - M_PI / 2.f;
//         float r = (i % 2 == 0) ? radius : innerRadius;
//         star.setPoint(i, {r * std::cos(angle), r * std::sin(angle)});
//     }
//     return star;
// }
//
// // ---------------- CONSTRUCTOR ----------------
// Display::Display(const std::vector<Star>& dataStars)
// : window(sf::VideoMode({1200u, 600u}),
//          "Constellation Connection",
//          sf::State::Windowed),
//   font(),
//   title(font, "", 20),
//   algo1Label(font, "", 16),
//   algo2Label(font, "", 14),
//   rand1Text(font, "", 18),
//   rand2Text(font, "", 18),
//   generateLabel(font, "", 18),
//   selectedAlgorithm(""),
//   infoBox(font, "", 20)
// {
//     window.setFramerateLimit(60);
//     std::srand(static_cast<unsigned>(std::time(nullptr)));
//
//     if (!font.openFromFile("resources/fonts/OpenSans.ttf")) {
//         std::cerr << "Failed to load font!" << std::endl;
//     }
//
//     setupStars(dataStars);
//     setupSidebar();
// }
//
// // Display::Display()
// // : window(sf::VideoMode({1200u, 600u}),
// //          "Constellation Connection",
// //          sf::State::Windowed),
// //   font(),
// //   title(font, "", 20),
// //   algo1Label(font, "", 16),
// //   algo2Label(font, "", 14),
// //   rand1Text(font, "", 18),
// //   rand2Text(font, "", 18),
// //   generateLabel(font, "", 18),
// //   selectedAlgorithm(""),
// //   infoBox(font, "", 20)
// // {
// //     window.setFramerateLimit(60);
// //     std::srand(static_cast<unsigned>(std::time(nullptr)));
// //
// //     if (!font.openFromFile("resources/fonts/OpenSans.ttf")) {
// //         std::cerr << "Failed to load font!" << std::endl;
// //     }
// //
// //     setupStars(dataStars);
// //     setupSidebar();
// // }
// void Display::setupStars(const std::vector<class Star>& dataStars) {
//     stars.clear(); // clear any existing random stars
//
//     for (const auto& sData : dataStars) {
//         Star s;
//
//         // Map coordinates: convert real (x, y) in pc to screen pixels
//         // You can tweak the scale later
//         float scale = 2.0f;  // determines how spread out the stars appear
//         float offsetX = 600.f;  // center horizontally
//         float offsetY = 300.f;  // center vertically
//
//         s.position = {
//             static_cast<float>(sData.getX() * scale + offsetX),
//             static_cast<float>(sData.getY() * scale + offsetY)
//         };
//
//         float radius = 4.0f; // uniform size for now
//         s.shape = makeStar(radius);
//         s.shape.setFillColor(sf::Color::White);
//         s.shape.setPosition(s.position);
//
//         s.shadow.setRadius(radius * 1.8f);
//         s.shadow.setOrigin({radius * 1.8f, radius * 1.8f});
//         s.shadow.setFillColor(sf::Color(255, 255, 220, 20));
//         s.shadow.setPosition(s.position);
//
//         s.twinklePhase = static_cast<float>(std::rand() % 360);
//         s.twinkleSpeed = 0.5f + static_cast<float>(std::rand() % 100) / 200.f;
//
//         stars.push_back(s);
//     }
//
//     // Optional: connect two random stars for now
//     if (stars.size() > 2) {
//         int startIndex = std::rand() % stars.size();
//         int endIndex = std::rand() % stars.size();
//         path = sf::VertexArray(sf::PrimitiveType::LineStrip);
//         path.append(sf::Vertex(stars[startIndex].position, sf::Color::Red));
//         path.append(sf::Vertex(stars[endIndex].position, sf::Color::Red));
//     }
// }
//
// // // ---------------- STARS ----------------
// // void Display::setupStars() {
// //     for (int i = 0; i < 300; ++i) {
// //         Star s;
// //         s.position = {
// //             static_cast<float>(std::rand() % 950 + 225),
// //             static_cast<float>(std::rand() % 550 + 25)
// //         };
// //
// //         float radius = static_cast<float>((std::rand() % 6) + 5);
// //         s.shape = makeStar(radius);
// //         s.shape.setFillColor(sf::Color::White);
// //         s.shape.setPosition(s.position);
// //         s.shape.setRotation(sf::degrees(static_cast<float>(std::rand() % 360)));
// //
// //         s.shadow.setRadius(radius * 1.8f);
// //         s.shadow.setOrigin({radius * 1.8f, radius * 1.8f});
// //         s.shadow.setFillColor(sf::Color(255, 255, 220, 20));
// //         s.shadow.setPosition(s.position);
// //
// //         s.twinklePhase = static_cast<float>(std::rand() % 360);
// //         s.twinkleSpeed = 0.5f + static_cast<float>(std::rand() % 100) / 200.f;
// //
// //         stars.push_back(s);
// //     }
// //
// //     int startIndex = std::rand() % stars.size();
// //     int endIndex   = std::rand() % stars.size();
// //     path = sf::VertexArray(sf::PrimitiveType::LineStrip);
// //     path.append(sf::Vertex(stars[startIndex].position, sf::Color::Red));
// //     path.append(sf::Vertex(stars[endIndex].position,   sf::Color::Red));
// // }
//
// // ---------------- SIDEBAR ----------------
// void Display::setupSidebar() {
//     sidebar.setSize({200.f, 600.f});
//     sidebar.setFillColor(sf::Color(180, 180, 200));
//
//     title.setString("Pick which\nalgorithm to use");
//     title.setFillColor(sf::Color::Black);
//     title.setStyle(sf::Text::Bold);
//     title.setPosition({20.f, 20.f});
//
//     algo1Btn.setSize({80.f, 30.f});
//     algo1Btn.setFillColor(sf::Color::White);
//     algo1Btn.setPosition({20.f, 100.f});
//
//     algo2Btn.setSize({80.f, 30.f});
//     algo2Btn.setFillColor(sf::Color::White);
//     algo2Btn.setPosition({115.f, 100.f});
//
//     algo1Label.setString("Dijkstra");
//     algo1Label.setFillColor(sf::Color::Black);
//     algo1Label.setStyle(sf::Text::Bold);
//     algo1Label.setPosition({28.f, 106.f});
//
//     algo2Label.setString("A* Search");
//     algo2Label.setFillColor(sf::Color::Black);
//     algo2Label.setStyle(sf::Text::Bold);
//     algo2Label.setPosition({118.f, 106.f});
//
//     rand1Text.setString("Random\nstar 1");
//     rand1Text.setFillColor(sf::Color::Black);
//     rand1Text.setStyle(sf::Text::Bold);
//     rand1Text.setPosition({20.f, 170.f});
//
//     rand2Text.setString("Random\nstar 2");
//     rand2Text.setFillColor(sf::Color::Black);
//     rand2Text.setStyle(sf::Text::Bold);
//     rand2Text.setPosition({20.f, 240.f});
//
//     rand1Btn.setSize({70.f, 30.f});
//     rand1Btn.setFillColor(sf::Color::White);
//     rand1Btn.setOutlineColor(sf::Color::Black);
//     rand1Btn.setOutlineThickness(1.f);
//     rand1Btn.setPosition({100.f, 180.f});
//
//     rand2Btn.setSize({70.f, 30.f});
//     rand2Btn.setFillColor(sf::Color::White);
//     rand2Btn.setOutlineColor(sf::Color::Black);
//     rand2Btn.setOutlineThickness(1.f);
//     rand2Btn.setPosition({100.f, 250.f});
//
//     generateBtn.setSize({120.f, 40.f});
//     generateBtn.setFillColor(sf::Color(240, 240, 240));
//     generateBtn.setOutlineColor(sf::Color::Black);
//     generateBtn.setOutlineThickness(1.f);
//     generateBtn.setPosition({40.f, 303.f});
//
//     generateLabel.setString("Generate");
//     generateLabel.setFillColor(sf::Color::Black);
//     generateLabel.setStyle(sf::Text::Bold);
//     generateLabel.setPosition({60.f, 310.f});
//
//     // Placeholder box for info section
//     sf::RectangleShape infoBox;
//     infoBox.setSize({150.f, 100.f});
//     infoBox.setFillColor(sf::Color(230, 230, 240));
//     infoBox.setOutlineColor(sf::Color::Black);
//     infoBox.setOutlineThickness(1.f);
//     infoBox.setPosition({25.f, 390.f});
//
// }
//
// void Display::drawSidebar() {
//     window.draw(sidebar);
//     window.draw(title);
//     window.draw(algo1Btn);
//     window.draw(algo2Btn);
//     window.draw(algo1Label);
//     window.draw(algo2Label);
//     window.draw(rand1Text);
//     window.draw(rand2Text);
//     window.draw(rand1Btn);
//     window.draw(rand2Btn);
//     window.draw(generateBtn);
//     window.draw(generateLabel);
//     window.draw(infoBox);
//
// }
//
//
// void Display::drawStars() {
//     float time = clock.getElapsedTime().asSeconds();
//
//     for (auto& s : stars) {
//         float brightness = 170 + 85 * std::sin(time * s.twinkleSpeed * 4.0f + s.twinklePhase);
//         uint8_t alpha = static_cast<uint8_t>(brightness);
//         s.shape.setFillColor(sf::Color(255, 255, 255, alpha));
//         s.shadow.setFillColor(sf::Color(255, 255, 220, alpha / 12));
//
//         float scale = 1.0f + 0.05f * std::sin(time * s.twinkleSpeed + s.twinklePhase);
//         s.shape.setScale({scale, scale});
//         s.shadow.setScale({scale, scale});
//
//         window.draw(s.shadow);
//         window.draw(s.shape);
//     }
//
//     window.draw(path);
// }
//


#include "display.h"
#include <iostream>

// ---------------- HELPER FUNCTION ----------------
sf::ConvexShape Display::makeStar(float radius, int points) {
    sf::ConvexShape star(points * 2);
    float innerRadius = radius * 0.5f;
    float angleStep = static_cast<float>(M_PI) / points;

    for (int i = 0; i < points * 2; ++i) {
        float angle = i * angleStep - M_PI / 2.f;
        float r = (i % 2 == 0) ? radius : innerRadius;
        star.setPoint(i, {r * std::cos(angle), r * std::sin(angle)});
    }
    return star;
}

// ---------------- CONSTRUCTOR ----------------
Display::Display(const std::vector<Star>& dataStars)
: window(sf::VideoMode({1200u, 600u}),
         "Constellation Connection",
         sf::State::Windowed),
  font(),
  title(font, "", 20),
  algo1Label(font, "", 16),
  algo2Label(font, "", 14),
  rand1Text(font, "", 18),
  rand2Text(font, "", 18),
  generateLabel(font, "", 18),
  selectedAlgorithm("")
{
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!font.openFromFile("resources/fonts/OpenSans.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    setupStars(dataStars);
    setupSidebar();
}

// ---------------- STARS (BASED ON REAL DATA) ----------------

void Display::setupStars(const std::vector<Star>& dataStars) {
    stars.clear();

    // find min/max to normalize all coordinates
    double minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (const auto& s : dataStars) {
        minX = std::min(minX, s.getX());
        maxX = std::max(maxX, s.getX());
        minY = std::min(minY, s.getY());
        maxY = std::max(maxY, s.getY());
    }

    //  scale factors to fit stars within 1200x600 window
    float scaleX = 950.f / static_cast<float>(maxX - minX);  // 950 leaves room for sidebar
    float scaleY = 550.f / static_cast<float>(maxY - minY);

    //  convert each star's (x,y) to pixel coordinates
    for (const auto& sData : dataStars) {
        VisualStar s;

        // Map coordinates to screen pixels
        s.position = {
            static_cast<float>((sData.getX() - minX) * scaleX + 225.f),
            static_cast<float>((sData.getY() - minY) * scaleY + 25.f)
        };


        float radius = 3.5f;
        s.shape = makeStar(radius);
        s.shape.setFillColor(sf::Color::White);
        s.shape.setPosition(s.position);

        s.shadow.setRadius(radius * 1.8f);
        s.shadow.setOrigin({radius * 1.8f, radius * 1.8f});
        s.shadow.setFillColor(sf::Color(255, 255, 220, 20));
        s.shadow.setPosition(s.position);

        s.twinklePhase = static_cast<float>(std::rand() % 360);
        s.twinkleSpeed = 0.5f + static_cast<float>(std::rand() % 100) / 200.f;

        stars.push_back(s);
    }

    std::cout << "Loaded " << stars.size() << " stars into display.\n";
}


// ---------------- SIDEBAR SETUP ----------------
void Display::setupSidebar() {
    sidebar.setSize({200.f, 600.f});
    sidebar.setFillColor(sf::Color(180, 180, 200));

    title.setString("Pick which\nalgorithm to use");
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition({20.f, 20.f});

    algo1Btn.setSize({80.f, 30.f});
    algo1Btn.setFillColor(sf::Color::White);
    algo1Btn.setPosition({20.f, 100.f});

    algo2Btn.setSize({80.f, 30.f});
    algo2Btn.setFillColor(sf::Color::White);
    algo2Btn.setPosition({115.f, 100.f});

    algo1Label.setString("Dijkstra");
    algo1Label.setFillColor(sf::Color::Black);
    algo1Label.setStyle(sf::Text::Bold);
    algo1Label.setPosition({28.f, 106.f});

    algo2Label.setString("A* Search");
    algo2Label.setFillColor(sf::Color::Black);
    algo2Label.setStyle(sf::Text::Bold);
    algo2Label.setPosition({118.f, 106.f});

    rand1Text.setString("Random\nstar 1");
    rand1Text.setFillColor(sf::Color::Black);
    rand1Text.setStyle(sf::Text::Bold);
    rand1Text.setPosition({20.f, 170.f});

    rand2Text.setString("Random\nstar 2");
    rand2Text.setFillColor(sf::Color::Black);
    rand2Text.setStyle(sf::Text::Bold);
    rand2Text.setPosition({20.f, 240.f});

    rand1Btn.setSize({70.f, 30.f});
    rand1Btn.setFillColor(sf::Color::White);
    rand1Btn.setOutlineColor(sf::Color::Black);
    rand1Btn.setOutlineThickness(1.f);
    rand1Btn.setPosition({100.f, 180.f});

    rand2Btn.setSize({70.f, 30.f});
    rand2Btn.setFillColor(sf::Color::White);
    rand2Btn.setOutlineColor(sf::Color::Black);
    rand2Btn.setOutlineThickness(1.f);
    rand2Btn.setPosition({100.f, 250.f});

    generateBtn.setSize({120.f, 40.f});
    generateBtn.setFillColor(sf::Color(240, 240, 240));
    generateBtn.setOutlineColor(sf::Color::Black);
    generateBtn.setOutlineThickness(1.f);
    generateBtn.setPosition({40.f, 303.f});

    generateLabel.setString("Generate");
    generateLabel.setFillColor(sf::Color::Black);
    generateLabel.setStyle(sf::Text::Bold);
    generateLabel.setPosition({60.f, 310.f});

    // Info box area
    infoBox.setSize({150.f, 100.f});
    infoBox.setFillColor(sf::Color(230, 230, 240));
    infoBox.setOutlineColor(sf::Color::Black);
    infoBox.setOutlineThickness(1.f);
    infoBox.setPosition({25.f, 390.f});
}

// ---------------- DRAW ----------------
void Display::drawSidebar() {
    window.draw(sidebar);
    window.draw(title);
    window.draw(algo1Btn);
    window.draw(algo2Btn);
    window.draw(algo1Label);
    window.draw(algo2Label);
    window.draw(rand1Text);
    window.draw(rand2Text);
    window.draw(rand1Btn);
    window.draw(rand2Btn);
    window.draw(generateBtn);
    window.draw(generateLabel);
    window.draw(infoBox);
}

// ---------------- DRAW STARS ----------------
void Display::drawStars() {
    float time = clock.getElapsedTime().asSeconds();

    for (auto& s : stars) {
        float brightness = 170 + 85 * std::sin(time * s.twinkleSpeed * 4.0f + s.twinklePhase);
        uint8_t alpha = static_cast<uint8_t>(brightness);
        s.shape.setFillColor(sf::Color(255, 255, 255, alpha));
        s.shadow.setFillColor(sf::Color(255, 255, 220, alpha / 12));

        float scale = 1.0f + 0.05f * std::sin(time * s.twinkleSpeed + s.twinklePhase);
        s.shape.setScale({scale, scale});
        s.shadow.setScale({scale, scale});

        window.draw(s.shadow);
        window.draw(s.shape);
    }

    window.draw(path);
}

void Display::start() {
    while (window.isOpen()) {
        // ---------------- HANDLE EVENTS ----------------
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});

                if (algo1Btn.getGlobalBounds().contains(mousePos)) {
                    selectedAlgorithm = "Dijkstra";
                    std::cout << "Selected Dijkstra!\n";
                }
                else if (algo2Btn.getGlobalBounds().contains(mousePos)) {
                    selectedAlgorithm = "A* Search";
                    std::cout << "Selected A* Search!\n";
                }
                else if (generateBtn.getGlobalBounds().contains(mousePos)) {
                    if (!selectedAlgorithm.empty()) {
                        generateActive = true;
                        std::cout << "Generating path using " << selectedAlgorithm << "...\n";
                        // TODO: connect with backend logic
                    } else {
                        std::cout << "Please select an algorithm first!\n";
                    }
                }

            }
        }

        // ---------------- HOVER LOGIC  ----------------
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        sf::Color hoverColor(200, 200, 255);
        sf::Color normalColor(255, 255, 255);
        sf::Color selectedColor(150, 150, 255);
        sf::Color generateNormal(240, 240, 240);

        algo1Btn.setFillColor(normalColor);
        algo2Btn.setFillColor(normalColor);
        generateBtn.setFillColor(generateNormal);

        // Highlight the selected algorithm
        if (selectedAlgorithm == "Dijkstra")
            algo1Btn.setFillColor(selectedColor);
        else if (selectedAlgorithm == "A* Search")
            algo2Btn.setFillColor(selectedColor);

        // Highlight generate if it's active
        if (generateActive)
            generateBtn.setFillColor(selectedColor);


        // apply hover (only if not already selected)
        if (algo1Btn.getGlobalBounds().contains(worldPos) && selectedAlgorithm != "Dijkstra")
            algo1Btn.setFillColor(hoverColor);

        if (algo2Btn.getGlobalBounds().contains(worldPos) && selectedAlgorithm != "A* Search")
            algo2Btn.setFillColor(hoverColor);

        if (generateBtn.getGlobalBounds().contains(worldPos) && selectedAlgorithm != "Generate")
            generateBtn.setFillColor(hoverColor);

        // ---------------- DRAW FRAME ----------------
        window.clear(sf::Color(5, 10, 30));
        drawSidebar();
        drawStars();
        window.display();
    }
}

// ---------------- PATH DRAWING ----------------
void Display::setPath(const std::vector<int>& indices) {
    path.clear();
    for (int idx : indices) {
        if (idx >= 0 && idx < static_cast<int>(stars.size())) {
            path.append(sf::Vertex(stars[idx].position, sf::Color::Red));
        }
    }
}



