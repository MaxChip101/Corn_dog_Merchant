#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cctype>

#include "player.h"
#include "shop.h"
#include "customer.h"
#include "dialogs2.h"
#include "dialog.h"

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

string get_corndogs() {
    return "corn dogs: " + to_string(corndogs);
}

void endings(string ending) {

    // trigger different endings
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
    exit(0);
}

void customer_dialog(Character customer, string dialog_choice, int (*func)(int, int)) {

    // if the customer does not have any mood left
    if(dialog_choice == "talk" && customer.mood <= 0) {
        say(customer, "I don't want to talk right now");
        sell_dialog(customer, func);
    }

    // if the customer is gabe newell
    if(customer.isGabe) {
        // sell
        if(dialog_choice == "sell") {
            if(sellable()) {
                // gabe newell ending
                endings("gabe");
            } else {
                // if there are no corn dogs then it will send you to the shop
                render_text("Not enough corn dogs, going to shop");
                shop_dialog(func, customer);
            }
        // talk
        } else if(dialog_choice == "talk") {
            // always positive
            say(customer, "That was an excellent conversation");
            sell_dialog(customer, func);
        // turn down
        } else if(dialog_choice == "reject") {
            render_text(customer.name + " has left your stand");
            sell_dialog(create_character(func), func);
        }
    } else {
        // male
        if(customer.isMale) {
            // royalty
            if(customer.royalty) {
                // sell
                if(dialog_choice == "sell") {
                    if(sellable()) {
                        if(respectable(customer)) {
                            // sell corn dog
                            sell();
                            say(customer, "I deeply applaud you Merchant");
                        } else {
                            // increase prices if the price is too high
                            say(customer, "That is not a reasonable price might I add");
                            render_text(customer.name + " has left your stand");
                            corndog_price += 1;
                        }
                        sell_dialog(create_character(func), func);
                    } else {
                        // if there are no corn dogs then it will send you to the shop
                        render_text("Not enough corn dogs, going to shop");
                        shop_dialog(func, customer);
                    }
                // talk
                } else if(dialog_choice == "talk") {
                    if(func(0, 2) == 0) {
                        // if talk was good then there is a chance for a tip and it also decreases the corndog price
                        say(customer, "I am greatly ammused by your chatter");
                        if (corndog_price - 1 > 0) {
                            // reduce price
                            corndog_price -= 1;
                            // tip
                            if (func(0, 4) == 0) {
                                render_text(customer.name + " has left a tip of $1");
                                money += 1;
                            }
                        }
                        customer.mood -= 0.1;
                    } else {
                        // decreases hapiness if it is a bad talk
                        say(customer, "I am greatly discouraged by your chatter");
                        customer.mood -= 0.2;
                        customer.happiness -= 0.2;
                    }
                    sell_dialog(customer, func);
                } else if(dialog_choice == "reject") {
                    // if the customer is happy then the customer will leave but otherwise the customer will exile you
                    if(customer.happiness >= 0.2) {
                        // leave
                        render_text(customer.name + " has left your stand");
                        sell_dialog(create_character(func), func);
                    } else {
                        // exile
                        endings("exile");
                    }
                }
            // peasant
            } else if(customer.peasant) {
                // sell
                if(dialog_choice == "sell") {
                    if(sellable()) {
                        // sell corn dog
                        if(respectable(customer)) {
                            sell();
                            say(customer, "Thank you :)");
                        } else {
                            // increase prices if the price is too high
                            say(customer, "I'm reporting this to the opps");
                            render_text(customer.name + " has left your stand");
                            corndog_price += 1;
                        }
                    } else {
                            // if no corndogs then it will bring you to shop
                            render_text("Not enough corn dogs, going to shop");
                            shop_dialog(func, customer);
                        }
                        sell_dialog(create_character(func), func);
                // talk
                } else if(dialog_choice == "talk") {
                    if(func(0, 2) == 0) {
                        // if the talk was good
                        say(customer, "Nice Talk :)");
                        if (corndog_price - 1 > 0) {
                            // decrease corndog price
                            corndog_price -= 1;
                            // tip
                            if (func(0, 4) == 0) {
                                render_text(customer.name + " has left a tip of $1");
                                money += 1;
                            }
                        }
                        customer.mood -= 0.1;
                    } else {
                        // if the talk was bad decrease hapiness
                        say(customer, "Bad Talk :(");
                        customer.mood -= 0.2;
                        customer.happiness -= 0.2;
                    }
                    sell_dialog(customer, func);
                // turn down
                } else if(dialog_choice == "reject") {
                    // if happiness is above 0.2
                    if(customer.happiness >= 0.2) {
                        // leave stand
                        render_text(customer.name + " has left your stand");
                        sell_dialog(create_character(func), func);
                    } else {
                        // customer kills you
                        endings("killed");
                    }
                }
            // middle class
            } else {
                // sell
                if(dialog_choice == "sell") {
                    if(sellable()) {
                        if(respectable(customer)) {
                            // sell corn dog
                            sell();
                            say(customer, "Thank you");
                        } else {
                            // if price too high then increase prices
                            say(customer, "This is outrageous");
                            render_text(customer.name + " has left your stand");
                            corndog_price += 1;
                        }
                    } else {
                        // if not enough corn dogs then go to shop
                        render_text("Not enough corn dogs, going to shop");
                        shop_dialog(func, customer);
                    }
                    sell_dialog(create_character(func), func);
                // talk
                } else if(dialog_choice == "talk") {
                    if(func(0, 2) == 0) {
                        // good talk
                        say(customer, "That was a nice chatter");
                        if (corndog_price - 1 > 0) {
                            // decrease price
                            corndog_price -= 1;
                            // tip
                            if (func(0, 4) == 0) {
                                render_text(customer.name + " has left a tip of $1");
                                money += 1;
                            }
                        }
                        customer.mood -= 0.1;
                    } else {
                        // decrease happiness if bad talk
                        say(customer, "that was a bad chatter");
                        customer.mood -= 0.2;
                        customer.happiness -= 0.2;
                    }
                    sell_dialog(customer, func);
                // turn down
                } else if(dialog_choice == "reject") {
                    // if happiness is above 0.2
                    if(customer.happiness >= 0.2) {
                        // leave stand
                        render_text(customer.name + " has left your stand");
                        sell_dialog(create_character(func), func);
                    } else {
                        // decrease popularity
                        say(customer, "I will be decreasing your fame");
                        if (popularity - 5 >= 0) {
                            popularity -= 5;
                        }
                        sell_dialog(create_character(func), func);
                    }
                }
            }
        // female
        } else {
            // royalty
            if(customer.royalty) {
                // sell
                if(dialog_choice == "sell") {
                    if(sellable()) {
                        if(respectable(customer)) {
                            // sell corn dog
                            sell();
                            say(customer, "I applaud you");
                        } else {
                            // if price too high then increase price
                            say(customer, "That is not a reasonable price might I add");
                            render_text(customer.name + " has left your stand");
                            corndog_price += 1;
                        }
                    } else {
                        // if no corn dogs then go to shop
                        render_text("Not enough corn dogs, going to shop");
                        shop_dialog(func, customer);
                    }
                        sell_dialog(create_character(func), func);
                // talk
                } else if(dialog_choice == "talk") {
                    if(func(0, 2) == 0) {
                        // good talk
                        say(customer, "I am greatly pleased by your chatter");
                        if (corndog_price - 1 > 0) {
                            // decrease price
                            corndog_price -= 1;
                            // tip
                            if (func(0, 4) == 0) {
                                render_text(customer.name + " has left a tip of $1");
                                money += 1;
                            }
                        }
                        customer.mood -= 0.1;
                    } else {
                        // bad talk, decrease happiness
                        say(customer, "I am greatly offended by your chatter");
                        customer.mood -= 0.2;
                        customer.happiness -= 0.2;
                    }
                    sell_dialog(customer, func);
                // turn down
                } else if(dialog_choice == "reject") {
                    // if happiness above 0.2
                    if(customer.happiness >= 0.2) {
                        // leave stand
                        render_text(customer.name + " has left your stand");
                        sell_dialog(create_character(func), func);
                    } else {
                        // exile player
                        endings("exile");
                    }
                }
            // peasant
            } else if(customer.peasant) {
                // sell
                if(dialog_choice == "sell") {
                    if(sellable()) {
                        if(respectable(customer)) {
                            // sell corn dog
                            sell();
                            say(customer, "Thank :)");
                        } else {
                            // if price too high then increase price
                            say(customer, "Bad Price :(");
                            render_text(customer.name + " has left your stand");
                            corndog_price += 1;
                        }
                    } else {
                        // if you have no corn dogs then it will send you to the shop
                        render_text("Not enough corn dogs, going to shop");
                        shop_dialog(func, customer);
                    }
                    sell_dialog(create_character(func), func);
                // talk
                } else if(dialog_choice == "talk") {
                    if(func(0, 2) == 0) {
                        // nice talk
                        say(customer, "Nice Talk :)");
                        if (corndog_price - 1 > 0) {
                            // decrease price
                            corndog_price -= 1;
                            // tip
                            if (func(0, 4) == 0) {
                                render_text(customer.name + " has left a tip of $1");
                                money += 1;
                            }
                        }
                        customer.mood -= 0.1;
                    } else {
                        // decrease happiness
                        say(customer, "Bad Talk :(");
                        customer.mood -= 0.2;
                        customer.happiness -= 0.2;
                    }
                    sell_dialog(customer, func);
                // turn down
                } else if(dialog_choice == "reject") {
                    // if happiness above 0.2
                    if(customer.happiness >= 0.2) {
                        // leave stand
                        render_text(customer.name + " has left your stand");
                        sell_dialog(create_character(func), func);
                    } else {
                        // kill player
                        endings("killed");
                    }
                }
            // middle class
            } else {
                // sell
                if(dialog_choice == "sell") {
                    if(sellable()) {
                        if(respectable(customer)) {
                                // sell corn dog
                                sell();
                                say(customer, "Thank you kind Merchant");
                            } else {
                                // if price too high then increase price
                                say(customer, "Yeah, no I'm not paying for this");
                                render_text(customer.name + " has left your stand");
                                corndog_price += 1;   
                            }
                    } else {
                            // if no corn dogs then go to shop
                            render_text("Not enough corn dogs, going to shop");
                            shop_dialog(func, customer);
                        }
                        sell_dialog(create_character(func), func);
                // talk
                } else if(dialog_choice == "talk") {
                    if(func(0, 2) == 0) {
                        // nice talk
                        say(customer, "That was a nice chatter");
                        if (corndog_price - 1 > 0) {
                            // decrease price
                            corndog_price -= 1;
                            // tip
                            if (func(0, 4) == 0) {
                                render_text(customer.name + " has left a tip of $1");
                                money += 1;
                            }
                        }
                        customer.mood -= 0.1;
                    } else {
                        // decrease happiness
                        say(customer, "That was a bad chatter");
                        customer.mood -= 0.2;
                        customer.happiness -= 0.2;
                    }
                    sell_dialog(customer, func);
                // turn down
                } else if(dialog_choice == "reject") {
                    // if happiness above 0.2
                    if(customer.happiness >= 0.2) {
                        // leave stand
                        render_text(customer.name + " has left your stand");
                        sell_dialog(create_character(func), func);
                    } else {
                        // decrease popularity
                        say(customer, "I will be decreasing your fame");
                        if (popularity - 5 >= 0) {
                            popularity -= 5;
                        }
                        sell_dialog(create_character(func), func);
                    }
                }
            }
        }
    }
}



