/********
 Author: Gillian Kaufman
 Program: Money class - program assignment #1
 Due Date: February 3, 2020
 Purpose: Class file for the money main driver
 ********/
#include "money.h"

// convert current currency values to a string
string Money::toString() 
{
    stringstream ss;

    ss << hundreds << " hundreds " << tens << " tens " << fives << " fives " << ones << " ones " << quarters <<
        " quarters " << dimes << " dimes " << nickels << " nickels " << pennies << " pennies";

    return ss.str();
}

// format amount as a local currency and return
string Money::toCurrency(double amount) 
{
    stringstream ss;
    ss.imbue(locale("")); 

    ss << showbase << put_money(amount * 100);

    return ss.str();
}

// convert currency to float
// read currency values from stdin and compute value
// return results
string Money::processChange() 
{   
    //Declare variables
    stringstream ss;
  
    //Get input
    cin >> hundreds >> tens >> fives >> ones >> quarters >> dimes >> nickels >> pennies;
  
    //Calculate change
    total = static_cast<double>(hundreds) * 100 + static_cast<double>(tens) * 10 + static_cast<double>(fives) * 5 + static_cast<double>(ones) * 1
        + static_cast<double>(quarters) * 0.25 + static_cast<double>(dimes) * 0.10 + static_cast<double>(nickels) * 0.05 + static_cast<double>(pennies) * 0.01;
   
    //Output change
    ss << toString() << " = " << toCurrency(total);
    return ss.str();
}

// read from stdin and process float command
// convert float to change
// return results
string Money::processFloat() 
{   
    //Declare variables
    double number;
    stringstream ss;

    //Get input
    cin >> total;

    //Find change
    hundreds = total / 100;             //Get number of hundreds
    number = total - (hundreds*100);
    tens = number / 10;                 //Get number of tens
    number -= (tens*10);
    fives = number / 5;                 //Get number of fives
    number -= (fives * 5);
    ones = number/1;                    //Get number of ones
    number -= (ones * 1);
    quarters = number / 0.25;           //Get number of quarters
    number -= (quarters * 0.25);
    dimes = number/0.10;                //Get number of dimes
    number -= (dimes * 0.10);
    nickels = number/0.05;              //Get number of nickels
    number -= (nickels * 0.05);
    pennies = number/0.01;              //Get number of pennies

    //Output change
    ss << toString() << " = " << toCurrency(total);
    return ss.str();
}

