#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cctype>

#include "player.h"
#include "shop.h"
#include "customer.h"

using namespace std;

// console rendering and inputs

// function to check if a string is a number
bool isNumeric(const string& str) {
    if(str[0] == '-') {
        string str2 = "";

        for(string::size_type i = 1; i < str.length(); i++) {
            str2 += str[i];
        }

        str2 += "0";
        return all_of(str2.begin(), str2.end(), ::isdigit);
    } else {
        return all_of(str.begin(), str.end(), ::isdigit);
    }
}

// waits a certain ammount of milliseconds
void wait(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// safe user input
string input() {
    string inp_str;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        inp_str += ch;
    }
    return inp_str;
}

// render the text character by character
void render_text(string text) {
    // renders the text one by one
    for(char c : text) {
        cout << c << flush;
        // waits 0.02 seconds per character
        wait(20);
    }
    // creates a new line
    cout << endl;
}

// prompt a string text
string prompt(string text) {
    // render the prompt text
    render_text(text);
    // displays the input text
    cout << " > " << flush;

    string s;
    s = input();

    // gets user input
    return s;
}


// prompt a number
int prompt_int(string text) {
    // render the prompt text
    render_text(text);
    // displays the input text
    cout << " > " << flush;

    // gets user input
    int i;
    string s = input();

    if(isNumeric(s)) {
        i = stoi(s);
    } else {
        prompt_int(text);
    }

    return i;
}

char choice2(string text, string _choice1, string _choice2) {
    // renders the prompt text with the choices
    render_text(text);
    render_text("   1) " + _choice1 + ", 2) " + _choice2);

    // user input
    string picked;

    cout << " > " << flush;
    picked = input();

    // if input is within the choices then exit loop
    if(picked[0] == '1' || picked[0] == '2') {
        return picked[0];
    } else {
        choice2(text, _choice1, _choice2);
    }

    return '0';
}

char choice3(string text, string _choice1, string _choice2, string _choice3) {
    // renders the prompt text with the choices
    render_text(text);
    render_text("   1) " + _choice1 + ", 2) " + _choice2 + ", 3) " + _choice3);

    // user input
    string picked;

    cout << " > " << flush;
    picked = input();

    // if input is within the choices then exit loop
    if(picked[0] == '1' || picked[0] == '2' || picked[0] == '3') {
        return picked[0];
    } else {
        choice3(text, _choice1, _choice2, _choice3);
    }

    return '0';
}

char choice4(string text, string _choice1, string _choice2, string _choice3, string _choice4) {
    // renders the prompt text with the choices
    render_text(text);
    render_text("   1) " + _choice1 + ", 2) " + _choice2 + ", 3) " + _choice3 + ", 4) " + _choice4);

    // user input
    string picked;

    cout << " > " << flush;
    picked = input();

    // if input is within the choices then exit loop
    if(picked[0] == '1' || picked[0] == '2' || picked[0] == '3' || picked[0] == '4') {
        return picked[0];
    } else {
        choice4(text, _choice1, _choice2, _choice3, _choice4);
    }

    return '0';
}

// embeds the player's money into a string
string get_money() {
    return "($" + to_string(money) + ")";
}

void endings(string ending) {
    if(ending == "gabe") {
        render_text("GAME ENDED: Gabe Newell Ending");
    } else if(ending == "exile") {
        render_text("GAME ENDED: Exiled Ending");
    } else if(ending == "killed") {
        render_text("GAME ENDED: Murdered Ending");
    } else if(ending == "broke") {
        render_text("GAME ENDED: Bankrupt Ending");
    } else if(ending == "rich") {
        render_text("GAME ENDED: Monopoly Ending");
    }
    input();
    return;
}

