#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class OrderWindow : public sc_module {

	// Inputs
	double_handshake<int> fromMealCombiner;
	double_handshake<MoneyTransaction> fromMoneyManager;
	double_handshake<bool> fromSupplyTracker;

	// Outputs
	double_handshake<Meal> toMealCombiner;
	double_handshake<MoneyTransaction> toMoneyManager;
	double_handshake<Meal> toSupplyTracker;

};
