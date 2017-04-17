#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class AdminInterface : public sc_module {

        // Inputs
        double_handshake<MoneyTransaction> fromMoneyManager;

        // Outputs
        double_handshake<MoneyTransaction> toMoneyManager;

};

