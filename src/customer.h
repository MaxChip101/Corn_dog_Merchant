#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

#include "shop.h"

using namespace std;

struct Character {
    string name;
    bool isGabe = false;
    bool royalty = false;
    bool peasant = false;
    bool isMale = false;
    int price_acceptance;
    float hunger = 0;
    float mood = 0;
    float happiness = 0;
};

Character create_character(int (*func)(int, int));

void say(Character customer, string text);

int sell(Character customer, string item);

#endif
