#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class AdminInterface : public sc_module {

	public:
		// Inputs
		sc_port< dh_read_if<MoneyTransaction> > fromInputWrapper;
		sc_port< dh_read_if<MoneyTransaction> > fromMoneyManager;

		// Outputs
		sc_port< dh_write_if<MoneyTransaction> > toMoneyManager;

		void runAdmin();
		
		SC_HAS_PROCESS(AdminInterface);
		
		AdminInterface(sc_module_name nm) : sc_module(nm) {SC_THREAD(runAdmin)}

};

#endif
