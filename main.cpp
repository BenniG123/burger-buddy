#include "systemc.h"
#include "burger_buddy.h"
#include "double_handshake.h"
#include "double_handshake_tb.h"
#include "OrderWindow.h"
#include "Maker.h"
#include "DeliveryWindow.h"
#include "AdminInterface.h"

int sc_main(int argc, char* argv[])
{
	// double handshake test bench for string messaging
	double_handshake<string> dhSTR("DH_STR");
	producer<string> ps("PRODUCER_STR");
	consumer<string> cs("CONSUMER_STR");
	ps.out(dhSTR);
	cs.in(dhSTR);

	// double handshake test bench for int messaging
	// double_handshake<int> dhINT("DH_INT");
	// producer<int> pi("PRODUCER_INT");
	// consumer<int> ci("CONSUMER_INT");
	// pi.out(dhINT);
	// ci.in(dhINT);

	sc_start();

	return 0;
}
