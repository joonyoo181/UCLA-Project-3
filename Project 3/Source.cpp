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
}

int extractNumber(string s, size_t & index){
    int quantity(0);
    bool foundADigit = false;

    while (index < s.size()){
        char c = s.at(index);

        if (c >= '0' && c <= '9'){
            foundADigit = true;
            int digit = c - '0';
            quantity = quantity * 10 + digit;
            index = index + 1;
        }
        else{
            break;
        }
    }
    if (!foundADigit){
        quantity = -1;
    }
    return(quantity);
}