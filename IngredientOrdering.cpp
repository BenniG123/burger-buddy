#include <systemc.h>
#include "double_handshake.h"
#include "IngredientOrdering.h"

using namespace std;

void IngredientOrdering::main() {
	
	Meal requestedMeal;
	Meal sentMeal;
	MoneyTransaction requestedMoney;
	MoneyTransaction sentMoney;
	
	while (1) {
		cout << "Waiting for ingredient order request" << endl;

		// Wait for Supply Tracker to make a food order request
		fromSupplyTracker->read(requestedMeal);

		requestedMoney.amt = 0;
		requestedMoney.amt += requestedMeal.numBurgers * BURGER_COST;
		requestedMoney.amt += requestedMeal.numFries * FRY_COST;
		requestedMoney.amt += requestedMeal.numDrinks * DRINK_COST;
		requestedMoney.type = WITHDRAW;

		cout << "Requested meal: " << requestedMeal.numBurgers <<
			" Burgers, " << requestedMeal.numFries <<
			" Fries, " << requestedMeal.numDrinks <<
			"Drinks" << endl;

		cout << "Total cost: " << requestedMoney.amt << endl;

		// Try to withdraw that much from the money manager to spend
		// on the order
		toMoneyManager->write(requestedMoney);

		fromMoneyManager->read(sentMoney);

		if (sentMoney.amt == requestedMoney.amt) {
			// If it's enough, order the quantity and pass the this back to
			// Supply Tracker
			sentMeal.numBurgers = requestedMeal.numBurgers;
			sentMeal.numFries = requestedMeal.numFries;
			sentMeal.numDrinks = requestedMeal.numDrinks;

			toSupplyTracker->write(sentMeal);
		} else {
			// If it's not enough, send an error back to the Supply Tracker
			sentMeal.numBurgers = -1;
			// toMoneyManager->write(sentMoney);
			toSupplyTracker->write(sentMeal);
		}
	}
}
