#ifndef SUPPLY_TRACKER_H
#define SUPPLY_TRACKER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class SupplyTracker : public sc_module {

	public:
        	// Inputs
        	sc_port< dh_read_if<Meal> > fromOrderWindow;
		sc_port< dh_read_if<Meal> > fromIngredientOrdering;

		sc_port< dh_read_if<int> > fromBurgerMaker;
		sc_port< dh_read_if<int> > fromFryMaker;
		sc_port< dh_read_if<int> > fromDrinkMaker;

        	// Outputs
        	sc_port< dh_write_if<bool> > toOrderWindow;
		
		sc_port< dh_read_if<int> > toBurgerMaker;
                sc_port< dh_read_if<int> > toFryMaker;
                sc_port< dh_read_if<int> > toDrinkMaker;

		sc_port< dh_read_if<Meal> > toIngredientOrdering;

		
		SC_HAS_PROCESS(SupplyTracker);
		
		SupplyTracker(sc_module_name nm) : sc_module(nm) {SC_THREAD(main)}

                void main();

};

#endif
