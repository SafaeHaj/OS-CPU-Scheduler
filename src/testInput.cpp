#include <SFML/Graphics.hpp>
#include "gui/UIController.h"

int main(){
    sf::RenderWindow window({1200,600}, "Scheduling Algorithm Simulator");
    UIController ui;
    ui.initialize();

    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            if(ev.type == sf::Event::Closed) window.close();
            ui.handleEvent(ev);
        }
        ui.update();

        window.clear(sf::Color::Black);
        ui.render(window);
        window.display();
    }
    return 0;
}
