
#include <systemc.h>
#include "InputWrapper.h"
#include "double_handshake.h"
#include "burger_buddy.h"

using namespace std;


void retrieveIntegerInput(int &n)
{
	cin >> n;
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid number. Please try again: " << endl;
		cin >> n;
	}
}

void InputWrapper:: main()
{	int i, x, y,z, m;
	Meal requestedMeal; 
	MoneyTransaction money;

	DEBUG_MSG("Spawned");

	while (1)
	{	static int Number=0;
		money.amt=0;
		cout <<"Press 1 for order window or 2 for admin interface"<<endl;
		retrieveIntegerInput(i);
		if  (i == 1) 
		{
			cout <<"Welcome to order window. Enter the number of burgers"<<endl;
			retrieveIntegerInput(x);
			cout <<"Enter the number of fries"<<endl;
			retrieveIntegerInput(y);
			cout <<"Enter the number of drinks"<<endl;
			retrieveIntegerInput(z);
			Number = Number+1;
			requestedMeal.orderNumber = Number;
			requestedMeal.numBurgers = x;
			requestedMeal.numFries = y;
			requestedMeal.numDrinks = z;
			DEBUG_MSG("sent order to order window");
			toOrderWindow -> write (requestedMeal);

			//bool dontMatter; // :p
			//this->fromDeliveryWindow->read(dontMatter);
		}
		else 
			{	
				cout <<"welcome to admin interface. "<<endl;
				cout <<" deposit press 1, withdraw press 2, checking press 3"<<endl;
				retrieveIntegerInput(i);
				if (i  == 1 )
				{	cout<<"enter the amount to be deposited"<<endl;
					retrieveIntegerInput(m);
					money.type = DEPOSIT;
					money.amt = m;
					DEBUG_MSG("DEPOSIT request sent");
					toAdminInterface -> write(money);			
				}
				else if (i ==2)
				{	cout<<"enter the amount to be withdrawn"<<endl;
					retrieveIntegerInput(m);
					money.type = WITHDRAW;
					money.amt = m;
					DEBUG_MSG("WITHDRAW request sent");
					toAdminInterface -> write(money);	
				}
				else
				{	money.type = CHECK;
					money.amt=0;
					DEBUG_MSG("CHECK request sent");
					toAdminInterface -> write(money);	
				}

				bool dontMatter; // :p
				this->fromAdminInterface->read(dontMatter);
	
			}

	}
}


