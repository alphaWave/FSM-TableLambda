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
        []() {
            myValve.setLed("white blinking");
            myValve.close();
        },
        closingState},
    {closingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evClosed == e; },
        []() {
            myValve.setLed("white static");
        },
        closedState},
    {closingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evBlocked == e; },
        []() {
            myValve.setLed("red");
            myValve.setCurrent(0);
        },
        blockedState},
    {closedState,
        [](ValveCtrl::Event e) { return ValveCtrl::evOpen == e; },
        []() {
            myValve.setLed("green blinking");
            myValve.open();
        },
        openingState},
    {openingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evOpen == e; },
        []() {
            myValve.setLed("green");
        },
        openState},
    {openingState,
        [](ValveCtrl::Event e) { return ValveCtrl::evBlocked == e; },
        []() {
            myValve.setLed("red");
            myValve.setCurrent(0);
        },
        blockedState},
    {blockedState,
        [](ValveCtrl::Event e) { return ValveCtrl::evOpen == e; },
        []() {
            myValve.unblock();
            myValve.setCurrent(1);
            myValve.setLed("green");
        },
        openState}
};

void ValveCtrl::process(Event e) // excecution engine
{
    for (int i = 0; i < sizeof(fsm)/sizeof(Transition); ++i)
    {
        if (fsm[i].currentState == currentState &&
            (fsm[i].checker)(e))
        {
            (fsm[i].action)();
            currentState = fsm[i].nextState;
            break;
        }
    }
}
