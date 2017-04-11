#ifndef DOUBLE_HANDSHAKE_H
#define DOUBLE_HANDSHAKE_H

#include <systemc.h>
using namespace sc_core;

template <class T>
class dh_write_if : virtual public sc_interface
{
public:
	virtual void write(T) = 0;
};

template <class T>
class dh_read_if : virtual public sc_interface
{
public:
	virtual void read(T&) = 0;
};

template <class T>
class double_handshake : public sc_channel, public dh_write_if<T>, public dh_read_if<T>
{
public:
	T data;
	sc_event write_event;
	sc_event read_ready_event;
	bool valid;
	bool ready;
	sc_event read_done_event;

	double_handshake(sc_module_name nm) : sc_module(nm), valid(false), ready(false)
	{

	}

	// blocks for ACK
	void write(T t)
	{
		this->data = t;
		this->valid = true;
		
		if(!(this->ready))
				wait(read_ready_event);

		this->write_event.notify();
		wait(read_done_event);
		this->valid = false;
	}

	// blocking read
	void read(T& t)
	{
		this->ready=true;
		this->read_ready_event.notify();
		wait(write_event);
		this->ready = false;
		t = this->data;
		this->read_done_event.notify();
	}

	// getter for valid 
	bool checkValid()
	{
		return this->valid;
	}

};

#endif /* DOUBLE_HANDSHAKE_H */