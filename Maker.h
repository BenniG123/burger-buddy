#ifndef MAKER_H
#define MAKER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"


/*

Steps:
1. Wait for Meal Combiner to issue an order
2. Request ingredients from Supply Tracker
3. Wait for Supply Tracker to respond with a number of ingredients
4. Keep making meal components until the order is filled (wait/sleep in between each one)
   a. Insert finished meal components into queue/semaphore

*/

class Maker : public sc_module {

	public:
    	// Inputs
		sc_port< dh_read_if<int> > fromMealCombiner;
		sc_port< dh_read_if<int> > fromSupplyTracker;

    	// Outputs
    	sc_port< sc_semaphore_if > toMealCombiner;

        sc_port< dh_write_if<int> > toSupplyTracker;

        void processCombinerRequest();
		
		SC_HAS_PROCESS(Maker);
		
		Maker(sc_module_name nm) : sc_module(nm) {SC_THREAD(processCombinerRequest)}

};

#endif
