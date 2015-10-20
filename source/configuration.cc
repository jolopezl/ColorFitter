#include "configuration.h"
#include <iostream>

myConfig::myConfig() {
  std::cout << "Configuration created" << std::endl;
}

myConfig::~myConfig() {
  std::cout << "Configuration destroyed" << std::endl;
}

// void myConfig::Update() {
//   std::ostringstream foo;
//   foo << "iFit: energy loss: " << m_energyloss;
//   foo << " He subtraction: " << m_subtraction;
//   foo << " correlation = " << m_correlation;
//   m_comment = foo.str();
// }