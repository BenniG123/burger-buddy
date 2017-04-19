#ifndef DELIVERY_WINDOW_H
#define DELIVERY_WINDOW_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class DeliveryWindow : public sc_module {

	public:
        	// Inputs
        	sc_port< dh_read_if<Meal> > fromMealCombiner;

        	// Outputs

                void main();
		
		SC_HAS_PROCESS(DeliveryWindow);
		
		DeliveryWindow(sc_module_name nm) : sc_module(nm) {SC_THREAD(main)}

};

#endif
