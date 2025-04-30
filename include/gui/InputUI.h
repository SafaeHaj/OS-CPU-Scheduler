#include <SFML/Graphics.hpp>
#include <vector>

class InputUI {
public:
    InputUI();
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::Vector2f mousePos);
    bool isInputComplete() const;
    std::vector<int> getProcessValues() const;

private:
    int numProcesses = 0;
    sf::RectangleShape inputBox;
    sf::Text inputText;
    bool focused = false;
    std::string buffer;

    void updateText();
    bool isNumber(const std::string& str);
};
