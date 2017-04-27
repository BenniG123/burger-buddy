#ifndef BURGER_BUDDY_H
#define BURGER_BUDDY_H

#define BURGER_COST 100
#define FRY_COST 25
#define DRINK_COST 5

#define BURGER_PRICE 300
#define FRY_PRICE 150
#define DRINK_PRICE 100

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
