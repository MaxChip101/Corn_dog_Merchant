#ifndef DIALOG_H
#define DIALOG_H

#include <string>

using namespace std;

void wait(int milliseconds);
void render_text(string text);
string prompt(string text);
int prompt_int(string text);
int choice2(string text, string choice1, string choice2);
int choice3(string text, string choice1, string choice2, string choice3);
int choice4(string text, string choice1, string choice2, string choice3, string choice4);
void shop_dialog(int (*func)(int, int));

#endif