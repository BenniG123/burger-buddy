#include "double_handshake_tb.h"

template<>
void producer<int>::do_write(int i)
{
	cout << "do write INT\n";
	out->write(i);
	cout << "end do write INT\n";
}

template<>
void producer<int>::main()
{
	cout << "PRODUCER_INT STARTED" << endl;

	int i = 3;
	while(i > 0)
	{
		this->do_write(i);
		i--;
	}
	cout << "PRODUCER_INT DONE" << endl;
}

template<>
void producer<string>::do_write(string s)
{
	cout << "do write STR\n";
	out->write(s);
	cout << "end do write STR\n";
}

template<>
void producer<string>::main()
{
	vector<string> testStrings;
	cout << "PRODUCER_STR STARTED" << endl;
	testStrings.push_back("hello ");
	testStrings.push_back("world ");
	testStrings.push_back("double handshake ");

	int i = 0;
	while(i < 3)
	{
		string to_write = testStrings[i];
		do_write(to_write);
		i++;
	}
	cout << "PRODUCER_STR DONE" << endl;
}

template<>
void consumer<int>::do_read()
{
	cout << "do read INT\n";
	int read_val;
	in->read(read_val);
	cout << read_val << endl;
	cout << "end do read INT\n";
}

template<>
void consumer<int>::main()
{
	cout << "CONSUMER_INT STARTED" << endl;

	int i = 3;
	while(i > 0)
	{
			do_read();
			i--;
	}

	cout << "CONSUMER_INT DONE" << endl;
}

template<>
void consumer<string>::do_read()
{
	cout << "do read STR\n";
	string read_val;
	in->read(read_val);
	cout << read_val << endl;
	cout << "end do read STR\n";
}

template<>
void consumer<string>::main()
{
	cout << "CONSUMER_STR STARTED" << endl;

	int i = 3;
	while(i > 0)
	{
			do_read();
			i--;
	}
	cout << "CONSUMER_STR DONE" << endl;
}