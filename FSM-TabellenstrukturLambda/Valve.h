//
// Valve.h
//
// implements a HV valve
//
// (C) R. Bonderer, HSR Hochschule Rapperswil, Nov. 2014
//

#ifndef VALVE_H__
#define VALVE_H__

class Valve
{
  public:
    Valve(int theCurrent = 0);
      void open();
      void close();
      void setLed(const char* text);
      void setCurrent(int c);
      void unblock();
   private:
     int current;
};

#endif

