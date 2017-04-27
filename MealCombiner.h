#ifndef MEAL_COMBINER_H
#define MEAL_COMBINER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

/*

Steps:
1. Wait for an order to come in from the Order Window
2. Send components of the order to the respective makers
3. Attempt to pull number of ingredients off of the queues
   a. Block until we get all of them
4. Once we have all of the order, send it to the delivery window

*/

class MealCombiner : public sc_module {

	public:
    	// Inputs
    	sc_port< dh_read_if<Meal> > fromOrderWindow;

		sc_port< sc_semaphore_if > fromBurgerMaker;
		sc_port< sc_semaphore_if > fromFryMaker;
		sc_port< sc_semaphore_if > fromDrinkMaker;

    	// Outputs
        sc_port< dh_write_if<Meal> > toDeliveryWindow;
		
		sc_port< dh_write_if<int> > toBurgerMaker;
        sc_port< dh_write_if<int> > toFryMaker;
        sc_port< dh_write_if<int> > toDrinkMaker;

		SC_HAS_PROCESS(MealCombiner);
		
		void processMeals();

		MealCombiner(sc_module_name nm) : sc_module(nm) {
			SC_THREAD(processMeals);
		}
};

#endif
