#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Audio.hpp>
#include "WorldGrid.h"

class Slider : public sf::Drawable {
public:
  enum Direction {UP, DOWN, LEFT, RIGHT, NONE};
  enum Type {ALPHA, BETA};

private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  float speed;
  int hurtTimer;
  int health;
  bool isMoving;
  WorldGrid* worldGrid;
  Slider* partner;
  Type type;
  sf::RectangleShape body;
  sf::Color baseColor;
  sf::Color flashColor;
  sf::Sound hopSound;
  sf::Sound ouchSound;
  sf::Sound landSound;

public:
  Slider(Type, WorldGrid*);

  void update(Direction);

  void setPosition(sf::Vector2f);
  void setSpeed(float);
  void setHealth(int);
  void setPartner(Slider*);

  int getHealth();
  bool isOccupyingAt(sf::Vector2f);
  bool isAtGoal();

  void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
