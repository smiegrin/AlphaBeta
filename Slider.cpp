#include "Slider.h"

Slider::Slider(Type aob, WorldGrid* level):
  position(sf::Vector2f(0,0)),
  velocity(sf::Vector2f(0,0)),
  speed(12.0),
  hurtTimer(0),
  health(5),
  isMoving(false),
  worldGrid(level),
  partner(NULL),
  type(aob),
  body(sf::Vector2f(32, 32))
  //sf::Sound hopSound;
  //sf::Sound ouchSound;
  //sf::Sound landSound;
  {
  baseColor = ((type == ALPHA) ? sf::Color::Cyan : sf::Color::Magenta);
  flashColor = ((type == ALPHA) ? sf::Color(0, 0, 128) : sf::Color(128, 0, 0));
  //loadSounds
}

void Slider::update(Direction dir) {
  if (partner == NULL) return;

  sf::Vector2f topLeftCorner = sf::Vector2f(0,0);
  sf::Vector2f topRightCorner = sf::Vector2f(31.99, 0);
  sf::Vector2f bottomLeftCorner = sf::Vector2f(0, 31.99);
  sf::Vector2f bottomRightCorner = sf::Vector2f(31.99, 31.99);

  if (isMoving) {
    float moveCounter = abs(velocity.x + velocity.y);
    sf::Vector2f unitVelocity = sf::Vector2f(velocity.x/moveCounter, velocity.y/moveCounter);
    while (moveCounter >= 1.0 &&
            worldGrid->getBlockAt(topLeftCorner + position + unitVelocity) != WorldGrid::WALL &&
            worldGrid->getBlockAt(topLeftCorner + position + unitVelocity) != WorldGrid::SPIKES &&
            worldGrid->getBlockAt(topRightCorner + position + unitVelocity) != WorldGrid::WALL &&
            worldGrid->getBlockAt(topRightCorner + position + unitVelocity) != WorldGrid::SPIKES &&
            worldGrid->getBlockAt(bottomLeftCorner + position + unitVelocity) != WorldGrid::WALL &&
            worldGrid->getBlockAt(bottomLeftCorner + position + unitVelocity) != WorldGrid::SPIKES &&
            worldGrid->getBlockAt(bottomRightCorner + position + unitVelocity) != WorldGrid::WALL &&
            worldGrid->getBlockAt(bottomRightCorner + position + unitVelocity) != WorldGrid::SPIKES &&
            !partner->isOccupyingAt(position + sf::Vector2f(16,16) + 17.0f*unitVelocity)
            ) {
      moveCounter -= 1.0;
      position += unitVelocity;
    }
    if (moveCounter > 0 && moveCounter < 1.0 &&
        worldGrid->getBlockAt(topLeftCorner + position + moveCounter*unitVelocity) != WorldGrid::WALL &&
        worldGrid->getBlockAt(topLeftCorner + position + moveCounter*unitVelocity) != WorldGrid::SPIKES &&
        worldGrid->getBlockAt(topRightCorner + position + moveCounter*unitVelocity) != WorldGrid::WALL &&
        worldGrid->getBlockAt(topRightCorner + position + moveCounter*unitVelocity) != WorldGrid::SPIKES &&
        worldGrid->getBlockAt(bottomLeftCorner + position + moveCounter*unitVelocity) != WorldGrid::WALL &&
        worldGrid->getBlockAt(bottomLeftCorner + position + moveCounter*unitVelocity) != WorldGrid::SPIKES &&
        worldGrid->getBlockAt(bottomRightCorner + position + moveCounter*unitVelocity) != WorldGrid::WALL &&
        worldGrid->getBlockAt(bottomRightCorner + position + moveCounter*unitVelocity) != WorldGrid::SPIKES &&
        !partner->isOccupyingAt(position + sf::Vector2f(16,16) + 17.0f*unitVelocity)
        ) {
      position += moveCounter*unitVelocity;
      moveCounter = 0;
    }
    if (moveCounter != 0) {
      if (worldGrid->getBlockAt(position + sf::Vector2f(16,16) + 17.0f*unitVelocity) == WorldGrid::SPIKES) {
        //ouch
        if (health > 0 && hurtTimer == 0) {
          health -= 1;
          hurtTimer = 120;
        }
      }
      else {
        //thump
      }
      velocity = sf::Vector2f(0,0);
      isMoving = false;
    }

  }
  else {
    switch (dir) {
    case UP:
      velocity = sf::Vector2f(0, -speed);
      isMoving = true;
      break;
    case DOWN:
      velocity = sf::Vector2f(0, speed);
      isMoving = true;
      break;
    case LEFT:
      velocity = sf::Vector2f(-speed, 0);
      isMoving = true;
      break;
    case RIGHT:
      velocity = sf::Vector2f(speed, 0);
      isMoving = true;
      break;
    case NONE:
      break;
    }
  }

  if (hurtTimer == 0 && worldGrid->getBlockAt(position + sf::Vector2f(16, 16)) == WorldGrid::NOISE) {
    //ouch
    hurtTimer = 120;
    health--;
  }

  if (hurtTimer > 0) hurtTimer--;

  body.setPosition(position);
  body.setFillColor((hurtTimer % 12 == 0) ? baseColor : flashColor);
}

void Slider::setPosition(sf::Vector2f p) {
  velocity = sf::Vector2f(0,0);
  position = p;
  isMoving = false;
  body.setPosition(p);
}

void Slider::setSpeed(float s) {
  speed = s;
}

void Slider::setHealth(int h) {
  health = h;
  hurtTimer = 0;
}

void Slider::setPartner(Slider* p) {
  partner = p;
}

int Slider::getHealth() { return health; }

bool Slider::isOccupyingAt(sf::Vector2f point) {
  if (point.x < position.x ||
      point.x >= position.x + 32 ||
      point.y < position.y ||
      point.y >= position.y + 32) return false;
  else return true;
}

bool Slider::isAtGoal() {
  if (type == ALPHA && worldGrid->getBlockAt(position + sf::Vector2f(16,16)) == WorldGrid::FINISH_A) return true;
  if (type == BETA && worldGrid->getBlockAt(position + sf::Vector2f(16,16)) == WorldGrid::FINISH_B) return true;
  return false;
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
  target.draw(body);
}
