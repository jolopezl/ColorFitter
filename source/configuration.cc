#include "configuration.h"

myConfig::myConfig() {
  std::cout << "Configuration created" << std::endl;
}

myConfig::~myConfig() {
  std::cout << "Configuration destroyed" << std::endl;
}

void myConfig::Update() {
  std::ostringstream foo;
  foo << "iFit Info: Energy Loss: " << m_energyloss;
  foo << " - He subtraction: "      << m_subtraction;
  foo << " with correlation = "     << m_correlation;
  if (m_preh == false) {
    foo << " - Cross Section = "      << m_initial_sigma;
    foo << " mbarn";
    foo << " fixed";
  }
  m_comment = foo.str();
}