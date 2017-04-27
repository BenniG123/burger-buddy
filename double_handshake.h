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
	sc_event data_ready;
	virtual void read(T&) = 0;
	virtual const sc_event& data_ready_event() const { return this->data_ready;}
	virtual bool checkValid();
};

template <class T>
class double_handshake : public sc_channel, public dh_write_if<T>, public dh_read_if<T>
{
public:
	T data;
	sc_event read_ready_event, write_event;
	bool valid;
	bool ready;
	sc_event read_done_event;

	double_handshake(sc_module_name nm) : sc_module(nm), valid(false), ready(false)
	{

	}

	// blocks for ACK
	void write(T t)
	{
		cout << "writing started!" << endl;
		this->data = t;
		this->valid = true;

		this->data_ready.notify();
		
		if(!(this->ready)) {
				wait(read_ready_event);
				cout << "writer blocking" << endl;
			}

		this->write_event.notify();
		wait(read_done_event);
		this->valid = false;
		cout << "writing done!" << endl;
	}

	// blocking read
	void read(T& t)
	{
		cout << "reading started!" << endl;
		this->ready=true;
		this->read_ready_event.notify();
		wait(this->write_event);
		this->ready = false;
		t = this->data;
		this->read_done_event.notify();
		cout << "reading done!" << endl;
	}

	// getter for valid 
	bool checkValid()
	{
		return this->valid;
	}

};

#endif /* DOUBLE_HANDSHAKE_H */