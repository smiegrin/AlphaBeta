#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window.hpp>
#include "View.h"
#include "Model.h"
#include "KeyClicks.h"

class Controller {
private:
  View* view;
  Model* model;
  bool active;
public:
  Controller(Model*, View*);
  bool isActive();
  void setView(View*);
  void setModel(Model*);

  void handleKey(KeyClicks);
};

#endif
