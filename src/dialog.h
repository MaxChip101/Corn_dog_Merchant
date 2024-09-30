#ifndef DIALOG_H
#define DIALOG_H

#include <string>
#include "customer.h"

using namespace std;

void wait(int milliseconds);
void render_text(string text);
string prompt(string text);
int prompt_int(string text);
char choice2(string text, string choice1, string choice2);
char choice3(string text, string choice1, string choice2, string choice3);
char choice4(string text, string choice1, string choice2, string choice3, string choice4);
void shop_dialog(int (*func)(int, int), Character character);
void customer_dialog(Character customer, string dialog_choice, int (*func)(int, int));
#endif
