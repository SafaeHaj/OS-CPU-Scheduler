#pragma once
#include <SFML/Graphics.hpp>
#include "gui/InputUI.h"

enum class Status {
    IDLE,   
    RUNNING, // simulation
    DONE
};

class Start {
public:
    Start(sf::Font& font, sf::Vector2f windowSize);

    // Called every frame from main()
    void handleEvent(const sf::Event& event);
    void update();         // advance state machine
    void draw(sf::RenderWindow& window);

    Status getStatus() const { return status; }

private:
    Status     status = Status::IDLE;
    sf::Font&  font;
   
    // --- Shared helper ---
    void displayError(const std::string& msg);

    // Internal state‐handlers
    void doStartState(const sf::Event& ev);
};
