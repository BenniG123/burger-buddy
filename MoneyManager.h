#ifndef MONEY_MANAGER_H
#define MONEY_MANAGER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class MoneyManager : public sc_module {
	private:
		double money;

	public:
		// Inputs
		sc_port< dh_read_if<MoneyTransaction> > fromOrderWindow;
		sc_port< dh_read_if<MoneyTransaction> > fromIngredientOrdering;
		sc_port< dh_read_if<MoneyTransaction> > fromAdminInterface;

		// Outputs
		sc_port< dh_write_if<MoneyTransaction> > toOrderWindow;
		sc_port< dh_write_if<MoneyTransaction> > toIngredientOrdering;
		sc_port< dh_write_if<MoneyTransaction> > toAdminInterface;

		void processTransaction();

		SC_HAS_PROCESS(MoneyManager);
		
		MoneyManager(sc_module_name nm) : sc_module(nm) {SC_THREAD(processTransaction)}

};

#endif
