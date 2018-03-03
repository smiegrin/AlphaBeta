#ifndef PLAYLEVEL_H
#define PLAYLEVEL_H

#include "Slider.h"
#include "WorldGrid.h"
#include "KeyClicks.h"
#include <fstream>

class PlayLevel : public sf::Drawable {
  //public enum Block {AIR, WALL, SPIKES, NOISE, FINISH_A, FINISH_B};

  float gridSize;
  int phaseCounter;
  int animationCounter;

  WorldGrid worldGrid;
  Slider alphaA, betaB;

  sf::RectangleShape alphaHealth, betaHealth;

  sf::RectangleShape wipeRect;
  //sf::Sprite healthOverlay
  //sf::Texture tileSheet


  //bool ready;
  //sf::RenderTexture look;
public:
  enum Result {WIN, LOSE, CONTINUING};

  PlayLevel();

  void initialize(std::string);

  Result update(KeyClicks);

  void draw(sf::RenderTarget&,  sf::RenderStates) const;
};

#endif
