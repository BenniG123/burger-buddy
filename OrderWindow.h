#ifndef ORDER_WINDOW_H
#define ORDER_WINDOW_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class OrderWindow : public sc_module {

	public:
        	// Inputs
        	sc_port< dh_read_if<Meal> > fromInputWrapper;
		sc_port< dh_read_if<int> > fromMealCombiner;

		sc_port< dh_read_if<MoneyTransaction> > fromMoneyManager;
		sc_port< dh_read_if<bool> > fromSupplyTracker;

        	// Outputs
        	sc_port< dh_write_if<Meal> > toMealCombiner;
		sc_port< dh_read_if<MoneyTransaction> > toMoneyManager;
                sc_port< dh_read_if<int> > toSupplyTracker;

                void main();
		
		SC_HAS_PROCESS(OrderWindow);
		
		OrderWindow(sc_module_name nm) : sc_module(nm) {SC_THREAD(main)}


};

#endif
