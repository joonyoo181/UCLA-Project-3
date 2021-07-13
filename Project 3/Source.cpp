#include <iostream>
#include <cassert>

using namespace std;

int extractNumber(string s, size_t& index);

bool isValidElevatorString(string elevatorstring);
bool doorsOpen(string elevatorstring);
int endingPassengers(string elevatorstring);
int mostPassengers(string elevatorstring);
int endingFloor(string elevatorstring);
int highestFloor(string elevatorstring);

int main() {
    assert(isValidElevatorString("M") == false);
    assert(isValidElevatorString("M1C") == false);
    assert(isValidElevatorString("M1OCOO") == false);
    assert(isValidElevatorString("M1O-12+50") == false);
    assert(isValidElevatorString("M1O+4-3-1CM2O-1") == false);
    assert(isValidElevatorString("M1O+-C") == false);
    assert(isValidElevatorString("M-3") == false);
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

    //check if the elevator string begin with M followed by digits
    cout << "check if the elevator string begin with M followed by digits" << endl;
    if (str.at(0) == 'M') {
        cout << "in the if statement" << endl;
        if (str.at(1) >= '0' && str.at(1) <= '9') {
            cout << "in the second if statement" << endl;
            //emptied for readability
        }
        else {
            cout << "return at line 62" << endl;
            return false;
        }
    }
    else {
        cout << "return at line 67" << endl;
        return false;
    }

    char c;
    bool isOpen = false;
    int people = 0;
    for (size_t pos = 0; pos < str.length(); pos++) {
        c = str.at(pos);

        //check if the only characters present are M, O, C, +, -, and digit chars
        cout << "check if the only characters present are M, O, C, +, -, and digit chars" << endl;
        if (c < '+' || c == 44 || (c > '-' && c < '0') || 
            (c > '9' && c < 'C') || (c > 'C' && c < 'M') || 
            (c > 'M' && c < 'O') || c > 'O') {
            cout << "return at line 81" << endl;
            return false;
        }

        //check that when the elevator moves, the door is closed
        cout << "check that when the elevator moves, the door is closed" << endl;
        if (c == 'M'){
            if (!isOpen) {
                //check that when the elevator moves, it is followed by a number
                cout << "check that when the elevator moves, it is followed by a number" << endl;
                if (str.at(pos + 1) >= '0' && str.at(pos + 1) <= '9') {
                    //emptied for readability
                }
                else {
                    cout << "return at line 92" << endl;
                    return false;
                }
            }
            else {
                cout << "return at line 97" << endl;
                return false;
            }
        }

        //check to see that the door was closed before opening
        cout << "check to see that the door was closed before opening" << endl;
        if (c == 'O'){
            if (!isOpen) {
                isOpen = true;
            }
            else {
                cout << "return at line 107" << endl;
                return false;
            }
        }

        //check to see that the door was opened before closing
        cout << "check to see that the door was opened before closing" << endl;
        if (c == 'C'){
            if (isOpen) {
                isOpen = false;
            }
            else {
                cout << "return at line 118" << endl;
                return false;
            }
        }

        //if there is a plus sign, then check to see that the door is open
        cout << "if there is a plus sign, then check to see that the door is open" << endl;
        if (c == '+'){
            if (isOpen) {
                people += extractNumber(str, pos + 1);
            }
            else {
                cout << "return at line 124" << endl;
                return false;
            }
        }

        //if there is a minus sign, then check to see that the door is open
        cout << "if there is a minus sign, then check to see that the door is open" << endl;
        if (c == '-' ){
            if (isOpen) {
                people -= extractNumber(str, pos + 1);
            }
            else {
                cout << "return at line 133" << endl;
                return false;
            }
        }

        //check if there is negative number of ppl in elevator
        cout << "check if there is negative number of ppl in elevator" << endl;
        if (people < 0) {
            cout << "return at line 139" << endl;
            return false;
        }
    }

    char lastChar = str.at(str.length() - 1);
    if (lastChar == 'O' || lastChar == 'C' || (lastChar >= '0' && lastChar <= '9')) {
        //emptied for readability
    }
    else {
        cout << "return at line 149" << endl;
        return false;
    }

    return true;
}