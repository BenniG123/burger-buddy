#include <systemc.h>
#include "double_handshake.h"
#include "SupplyTracker.h"

using namespace std;

void SupplyTracker::processOrderRequest() {
	
	Meal requestedMeal;
	Meal sentMeal;
	
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
			int amount;
			this->fromDrinkMaker->read(amount);
			storedMeal.numDrinks -= amount;
			this->toDrinkMaker->write(amount);
		}
		else if (this->fromBurgerMaker->checkValid()) {
			cout << "Burger Request" << endl;
                        int amount;
                        this->fromBurgerMaker->read(amount);
			storedMeal.numBurgers -= amount;
                        this->toBurgerMaker->write(amount);
		}
		else if (this->fromFryMaker->checkValid()) {
			cout << "Fry Request" << endl;
                        int amount;
                        this->fromFryMaker->read(amount);
                        storedMeal.numFries -= amount;
                        this->toFryMaker->write(amount);
		}
 	}
}
