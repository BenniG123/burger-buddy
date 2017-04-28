#include "Maker.h"

/*

Steps:
1. Wait for Meal Combiner to issue an order
2. Request ingredients from Supply Tracker
3. Wait for Supply Tracker to respond with a number of ingredients
4. Keep making meal components until the order is filled (wait/sleep in between each one)
   a. Insert finished meal components into queue/semaphore

*/

void Maker::processCombinerRequest() {

	DEBUG_MSG("Spawned");


	while(true) {

		// Step 1 Wait for Meal Combiner to issue an order
		wait(this->fromMealCombiner->data_ready_event());
		int numRequested;
		this->fromMealCombiner->read(numRequested);

		// Step 2 Request ingredients from Supply Tracker
		this->toSupplyTracker->write(numRequested);

		// Step 3 Wait for Supply Tracker to respond with a number of ingredients
		int numSuppliedTotal;
		wait(this->fromSupplyTracker->data_ready_event());
		this->fromSupplyTracker->read(numSuppliedTotal);
		while(numSuppliedTotal < numRequested) // if the Supply Tracker couldn't afford enough ingredients then continue waiting until it can
		{
			this->toSupplyTracker->write(numRequested - numSuppliedTotal);
			wait(this->fromSupplyTracker->data_ready_event());
			int numToAdd;
			this->fromSupplyTracker->read(numToAdd);
			numSuppliedTotal += numToAdd;
		}


		// Step 4 Keep making meal components until the order is filled (wait/sleep in between each one)
		// Step 4a Insert finished meal components into queue/semphore
		// javey: Should the maker actually wait between each food creation?
		//         I know it makes sense but are we actually implementing the wait/sleep
		int numFoodCreated = 0;
		while(numFoodCreated < numRequested) {
			// delay/wait/sleep would go here
			this->toMealCombiner->post(); // food created (increment semaphore)
		}
	}
}