void shop_dialog(int (*func)(int, int), Character customer) {
    char choice;
    // shop: corn dog, advertisement, exit shop
    choice = choice3("Shop: What would you like to do?    " + get_money() , "Buy corn dog", "Buy advertisement", "Exit shop");

    // corn dog
    if(choice == '1') {
        render_text("Corndogs cost $" + to_string(corndog_price) + " dollars");
        choice = choice2("Are you sure you want to buy this?    " + get_money(), "Yes", "No");

        // yes
        if(choice == '1') {
            if(money - corndog_price < 0) {
                render_text("You don't have enough money");
                shop_dialog(func, customer);
            } else {
                // TODO: make corn dogs and advertisements be able to bulk sell
                money -= corndog_price;
                corndogs += 1;
                render_text("You now have " + to_string(corndogs) + " corn dogs  -$" + to_string(corndog_price));
                if (func(0, 8) == 0) {
                    corndog_price += 1;
                }
                shop_dialog(func, customer);
            }
        // no
        } else {
            shop_dialog(func, customer);
        }
    
    // advertisement
    } else if(choice == '2') {
        render_text("Advertisements cost $" + to_string(advertisement_price) + " dollars");
        choice = choice2("Are you sure you want to buy this?    " + get_money(), "Yes", "No");

        // yes
        if(choice == '1') {
            if(money - advertisement_price < 0) {
                render_text("You don't have enough money");
                shop_dialog(func, customer);
            } else {
                money -= advertisement_price;
                popularity += 10;
                render_text("You have gained more popularity  -$" + to_string(advertisement_price));
                if (func(0, 4) == 0) {
                    advertisement_price += 2;
                }
                shop_dialog(func, customer);
            }

        // no
        } else {
            shop_dialog(func, customer);
        }

    // exit shop
    } else {
        corndog_value = prompt_int("Set the price of your corndogs; Current Price: $" + to_string(corndog_value));
        sell_dialog(customer, func);
    }
}

void sell_dialog(Character customer, int (*func)(int, int)) {
    char choice;
    render_text(customer.name + " walks up to your stand");
    choice = choice4("What do you do?", "Sell Corn Dog", "Small Talk", "Go To Shop", "Turn Down");
    if(choice == '1') {
        customer_dialog(customer, "sell", func);
    } else if(choice == '2') {
        customer_dialog(customer, "talk", func);
    } else if(choice == '3') {
       shop_dialog(func, customer);
       sell_dialog(customer, func);
    } else if(choice == '4') {
        customer_dialog(customer, "reject", func);
    }
}

void customer_dialog(Character customer, string dialog_choice, int (*func)(int, int)) {
    if(dialog_choice == "talk" && customer.mood <= 0) {
        say(customer, "I don't want to talk right now");
        return;
    }

    if(customer.isGabe) {
        if(dialog_choice == "sell") {
            endings("gabe");
        } else if(dialog_choice == "talk") {
            say(customer, "That was a excelent conversation");
        } else if(dialog_choice == "reject") {
            render_text(customer.name + " has left your stand");
            sell_dialog(create_character(func), func);
        }
    } else {
        if(customer.isMale) {
            if(customer.royalty) {
                if(dialog_choice == "sell") {
                    endings("gabe");
                } else if(dialog_choice == "talk") {
                    say(customer, "That was a excelent conversation");
                } else if(dialog_choice == "reject") {
                    render_text(customer.name + " has left your stand");
                    sell_dialog(create_character(func), func);
                }
            } else if(customer.peasant) {
                if(dialog_choice == "sell") {
                    endings("gabe");
                } else if(dialog_choice == "talk") {
                    say(customer, "That was a excelent conversation");
                } else if(dialog_choice == "reject") {
                    render_text(customer.name + " has left your stand");
                    sell_dialog(create_character(func), func);
                }
            } else {
                if(dialog_choice == "sell") {
                    endings("gabe");
                } else if(dialog_choice == "talk") {
                    say(customer, "That was a excelent conversation");
                } else if(dialog_choice == "reject") {
                    render_text(customer.name + " has left your stand");
                    sell_dialog(create_character(func), func);
                }
            }
        } else {
            if(customer.royalty) {
                if(dialog_choice == "sell") {
                    endings("gabe");
                } else if(dialog_choice == "talk") {
                    say(customer, "That was a excelent conversation");
                } else if(dialog_choice == "reject") {
                    render_text(customer.name + " has left your stand");
                    sell_dialog(create_character(func), func);
                }
            } else if(customer.peasant) {
                if(dialog_choice == "sell") {
                    endings("gabe");
                } else if(dialog_choice == "talk") {
                    say(customer, "That was a excelent conversation");
                } else if(dialog_choice == "reject") {
                    render_text(customer.name + " has left your stand");
                    sell_dialog(create_character(func), func);
                }
            } else {
                if(dialog_choice == "sell") {
                    endings("gabe");
                } else if(dialog_choice == "talk") {
                    say(customer, "That was a excelent conversation");
                } else if(dialog_choice == "reject") {
                    render_text(customer.name + " has left your stand");
                    sell_dialog(create_character(func), func);
                }
            }
        }
    }
    
}

