#include <string>

#include "shop.h"
#include "player.h"

using namespace std;

int corndog_price;

int advertisement_price;

// stock shop

void initialize_shop(int (*func)(int, int)) {
    corndog_price = 5 + func(-2, 2);
    advertisement_price = 20 + func(-5, 5);
}

// player shop

// if corn dog sellable
bool sellable() {
    if(corndogs >= 1) {
        return true;
    } else {
        return false;
    }
}

// sell corndog to customer
void sell() {
    corndogs -= 1;
    money += corndog_value;
}