// read from stdin and process check command
// convert float to dollar words & cents
// return results
string Money::processCheck() 
{
    //Declare variables
    string onesPlace[10] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string tensPlace[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen","sixteen", "seventeen", "eighteen", "nineteen"};
    string hundredsPlace[10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    string nameOfNumber = "";
    stringstream ss;
    int dollars, cents, temp;

    //Get total from input and change to dollar format
    cin >> total;

    //Calculate change
    dollars = (total / 100) * 100;
    cents = total * 100;
    cents = cents % 100;
    //Change dollars to words
    if (dollars < 10)                                       //If amount of dollars is less than 10
        nameOfNumber = onesPlace[dollars];
    else if (dollars < 20)                                  //If amount of dollars is less than 20
        nameOfNumber = hundredsPlace[dollars - 10];
    else if (dollars < 100)                                 //If amount of dollars is less than 100
    {
        nameOfNumber = hundredsPlace[dollars / 10];
        if ((dollars % 10) != 0)                            //If amount of dollars does not divide evenly
            nameOfNumber += " " + onesPlace[dollars % 10];
    }
    else if (dollars < 1000)                                //If amount of dollars is less than 1000
    {
        nameOfNumber = onesPlace[dollars / 100] + " hundred";

        //Temporary placeholder for larger dollar amounts
        temp = (dollars % 100);
        if (temp != 0)                           //If amount of dollars does not divide evenly
        {
            if (temp < 10)
                nameOfNumber += " " + hundredsPlace[temp];
            else if (temp > 10)
                nameOfNumber += " " + hundredsPlace[temp / 10] + " " + onesPlace[temp % 10];             
        }
    }
    else if (dollars < 10000)
    {
        nameOfNumber = onesPlace[dollars / 1000] + " thousand";
        temp = (dollars % 1000);
        if (temp != 0)
        {
            if (temp < 100)
            {
                nameOfNumber += " " + hundredsPlace[temp / 10] + " ";
                if (temp % 10 < 10)
                    nameOfNumber += onesPlace[temp % 10];
            }
            else if (temp > 100)
            {
                nameOfNumber += " " + onesPlace[temp / 100] + " hundred";
                temp = temp % 100;
                if (temp < 10)
                    nameOfNumber += " " + onesPlace[temp];
                else if (temp / 10 == 1)
                    nameOfNumber += " " + tensPlace[temp % 10];
                else if (temp > 10)
                    nameOfNumber += " " + hundredsPlace[temp / 10] + " " + onesPlace[temp % 10];
            }
        }
    }
    //Output result
    ss << "check for " << toCurrency(total) << " = " << nameOfNumber << " dollars and " << cents << " cents\n";
    return ss.str();
}

// read from stdin and process change-float command
// read float of customer payment
// read float of transaction cost
// calculate difference and compute change values
// return the results
string Money::processChangeFloat() 
{
    //Declare variables
    double amount, fromCustomer, number;
    stringstream ss;

    //Take in float inputs
    cin >> fromCustomer >> amount;

    //Calculate difference
    total = fromCustomer - amount;

    //Find change
    hundreds = total / 100;             //Get number of hundreds
    number = total - (hundreds * 100);
    tens = number / 10;                 //Get number of tens
    number -= (tens * 10);
    fives = number / 5;                 //Get number of fives
    number -= (fives * 5);
    ones = number / 1;                    //Get number of ones
    number -= (ones * 1);
    quarters = number / 0.25;           //Get number of quarters
    number -= (quarters * 0.25);
    dimes = number / 0.10;                //Get number of dimes
    number -= (dimes * 0.10);
    nickels = number / 0.05;              //Get number of nickels
    number -= (nickels * 0.05);
    pennies = number / 0.01;              //Get number of pennies
    if (((number -= (nickels * 0.05)) - number / 0.01) >= 0.01)
        ++pennies;

    //Output in change format
    ss << "change back on " << toCurrency(fromCustomer) << " for purchase of " << toCurrency(amount) << " is " << toCurrency(total) << " which is " << toString();
    return ss.str();
}

// read from stdin and process change-change command
// read change of customer payment
// read float of transaction cost
// calculate difference and compute change values
// output the results
string Money::processChangeChange() 
{
    //Declare variables
    stringstream ss;
    double amount, change, number;
   
    //Take in change and float input
    cin >> hundreds >> tens >> fives >> ones >> quarters >> dimes >> nickels >> pennies >> amount;
   
    //Calculate difference
    total = static_cast<double>(hundreds) * 100 + static_cast<double>(tens) * 10 + static_cast<double>(fives) * 5 + static_cast<double>(ones) * 1
        + static_cast<double>(quarters) * 0.25 + static_cast<double>(dimes) * 0.10 + static_cast<double>(nickels) * 0.05 + static_cast<double>(pennies) * 0.01;
    
    //Output the first set of change
    cout << "change back on " << toString();
    change = total - amount;

    //Calculate difference change
    hundreds = change / 100;             //Get number of hundreds
    number = change - (hundreds * 100);
    tens = number / 10;                 //Get number of tens
    number -= (tens * 10);
    fives = number / 5;                 //Get number of fives
    number -= (fives * 5);
    ones = number / 1;                    //Get number of ones
    number -= (ones * 1);
    quarters = number / 0.25;           //Get number of quarters
    number -= (quarters * 0.25);
    dimes = number / 0.10;                //Get number of dimes
    number -= (dimes * 0.10);
    nickels = number / 0.05;              //Get number of nickels
    number -= (nickels * 0.05);
    pennies = number / 0.01;              //Get number of pennies
    if (((number -= (nickels * 0.05)) - number / 0.01) >= 0.01)
        ++pennies;
   
    //Output change format
    ss << " for purchase of " << toCurrency(amount) << " is " << toCurrency(change) << " which is " << toString();
    return ss.str();
}
