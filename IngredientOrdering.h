#ifndef INGREDIENT_ORDERING_H
#define INGREDIENT_ORDERING_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class IngredientOrdering : public sc_module {

	public:
        	// Inputs
		sc_port< dh_read_if<Meal> > fromSupplyTracker;
        	sc_port< dh_read_if<MoneyTransaction> > fromMoneyManager;

        	// Outputs
        	sc_port< dh_write_if<MoneyTransaction> > toMoneyManager;
		sc_port< dh_write_if<Meal> > toSupplyTracker;
		
		SC_HAS_PROCESS(IngredientOrdering);
		
		IngredientOrdering(sc_module_name nm) : sc_module(nm) {SC_THREAD(main)}

                void main();

};

#endif
