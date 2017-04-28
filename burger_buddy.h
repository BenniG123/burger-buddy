#ifndef BURGER_BUDDY_H
#define BURGER_BUDDY_H

#define BURGER_COST 100
#define FRY_COST 25
#define DRINK_COST 5

#define BURGER_PRICE 300
#define FRY_PRICE 150
#define DRINK_PRICE 100

// turn off general debug messages by commenting out the line below 
#define DEBUG

// turn off channel (double_handshake) debug messages by commenting out the line below
#define DEBUG_CHANNELS

#ifdef DEBUG
#define DEBUG_MSG(X) (std::cout << this->name()  <<": " << X << std::endl)
#else
#define DEBUG_MSG(X)
#endif

#ifdef DEBUG_CHANNELS
#define DEBUG_MSG_CHANNEL(X) (std::cout << this->name()  <<": " << X << std::endl)
#else 
#define DEBUG_MSG_CHANNEL(X)
#endif


#include <iostream>
using namespace std;

enum TransactionType {
	WITHDRAW,
	DEPOSIT,
	CHECK
};

struct MoneyTransaction {
	TransactionType type;
	int amt;
};

struct Meal {
	int orderNumber;
	int numBurgers;
	int numFries;
	int numDrinks;

	friend ostream& operator<<(ostream& os, const Meal& m) {
		os  << "orderNumber: " << m.orderNumber << endl
			<< "numBurgers: " << m.numBurgers << endl
			<< "numFries: " << m.numFries << endl
			<< "numDrinks: " << m.numDrinks << endl;
		return os;
	}

	int getPrice() {
		return numBurgers * BURGER_PRICE + numFries * FRY_PRICE + numDrinks * DRINK_PRICE;
	}
};

#endif
