#include <SFML/Graphics.hpp>
#include <vector>
#include "ProcessUIManager.h"
#include "ProcessUI.h"

ProcessUIManager::ProcessUIManager(sf::Font &font) : font(font)
{
    std::string titles[5] = {"Priority", "Burst Time", "Arrival", "Simulation", "Time"};
    for (int i = 0; i < 5; ++i)
    {
        headers[i].setFont(font);
        headers[i].setString(titles[i]);
        headers[i].setCharacterSize(18);
        headers[i].setFillColor(sf::Color::White);
        headers[i].setPosition(10 + i * 90, 60); // Adjust x offset
    }

    avgBox.setSize(sf::Vector2f(100, 30));
    avgBox.setFillColor(sf::Color::Black);
    avgBox.setOutlineColor(sf::Color::White);
    avgBox.setOutlineThickness(1.f);
    avgBox.setPosition(600, 500);

    avgTurnaroundText.setFont(font);
    avgTurnaroundText.setCharacterSize(16);
    avgTurnaroundText.setFillColor(sf::Color::White);
    avgTurnaroundText.setPosition(460, 505);
    avgTurnaroundText.setString("Avg. Turnaround Time:");
}

void ProcessUIManager::setProcesses(const std::vector<Process *> &processes)
{
    processRows.clear();
    float yOffset = 100;
    for (auto *proc : processes)
    {
        processRows.emplace_back(proc, yOffset, 700, 50, font);
        yOffset += 60;
    }
}

void ProcessUIManager::draw(sf::RenderWindow &window)
{
    for (auto &header : headers)
        window.draw(header);

    for (auto &row : processRows)
        row.draw(window);

    window.draw(avgTurnaroundText);
    window.draw(avgBox);
}

void ProcessUIManager::updateAvgTurnaround(float avg)
{
    sf::Text value;
    value.setFont(font);
    value.setCharacterSize(16);
    value.setFillColor(sf::Color::White);
    value.setString(std::to_string(avg) + " ms");
    value.setPosition(avgBox.getPosition().x + 10, avgBox.getPosition().y + 5);
    avgTurnaroundText.setString("Avg. Turnaround Time:");
    avgTurnaroundText.setPosition(avgBox.getPosition().x - 140, avgBox.getPosition().y + 5);
}
