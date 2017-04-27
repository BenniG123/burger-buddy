#ifndef DOUBLE_HANDSHAKE_H
#define DOUBLE_HANDSHAKE_H

#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(X) (std::cout << this->channelName  <<": " << X << std::endl)
#else
#define DEBUG_MSG(X)
#endif

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
	bool valid;
	virtual void read(T&) = 0;
	virtual const sc_event& data_ready_event() const { return this->data_ready;}
	virtual const bool checkValid() const { return this->valid; };
};

template <class T>
class double_handshake : public sc_channel, public dh_write_if<T>, public dh_read_if<T>
{
public:
	T data;
	sc_event read_ready_event, write_event;
	bool ready;
	std::string channelName;
	sc_event read_done_event;

	double_handshake(sc_module_name nm) : sc_module(nm), ready(false), channelName(nm)
	{
		this->valid = false;
	}

	// blocks for ACK
	void write(T t)
	{
		DEBUG_MSG("writing started!");
		this->data = t;
		this->valid = true;

		this->data_ready.notify();
		
		if(!(this->ready)) {
				wait(read_ready_event);
				DEBUG_MSG("writer blocking");
			}

		this->write_event.notify();
		wait(read_done_event);
		this->valid = false;
		DEBUG_MSG("writing done!");
	}

	// blocking read
	void read(T& t)
	{
		DEBUG_MSG("reading started!");
		this->ready=true;
		this->read_ready_event.notify();
		wait(this->write_event);
		this->ready = false;
		t = this->data;
		this->read_done_event.notify();
		DEBUG_MSG("reading done!");
	}

};

#endif /* DOUBLE_HANDSHAKE_H */
