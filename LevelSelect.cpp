#include "LevelSelect.h"


LevelSelect::LevelSelect():
  //sf::Sprite backgroundGraphic,
  //std::vector<sf::Sprite> nodeGraphics,
  selectorGraphic(sf::Vector2f(92,76)),
  //sf::Sound selectionSound,
  //sf::Sound moveSound,
  //sf::Sound bonkSound,
  levelGrid(sf::Vector2i(5,5), sf::Vector2f(96, 80), sf::Vector2f(82, 162), false),
  cutscene(),
  level(),

  phaseCounter(0),
  selectorAnim(0),
  selectionRegister(0)
  {

  //Temporary Title label
  tempFont.loadFromFile("Graphics/TYPOSTUCK.ttf");
	tempLabel.setString("Select Level");
	tempLabel.setFont(tempFont);
	tempLabel.setColor(sf::Color::Yellow);

	tempLabel.setPosition(20.0, 20.0);

	//Fade Rectangle
  fadeRect.setFillColor(sf::Color(0,0,0,255));
  fadeRect.setSize(sf::Vector2f(600,600));

  fadeRect.setPosition(0,0);

  //initialize nodes
  for (int i = 0; i < 25; i++) {
    nodeGraphics.push_back(sf::RectangleShape(sf::Vector2f(92,76)));
    nodeGraphics[i].setFillColor((i%4) ? sf::Color::Blue : sf::Color::Red);
    nodeGraphics[i].setPosition(levelGrid.getCellPosition(sf::Vector2i(i%5,i/5)));
  }

  //initialize selection indicator
  selectorGraphic.setFillColor(sf::Color::Transparent);
  selectorGraphic.setOutlineThickness(2);
  selectorGraphic.setOutlineColor(sf::Color::White);
}

LevelSelect::Result LevelSelect::update(KeyClicks keyInfo) {
  /* phase table
    0   -   59    fade in
    60            wait for input
                  SELECT -> 61
                  ESCAPE -> 121
    61  -   120   fade out
    120           delegate to game
                  DONE -> 0
    121 - 180     fade to title
  */

  Result endResult = DONE;

  if (phaseCounter == 0) { //start phase
    //start the music
    //
    selectionRegister = 0;
    phaseCounter++;
    endResult = CONTINUING;
  }

  else if (phaseCounter > 0 && phaseCounter < 60) {//fade in phase
    fadeRect.setFillColor(sf::Color(0,0,0,255-(int) (phaseCounter*255.0/60.0)));
    phaseCounter++;
    endResult = CONTINUING;
  }

  else if (phaseCounter == 60) {// wait phase
    if (keyInfo.getHit(8)) {//enter
      //try to select the level
      sf::Vector2i selection = levelGrid.getSelectorPosition();
      selectionRegister = selection.x + 5*selection.y;
      if (selectionRegister % 4 == 0) { //cutscene selected
        if      (selectionRegister == 0)  cutscene.readyCutscene("Scripts/chapter1.dlg");
        else if (selectionRegister == 4)  cutscene.readyCutscene("Scripts/chapter2.dlg");
        else if (selectionRegister == 8)  cutscene.readyCutscene("Scripts/chapter3.dlg");
        else if (selectionRegister == 12) cutscene.readyCutscene("Scripts/chapter4.dlg");
        else if (selectionRegister == 16) cutscene.readyCutscene("Scripts/chapter5.dlg");
        else if (selectionRegister == 20) cutscene.readyCutscene("Scripts/chapter6.dlg");
        else if (selectionRegister == 24) cutscene.readyCutscene("Scripts/chapter7.dlg");
      }
      else { //level selected
        level.initialize("Levels/level01.lvl");
      }
      phaseCounter = 61;
    }
    else if (keyInfo.getHit(9)) {//escape
      //go back to main menu
      phaseCounter = 121;
    }
    else if (keyInfo.getHit(0) || keyInfo.getHit(4)) {//up
      //beep!
      levelGrid.moveSelector(SelectionGrid::UP);
    }
    else if (keyInfo.getHit(1) || keyInfo.getHit(5)) {//right
      //beep!
      levelGrid.moveSelector(SelectionGrid::RIGHT);
    }
    else if (keyInfo.getHit(2) || keyInfo.getHit(6)) {//down
      //beep!
      levelGrid.moveSelector(SelectionGrid::DOWN);
    }
    else if (keyInfo.getHit(3) || keyInfo.getHit(7)) {//left
      //beep!
      levelGrid.moveSelector(SelectionGrid::LEFT);
    }

    endResult = CONTINUING;
  }

  else if (phaseCounter > 60 && phaseCounter < 120) {//fade out to game phase
    fadeRect.setFillColor(sf::Color(0,0,0,(int) ((phaseCounter-60)*255.0/60.0)));
    phaseCounter++;
    endResult = CONTINUING;
  }

  else if (phaseCounter == 120) {//go to level
    //delegate to game
    endResult = CONTINUING;
    if (selectionRegister % 4 == 0) phaseCounter = (cutscene.update(keyInfo) == ViewCutscene::CONTINUING) ? 120 : 0;
    else {
      PlayLevel::Result r = level.update(keyInfo);
      switch(r) {
      case PlayLevel::WIN:
        //advance level availability
      case PlayLevel::LOSE:
        phaseCounter = 0;
        break;
      case PlayLevel::CONTINUING:
        break;
      }
      //phaseCounter = 121;
    }
  }

  else if (phaseCounter > 120 && phaseCounter < 180) {//fade out to main menu
    fadeRect.setFillColor(sf::Color(0,0,0,(int) ((phaseCounter-120)*255.0/60)));
    phaseCounter++;
    endResult = CONTINUING;
  }

  else if (phaseCounter == 180) {
    endResult = DONE;
  }

  //update graphics
  selectorGraphic.setPosition(levelGrid.getCellPosition(levelGrid.getSelectorPosition()));

  return endResult;

}

void LevelSelect::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
  if (phaseCounter == 120) {
    if (selectionRegister%4 == 0) target.draw(cutscene);
    else target.draw(level);
  }
  else {
    for (int i = 0; i < 25; i++) {
      target.draw(nodeGraphics[i]);
    }
    target.draw(tempLabel);
    target.draw(selectorGraphic);
    target.draw(fadeRect);
  }
}
