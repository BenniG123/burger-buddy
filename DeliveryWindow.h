#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"

class DeliveryWindow : public sc_module {

        // Inputs
        double_handshake<Meal> fromMealCombiner;

};

