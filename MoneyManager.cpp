#include "MoneyManager.h"

void MoneyManager::processTransaction() { 

	DEBUG_MSG("Spawned");

	while(true) {
		// Step 1 wait for an order to come in from the Order Window
		wait(this->fromAdminInterface->data_ready_event() | this->fromIngredientOrdering->data_ready_event() | this->fromOrderWindow->data_ready_event());
		if (this->fromAdminInterface->checkValid()) {
			DEBUG_MSG("Admin Interface is making a request");
			MoneyTransaction t;

			// Step 1, read the request
			this->fromAdminInterface->read(t);

			// Step 2, process the request
			switch (t.type) {
				case WITHDRAW:
					if (t.amt > this->money) {
						// Insufficient funds
						t.amt = this->money - t.amt;

						// Step 3a, send error
						this->toAdminInterface->write(t);
					}
					else {
						this->money -= t.amt;
						
						// Step 3b, send money
						this->toAdminInterface->write(t);
					}
					break;
				case DEPOSIT:
					// Do nothing
					this->money = t.amt;
					break;
				case CHECK:
					t.amt = this->money;

					// Step 3, send money
					this->toAdminInterface->write(t);
					break;
			}

		}
		else if (this->fromIngredientOrdering->checkValid()) {
			DEBUG_MSG("Ingredient Ordering is making a request");
			MoneyTransaction t;

			// Step 1, read the request
			this->fromIngredientOrdering->read(t);

			// Step 2, process withdrawl
			if (t.type == WITHDRAW) {
				if (t.amt > this->money) {
					// Insufficient funds
					t.amt = this->money - t.amt;

					// Step 3, send error
					this->toIngredientOrdering->write(t);
				}
				else {
					this->money -= t.amt;

					// Step 3, send money
					this->toIngredientOrdering->write(t);
				}
			}
			else {
				cout << "Error: Ingredient Ordering can only withdraw money" << endl;
			}
		}
		else if (this->fromOrderWindow->checkValid()) {
			DEBUG_MSG("Order Window is submitting payment");
			MoneyTransaction t1, t2;

			// Step 1, read request
			this->fromOrderWindow->read(t1);

			// Step 2, process deposit
			if (t1.type == DEPOSIT) {
				this->money += t1.amt;
				
				// Step 3, read withdrawl request
				this->fromIngredientOrdering->read(t2);

				// Step 4, send change back
				if (t2.amt < t1.amt) {
					// Good to go
					this->money -= t2.amt;
					this->toIngredientOrdering->write(t2);
				}
				else {
					// Bad
					cout << "Error: Cannot request more change than money submitted" << endl;
				}
			}
			else {
				cout << "Error: Order Window must submit money before withdrawing change" << endl;
			}
		}
	}
}