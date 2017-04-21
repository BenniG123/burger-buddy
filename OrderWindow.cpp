#include <systemc.h>
#include "double_handshake.h"
#include "OrderWindow.h"
using namespace std;

void OrderWindow::main() {
		bool fromSupplyTracker; // will come from supply tracker
            Meal fromInputWrapper;
	    MoneyTransaction fromMoneyManager;

            // Outputs
            Meal toMealCombiner;
            MoneyTransaction toMoneyManager;
                
            while(1)
            { 
                      cout << "Waiting for input wrapper" << endl;
		    	fromInputWrapper -> read(fromInputWrapper);
		    	toSupplyTracker -> write (fromInputWrapper);
                      if (fromSupplyTracker == true)
		      {      cout<< " Enter the amount"<<endl; 
				toMoneyManager = // input money
		      }
		      else
			     cout << " insufficient supply. Order cancelled "<< endl;
            		toMoneyManager -> write (toMoneyManager);
	    
	    
	    }





}





