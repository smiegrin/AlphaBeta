#include "PlayLevel.h"

PlayLevel::PlayLevel():
  gridSize(32.0),
  phaseCounter(0),
  animationCounter(0),
  worldGrid(),
  alphaA(Slider::ALPHA, &worldGrid),
  betaB(Slider::BETA, &worldGrid),
  alphaHealth(sf::Vector2f(320,64)),
  betaHealth(sf::Vector2f(320,64)),
  wipeRect(sf::Vector2f(640, 640))
  {
  //setup healthbars

  wipeRect.setFillColor(sf::Color::Black);
  alphaHealth.setPosition(sf::Vector2f(0, 576));
  alphaHealth.setFillColor(sf::Color::Cyan);
  betaHealth.setPosition(sf::Vector2f(320, 576));
  betaHealth.setFillColor(sf::Color::Magenta);

  alphaA.setPartner(&betaB);
  betaB.setPartner(&alphaA);
}


void PlayLevel::initialize(std::string fileName) {
    std::ifstream stream;
    stream.open(fileName.c_str());

    sf::Vector2i dimensions;

    stream >> dimensions.x;
    stream >> dimensions.y;

    int healthInt;
    stream >> healthInt;
    alphaA.setHealth(healthInt);
    stream >>healthInt;
    betaB.setHealth(healthInt);
    //space = new Block[width*height];

    char piece;
    for (int v = 0; v < dimensions.y; v++) for (int u = 0; u < dimensions.x; u++) {
        stream >> piece;
        WorldGrid::Block thisBlock = WorldGrid::AIR;
        if (piece == '\n') stream >> piece;
        switch (piece) {
        case '`':
            thisBlock = WorldGrid::AIR;
            break;
        case '#':
            thisBlock = WorldGrid::WALL;
            break;
        case '^':
            thisBlock = WorldGrid::SPIKES;
            break;
        case 'X':
            thisBlock = WorldGrid::NOISE;
            break;
        case 'A':
            thisBlock = WorldGrid::FINISH_A;
            break;
        case 'B':
            thisBlock = WorldGrid::FINISH_B;
            break;
        case 'a':
            thisBlock = WorldGrid::AIR;
            alphaA.setPosition(sf::Vector2f(u*gridSize, v*gridSize));
            break;
        case 'b':
            thisBlock = WorldGrid::AIR;
            betaB.setPosition(sf::Vector2f(u*gridSize, v*gridSize));
            break;
        }
        worldGrid.setBlock(sf::Vector2i(u,v), thisBlock);
    }

    stream.close();

    /*/draw up stage
    look.create(dimensions.x*gridSize,dimensions.y*gridSize);
    look.clear(sf::Color::Transparent);
    sf::RectangleShape printHead(sf::Vector2f(gridSize, gridSize));
    for (int x = 0; x < dimensions.x; x++) for (int y = 0; y < dimensions.y; y++) {
        switch (gridSpaces[x+y*dimensions.y]) {
        case AIR:
          printHead.setFillColor(sf::Color::Transparent);
          break;
        case WALL:
          printHead.setFillColor(sf::Color::Blue);
          break;
        case SPIKES:
          printHead.setFillColor(sf::Color::Red);
          break;
        case NOISE:
          printHead.setFillColor(sf::Color(255, 0, 128, 128));
          break;
        case FINISH_A:
          printHead.setFillColor(sf::Color::Cyan);
          break;
        case FINISH_B:
          printHead.setFillColor(sf::Color::Magenta);
          break;
        }
        //printHead.setTextureRect(sf::IntRect(u,v,32,32));
        printHead.setPosition(gridSize*x,gridSize*y);
        look.draw(printHead);
    }
    look.display();
  */
}

