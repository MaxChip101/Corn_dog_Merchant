#include "dialog.h"
#include "customer.h"
#include "player.h"
#include "shop.h"
#include "dialogs2.h"

using namespace std;

void sell_dialog(Character customer, int (*func)(int, int)) {
    // if 10,000 dollars then end game
    if(money >= 10000) {
        endings("rich");
    }
    char choice;
    // shop
    render_text(customer.name + " walks up to your stand");
    choice = choice4("What do you do?    " + get_money() + ", " + get_corndogs(), "Sell Corn Dog", "Small Talk", "Go To Shop", "Turn Down");
    // sell
    if(choice == '1') {
        customer_dialog(customer, "sell", func);
    // small talk
    } else if(choice == '2') {
        customer_dialog(customer, "talk", func);
    // shop
    } else if(choice == '3') {
       shop_dialog(func, customer);
    // turn down
    } else if(choice == '4') {
        customer_dialog(customer, "reject", func);
    }
}