#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "gui/ProcessUIManager.h"
#include "gui/DropDownMenu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Test");
    std::vector<std::string> options = {"Alg 1", "Alg 2", "Alg 3"};
    sf::Font font;

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1;
    }

    DropDownMenu dropdown(sf::Vector2f(1000, 0), 200, options, font);


    Process* process = new Process(0, 0, 10, 1);
    Process* process2 = new Process(1, 0, 10, 3);
    ProcessUIManager processUIManager(300, 100, font);
    processUIManager.setProcesses({process, process2});
    processUIManager.updateAvgTurnaround(5.0f);

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
        processUIManager.draw(window);
        window.display();
    }

    return 0;
}