#include <SFML/Graphics.hpp>

enum class Status {
    START,
    INPUT,
    RUNNING,
    DONE,
};

class Start {
public:
    Start();
    Status status = Status::START;

    void run(); // dispatch flow based on current status
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::Vector2f mousePos);

    void reset(); // reset state if invalid input or restart requested

private:
    sf::RectangleShape startButton;
    sf::Text startText;
    bool buttonPressed(sf::Vector2f mousePos);
};
