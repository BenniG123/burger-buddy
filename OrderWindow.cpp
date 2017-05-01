#include <systemc.h>
#include <iomanip>
#include "OrderWindow.h"
#include "double_handshake.h"
#include "burger_buddy.h"

using namespace std;
	
void OrderWindow::main()
{		Meal requestedMeal;
		MoneyTransaction inputMoney,changeMoney,outputMoney;
		bool b;

		DEBUG_MSG("Spawned");
		
		while(1)
		{
			DEBUG_MSG("wait for input wrapper meal plan");
			fromInputWrapper-> read(requestedMeal);
			DEBUG_MSG("checking with supply tracker");
			toSupplyTracker -> write(requestedMeal);
			fromSupplyTracker -> read(b);
			if (b == false) {
				cout<<"cancel the order as not enough supplies"<<endl;
				continue;
			}

			cout<<"Please enter payment of $" << fixed << setprecision(2) << requestedMeal.getPrice() / 100.0 << " or more: ";
			cin >> inputMoney.amt;
			while (inputMoney.amt < requestedMeal.getPrice())
			{
					cout << "Insufficient money entered. "<<endl;
					cout << "Enter equal or more than $"<< fixed << setprecision(2) << requestedMeal.getPrice() / 100.0 << " amount" << endl;
					cin >> inputMoney.amt;
			}
			inputMoney.type = DEPOSIT;
			toMoneyManager -> write (inputMoney);
			changeMoney.amt = inputMoney.amt - requestedMeal.getPrice();
			changeMoney.type = WITHDRAW;
			toMoneyManager -> write (changeMoney);
			fromMoneyManager -> read (outputMoney);
			if (outputMoney.amt != 0) {
				cout<<"the remaining balance returned is $" << fixed << setprecision(2) << outputMoney.amt  / 100.0 << endl;
			}
			
			DEBUG_MSG("sending request to meal combiner with order number " << requestedMeal.orderNumber);
			toMealCombiner -> write(requestedMeal);
		}
}
