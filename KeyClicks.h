#ifndef KEYCLICKS_H
#define KEYCLICKS_H

class KeyClicks {
  bool* hit;
  bool* down;
  bool* up;
  int keyLength;

public:

  KeyClicks(int);
  ~KeyClicks();

  bool getHit(int keyNum);
  bool getDown(int keyNum);
  bool getUp(int keyNum);

  void hitKey(int keyNum);
  void upKey(int keyNum);
  void timeStep();
};

#endif
