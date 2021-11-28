/* Original source code from Walter Savitch, Absolute C++
 * derived class implementation 
 */

#include <iostream>
#include "pfarrayd.h"
#include "pfarraydbak.h"

using std::cout;
using std::endl;

PFArrayDBak::PFArrayDBak() : PFArrayD(), usedB(0) {
  b = new double[capacity];
}

PFArrayDBak::PFArrayDBak(int capacityValue) : PFArrayD(capacityValue), usedB(0) {
  b = new double[capacity];
}

PFArrayDBak::PFArrayDBak(const PFArrayDBak& object) : PFArrayD(object) {
  b = new double[capacity];
  usedB = object.usedB;
  for (int i = 0; i < usedB; i++) {
    b[i] = object.a[i];
  }

}

void PFArrayDBak::backup() {
  usedB = used;
  for(int i=0; i<usedB; i++) {
    b[i] = a[i];
  }
}

void PFArrayDBak::restore() {
  used = usedB;
  for(int i=0; i<used; i++) {
    a[i] = b[i];
  }
}

PFArrayDBak& PFArrayDBak::operator =(const PFArrayDBak& rightSide) {
  int oldCapacity = capacity;
  PFArrayD::operator= (rightSide);

  if (oldCapacity != capacity) {
    delete [] b;
    b = new double[rightSide.capacity];
  }

  usedB = rightSide.usedB;
  for(int i=0; i<usedB; i++) {
    b[i] = rightSide.b[i];
  }

  return *this;
}

PFArrayDBak::~PFArrayDBak() {
  delete [] b;
  // base class destructor is automatically invoked
}