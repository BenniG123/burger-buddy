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
			cout<<"wait for input wrapper meal plan"<<endl;
			fromInputWrapper-> read(requestedMeal);
			cout<<"checking with supply tracker"<<endl;
			toSupplyTracker -> write(requestedMeal);
			fromSupplyTracker -> read(b);
				if (b == false)
				cout<<"cancel the order as not enough supplies"<<endl;
				else 
				cout<<"enter the amount"<<endl;
			cin>>inputMoney.amt;
			while (1)
			{	if (inputMoney.amt < requestedMeal.getPrice())
				{
					cout <<"Insufficient money entered. "<<endl;
					cout <<"Enter equal or more than "<<requestedMeal.getPrice()-inputMoney.amt<<"amount"<<endl;
				}
				else
				{
					break;
				}
			}
			inputMoney.type = DEPOSIT;
			toMoneyManager -> write (inputMoney);
			changeMoney.amt = requestedMeal.getPrice();
			changeMoney.type = WITHDRAW;
			toMoneyManager -> write (changeMoney);
			fromMoneyManager -> read (outputMoney);
			if (outputMoney.amt != 0 && outputMoney.type == WITHDRAW)
				cout<<"the remaining balance returned is"<<outputMoney.amt<<endl;
			
			cout <<"sending request to meal combiner"<<"with order number"<<requestedMeal.orderNumber<<endl;
			toMealCombiner -> write(requestedMeal);
		}
}
