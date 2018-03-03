#include "Model.h"
#include <sstream>
#include <iostream>

Model::Model() { std::cout<< "whatdapoop?\n"; };

Model::Model(std::string fileName) {
    file.open(fileName.c_str());
}

Model::~Model() {
    file.close();
}

std::string Model::getString() {
  std::getline(file, phrase);
  return phrase;
}

void Model::advance() { std::getline(file, phrase); }