void shop_dialog(int (*func)(int, int), Character customer) {
    char choice;
    // shop: corn dog, advertisement, exit shop
    choice = choice3("Shop: What would you like to do?    " + get_money() + ", " + get_corndogs() , "Buy corn dog", "Buy advertisement", "Exit shop");

    // corn dog
    if(choice == '1') {
        render_text("Corndogs cost $" + to_string(corndog_price) + " dollars");
        choice = choice2("Are you sure you want to buy this?    " + get_money(), "Yes", "No");

        // yes
        if(choice == '1') {
            int amount = prompt_int("How many corn dogs do you want to buy?");
            if(money - (corndog_price * amount) < 0) {
                render_text("You don't have enough money");
                shop_dialog(func, customer);
            } else {
                money -= corndog_price * amount;
                corndogs += 1 * amount;
                render_text("You now have " + to_string(corndogs) + " corn dogs  -$" + to_string(corndog_price * amount));
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
            int amount = prompt_int("How many advertisements do you want to buy?");
            if(money - (advertisement_price * amount) < 0) {
                render_text("You don't have enough money");
                shop_dialog(func, customer);
            } else {
                money -= advertisement_price * amount;
                popularity += 10 * amount;
                render_text("You have gained more popularity  -$" + to_string(advertisement_price * amount));
                if (func(0, 4) == 0) {
                    advertisement_price += 10;
                }
                shop_dialog(func, customer);
            }

        // no
        } else {
            shop_dialog(func, customer);
        }

    // exit shop
    } else {
        if (corndogs == 0 && money - corndog_price < 0) {
            endings("broke");
            return;
        } else {
            corndog_value = prompt_int("Set the price of your corndogs; Current Price: $" + to_string(corndog_value));
            sell_dialog(customer, func);
        }
    }
}