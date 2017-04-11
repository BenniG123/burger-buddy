#include <systemc.h>
#include <string>
#include "double_handshake.h"

using namespace std;

template <class T>
class producer : public sc_module
{
public:
	sc_port< dh_write_if<T> > out;
	SC_HAS_PROCESS(producer);

	producer(sc_module_name nm) : sc_module(nm){SC_THREAD(main)}

	void do_write(T i);
	void main();
};

template <class T>
class consumer : public sc_module
{
public:
	sc_port< dh_read_if<T> > in;

	SC_HAS_PROCESS(consumer);

	consumer(sc_module_name nm) : sc_module(nm){ SC_THREAD(main)}

	void do_read();
	void main();
};