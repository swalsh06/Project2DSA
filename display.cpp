#include "display.h"
#include <iostream>
#include <iomanip>


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
  infoText(font, "", 14),
  rand1Value(font, "", 14),
  rand2Value(font, "", 14),
  selectedAlgorithm(""),
  starCountInput(font,"", 16),
starCountLabel(font, "", 16),
numStars(200),                  // ✅ default
  isTypingStarCount(false)        // ✅ default

{
    this->dataStars = dataStars;
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!font.openFromFile("OpenSans.ttf")) {
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
    float scaleX = 950.f / static_cast<float>(maxX - minX);
    float scaleY = 550.f / static_cast<float>(maxY - minY);

    //  convert each star's (x,y) to pixel coordinates
    for (const auto& sData : dataStars) {
        VisualStar s;

        // Map coordinates to screen pixels
        s.position = {
            static_cast<float>((sData.getX() - minX) * scaleX + 225.f),
            static_cast<float>((sData.getY() - minY) * scaleY + 25.f)
        };


        float radius = 6.5f;
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

void Display::connectTwoRandomStars() {
    if (stars.size() < 2) return;

    // pick two random stars
    int startIndex = std::rand() % stars.size();
    int endIndex = std::rand() % stars.size();
    while (endIndex == startIndex)
        endIndex = std::rand() % stars.size();

    // create red line
    path = sf::VertexArray(sf::PrimitiveType::LineStrip);
    path.append(sf::Vertex(stars[startIndex].position, sf::Color::Red));
    path.append(sf::Vertex(stars[endIndex].position, sf::Color::Red));

    rand1Value.setString(std::to_string(startIndex));
    rand2Value.setString(std::to_string(endIndex));

    // star data
    auto s1 = dataStars[startIndex];
    auto s2 = dataStars[endIndex];

    std::ostringstream info;
    info << std::fixed << std::setprecision(2);

    info << "Star 1: ("
         << s1.getX() << ", " << s1.getY() << ")\n";
    info << "Star 2: ("
         << s2.getX() << ", " << s2.getY() << ")\n";

    // show distance between them
    double dx = s1.getX() - s2.getX();
    double dy = s1.getY() - s2.getY();
    double dist = std::sqrt(dx*dx + dy*dy);
    info << "Distance: " << std::fixed << std::setprecision(2) << dist << " pc";

    infoText.setString(info.str());

}



// ---------------- SIDEBAR SETUP ----------------
void Display::setupSidebar() {
    sidebar.setSize({200.f, 600.f});
    sidebar.setFillColor(sf::Color(180, 180, 200));

    title.setString("Pick an algorithm");
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition({20.f, 20.f});

    algo1Btn.setSize({80.f, 30.f});
    algo1Btn.setFillColor(sf::Color::White);
    algo1Btn.setPosition({20.f, 60.f});

    algo2Btn.setSize({80.f, 30.f});
    algo2Btn.setFillColor(sf::Color::White);
    algo2Btn.setPosition({115.f, 60.f});

    algo1Label.setString("Dijkstra");
    algo1Label.setFillColor(sf::Color::Black);
    algo1Label.setStyle(sf::Text::Bold);
    algo1Label.setPosition({28.f, 63.f});
    algo2Label.setString("A* Search");
    algo2Label.setFillColor(sf::Color::Black);
    algo2Label.setStyle(sf::Text::Bold);
    algo2Label.setPosition({118.f, 64.f});

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

    infoText.setFont(font);
    infoText.setCharacterSize(14);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition({30.f, 400.f});
    infoText.setString("Star 1:\nStar 2:");

    rand1Value.setFont(font);
    rand1Value.setCharacterSize(20);
    rand1Value.setFillColor(sf::Color::Black);
    rand1Value.setPosition({120.f, 182.f});
    rand1Value.setString("");

    rand2Value.setFont(font);
    rand2Value.setCharacterSize(20);
    rand2Value.setFillColor(sf::Color::Black);
    rand2Value.setPosition({120.f, 252.f});
    rand2Value.setString("");

    //starCountLabel.setString("Number of Stars:", font, 16);
    starCountLabel.setFillColor(sf::Color::Black);
    starCountLabel.setStyle(sf::Text::Bold);
    starCountLabel.setPosition({20.f, 460.f});

    // Input box
    inputBox.setSize({100.f, 30.f});
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(1.f);
    inputBox.setPosition({40.f, 490.f});

    // Text inside box
    //starCountInput = sf::Text(std::to_string(numStars), font, 16);
    starCountInput.setFillColor(sf::Color::Black);
    starCountInput.setPosition({50.f, 493.f});


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
    window.draw(rand1Value);
    window.draw(rand2Value);
    window.draw(generateBtn);
    window.draw(generateLabel);
    window.draw(infoBox);
    window.draw(infoText);
    window.draw(starCountLabel);
    window.draw(inputBox);
    window.draw(starCountInput);

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

    // --- Handle Mouse Clicks ---
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
        sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});

        // Input box focus
        if (inputBox.getGlobalBounds().contains(mousePos)) {
            isTypingStarCount = true;
            inputBox.setOutlineColor(sf::Color(100, 100, 255)); // blue border
        } else {
            isTypingStarCount = false;
            inputBox.setOutlineColor(sf::Color::Black);
        }

        // Generate button
        if (generateBtn.getGlobalBounds().contains(mousePos)) {
            if (!selectedAlgorithm.empty()) {
                generateActive = true;
                std::cout << "Generating " << numStars << " stars...\n";
                connectTwoRandomStars();
            } else {
                std::cout << "Please select an algorithm first!\n";
            }
        }

        // Algorithm buttons
        if (algo1Btn.getGlobalBounds().contains(mousePos)) {
            selectedAlgorithm = "Dijkstra";
            generateActive = false;
            std::cout << "Selected Dijkstra!\n";
        } else if (algo2Btn.getGlobalBounds().contains(mousePos)) {
            selectedAlgorithm = "A* Search";
            generateActive = false;
            std::cout << "Selected A* Search!\n";
        }
    }

    // --- Handle Keyboard Input ---
    if (event->is<sf::Event::TextEntered>() && isTypingStarCount) {
        auto textEvent = event->getIf<sf::Event::TextEntered>();
        uint32_t unicode = textEvent->unicode;

        if (unicode == 8) {  // backspace
            std::string current = starCountInput.getString().toAnsiString();
            if (!current.empty()) current.pop_back();
            starCountInput.setString(current);
        }
        else if (unicode >= '0' && unicode <= '9') {  // digits only
            std::string current = starCountInput.getString().toAnsiString();
            current += static_cast<char>(unicode);
            starCountInput.setString(current);
        }
        else if (unicode == 13) {  // enter key
            std::string input = starCountInput.getString().toAnsiString();
            if (!input.empty()) {
                int entered = std::stoi(input);

                // ✅ Limit between 20 and 500
                if (entered < 20) entered = 20;
                if (entered > 500) entered = 500;

                numStars = entered;
                starCountInput.setString(std::to_string(numStars));
                std::cout << "✅ Number of stars set to " << numStars << "\n";
            }

            isTypingStarCount = false;
            inputBox.setOutlineColor(sf::Color::Black);
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

        // Highlight selected algorithm
        if (selectedAlgorithm == "Dijkstra")
            algo1Btn.setFillColor(selectedColor);
        else if (selectedAlgorithm == "A* Search")
            algo2Btn.setFillColor(selectedColor);

        // Highlight generate if active
        if (generateActive)
            generateBtn.setFillColor(selectedColor);

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



