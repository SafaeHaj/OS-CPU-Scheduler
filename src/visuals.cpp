#include<SFML/Graphics.hpp>
#include<unordered_map>
#include<string>
#include<random>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

    std::unordered_map<std::string, int> processes;

    for (int i = 0; i < 5; i++) {
        processes["Process " + std::to_string(i)] = i;
    }
    std::unordered_map<std::string, sf::RectangleShape> rectangles;
    for (const auto& process : processes) {
        sf::RectangleShape rectangle(sf::Vector2f(0, 35));
        rectangle.setFillColor(sf::Color(50 + process.second * 50, 200, 0));
        rectangle.setPosition(0, 50*5 - (process.second * 50));
        rectangles[process.first] = rectangle;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0.0f, 1.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        static size_t currentIndex = 0;
        auto it = rectangles.begin();
        std::advance(it, currentIndex);

        if (it->second.getSize().x <= 700) {
            float x = it->second.getSize().x + disX(gen)+processes[it->first];
            it->second.setSize(sf::Vector2f(x, it->second.getSize().y));
        }

        currentIndex = (currentIndex + 1) % rectangles.size();

        window.clear();

        for (const auto& [name, rectangle] : rectangles) {
            window.draw(rectangle);
        }

        window.display();
    }

    return 0;
}