//
//  ValveCtrl.h
//  FSM-Tabellenstruktur
//
//  Created by Dolp Diego on 23.11.21.
//

#ifndef ValveCtrl_h
#define ValveCtrl_h
#include "Valve.h"

class ValveCtrl {
public:
    enum Event
    {
        evOpen,
        evClose,
        evReset,
        evOpened,
        evClosed,
        evBlocked
    };
    
    ValveCtrl();
    void process(Event e);

private:
    enum State
    {
        openState,
        closingState,
        closedState,
        openingState,
        blockedState
    };
    
    State currentState;
    Valve myValve;
    
//    typedef bool (ValveCtrl::*Checker)(Event e); // old version, with function-ptr
    typedef std::function<bool(Event e)> Checker;
//    typedef void (ValveCtrl::*Action)(void);
    typedef std::function<void(void)> Action;
    // 1. The Lambda-version doesn't work because of the fsm-Array being static -> no way to access the dynamic object myValve. Except if myValve were static, which defeats the purpose of having an OO-design.
    // 2. I can't seem to make the std::function version work while keeping the action-functions due to a conversion error.
    
    void actionOpenClosing(void);
    void actionClosingClosed(void);
    void actionClosingBlocked(void);
    void actionClosedOpening(void);
    void actionOpeningOpen(void);
    void actionOpeningBlocked(void);
    void actionBlockedOpen(void);
    void actionDoNothing(void);
    
    struct Transition
    {
        State currentState;
        Checker checker;
        Action action;
        State nextState;
    };
    static const Transition fsm[];
    
};

#endif /* ValveCtrl_h */


