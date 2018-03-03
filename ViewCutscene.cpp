#include "ViewCutscene.h"


sf::Vector2f operator*(float f, sf::Vector2f v) {
  return sf::Vector2f(f*v.x, f*v.y);
}


ViewCutscene::ViewCutscene():
  view(new View()),
  model(new Model("Scripts/chapter1.dlg")),
  controller(new Controller(model, view)),
  phaseCounter(0),
  textBox(sf::Vector2f(0,0)),
  rightFaceBox(sf::Vector2f(0,0)),
  middleFaceBox(sf::Vector2f(0,0)),
  leftFaceBox(sf::Vector2f(0,0))
  {

  textBox.setFillColor(sf::Color::Transparent);
  textBox.setOutlineThickness(8);
  textBox.setOutlineColor(sf::Color::White);

  rightFaceBox.setFillColor(sf::Color::Transparent);
  rightFaceBox.setOutlineThickness(8);
  rightFaceBox.setOutlineColor(sf::Color::White);

  middleFaceBox.setFillColor(sf::Color::Transparent);
  middleFaceBox.setOutlineThickness(8);
  middleFaceBox.setOutlineColor(sf::Color::White);

  leftFaceBox.setFillColor(sf::Color::Transparent);
  leftFaceBox.setOutlineThickness(8);
  leftFaceBox.setOutlineColor(sf::Color::White);

  //initialize textures
  facePlates.loadFromFile("Graphics/facePlates.png");
  pixelFont.loadFromFile("Graphics/tempfont.png");

  //initialize MVC Dialogue
  view->setFaceTexture(facePlates);
  view->setTextTexture(pixelFont);
  view->setBounds(sf::IntRect(32,32,576,384));
  view->setSpeed(1);



}

ViewCutscene::Result ViewCutscene::update(KeyClicks keyInfo) {
  /* Phase Table
  0 - 14    open squares virtically
  15 - 29   open sqares horizontally
  30        operate dialogue
  31 - 45   close Squares horizontally
  46 - 60   close Squares vertically
  */

  Result endResult = CONTINUING;

  sf::Vector2f textBoxCenter(320, 224);
  sf::Vector2f leftFaceBoxCenter(104, 536);
  sf::Vector2f middleFaceBoxCenter(320, 536);
  sf::Vector2f rightFaceBoxCenter(536, 536);

  if (phaseCounter >= 0 && phaseCounter < 15) { //open vertically
    float percent = phaseCounter/15.0;
    textBox.setPosition(textBoxCenter - .5*percent*sf::Vector2f(592,0));
    textBox.setSize(percent*sf::Vector2f(592,0));
    rightFaceBox.setPosition(rightFaceBoxCenter - .5*percent*sf::Vector2f(160,0));
    rightFaceBox.setSize(percent*sf::Vector2f(160,0));
    middleFaceBox.setPosition(middleFaceBoxCenter - .5*percent*sf::Vector2f(160,0));
    middleFaceBox.setSize(percent*sf::Vector2f(160,0));
    leftFaceBox.setPosition(leftFaceBoxCenter - .5*percent*sf::Vector2f(160,0));
    leftFaceBox.setSize(percent*sf::Vector2f(160,0));
    phaseCounter++;
  }

  else if (phaseCounter >=15 && phaseCounter < 30) { //open horizontally
    float percent = (phaseCounter-15)/15.0;
    textBox.setPosition(textBoxCenter - .5*sf::Vector2f(592,percent*400));
    textBox.setSize(sf::Vector2f(592,percent*400));
    rightFaceBox.setPosition(rightFaceBoxCenter - .5*sf::Vector2f(160,percent*160));
    rightFaceBox.setSize(sf::Vector2f(160,percent*160));
    middleFaceBox.setPosition(middleFaceBoxCenter - .5*sf::Vector2f(160,percent*160));
    middleFaceBox.setSize(sf::Vector2f(160,percent*160));
    leftFaceBox.setPosition(leftFaceBoxCenter - .5*sf::Vector2f(160,percent*160));
    leftFaceBox.setSize(sf::Vector2f(160,percent*160));
    phaseCounter++;
  }

  else if (phaseCounter == 30) { //operate dialogue
    textBox.setPosition(textBoxCenter - .5*sf::Vector2f(592,400));
    textBox.setSize(sf::Vector2f(592,400));
    rightFaceBox.setPosition(rightFaceBoxCenter - .5*sf::Vector2f(160,160));
    rightFaceBox.setSize(sf::Vector2f(160,160));
    middleFaceBox.setPosition(middleFaceBoxCenter - .5*sf::Vector2f(160,160));
    middleFaceBox.setSize(sf::Vector2f(160,160));
    leftFaceBox.setPosition(leftFaceBoxCenter - .5*sf::Vector2f(160,160));
    leftFaceBox.setSize(sf::Vector2f(160,160));

    if (keyInfo.getHit(8)) {
      if (!controller->isActive()) phaseCounter++;
      else controller->handleKey(keyInfo);
    }
    else if(keyInfo.getHit(9)) phaseCounter++;

    view->update();
  }

  else if (phaseCounter > 30 && phaseCounter <= 45) { //close horizontally
    float percent = (45-phaseCounter)/15.0;
    textBox.setPosition(textBoxCenter - .5*sf::Vector2f(592,percent*400));
    textBox.setSize(sf::Vector2f(592,percent*400));
    rightFaceBox.setPosition(rightFaceBoxCenter - .5*sf::Vector2f(160,percent*160));
    rightFaceBox.setSize(sf::Vector2f(160,percent*160));
    middleFaceBox.setPosition(middleFaceBoxCenter - .5*sf::Vector2f(160,percent*160));
    middleFaceBox.setSize(sf::Vector2f(160,percent*160));
    leftFaceBox.setPosition(leftFaceBoxCenter - .5*sf::Vector2f(160,percent*160));
    leftFaceBox.setSize(sf::Vector2f(160,percent*160));
    phaseCounter++;
  }

  else if (phaseCounter > 45 && phaseCounter < 60) { //close vertically
    float percent = (60-phaseCounter)/15.0;
    textBox.setPosition(textBoxCenter - .5*percent*sf::Vector2f(592,0));
    textBox.setSize(percent*sf::Vector2f(592,0));
    rightFaceBox.setPosition(rightFaceBoxCenter - .5*percent*sf::Vector2f(160,0));
    rightFaceBox.setSize(percent*sf::Vector2f(160,0));
    middleFaceBox.setPosition(middleFaceBoxCenter - .5*percent*sf::Vector2f(160,0));
    middleFaceBox.setSize(percent*sf::Vector2f(160,0));
    leftFaceBox.setPosition(leftFaceBoxCenter - .5*percent*sf::Vector2f(160,0));
    leftFaceBox.setSize(percent*sf::Vector2f(160,0));
    phaseCounter++;
  }

  else if (phaseCounter == 60) { //return to level select
    endResult = DONE;
    phaseCounter = 0;
  }

  return endResult;
}

void ViewCutscene::readyCutscene(std::string fileName) {
  delete model;
  delete view;
  delete controller;
  model = new Model(fileName);
  view = new View();
  view->setFaceTexture(facePlates);
  view->setTextTexture(pixelFont);
  view->setBounds(sf::IntRect(32,32,576,384));
  view->setSpeed(1);
  controller = new Controller(model, view);
  //controller->setModel(model);
}

void ViewCutscene::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
  target.draw(textBox);
  target.draw(leftFaceBox);
  target.draw(middleFaceBox);
  target.draw(rightFaceBox);
  if (phaseCounter == 30) target.draw(*view);
}
