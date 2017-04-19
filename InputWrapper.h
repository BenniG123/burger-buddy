#ifndef INPUT_WRAPPER_H
#define INPUT_WRAPPER_H

#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class InputWrapper : public sc_module {

	public:
        	// Outputs
        	sc_port< dh_write_if<Meal> > toOrderWindow;
		sc_port< dh_write_if<MoneyTransaction> > toAdminInterface;
		
		SC_HAS_PROCESS(InputWrapper);

		void main();

		InputWrapper(sc_module_name nm) : sc_module(nm) {SC_THREAD(main)}


};

#endif
