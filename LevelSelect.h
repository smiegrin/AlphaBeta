#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "KeyClicks.h"
#include "SelectionGrid.h"
#include "KeyClicks.h"
#include "ViewCutscene.h"
#include "PlayLevel.h"

class LevelSelect : public sf::Drawable {
  sf::Sprite backgroundGraphic;
  //std::vector<sf::Sprite> nodeGraphics;
  //sf::Sprite selectorGraphic;
  //sf::Sound selectionSound,
  //      moveSound,
  //      bonkSound;
  sf::RectangleShape fadeRect;
  SelectionGrid levelGrid;
  ViewCutscene cutscene;
  PlayLevel level;

  int phaseCounter;
  int selectorAnim;
  int selectionRegister;

	//temporary things
	sf::Text tempLabel;
  sf::Font tempFont;
  std::vector<sf::RectangleShape> nodeGraphics;
  sf::RectangleShape selectorGraphic;
public:
  enum Result{CONTINUING, DONE};

  LevelSelect();

  Result update(KeyClicks);

  void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
