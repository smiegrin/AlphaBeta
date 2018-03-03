#ifndef MODEL_H
#define MODEL_H

//#define _GLIBCXX_USE_CXX11_ABI 0
#include <fstream>

class Model {
private:
  std::string phrase;
  std::ifstream file;
public:
  Model();
  Model(std::string);
  ~Model();
  std::string getString();
  void advance();
};

#endif
