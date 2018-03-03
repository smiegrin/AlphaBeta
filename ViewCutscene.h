#ifndef VIEWCUTSCENE_H
#define VIEWCUTSCENE_H

#include "KeyClicks.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

class ViewCutscene : public sf::Drawable {
  View* view;
  Model* model;
  Controller* controller;

  sf::RectangleShape fadeRect;
  int phaseCounter;

  //dialogue textures
  sf::Texture facePlates;
  sf::Texture pixelFont;

  //graphic effects
  sf::RectangleShape textBox;
  sf::RectangleShape rightFaceBox;
  sf::RectangleShape middleFaceBox;
  sf::RectangleShape leftFaceBox;

public:
  enum Result {DONE, CONTINUING};

  ViewCutscene();

  Result update(KeyClicks);

  void readyCutscene(std::string);

  void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
