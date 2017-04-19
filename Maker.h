#ifndef MAKER_H
#define MAKER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class Maker : public sc_module {

	public:
        	// Inputs
		sc_port< dh_read_if<int> > fromMealCombiner;
		sc_port< dh_read_if<int> > fromSupplyTracker;

        	// Outputs
        	sc_port< sc_semaphore_if > toMealCombiner;

                sc_port< dh_read_if<int> > toSupplyTracker;

                void main();
		
		SC_HAS_PROCESS(Maker);
		
		Maker(sc_module_name nm) : sc_module(nm) {SC_THREAD(main)}

};

#endif
