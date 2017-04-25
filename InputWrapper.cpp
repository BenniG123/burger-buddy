
#include <systemc.h>
#include "InputWrapper.h"
#include "double_handshake.h"
#include "burger_buddy.h"

using namespace std;

void InputWrapper:: main()
{	int i, x, y,z, m;
	Meal requestedMeal; 
	MoneyTransaction money;
		while (1)
		{	static int Number=0;
			money.amt=0;
			cout <<"press 1 for order window or 2 for admin"<<endl;
			cin >> i;
			if  (i ==1) 
			{
				cout <<"Welcome to order window. Enter the number of burgers"<<endl;
				cin>>x;
				cout <<" Enter the number of fries"<<endl;
				cin>>y;
				cout <<"Enter the number of drinks"<<endl;
				cin>>z;
				Number = Number+1;
				requestedMeal.orderNumber = Number;
				requestedMeal.numBurgers = x;
				requestedMeal.numFries = y;
				requestedMeal.numDrinks = z;
				toOrderWindow -> write (requestedMeal);
				cout <<"sent order"<<endl;
			}
			else 
				{	
					cout <<"welcome to admin interface. "<<endl;
					cout <<" deposit press 1,  withdraw press 2, checking press 3"<<endl;
					cin >> i;
					if (i  == 1 )
					{	cout<<"enter the amount to be deposited"<<endl;
						cin >> m;
						money.type = DEPOSIT;
						money.amt = m;
						toAdminInterface -> write(money);	
						cout<<"request sent"<<endl;		
					}
					else if (i ==2)
					{	cout<<"enter the amount to be withdrawn"<<endl;
						cin >> m;
						money.type = WITHDRAW;
						money.amt = m;
						toAdminInterface -> write(money);	
						cout<<"request sent"<<endl;
					}
					else
					{	money.type = CHECK;
						money.amt=0;
						toAdminInterface -> write(money);	
						cout<<"request sent"<<endl;
					}
		
				}
		}
}

