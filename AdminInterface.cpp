#include "AdminInterface.h"
#include <iomanip>

void AdminInterface::runAdmin() { 

	while(true) {

		// Step 1 wait for the user to access the interface
		wait(this->fromInputWrapper->data_ready_event());
		cout << "Input Wrapper has accessed the Admin Interface" << endl;
		MoneyTransaction t1, t2;
		this->fromInputWrapper->read(t1);
		
		// Step 2 forward the request to the money manager
		this->toMoneyManager->write(t1);

		// Step 3a, no response needed if deposit
		if (t1.type == DEPOSIT) {
			cout << "Successfully deposited $" << setprecision(2) << t1.amt << endl;
		}
		// Step 3b, get the response from the Money Manager
		else {
			this->fromMoneyManager->read(t2);
			switch(t2.type) {
				case WITHDRAW:
					if (t2.amt < 0) {
						// Insufficient funds
						cout << "Insufficient funds: Money Manager only has $" << t1.amt + t2.amt << endl;
					}
					else {
						cout << "Successfully withdrew $" << setprecision(2) << t2.amt << endl;
					}
					break;
				case DEPOSIT:
					// Do nothing
					break;
				case CHECK:
					cout << "Current balance is $" << setprecision(2) << t2.amt << endl;
					break;
			}
		}
	}
}