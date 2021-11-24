//
// valveTest.cpp
//
// Test program for the Finite State Machine (FSM) of an HV valve
//
// (C) R. Bonderer, HSR Hochschule Rapperswil, Nov. 2010
//

#include <iostream>
#include "ValveCtrl.h"
using namespace std;

int main(void)
{
  char answer;
  ValveCtrl myFsm;
  
  do
  {
    cout << endl << "-------------------------------------------" << endl;
    cout << "    O   Open" << endl;
    cout << "    C   Close" << endl;
    cout << "    R   Reset" << endl << endl;
    cout << "    o   opened" << endl;
    cout << "    c   closed" << endl;
    cout << "    b   blocked" << endl;
    cout << "    q   Quit" << endl;

    cout << endl << "Please press key: ";
    cin >> answer;
    cout << endl;
      
    switch (answer)
    {
      case 'O':
        myFsm.process(ValveCtrl::evOpen);
        break;
      case 'C':
        myFsm.process(ValveCtrl::evClose);
        break;
      case 'R':
        myFsm.process(ValveCtrl::evReset);
        break;
      case 'o':
        myFsm.process(ValveCtrl::evOpened);
        break;
      case 'c':
        myFsm.process(ValveCtrl::evClosed);
        break;
      case 'b':
        myFsm.process(ValveCtrl::evBlocked);
        break;
      default:
        break;
    }
  } while (answer != 'q');
  
  return 0;
}


