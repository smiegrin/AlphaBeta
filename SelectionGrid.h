#ifndef SELECTIONGRID_H
#define SELECTIONGRID_H

#include <SFML/Graphics.hpp>

class SelectionGrid {
  sf::Vector2i gridSize;
  sf::Vector2i selectorPosition;
  sf::Vector2f cellSize;
  bool doesLoop;
  sf::Vector2f origin;

public:
  enum Direction {UP, DOWN, LEFT, RIGHT};

  SelectionGrid(sf::Vector2i, sf::Vector2f, sf::Vector2f, bool);

  sf::Vector2f getCellPosition(sf::Vector2i);
  sf::Vector2i getSelectorPosition();

  void setOrigin(sf::Vector2f);

  void moveSelector(Direction);
  void moveSelectorTo(sf::Vector2i);
};

#endif
