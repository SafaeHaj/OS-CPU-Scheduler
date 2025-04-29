#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "ProcessUI.h"
#include "../../include/Process.h" // Include the header file for the Process class

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Test");
    std::vector<std::string> options = {"Alg 1", "Alg 2", "Alg 3"};
    sf::Font font;

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1;
    }
    Process* process = new Process(0, 0, 10, 1);
    ProcessUI processUI(process, 300, 50, 700, 60, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        processUI.draw(window);
        window.display();
    }

    return 0;
}