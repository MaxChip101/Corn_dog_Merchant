#include <iostream>
#include <chrono>

#include "customer.h"
#include "shop.h"
#include "dialog.h"
#include "player.h"

using namespace std;

int seed;

int randnum(int min, int max) {
    return rand() % max + min;
}

int main() {
    render_text("Welcome to the \"Travelling Corn dog Merchant\"");

    // seed
    seed = prompt_int("Type a seed (negative number for random)");
    if (seed < 0) {
        seed = time(NULL);
    }   
    srand(seed);
    render_text("selected seed is: " + to_string(seed));

    // setting up
    charisma = randnum(0, 100) / 100.0;
    money = randnum(10, 25);
    popularity = randnum(3, 5);
    corndogs = 0;

    // business name
    name = prompt("What's your name?");
    business_name = name + "'s Corn Dogs";

    // initialization
    initialize_shop(randnum);

    // start game
    render_text("Your business name is: " + business_name);
    wait(500);
    render_text("Loading...");
    wait(1000);
    render_text("You start off your business with: $" +  to_string(money) + " dollars");
    wait(1000);
    shop_dialog(randnum, create_character(randnum));

}
