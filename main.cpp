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
	// double_handshake<string> dhSTR("DH_STR");
	// producer<string> ps("PRODUCER_STR");
	// consumer<string> cs("CONSUMER_STR");
	// ps.out(dhSTR);
	// cs.in(dhSTR);

	double_handshake<MoneyTransaction> fMM("fMM");
	double_handshake<Meal> fST("fST");
	double_handshake<MoneyTransaction> tMM("tMM");
	double_handshake<Meal> tST("tST");

	IngredientOrdering ingredientOrdering("iO");
	ingredientOrdering.fromMoneyManager(fMM);
	ingredientOrdering.fromSupplyTracker(fST);
	ingredientOrdering.toMoneyManager(tMM);
	ingredientOrdering.toSupplyTracker(tST);

	double_handshake<Meal> fOW("fOW");
	double_handshake<bool> tOW("tOW");
	double_handshake<int> fBM("fBM");
	double_handshake<int> tBM("tBM");
	double_handshake<int> fDM("fDM");
	double_handshake<int> tDM("tDM");
	double_handshake<int> fFM("fFM");
	double_handshake<int> tFM("tFM");

	SupplyTracker supplyTracker("sT");
	supplyTracker.toIngredientOrdering(fST);
	supplyTracker.fromIngredientOrdering(tST);
	supplyTracker.toOrderWindow(tOW);
	supplyTracker.fromOrderWindow(fOW);
	supplyTracker.fromBurgerMaker(fBM);
	supplyTracker.toBurgerMaker(tBM);
	supplyTracker.fromDrinkMaker(fDM);
	supplyTracker.toDrinkMaker(tDM);
	supplyTracker.fromFryMaker(fFM);
	supplyTracker.toFryMaker(tFM);

	supplyTracker.burgerEvent = fBM.write_event;

	sc_start();

	return 0;
}
