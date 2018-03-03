#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>

class View : public sf::Drawable {
private:
  int anim;
  int speed;
  int pos;
  int offset;
  int soundNum;
  int faceNum1;
  int faceNum2;
  int faceNum3;
  bool done;
  std::string incoming;
  std::string displayed;
  sf::Color fontColor;
  sf::IntRect bounds;
  sf::RenderTexture display;
  sf::Sound sound;
  sf::SoundBuffer* soundList;
  sf::Texture faceSheet;
  sf::Texture fontSheet;
  sf::Texture styleSheet;

  void typeChar(char);

public:
  View();

  void finish();
  void addString(std::string);
  void setSound(int, std::string);
  void setSpeed(int);
  void setBounds(sf::IntRect);
  void setTextTexture(sf::Texture);
  void setFaceTexture(sf::Texture);
  void setBorderStyle(sf::Texture);
  bool isDone();

  void update();
  void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
