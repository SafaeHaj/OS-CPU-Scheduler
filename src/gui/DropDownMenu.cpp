#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "DropDownMenu.h"

DropdownMenu::DropdownMenu(sf::Vector2f pos, float width, std::vector<std::string> options, sf::Font &font)
    : font(font)
{
    baseButton.setSize(sf::Vector2f(width, itemHeight));
    baseButton.setPosition(pos);
    baseButton.setFillColor(sf::Color::White);

    baseText.setFont(font);
    baseText.setString(selectedItem);
    baseText.setCharacterSize(20);
    baseText.setFillColor(sf::Color::Black);
    baseText.setPosition(pos.x + 10, pos.y + 10);

    for (size_t i = 0; i < options.size(); ++i)
    {
        sf::RectangleShape item(sf::Vector2f(width, itemHeight));
        item.setPosition(pos.x, pos.y + itemHeight * (i + 1));
        item.setFillColor(sf::Color::White);
        items.push_back(item);

        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(pos.x + 10, pos.y + itemHeight * (i + 1) + 10);
        itemTexts.push_back(text);
    }
}

void DropdownMenu::handleEvent(sf::Event &event, sf::Vector2f mousePos)
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

void DropdownMenu::draw(sf::RenderWindow &window)
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

std::string DropdownMenu::getSelectedItem() const
{
    return selectedItem;
}
