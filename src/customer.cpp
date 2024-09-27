#include <string>
#include <iostream>
#include <functional>

#include "customer.h"
#include "shop.h"
#include "dialog.h"

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

void say(Character customer, string text) {
    render_text(customer.name + " says: \"" + text + "\"");
}

// create character
Character create_character(int (*func)(int, int)) {
    Character c;

    if(func(0, 100) == 0) {
        c.isGabe = true;
        c.royalty = true;
        c.happiness = 1;
        c.price_acceptance = 10000000;
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

        if(func(0, 1) == 0) {
            c.isMale = true;
        }
        c.hunger = func(0, 100) / 100.0;
        c.mood = func(0, 100) / 100.0;
        c.happiness = func(0, 100) / 100.0;

        if(c.royalty) {
            if(c.isMale) {
                c.name = royal_male[func(0, 6)] + " " + males[func(0, 14)];
                c.price_acceptance = func(16, 30);
            } else {
                c.name = royal_female[func(0, 5)] + " " + females[func(0, 14)];
                c.price_acceptance = func(15, 30);
            }
        } else if(c.peasant) { 
            if(c.isMale) {
                c.price_acceptance = func(9, 17);
            } else {
                c.price_acceptance = func(8, 18);
            }
        } else {
            if(c.isMale) {
                c.name = males[func(0, 14)] + " " + males[func(0, 14)];
                c.price_acceptance = func(12, 22);
            } else {
                c.name = females[func(0, 14)] + " " + females[func(0, 14)];
                c.price_acceptance = func(10, 20);
            }
        }
    }

    cout << c.name << endl;
    return c;
}

