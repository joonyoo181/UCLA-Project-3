#include <iostream>

using namespace std;

int extractNumber(string s, size_t& index);

bool isValidElevatorString(string elevatorstring);
bool doorsOpen(string elevatorstring);
int endingPassengers(string elevatorstring);
int mostPassengers(string elevatorstring);
int endingFloor(string elevatorstring);
int highestFloor(string elevatorstring);

int main() {
    string s = "Helo 123 My name is..";
    size_t t = 5;
    cout << extractNumber(s, t);
}

int extractNumber(string s, size_t & index)
{
    // track the integer value found
    int quantity(0);
    bool foundADigit = false;

    while (index < s.size())
    {
        char c = s.at(index);
        // we are only interested in digit characters 0-9
        if (c >= '0' && c <= '9')
        {
            foundADigit = true;
            // extract one digit and add it to the cumulative 
            // value held in quantity
            int digit = c - '0';
            quantity = quantity * 10 + digit;
            index = index + 1;
        }
        else
        {
            break;
        }
    }
    if (!foundADigit)
    {
        quantity = -1;
    }
    return(quantity);
}