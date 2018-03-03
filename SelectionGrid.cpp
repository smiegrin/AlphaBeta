#include "SelectionGrid.h"

SelectionGrid::SelectionGrid(
        sf::Vector2i dimensions = sf::Vector2i(1,1),
        sf::Vector2f cellDimensions = sf::Vector2f(5.0,5.0),
        sf::Vector2f orig = sf::Vector2f(0,0),
        bool doLoop = false):
  gridSize(dimensions),
  cellSize(cellDimensions),
  origin(orig),
  selectorPosition(0,0),
  doesLoop(doLoop)
{}

sf::Vector2f SelectionGrid::getCellPosition(sf::Vector2i cell) {
  //encapsulate x and y
  if (cell.x < 0) cell.x = 0;
  if (cell.y < 0) cell.y = 0;
  if (cell.x >= gridSize.x) cell.x = gridSize.x - 1;
  if (cell.y >= gridSize.y) cell.y = gridSize.y - 1;

  return origin + sf::Vector2f(cell.x * cellSize.x, cell.y * cellSize.y);
}

sf::Vector2i SelectionGrid::getSelectorPosition() {
  return selectorPosition;
}

void SelectionGrid::setOrigin(sf::Vector2f orig) {
  origin = orig;
}

void SelectionGrid::moveSelector(Direction dir) {
  sf::Vector2i oldPos = selectorPosition;
  switch(dir) {
  case UP:
    selectorPosition.y += -1;
  break;
  case DOWN:
    selectorPosition.y += 1;
  break;
  case LEFT:
    selectorPosition.x += -1;
  break;
  case RIGHT:
    selectorPosition.x += 1;
  break;
  }

  if (selectorPosition.x < 0) selectorPosition.x = (doesLoop) ? gridSize.x-1 : oldPos.x;
  if (selectorPosition.y < 0) selectorPosition.y = (doesLoop) ? gridSize.y-1 : oldPos.y;
  if (selectorPosition.x >= gridSize.x) selectorPosition.x = (doesLoop) ? 0 : oldPos.x;
  if (selectorPosition.y >= gridSize.y) selectorPosition.y = (doesLoop) ? 0 : oldPos.y;
}

void SelectionGrid::moveSelectorTo(sf::Vector2i newPos) {
  //encapsulate x and y
  if (newPos.x < 0) newPos.x = 0;
  if (newPos.y < 0) newPos.y = 0;
  if (newPos.x >= gridSize.x) newPos.x = gridSize.x - 1;
  if (newPos.y >= gridSize.y) newPos.y = gridSize.y - 1;

  selectorPosition = newPos;
}
