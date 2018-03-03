#include "View.h"
//#include "ResourceManager.h"

int parseHex(char c) {
  switch (c) {
    case '0':
      return 0;
      break;
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    case 'a':
    case 'A':
      return 10;
      break;
    case 'b':
    case 'B':
      return 11;
      break;
    case 'c':
    case 'C':
      return 12;
      break;
    case 'd':
    case 'D':
      return 13;
      break;
    case 'e':
    case 'E':
      return 14;
      break;
    case 'f':
    case 'F':
      return 15;
      break;
    default:
      return 0;
      break;
  }
}

View::View() {
  display.create(800,800);
  display.clear(sf::Color::Transparent);

  pos = 0;
  offset = 0;
  soundNum = 0;
  faceNum1 = 0;
  faceNum2 = 0;
  faceNum3 = 0;

  soundList = new sf::SoundBuffer[16];

  fontColor = sf::Color::White;
}

void View::typeChar(char c) {
  sf::Sprite typeHead(fontSheet);
  typeHead.setColor(fontColor);
  typeHead.setTextureRect(sf::Rect<int>(c%16*8,c/16*8,8,8));
  typeHead.setPosition(8*(pos+offset)%(bounds.width),8*(pos+offset)/(bounds.width)*8);//here
  display.draw(typeHead);
  display.display();
}

void View::finish() {
  while(!done) update();
}

void View::addString(std::string newString) {
  //string interpreting
  int i = 0;
  int width = (bounds.width)/8;//hereish
  int bulk = (offset+pos != 0) ? (offset+pos)%width : 0;

  while (i < newString.length()) {
    switch (newString[i]) {
    case '\\':
      if (newString[i+1] == 'n') bulk = 0;
      i += 2;
      break;
    case '%':
      i += 5;
      break;
    default:
      i++;
      bulk++;
      break;
    }
    if (bulk == width) {
      if (newString[i] == ' ') newString.erase(i, 1);
      else {
        while (newString[i] != ' ' && i > 0) {
          i--;
          bulk++;
        }
        if (i != 0) {
          newString.insert(i, "\\n");
          newString.erase(i+2,1);
        }
        //std::cout << newString << std::endl;
      }
      bulk -= width;
    }
  }
  if (!done && incoming != "") while (incoming[pos] != 0) {
    typeChar(incoming[pos]);
    //std::cout << incoming[pos];
    pos++;
  }
  displayed += incoming;
  incoming = newString;
  offset += pos;
  pos = 0;
  done = false;
}

void View::setSound(int i, std::string filename) {
  if (i > 15) return;
  soundList[i].loadFromFile(filename);
}

void View::setSpeed(int s) { speed = s; }

void View::setBounds(sf::IntRect r) {
  //r.width -= (r.width-160)%8;
  bounds = r;
}

void View::setTextTexture(sf::Texture t) { fontSheet = t; }

void View::setBorderStyle(sf::Texture t) { styleSheet = t; }

void View::setFaceTexture(sf::Texture t) { faceSheet = t; }

bool View::isDone() { return done; }

void View::update() {
  if (incoming[pos] == 0 && !done) {
    done = true;
  }
  else if (anim >= 0 && !done) {
    switch (incoming[pos]) {
    case '\\':
      switch (incoming[pos + 1]) {
        case 'n':
          offset += (bounds.width)/8 - (pos+offset)%((bounds.width)/8) - 1;//here
          break;
        //typable escape characters
        case '%':
        case '#':
          sound.setBuffer(soundList[soundNum]);
          sound.play();
          typeChar(incoming[pos+1]);
          break;
        case 'd'://clear dialogue
          display.clear(sf::Color::Transparent);
          //redraw borders and faces and the like.
          offset = -pos - 1;
          break;
      }
      pos++;
      offset--;
      break;
    case '%':
      switch (incoming[pos + 1]) {
        case 'f'://change face
          //std::cout << "Facecode Detected:" << incoming[pos+2] << incoming[pos+3] << incoming[pos+4] << "\n";
          if (parseHex(incoming[pos+3]) == 0) faceNum1 = parseHex(incoming[pos+4]);
          if (parseHex(incoming[pos+3]) == 1) faceNum2 = parseHex(incoming[pos+4]);
          if (parseHex(incoming[pos+3]) == 2) faceNum3 = parseHex(incoming[pos+4]);
          break;
        case 'c'://change color
          fontColor = sf::Color(
            parseHex(incoming[pos+2])*17,
            parseHex(incoming[pos+3])*17,
            parseHex(incoming[pos+4])*17
          );
          break;
        case 'w'://wait n frames extra
          anim -= parseHex(incoming[pos+2])*(16*16) + parseHex(incoming[pos+3])*16 + parseHex(incoming[pos+4]);
          break;
        case 's'://change sound used
          soundNum = parseHex(incoming[pos+4]);
          break;
      }
      pos += 4;
      offset -= 5;
      break;
    case ' ':
      typeChar(incoming[pos]);
      //std::cout << incoming[pos];
      break;
    default:
      sound.setBuffer(soundList[soundNum]);
      sound.play();
      typeChar(incoming[pos]);
      //std::cout << incoming[pos];
    }
    pos++;
    anim -= speed;
  }
  else anim++;
  if (anim > 10) anim = 10;
}

void View::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite textTemp(display.getTexture());
  textTemp.setPosition(bounds.left, bounds.top);
  target.draw(textTemp);

  sf::Sprite face1(faceSheet, sf::Rect<int>(faceNum1%4*160,0,160,160));
  face1.setPosition(24,456);
  target.draw(face1);

  sf::Sprite face2(faceSheet, sf::Rect<int>(faceNum2%4*160,160,160,160));
  face2.setPosition(240,456);
  target.draw(face2);

  sf::Sprite face3(faceSheet, sf::Rect<int>(faceNum3%4*160,320,160,160));
  face3.setPosition(456,456);
  target.draw(face3);
}
