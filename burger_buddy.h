#ifndef BURGER_BUDDY_H
#define BURGER_BUDDY_H

enum TransactionType {
	WITHDRAW,
	DEPOSIT,
	CHECK
};

struct MoneyTransaction {
	TransactionType type;
	float amt;
};

struct Meal {
	int orderNumber;
	int numBurgers;
	int numFries;
	int numDrinks;
};

#endif
