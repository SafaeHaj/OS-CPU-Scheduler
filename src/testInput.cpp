#include <SFML/Graphics.hpp>
#include "gui/InputUI.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "InputUI Test");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1;
    }

    InputUI inputUI(font, sf::Vector2f(800, 600));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            inputUI.handleEvent(event, sf::Vector2f(0, 0));
        }

        window.clear(sf::Color::Black);
        inputUI.draw(window);
        window.display();
    }

    return 0;
}
