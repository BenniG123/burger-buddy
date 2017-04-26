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
		sc_port< dh_write_if<MoneyTransaction> > toMoneyManager;
                sc_port< dh_write_if<Meal> > toSupplyTracker;

       void main();

       //         void test_write() {
       //         	Meal m1 = {1,2,3,4};
       //         	toMealCombiner->write(m1); 
       //         	Meal m2 = {5,6,7,8};
       //         	toMealCombiner->write(m2);
       //         }
		
		SC_HAS_PROCESS(OrderWindow);

		OrderWindow(sc_module_name nm) : sc_module(nm) {
			SC_THREAD(main);
		}


};

#endif
