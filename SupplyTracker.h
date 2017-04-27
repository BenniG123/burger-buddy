#ifndef SUPPLY_TRACKER_H
#define SUPPLY_TRACKER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class SupplyTracker : public sc_module {
	private:
		Meal storedMeal;

	public:
        	// Inputs
        	sc_port< dh_read_if<Meal> > fromOrderWindow;
		sc_port< dh_read_if<Meal> > fromIngredientOrdering;

		sc_port< dh_read_if<int> > fromBurgerMaker;
		sc_port< dh_read_if<int> > fromFryMaker;
		sc_port< dh_read_if<int> > fromDrinkMaker;

		sc_event burgerEvent;
		sc_event drinkEvent;
		sc_event fryEvent;

        	// Outputs
        	sc_port< dh_write_if<bool> > toOrderWindow;
		
		sc_port< dh_write_if<int> > toBurgerMaker;
                sc_port< dh_write_if<int> > toFryMaker;
                sc_port< dh_write_if<int> > toDrinkMaker;

		sc_port< dh_write_if<Meal> > toIngredientOrdering;

		
		SC_HAS_PROCESS(SupplyTracker);
		
		SupplyTracker(sc_module_name nm) : sc_module(nm) {
			SC_THREAD(processOrderRequest);
			SC_THREAD(processMakerRequest);
			}

                void processOrderRequest();
		void processMakerRequest();

};

#endif
