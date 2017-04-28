#include "MealCombiner.h"

void MealCombiner::processMeals() { 

	DEBUG_MSG("Spawned");

	while(true) {

		// Step 1 wait for an order to come in from the Order Window
		wait(this->fromOrderWindow->data_ready_event());
		DEBUG_MSG("MealCombiner tried to read OrderWindow!");
		Meal m;
		this->fromOrderWindow->read(m);
		
		// Step 2 send components of the order to the respective makers
		this->toBurgerMaker->write(m.numBurgers);
		this->toFryMaker->write(m.numFries);
		this->toDrinkMaker->write(m.numDrinks);

		// Step 3 attempt to pull number of ingredients off of the queues (semaphores)
		int burgerCount = 0, fryCount = 0, drinkCount = 0;
		while((burgerCount < m.numBurgers) &&
				(fryCount < m.numFries) &&
				(drinkCount < m.numDrinks)) {

			if(burgerCount < m.numBurgers) {
				this->fromBurgerMaker->wait(); // wait for burger maker to make a burg
				burgerCount++;
			}

			if(fryCount < m.numFries) {
				this->fromFryMaker->wait(); // wait for fry maker to make fries
				fryCount++;
			}

			if(drinkCount < m.numDrinks) {
				this->fromDrinkMaker->wait(); // wait for drink maker to make a drink
				drinkCount++;
			}

		}


		// Step 4 once we have all of the order, send it to the delivery window

		// the count variable is used for each food type because that is the actual
		// count of food created by the makers. This might be useful for debugging
		// in case the overall Maker/Meal Combiner structure is making incorrect
		// amounts of food for each order. 
		Meal toDeliver = {m.orderNumber, burgerCount, fryCount, drinkCount};
		this->toDeliveryWindow->write(toDeliver);
	}
}