#include "Controller.h"

Controller::Controller(Model* m, View* v) {
  model = m;
  view = v;
  active = true;

  std::string temp;
  for (int i = 0; i < 16; i++) {
    temp = model->getString();
    if (temp != "") view->setSound(i, temp);
  }

  view->addString(model->getString());
}

bool Controller::isActive() { return active; }

void Controller::setView(View* v) { view = v; }

void Controller::setModel(Model* m) { model = m; }

void Controller::handleKey(KeyClicks keyInfo) {
  if (!active) return;
  if (keyInfo.getHit(8)) { //replace later with "anyKey" function
    if (view->isDone()) {
      std::string temp;
      do { temp = model->getString(); } while (temp[0] == '#');
      if(temp == "////") active = false;
      else view->addString(temp);
    }
    else view->finish();
  }
}
