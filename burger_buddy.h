#ifndef BURGER_BUDDY_H
#define BURGER_BUDDY_H

#define BURGER_COST 100
#define FRY_COST 25
#define DRINK_COST 5

#define BURGER_PRICE 300
#define FRY_PRICE 150
#define DRINK_PRICE 100

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
};

#endif
