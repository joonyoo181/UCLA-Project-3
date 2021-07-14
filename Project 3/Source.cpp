#include <iostream>
#include <cassert>

using namespace std;

int extractNumber(string s, size_t index);

bool isValidElevatorString(string elevatorstring);
bool doorsOpen(string elevatorstring);
int endingPassengers(string elevatorstring);
int mostPassengers(string elevatorstring);
int endingFloor(string elevatorstring);
int highestFloor(string elevatorstring);

int main() {
    assert(isValidElevatorString("") == false);
    assert(isValidElevatorString("    ") == false);
    assert(doorsOpen("    ") == false);
    assert(endingPassengers("      ") == -1);
    assert(mostPassengers("      ") == -1);
    assert(endingFloor("       ") == -1);
    assert(highestFloor("       ") == -1);
    assert(isValidElevatorString("M1O+3-2C"));
    assert(doorsOpen("M1O+3-2C") == false);
    assert(endingPassengers("M1O+3-2C") == 1);
    assert(mostPassengers("M1O+3-2C") == 3);
    assert(endingFloor("M1O+3-2C") == 1);
    assert(highestFloor("M1O+3-2C") == 1);

    cout << "All tests succeeded" << endl;
    return 0;
}

int extractNumber(string s, size_t index){
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

bool isValidElevatorString(string elevatorstring) {
    string str = elevatorstring;

    //make sure the string is more than the length of 1
    if (str.length() >= 2) {

        char c;
        bool isOpen = false;
        int people = 0;

        for (size_t pos = 0; pos < str.length(); pos++) {
            c = str.at(pos);

            if (pos == 0) {
                if (c == 'M') {
                    //continue
                }
                else {
                    return false;
                }
            }

            //check if the only characters present are M, O, C, +, -, and digit chars
            if (c < '+' || c == 44 || (c > '-' && c < '0') ||
                (c > '9' && c < 'C') || (c > 'C' && c < 'M') ||
                (c > 'M' && c < 'O') || c > 'O') {
                return false;
            }

            //check that when the elevator moves, the door is closed
            if (c == 'M') {
                if (!isOpen) {
                    //check that when the elevator moves, it is followed by a number
                    if (str.at(pos + 1) > '0' && str.at(pos + 1) <= '9') {
                        //emptied for readability
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }

            //check to see that the door was closed before opening
            if (c == 'O') {
                if (!isOpen) {
                    isOpen = true;
                }
                else {
                    return false;
                }
            }

            //check to see that the door was opened before closing
            if (c == 'C') {
                if (isOpen) {
                    isOpen = false;
                }
                else {
                    return false;
                }
            }

            //if there is a plus sign, then check to see that the door is open
            if (c == '+') {

                //update number of ppl in the elevator
                if (isOpen) {
                    people += extractNumber(str, pos + 1);
                }
                else {
                    return false;
                }
            }

            //if there is a minus sign, then check to see that the door is open
            if (c == '-') {

                //update number of ppl in the elevator
                if (isOpen) {
                    people -= extractNumber(str, pos + 1);
                }
                else {
                    return false;
                }
            }

            //check if there is negative number of ppl in elevator
            if (people < 0) {
                return false;
            }
        }

        //check that the string ends with 'O', 'C', or a digit character
        char lastChar = str.at(str.length() - 1);
        if (lastChar == 'O' || lastChar == 'C' || (lastChar >= '0' && lastChar <= '9')) {
            //emptied for readability
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

    return true;
}

bool doorsOpen(string elevatorstring) {
    string str = elevatorstring;

    bool isOpen = false;

    //check if valid string
    if (isValidElevatorString(str)) {
        char c;

        //iterating thru each char and changeing the isOpen variable
        for (size_t pos = 0; pos < str.length(); pos++) {
            c = str.at(pos);

            if (c == 'O') {
                isOpen = true;
            }
            if (c == 'C') {
                isOpen = false;
            }
        }
    }

    return isOpen;
}

int endingPassengers(string elevatorstring) {
    string str = elevatorstring;

    int people = 0;

    //check if valid string
    if (isValidElevatorString(str)) {
        char c;

        //iterating thru each char and updating the number of ppl onboard
        for (size_t pos = 0; pos < str.length(); pos++) {
            c = str.at(pos);

            if (c == '+') {
                people += extractNumber(str, pos+1);
            }
            if (c == '-') {
                people -= extractNumber(str, pos + 1);
            }
        }
    }
    else {
        return -1;
    }

    return people;
}

int mostPassengers(string elevatorstring) {
    string str = elevatorstring;

    int max_ppl = INT_MIN;
    int people = 0;

    //check if valid string
    if (isValidElevatorString(str)) {
        char c;

        //iterating thru each char and updating number of ppl onboard
        for (size_t pos = 0; pos < str.length(); pos++) {
            c = str.at(pos);

            if (c == '+') {
                people += extractNumber(str, pos + 1);
            }
            if (c == '-') {
                people -= extractNumber(str, pos + 1);
            }

            //if the current number of ppl onboard is greater than the previous greatest number, set a new greatest number
            if (people > max_ppl) {
                max_ppl = people;
            }
        }
    }
    else {
        return -1;
    }

    return people;
}

int endingFloor(string elevatorstring) {
    string str = elevatorstring;

    int floor = 0;

    //check if valid string
    if (isValidElevatorString(str)) {
        char c;

        //iterating thru each char and set floor value
        for (size_t pos = 0; pos < str.length(); pos++) {
            c = str.at(pos);

            //set the floor variable as the number that follows 'M'
            if (c == 'M') {
                floor = extractNumber(str, pos + 1);
            }
        }
    }
    else {
        return -1;
    }

    return floor;
}

int highestFloor(string elevatorstring) {
    string str = elevatorstring;

    int max_floor = INT_MIN;
    int floor = 0;

    //check if valid string
    if (isValidElevatorString(str)) {
        char c;

        //iterating thru each char until it reaches 'M'
        for (size_t pos = 0; pos < str.length(); pos++) {
            c = str.at(pos);

            //set the floor variable
            if (c == 'M') {
                floor = extractNumber(str, pos + 1);
            }

            //if the current floor variable is larger than the max_floor variable, set max_floor to current floor.
            if (floor > max_floor) {
                max_floor = floor;
            }
        }
    }
    else {
        return -1;
    }

    return max_floor;
}