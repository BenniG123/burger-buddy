#include <systemc.h>
#include "double_handshake.h"
#include "SupplyTracker.h"

using namespace std;

void SupplyTracker::main() {
	
	Meal requestedMeal;
	Meal sentMeal;

	Meal storedMeal;
	
	while (1) {
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
