#include "MainMenu.h"
#include "KeyClicks.h"
#include <SFML/Graphics.hpp>

int main() {
	KeyClicks keyInfo(10); //10 stand for ten possible keys to map
	MainMenu mainMenu;

	sf::RenderWindow window(sf::VideoMode(640,640), "Alpha Beta", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	while (window.isOpen()) {

		//event polling
		sf::Event event;
		keyInfo.timeStep();
		MainMenu::Result menuResult = MainMenu::CONTINUING;
		while (window.pollEvent(event)) {
			//window
			if (event.type == sf::Event::Closed) window.close();

			//keyboard
			if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) keyInfo.hitKey(0); //up
        if (event.key.code == sf::Keyboard::Right) keyInfo.hitKey(1); //right
        if (event.key.code == sf::Keyboard::Down) keyInfo.hitKey(2); //down
        if (event.key.code == sf::Keyboard::Left) keyInfo.hitKey(3); //left
        if (event.key.code == sf::Keyboard::W) keyInfo.hitKey(4); //w
        if (event.key.code == sf::Keyboard::D) keyInfo.hitKey(5); //d
        if (event.key.code == sf::Keyboard::S) keyInfo.hitKey(6); //s
        if (event.key.code == sf::Keyboard::A) keyInfo.hitKey(7); //a
        if (event.key.code == sf::Keyboard::Return) keyInfo.hitKey(8); //enter
        if (event.key.code == sf::Keyboard::Escape) keyInfo.hitKey(9); //escape
			}
			if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) keyInfo.upKey(0); //S
        if (event.key.code == sf::Keyboard::Right) keyInfo.upKey(1); //S
        if (event.key.code == sf::Keyboard::Down) keyInfo.upKey(2); //S
        if (event.key.code == sf::Keyboard::Left) keyInfo.upKey(3); //S
        if (event.key.code == sf::Keyboard::W) keyInfo.upKey(4); //S
        if (event.key.code == sf::Keyboard::A) keyInfo.upKey(5); //S
        if (event.key.code == sf::Keyboard::S) keyInfo.upKey(6); //S
        if (event.key.code == sf::Keyboard::D) keyInfo.upKey(7); //S
        if (event.key.code == sf::Keyboard::Return) keyInfo.upKey(8); //S
        if (event.key.code == sf::Keyboard::Escape) keyInfo.upKey(9); //S
			}
		}

		//MainMenu::Result menuResult = MainMenu::CONTINUING;
		menuResult = mainMenu.update(keyInfo); //delegate update logic
    if (menuResult == MainMenu::DONE) window.close();

		//draw steps
		window.clear(sf::Color(0,0,0,255));
		window.draw(mainMenu);
		window.display();
	}

	return 0;
}
