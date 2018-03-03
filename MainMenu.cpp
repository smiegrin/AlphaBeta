#include "MainMenu.h"

MainMenu::MainMenu() :
	phaseCounter(0)
{
  //Temporary Title label
  tempFont.loadFromFile("Graphics/TYPOSTUCK.ttf");
	tempLabel.setString("Alpha Beta");
	tempLabel.setFont(tempFont);
	tempLabel.setColor(sf::Color::Yellow);

	tempLabel.setPosition(20.0, 20.0);

	//Fade Rectangle
  fadeRect.setFillColor(sf::Color(0,0,0,255));
  fadeRect.setSize(sf::Vector2f(600, 600));

  fadeRect.setPosition(0,0);
}

MainMenu::Result MainMenu::update(KeyClicks keyInfo)
{
  /* phase table
    0   -   59    fade in
    60            wait for input
                  BACK -> exit
                  SELECT -> 61
    61  -   120   fade out
    120           delegate to game
  */

  if (phaseCounter == 0) { //start phase
    //start the music
    //
    phaseCounter++;
    return CONTINUING;
  }

  else if (phaseCounter > 0 && phaseCounter < 60) {//fade in phase
    fadeRect.setFillColor(sf::Color(0,0,0,255-(int) (phaseCounter*255.0/60.0)));
    phaseCounter++;
    return CONTINUING;
  }

  else if (phaseCounter == 60) {// wait phase
    if (keyInfo.getHit(8)) { //play the game
      //probably play a sound here
      //stop the music
      phaseCounter++;
    }
    else if (keyInfo.getHit(9)) { //exit
      return DONE;
    }

    return CONTINUING;
  }

  else if (phaseCounter > 60 && phaseCounter < 120) {//fade out phase
    fadeRect.setFillColor(sf::Color(0,0,0,(int) (phaseCounter*255.0/60.0)));
    phaseCounter++;
    return CONTINUING;
  }

  else if (phaseCounter == 120) {//go to level select
    //delegate to level select
    LevelSelect::Result result = levelSelect.update(keyInfo);
    if (result == LevelSelect::DONE) phaseCounter = 0;
    return CONTINUING;
  }

  return DONE;
}


void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
  if (phaseCounter == 120) target.draw(levelSelect);
  else {
    target.draw(tempLabel);
    target.draw(fadeRect);
  }
}
