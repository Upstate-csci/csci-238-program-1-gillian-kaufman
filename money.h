/********
 Author: Gillian Kaufman   
 Program: Money class - program assignment #1
 Due Date: February 3, 2020
 Purpose: Header file for program assignment #1
 ********/
#ifndef MONEY_H
#define MONEY_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <locale>

using namespace std;
class Money
{
private:
    double total;
    int hundreds, tens, fives, ones, quarters, dimes, nickels, pennies;
public:
    string toString();
    string toCurrency(double amount);
    string processChange();
    string processFloat();
    string processCheck();
    string processChangeFloat();
    string processChangeChange();
};
#endif
