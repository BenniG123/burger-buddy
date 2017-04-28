#include <systemc.h>
#include "OrderWindow.h"
#include "double_handshake.h"
#include "burger_buddy.h"

using namespace std;
	
void OrderWindow::main()
{		Meal requestedMeal;
		MoneyTransaction inputMoney,changeMoney,outputMoney;
		bool b;
		
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

			cout<<"enter the payment amount"<<endl;
			cin >> inputMoney.amt;
			while (inputMoney.amt < requestedMeal.getPrice())
			{
					cout << "Insufficient money entered. "<<endl;
					cout << "Enter equal or more than "<< requestedMeal.getPrice() << " amount" << endl;
					cin >> inputMoney.amt;
			}
			inputMoney.type = DEPOSIT;
			toMoneyManager -> write (inputMoney);
			changeMoney.amt = requestedMeal.getPrice();
			changeMoney.type = WITHDRAW;
			toMoneyManager -> write (changeMoney);
			fromMoneyManager -> read (outputMoney);
			if (outputMoney.amt != 0 && outputMoney.type == WITHDRAW)
				cout<<"the remaining balance returned is"<<outputMoney.amt<<endl;
			
			DEBUG_MSG("sending request to meal combiner"<<"with order number"<<requestedMeal.orderNumber);
			toMealCombiner -> write(requestedMeal);
		}
}
