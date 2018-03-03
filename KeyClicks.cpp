#include "KeyClicks.h"

KeyClicks::KeyClicks(int numKeys) {
  hit = new bool[numKeys];
  down = new bool[numKeys];
  up = new bool[numKeys];
  keyLength = numKeys;
}

KeyClicks::~KeyClicks() {
  //delete hit;
  //delete down;
  //delete up;
}

bool KeyClicks::getHit(int keyNum) {
  if (keyNum < 0 || keyNum > keyLength) return false;
  else return hit[keyNum];
}

bool KeyClicks::getDown(int keyNum) {
  if (keyNum < 0 || keyNum > keyLength) return false;
  else return down[keyNum];
}

bool KeyClicks::getUp(int keyNum) {
  if (keyNum < 0 || keyNum > keyLength) return false;
  else return up[keyNum];
}

void KeyClicks::hitKey(int keyNum) {
  if (keyNum < 0 || keyNum > keyLength) return;
  else {
    hit[keyNum] = true;
    down[keyNum] = true;
  }
}

void KeyClicks::upKey(int keyNum) {
  if (keyNum < 0 || keyNum > keyLength) return;
  else {
    down[keyNum] = false;
    up[keyNum] = true;
  }
}

void KeyClicks::timeStep() {
  for (int i = 0; i < keyLength; i++) {
    up[i] = false;
    hit[i] = false;
  }
}
