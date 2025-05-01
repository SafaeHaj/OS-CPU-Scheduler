#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "gui/DropDownMenu.h"
#include "gui/Layout.h"

DropDownMenu::DropDownMenu(sf::Vector2f pos, float width, std::vector<std::string> options, sf::Font &font)
    : font(font)
{
    baseButton.setSize(sf::Vector2f(width, FIELD_HEIGHT));
    baseButton.setPosition(pos);
    baseButton.setFillColor(sf::Color::Black);
    baseButton.setOutlineColor(sf::Color::White);
    baseButton.setOutlineThickness(1.f);

    baseText.setFont(font);
    baseText.setString(selectedItem);
    baseText.setCharacterSize(CHAR_SIZE);
    baseText.setFillColor(sf::Color::White);
    baseText.setPosition(pos.x + PADDING, pos.y + (FIELD_HEIGHT - CHAR_SIZE) / 2);

    for (size_t i = 0; i < options.size(); ++i)
    {
        sf::RectangleShape item(sf::Vector2f(width, FIELD_HEIGHT));
        item.setPosition(pos.x, pos.y + FIELD_HEIGHT * (i + 1));
        item.setFillColor(sf::Color::White);
        item.setOutlineColor(sf::Color::Black);
        item.setOutlineThickness(1.f);
        items.push_back(item);

        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(CHAR_SIZE);
        text.setFillColor(sf::Color::Black);
        text.setPosition(pos.x + PADDING, pos.y + FIELD_HEIGHT * (i + 1) + (FIELD_HEIGHT - CHAR_SIZE) / 2);
        itemTexts.push_back(text);
    }
}

void DropDownMenu::setPosition(sf::Vector2f pos)
{
    baseButton.setPosition(pos);
    baseText.setPosition(pos.x + PADDING, pos.y + (FIELD_HEIGHT - CHAR_SIZE) / 2);

    for (size_t i = 0; i < items.size(); ++i)
    {
        items[i].setPosition(pos.x, pos.y + FIELD_HEIGHT * (i + 1));
        itemTexts[i].setPosition(pos.x + PADDING, pos.y + FIELD_HEIGHT * (i + 1) + (FIELD_HEIGHT - CHAR_SIZE) / 2);
    }
}


void DropDownMenu::handleEvent(sf::Event &event, sf::Vector2f mousePos)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {

        if (baseButton.getGlobalBounds().contains(mousePos))
        {
            isOpen = !isOpen;
        }
        else if (isOpen)
        {
            for (size_t i = 0; i < items.size(); ++i)
            {
                if (items[i].getGlobalBounds().contains(mousePos))
                {
                    selectedItem = itemTexts[i].getString();
                    baseText.setString(selectedItem);
                    isOpen = false;
                    break;
                }
            }
            if (isOpen)
                isOpen = false;
        }
    }
}

void DropDownMenu::draw(sf::RenderWindow &window)
{
    window.draw(baseButton);
    window.draw(baseText);
    if (isOpen)
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            window.draw(items[i]);
            window.draw(itemTexts[i]);
        }
    }
}

std::string DropDownMenu::getSelectedItem() const
{
    return selectedItem;
}
