#ifndef MEAL_COMBINER_H
#define MEAL_COMBINER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class MealCombiner : public sc_module {

	public:
        	// Inputs
        	sc_port< dh_read_if<Meal> > fromOrderWindow;

		//sc_port< sc_semaphore_if > fromBurgerMaker;
		//sc_port< sc_semaphore_if > fromFryMaker;
		//sc_port< sc_semaphore_if > fromDrinkMaker;

        	// Outputs
        //	sc_port< dh_write_if<Meal> > toDeliveryWindow;
		
		//sc_port< dh_read_if<int> > toBurgerMaker;
          //      sc_port< dh_read_if<int> > toFryMaker;
          //      sc_port< dh_read_if<int> > toDrinkMaker;
		
                void main();

		SC_HAS_PROCESS(MealCombiner);
		
		void readFromOrderWindow() { 

			while(true) {
				wait(fromOrderWindow->data_ready_event());
				cout << "MealCombiner tried to read OrderWindow!" << endl;
				Meal m;
				fromOrderWindow->read(m);
				cout << m;
			}
		}

		MealCombiner(sc_module_name nm) : sc_module(nm) {
			SC_THREAD(readFromOrderWindow);
		}
};

#endif