PlayLevel::Result PlayLevel::update(KeyClicks keyInfo) {

  Result endResult = LOSE;
  if (phaseCounter == 0) {
    //start music
    wipeRect.setPosition(0, 0);
    endResult = CONTINUING;
    phaseCounter++;
  }

  else if (phaseCounter > 0 && phaseCounter < 15) {
    wipeRect.setPosition(0, phaseCounter/15.0*640);
    endResult = CONTINUING;
    phaseCounter++;
  }

  else if (phaseCounter ==  15) { //game logic
    wipeRect.setPosition(0, -640);

    //key presses
    if (keyInfo.getDown(9)) phaseCounter++;

    if (keyInfo.getHit(0)) alphaA.update(Slider::UP);
    else if (keyInfo.getHit(1)) alphaA.update(Slider::RIGHT);
    else if (keyInfo.getHit(2)) alphaA.update(Slider::DOWN);
    else if (keyInfo.getHit(3)) alphaA.update(Slider::LEFT);
    else alphaA.update(Slider::NONE);

    if (keyInfo.getHit(4)) betaB.update(Slider::UP);
    else if (keyInfo.getHit(5)) betaB.update(Slider::RIGHT);
    else if (keyInfo.getHit(6)) betaB.update(Slider::DOWN);
    else if (keyInfo.getHit(7)) betaB.update(Slider::LEFT);
    else betaB.update(Slider::NONE);

    //update health bars:
    alphaHealth.setSize(sf::Vector2f(64*alphaA.getHealth(), 64));
    betaHealth.setSize(sf::Vector2f(64*betaB.getHealth(), 64));

    if (alphaA.getHealth() == 0 || betaB.getHealth() == 0) phaseCounter++;
    if (alphaA.isAtGoal() && betaB.isAtGoal()) phaseCounter = 31;

    endResult = CONTINUING;
  }

  else if (phaseCounter > 15 && phaseCounter < 30) {
    wipeRect.setPosition(0, (phaseCounter - 15)/15.0*640 - 640);
    endResult = CONTINUING;
    phaseCounter++;
  }

  else if (phaseCounter == 30) {
    endResult = LOSE;
    phaseCounter = 0;
    //stop the music
  }

  else if (phaseCounter > 30 && phaseCounter < 45) {
    float percent = (phaseCounter - 30)/15.0;
    wipeRect.setPosition(320 - percent*320, 320 - percent*320);
    wipeRect.setSize(sf::Vector2f(640*percent, 640*percent));
    endResult = CONTINUING;
    phaseCounter++;
  }

  else if (phaseCounter == 45) {
    endResult = WIN;
    phaseCounter = 0;
    //stop the music
  }

  return endResult;
}

void PlayLevel::draw(sf::RenderTarget& target,  sf::RenderStates states = sf::RenderStates::Default) const {

  target.draw(alphaA);
  target.draw(betaB);

  //sf::Vector2i dimensions(worldGrid.getDimensions());

  sf::RectangleShape printHead(sf::Vector2f(gridSize, gridSize));
  for (int x = 0; x < worldGrid.getDimensions().x; x++) for (int y = 0; y < worldGrid.getDimensions().y; y++) {
    switch (worldGrid.getBlockAt(sf::Vector2f(gridSize*x,gridSize*y))) {
    case WorldGrid::AIR:
      printHead.setFillColor(sf::Color::Transparent);
      break;
    case WorldGrid::WALL:
      printHead.setFillColor(sf::Color::Blue);
      break;
    case WorldGrid::SPIKES:
      printHead.setFillColor(sf::Color::Red);
      break;
    case WorldGrid::NOISE:
      printHead.setFillColor(sf::Color(255, 0, 128, 128));
      break;
    case WorldGrid::FINISH_A:
      printHead.setFillColor(sf::Color::Cyan);
      break;
    case WorldGrid::FINISH_B:
      printHead.setFillColor(sf::Color::Magenta);
      break;
    }
    //printHead.setTextureRect(sf::IntRect(u,v,32,32));
    printHead.setPosition(gridSize*x,gridSize*y);
    target.draw(printHead);
  }


  target.draw(alphaHealth);
  target.draw(betaHealth);
  //draw bar overlay

  target.draw(wipeRect);
}
