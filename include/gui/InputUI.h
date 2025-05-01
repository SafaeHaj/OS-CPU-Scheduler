#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct ProcessInput {
    int priority = 0;
    int burstTime = 0;
    int arrival = 0;
};

class InputUI {
public:
    InputUI(sf::Font& font, sf::Vector2f windowSize);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& win);
    bool isInputComplete() const;
    std::vector<ProcessInput> getProcessValues() const;

private:
    struct Field {
        sf::RectangleShape box;
        sf::Text            text;
        std::string         buffer;
        bool                active = false;
        int                 row, col;
    };

    sf::Font& font;
    sf::Vector2f winSize;

    // Step 1: enter count
    sf::Text               promptText;
    sf::RectangleShape     countBox;
    sf::Text               countText;
    std::string            countBuffer;
    bool                   countActive = false;
    sf::RectangleShape     goButton;
    sf::Text               goText;

    // Step 2: enter rows
    int                    numProcesses = 0;
    std::vector<Field>     fields;
    std::vector<ProcessInput> values;

    void commitCount();
    void createFields();
    void updateField(Field& f);
};
