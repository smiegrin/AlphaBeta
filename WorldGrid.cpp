#include "WorldGrid.h"
#include <fstream>

/*
class WorldGrid {
  public enum Block {AIR, WALL, SPIKES, NOISE, FINISH_A, FINISH_B};

  sf::Vector2i dimensions;
  Block* gridSpaces;
  float gridSize;

public:
  WorldGrid();

  void loadWorld(std::string);
  Block getBlockAt(sf::Vector2f);
};
*/

WorldGrid::WorldGrid() :
  dimensions(20,18),
  gridSpaces(new Block[dimensions.x*dimensions.y]),
  gridSize(32.0),
  animationCounter(0)
  {
  //load tileSheet
}

void WorldGrid::setBlock(sf::Vector2i coordinate, Block b) {
  gridSpaces[coordinate.x+coordinate.y*dimensions.x] = b;
}

WorldGrid::Block WorldGrid::getBlockAt(sf::Vector2f point) const {
  if (point.x < 0 ||
      point.y < 0 ||
      point.x > gridSize*dimensions.x ||
      point.y > gridSize*dimensions.y)
        return AIR;

  sf::Vector2i testSpace(0,0);

  testSpace.x = (int)(point.x/gridSize);
  testSpace.y = (int)(point.y/gridSize);
  /*
  while ((testSpace.x+1) * gridSize < point.x) testSpace.x++;
  while ((testSpace.y+1) * gridSize < point.y) testSpace.y++;//*/

  return *(gridSpaces + (testSpace.y*dimensions.x + testSpace.x));
}

sf::Vector2i WorldGrid::getDimensions() const { return dimensions; }
