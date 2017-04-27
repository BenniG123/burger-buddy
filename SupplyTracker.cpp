#include <systemc.h>
#include "double_handshake.h"
#include "SupplyTracker.h"

using namespace std;

void SupplyTracker::processOrderRequest() {
	
	Meal requestedMeal;
	Meal sentMeal;

	Meal storedMeal;
	
	while (true) {
		cout << "Waiting for supply request" << endl;

		// Wait for OrderWindow to make a food order request
		fromOrderWindow->read(requestedMeal);
		
		// If there are sufficient ingredients
		if (requestedMeal.numBurgers <= storedMeal.numBurgers &&
			requestedMeal.numFries <= storedMeal.numFries &&
			requestedMeal.numDrinks <= storedMeal.numDrinks) {
			
			// Send a confirmation to order window
			toOrderWindow->write(true);
		}
		else {
			// Request more supplies
			toIngredientOrdering->write(requestedMeal);
			fromIngredientOrdering->read(sentMeal);
			
			if (sentMeal.numBurgers > -1) {
				// Success
				toOrderWindow->write(true);
			}
			else {
				// Failure
				toOrderWindow->write(false);
			}
		}
	}
}

void SupplyTracker::processMakerRequest() {
 	while (true) {
		// Wait on multiple events
		wait(this->fromDrinkMaker->data_ready_event() | this->fromBurgerMaker->data_ready_event() | this->fromFryMaker->data_ready_event());
		if (this->fromDrinkMaker->checkValid()) {
			cout << "Drink Request" << endl;

		}
		else if (this->fromBurgerMaker->checkValid()) {
			cout << "Burger Request" << endl;

		}
		else if (this->fromFryMaker->checkValid()) {
			cout << "Fry Request" << endl;

		}
 	}
}
