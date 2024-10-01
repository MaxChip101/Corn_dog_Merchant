#include <string>
#include <iostream>
#include <functional>

#include "customer.h"
#include "shop.h"
#include "dialog.h"
#include "player.h"

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

    // if gabe
    if(func(0, 100) == 0) {
        c.isGabe = true;
        c.royalty = true;
        c.happiness = 1;
        c.price_acceptance = 10000000;
        c.mood = 1;
        c.isMale = true;
        c.name = "Gabe Newell";
    // if regular person
    } else {
        // royalty
        if(func(0, 10) == 0) {
            c.royalty = true;
        // peasant
        } else if(func(0, 5) == 0) {
            c.peasant = true;
        }

        // male
        if(func(0, 2) == 0) {
            c.isMale = true;
        }
        // mood control
        c.mood = func(0, 100) / 100.0;
        c.happiness = func(0, 100) / 100.0;
        
        // if royalty
        if(c.royalty) {
            // male
            if(c.isMale) {
                c.name = royal_male[func(0, 6)] + " " + males[func(0, 14)];
                c.price_acceptance = func(7, 14) + popularity;
            // female
            } else {
                c.name = royal_female[func(0, 5)] + " " + females[func(0, 14)];
                c.price_acceptance = func(6, 12) + popularity;
            }
        // if peasant
        } else if(c.peasant) { 
            // male
            if(c.isMale) {
                c.name = males[func(0, 14)] + " " + males[func(0, 14)];
                c.price_acceptance = func(5, 10) + popularity;
            // female
            } else {
                c.name = females[func(0, 14)] + " " + females[func(0, 14)];
                c.price_acceptance = func(4, 8) + popularity;
            }
        // middle class
        } else {
            // male
            if(c.isMale) {
                c.name = males[func(0, 14)] + " " + males[func(0, 14)];
                c.price_acceptance = func(3, 6) + popularity;
            // female
            } else {
                c.name = females[func(0, 14)] + " " + females[func(0, 14)];
                c.price_acceptance = func(2, 5) + popularity;
            }
        }
    }

    return c;
}

// if price is in customer's range
bool respectable(Character customer) {
    if(customer.price_acceptance > corndog_value) {
        return true;
    } else {
        return false;
    }
}