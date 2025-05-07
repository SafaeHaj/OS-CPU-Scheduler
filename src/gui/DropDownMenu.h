#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class DropDownMenu {
private:
    sf::RectangleShape baseButton;
    sf::Text baseText;
    std::vector<sf::RectangleShape> items;
    std::vector<sf::Text> itemTexts;

    sf::Font& font;
    bool isOpen = false;
    float itemHeight = 50;
    std::string selectedItem = "Select Algorithm";

public:
    DropDownMenu(sf::Vector2f pos, float width, std::vector<std::string> options, sf::Font& font);

    void handleEvent(sf::Event& event, sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos);
    std::string getSelectedItem() const;
};
