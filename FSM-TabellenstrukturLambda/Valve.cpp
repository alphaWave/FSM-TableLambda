//
// Valve.cpp
//
// implements an HV valve
//
// (C) R. Bonderer, HSR Hochschule Rapperswil, Nov. 2014
//

#include <iostream>
#include "Valve.h"
using namespace std;

Valve::Valve(int theCurrent):
  current(theCurrent)
{
}

void Valve::open()
{
  cout << "Valve command: open" << endl;
}

void Valve::close()
{
  cout << "Valve command: close" << endl;
}

void Valve::setLed(const char* text)
{
  cout << "Valve: " << text << endl;
}

void Valve::setCurrent(int c)
{
  current = c;
  cout << "Valve current = " << current << endl;
}
 void Valve::unblock()
{
  cout << "Unblock valve" << endl;
  cout << "Move valve manually to open position... " << endl << "...confirmed" << endl;
}



