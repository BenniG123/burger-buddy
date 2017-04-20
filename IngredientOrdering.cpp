#include <systemc.h>
#include "double_handshake.h"
#include "IngredientOrdering.h"

void IngredientOrdering::main() {
	
	Meal requestedMeal;
	MoneyTransaction requestedMoney;
	
	while (1) {
		// Wait for Supply Tracker to make a food order request
		fromSupplyTracker.read(requestedMeal);

		requestedMoney.amt = 0;
		requestedMoney.amt += requestedMeal.numBurgers * BURGER_COST;
		requestedMoney.amt += requestedMeal.numFries * FRY_COST;
		requestedMoney.amt += requestedMeal.numDrinks * DRINK_COST;

		// Try to withdraw that much from the money manager to spend
		// on the order
		toMoneyManager.write(requestedMoney);

		// If it's enough, order the quantity and pass the this back to
		// Supply Tracker

		// If it's not enough, send an error back to the Supply Tracker
	
}
