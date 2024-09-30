#include "dialog.h"
#include "customer.h"
#include "player.h"
#include "shop.h"
#include "dialogs2.h"

using namespace std;

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