//
// ValveCtrl.cpp
//
// implements the Finite State Machine (FSM) of a HV valve (table version)
//
// (C) R. Bonderer, HSR Hochschule Rapperswil, Oct. 2015
//

#include <iostream>
#include "ValveCtrl.h"
using namespace std;


ValveCtrl::ValveCtrl(): currentState(openState), myValve(1)
{
}

const ValveCtrl::Transition ValveCtrl::fsm[] =
{
    {openState,
        [](ValveCtrl::Event e) { return ValveCtrl::evClose == e; },
        &ValveCtrl::actionOpenClosing,
        closingState},
    {closingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evClosed == e; },
        &ValveCtrl::actionClosingClosed,
        closedState},
    {closingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evBlocked == e; },
        &ValveCtrl::actionClosingBlocked,
        blockedState},
    {closedState,
        [](ValveCtrl::Event e) { return ValveCtrl::evOpen == e; },
        &ValveCtrl::actionClosedOpening,
        openingState},
    {openingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evOpen == e; },
        &ValveCtrl::actionOpeningOpen,
        openState},
    {openingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evBlocked == e; },
        &ValveCtrl::actionOpeningBlocked,
        blockedState},
    {blockedState,
        [](ValveCtrl::Event e) { return ValveCtrl::evOpen == e; },
        &ValveCtrl::actionBlockedOpen,
        openState}
};

void ValveCtrl::process(Event e) // excecution engine
{
    for (int i = 0; i < sizeof(fsm)/sizeof(Transition); ++i)
    {
        if (fsm[i].currentState == currentState &&
            (fsm[i].checker)(e))
        {
            (this->*fsm[i].action)();
            currentState = fsm[i].nextState;
            break;
        }
    }
}

void ValveCtrl::actionOpenClosing()
{
    myValve.setLed("white blinking");
    myValve.close();
}

void ValveCtrl::actionClosingClosed()
{
    myValve.setLed("white static");
}

void ValveCtrl::actionClosingBlocked()
{
    myValve.setLed("red");
    myValve.setCurrent(0);
}

void ValveCtrl::actionClosedOpening()
{
    myValve.setLed("green blinking");
    myValve.open();
}

void ValveCtrl::actionOpeningOpen()
{
    myValve.setLed("green");
}

void ValveCtrl::actionOpeningBlocked()
{
    myValve.setLed("red");
    myValve.setCurrent(0);
}

void ValveCtrl::actionBlockedOpen()
{
    myValve.unblock();
    myValve.setCurrent(1);
    myValve.setLed("green");
}

void ValveCtrl::actionDoNothing()
{
}
