#include "cart.h"

#include <iostream>

#include <cmath>

int count = 1;

// callback every 100ms
class DisplayAngleCallback: public Cart::CompAngleCallback {
  public: int a = -87;
  int b = -51;
  int c = -91;
  float angle_updated;

  virtual void computeAngle(Cart & cart) {
    float d_a = pow(20, (a + 52));
    float d_b = pow(20, (b + 52));
    float d_c = pow(20, (c + 52));

    angle_updated = acos((pow(d_a, 2) + pow(d_b, 2) - pow(d_c, 2)) / (2 * d_a * d_b));

    std::cout << "the updated angle is" << angle_updated;
  }
};

int main(int, char ** ) {

  Cart cart;
  DisplayAngleCallback displayAngleCallback;
  cart.regCompAngleCallback( & displayAngleCallback);
  cart.start();
  while (count) {
    int ch = getchar();
    switch (ch) {
    case 27:
      count = 0;
      break;

    default:
      break;
    }
  }
  cart.stop();
}
