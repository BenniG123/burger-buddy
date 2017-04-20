#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"
#include "double_handshake_tb.h"
#include "InputWrapper.h"
#include "OrderWindow.h"
#include "DeliveryWindow.h"
#include "AdminInterface.h"
#include "Maker.h"
#include "MealCombiner.h"
#include "IngredientOrdering.h"
#include "SupplyTracker.h"
#include "MoneyManager.h"

int sc_main(int argc, char* argv[])
{
	// double handshake test bench for string messaging
	double_handshake<string> dhSTR("DH_STR");
	producer<string> ps("PRODUCER_STR");
	consumer<string> cs("CONSUMER_STR");
	ps.out(dhSTR);
	cs.in(dhSTR);

	double_handshake<MoneyTransaction> fMM("a");
	double_handshake<Meal> fST("b");
	double_handshake<MoneyTransaction> tMM("c");
	double_handshake<Meal> tST("d");

	IngredientOrdering ingredientOrdering("e");
	ingredientOrdering.fromMoneyManager(fMM);
	ingredientOrdering.fromSupplyTracker(fST);
	ingredientOrdering.toMoneyManager(tMM);
	ingredientOrdering.toSupplyTracker(tST);

	sc_start();

	return 0;
}
