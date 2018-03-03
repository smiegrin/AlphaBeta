#include <iostream>
#include <SFML/Graphics.hpp>
#include "KeyClicks.h"
#include "LevelSelect.h"

class MainMenu : public sf::Drawable {
	sf::Sprite startGraphic,
		titleGraphic,
		alphaBetaGraphic;
	sf::RectangleShape fadeRect;
	int phaseCounter;

	LevelSelect levelSelect;

	//temporary things
	sf::Text tempLabel;
  sf::Font tempFont;

public:
  enum Result {DONE, CONTINUING};
	MainMenu();
	Result update(KeyClicks);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
};
