#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1366, 768), "Test");

    // Create a dropdown menu
    // Initial button
    RectangleShape init_dropdown(Vector2f(200, 50));
    init_dropdown.setFillColor(Color(255, 255, 255));
    init_dropdown.setPosition(1000, 50);
    Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1;
    }
    Text dropdown_text("Select Algorithm", font, 20);
    dropdown_text.setFillColor(Color::Black);
    dropdown_text.setPosition(1000 + 10, 50 + 10);
    dropdown_text.setCharacterSize(20);

    // Dropdown items on click
    unordered_map<string, RectangleShape> drop_items = {
        {"Alg 1", RectangleShape(Vector2f(200, 50))},
        {"Alg 2", RectangleShape(Vector2f(200, 50))},
        {"Alg 3", RectangleShape(Vector2f(200, 50))}
    };

    while(window.isOpen()) {
        Event event;

        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        
        window.draw(init_dropdown);
        window.draw(dropdown_text);

        static bool dropdown_open = false;

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
            Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);

            // Check if the initial dropdown button is clicked
            if (init_dropdown.getGlobalBounds().contains(mouse_pos)) {
                dropdown_open = !dropdown_open; // Toggle dropdown visibility
            } else if (dropdown_open) {
                // Check if any dropdown item is clicked
                for (auto& item : drop_items) {
                if (item.second.getGlobalBounds().contains(mouse_pos)) {
                    dropdown_open = false; // Close dropdown after selection
                    // Handle selection logic here (e.g., print selected item)
                    cout << "Selected: " << item.first << endl;
                    break;
                }
                }

                // Close dropdown if clicked outside
                if (dropdown_open) {
                dropdown_open = false;
                }
            }
            }
        }

        // Draw dropdown items if dropdown is open
        if (dropdown_open) {
            for (auto& item : drop_items) {
            item.second.setFillColor(Color(255, 255, 255));
            item.second.setPosition(1000, 50 + 50 * (item.first[4] - '0'));
            window.draw(item.second);
            Text item_text(item.first, font, 20);
            item_text.setFillColor(Color::Black);
            item_text.setPosition(1000 + 10, 50 + 50 * (item.first[4] - '0') + 10);
            window.draw(item_text);
            }
        }

        window.display();
    }


    return 0;
}

