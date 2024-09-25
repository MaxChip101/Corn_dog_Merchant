#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cctype>

#include "player.h"
#include "shop.h"

using namespace std;

// console rendering and inputs

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


void wait(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

string input() {
    string inp_str;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        inp_str += ch;
    }
    return inp_str;
}

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

string get_money() {
    return "($" + to_string(money) + ")";
}

void shop_dialog(int (*func)(int, int)) {
    char choice; 
    choice = choice3("Shop: What would you like to do?    " + get_money() , "Buy corn dog", "Buy advertisement", "Exit shop");
    if(choice == '1') {
        render_text("Corndogs cost $" + to_string(corndog_price) + " dollars");
        choice = choice2("Are you sure you want to buy this?    " + get_money(), "Yes", "No");
        if(choice == '1') {
            if(money - corndog_price < 0) {
                render_text("You don't have enough money");
                shop_dialog(func);
            } else {
                money -= corndog_price;
                corndogs += 1;
                render_text("You now have " + to_string(corndogs) + " corn dogs  -$" + to_string(corndog_price));
                if (func(0, 8) == 0) {
                    corndog_price += 1;
                }
                shop_dialog(func);
            }
        } else {
            shop_dialog(func);
        }
    } else if(choice == '2') {
        render_text("Advertisements cost $" + to_string(advertisement_price) + " dollars");
        choice = choice2("Are you sure you want to buy this?    " + get_money(), "Yes", "No");
        if(choice == '1') {
            if(money - advertisement_price < 0) {
                render_text("You don't have enough money");
                shop_dialog(func);
            } else {
                money -= advertisement_price;
                popularity += 10;
                render_text("You have gained more popularity  -$" + to_string(advertisement_price));
                if (func(0, 4) == 0) {
                    advertisement_price += 2;
                }
                shop_dialog(func);
            }
        } else {
            shop_dialog(func);
        }
    } else {
        corndog_value = prompt_int("Set the price of your corndogs");
        return;
    }
}
