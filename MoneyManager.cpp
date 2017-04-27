#include "MoneyManager.h"

void MoneyManager::processTransaction() { 

	while(true) {
		// Step 1 wait for an order to come in from the Order Window
		wait(this->fromAdminInterface->data_ready_event() | this->fromIngredientOrdering->data_ready_event() | this->fromOrderWindow->data_ready_event());
		if (this->fromAdminInterface->checkValid()) {
			cout << "Admin Interface is making a request" << endl;
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
					break;
				case CHECK:
					t.amt = this->money;

					// Step 3, send money
					this->toAdminInterface->write(t);
					break;
			}

		}
		else if (this->fromIngredientOrdering->checkValid()) {
			cout << "Ingredient Ordering is making a request" << endl;
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
			cout << "Order Window is submitting payment" << endl;
			MoneyTransaction t;

			// Step 1, read submitted money
			this->fromOrderWindow->read(t);

			// Need to change spec, we currently have no way of determining change
		}
	}
}