#ifndef DELIVERY_WINDOW_H
#define DELIVERY_WINDOW_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"
#include <iostream>
using namespace std;

class DeliveryWindow : public sc_module {

	public:
    	// Inputs
    	sc_port< dh_read_if<Meal> > fromMealCombiner;

    	// Outputs
    	// none

        void deliverOrder() {
        	while(true) {
        		wait(this->fromMealCombiner->data_ready_event());
        		Meal deliveredMeal;
        		this->fromMealCombiner->read(deliveredMeal);
        		cout << "Order Up!: " << endl << deliveredMeal;
        	}
        }
		
		SC_HAS_PROCESS(DeliveryWindow);
		
		DeliveryWindow(sc_module_name nm) : sc_module(nm) {SC_THREAD(deliverOrder)}

};

#endif
