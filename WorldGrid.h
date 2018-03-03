#ifndef WORLDGRID_H
#define WORLDGRID_H
#include <SFML/Graphics.hpp>

class WorldGrid {
public: enum Block {AIR, WALL, SPIKES, NOISE, FINISH_A, FINISH_B};
private:
  //sf::Texture tileSheet
  sf::RenderTexture look;

  sf::Vector2i dimensions;
  Block* gridSpaces;
  float gridSize;
  int animationCounter;

public:
  WorldGrid();

  void setBlock(sf::Vector2i, Block);

  Block getBlockAt(sf::Vector2f) const;
  sf::Vector2i getDimensions() const;
};

#endif
