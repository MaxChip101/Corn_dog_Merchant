#ifndef SHOP_H
#define SHOP_H

#include <string>
#include "customer.h"

using namespace std;

void initialize_shop(int (*func)(int, int));

extern int corndog_price;

extern int advertisement_price;

bool sellable();

#endif
