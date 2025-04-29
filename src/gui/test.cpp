#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "DropDownMenu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Test");
    std::vector<std::string> options = {"Alg 1", "Alg 2", "Alg 3"};
    sf::Font font;

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1;
    }

    DropdownMenu dropdown(sf::Vector2f(1000, 50), 200, options, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    dropdown.handleEvent(event, mousePos);
                }
            }
        }

        window.clear();
        dropdown.draw(window);
        window.display();
    }

    return 0;
}