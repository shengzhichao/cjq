#ifndef menu_h
#define menu_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


void Recharge(long int number);
void Enter_User(long int number, int seat);
void Quit_User(int seat , long int number);

void SignIn_User_Menu();
void User_Menu();
void Manage_Menu();
void Seek_Menu();

void Main_Menu();


#endif