#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class Maker : public sc_module {

        // Inputs
        double_handshake<int> fromMealCombiner;
        double_handshake<int> fromSupplyTracker;

        // Outputs
        sc_semaphore toMealCombiner;
        double_handshake<int> toSupplyTracker;

};

