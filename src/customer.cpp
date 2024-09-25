#include <string>
#include <iostream>
#include <functional>

#include "customer.h"
#include "shop.h"

using namespace std;

// names for characters

string males[] = {
        "Godfrey", "Roland", "Alaric", "Geoffrey", "Thaddeus", 
        "Cedric", "Edmund", "Oswald", "Percival", "Baldwin", 
        "Anselm", "Berengar", "Wulfric", "Leofric", "Roderick"
    };

string females[] = {
    "Isolde", "Eleanora", "Seraphina", "Rowena", "Guinevere", 
    "Margery", "Beatrix", "Elfrida", "Matilda", "Gwendolyn", 
    "Aethelwyn", "Sibylla", "Adelaide", "Maud", "Cressida"
};

string royal_female[] = {
    "Queen", "Lady", "Princess", "Empress", "Duchess", "Countess"
};

string royal_male[] = {
    "King", "Lord", "Emperor", "Prince", "Duke", "Baron", "Marquis"
};


// create character
Character create_character(int (*func)(int, int)) {
    Character c;

    if(func(0, 100) == 0) {
        c.isGabe = true;
        c.money = 1000000;
        c.royalty = true;
        c.happiness = 1;
        c.mood = 0;
        c.hunger = 0.4;
        c.isMale = true;
        c.name = "Gabe Newell";
    } else {
        if(func(0, 10) == 0) {
            c.royalty = true;
        } else if(func(0, 5) == 0) {
            c.peasant = true;
        }
        if(c.royalty) {
            c.money = func(200, 500);
        } else if(c.peasant) {
            c.money = func(0, 20);
        } else {
            c.money = func(40, 100);
        }
        if(func(0, 1) == 0) {
            c.isMale = true;
        }
        c.hunger = func(0, 100) / 100.0;
        c.mood = func(0, 100) / 100.0;
        c.happiness = func(0, 100) / 100.0;

        if(c.royalty) {
            if(c.isMale) {
                c.name = royal_male[func(0, 6)] + " " + males[func(0, 14)];
            } else {
                c.name = royal_female[func(0, 5)] + " " + females[func(0, 14)];
            }
        } else {
            if(c.isMale) {
                c.name = males[func(0, 14)] + " " + males[func(0, 14)];
            } else {
                c.name = females[func(0, 14)] + " " + females[func(0, 14)];
            }
        }
    }

    cout << c.name << endl;
    return c;
}

// sell an item to a customer
int sell(Character customer, string item) {
    if(customer.money < 0) {

    }
    return 0;
}

