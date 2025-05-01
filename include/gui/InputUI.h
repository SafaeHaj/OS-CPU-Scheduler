#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct ProcessInput {
    int priority;
    int burstTime;
    int arrival;
};

class InputUI {
public:
    InputUI(sf::Font& font, sf::Vector2f winSize);
    void draw(sf::RenderWindow& win);
    void handleEvent(const sf::Event& ev, sf::Vector2f mousePos);
    bool isInputComplete() const;
    std::vector<ProcessInput> getProcessValues() const;

private:
    enum Field { PRIORITY, BURST, ARRIVAL };

    sf::Font& font;
    sf::Vector2f windowSize;

    sf::RectangleShape inputBox;
    sf::Text label;
    std::string buffer;

    int numProcesses = 0;
    int currentRow = 0;
    Field currentField = PRIORITY;

    std::vector<ProcessInput> results;

    sf::RectangleShape countBox;
    sf::Text countText;
    std::string countBuffer;

    enum class Status { IDLE, INPUTUI, INPUT, DONE };
    Status status = Status::IDLE;

    void updateDisplay();
    bool validateAndStore();
    void nextFieldOrRow();
    void displayError(const std::string& msg);

    // layout config
    float baseY = 200;
    float rowHeight = 50;
    float xStart = 100;
};
