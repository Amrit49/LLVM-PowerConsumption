#include <iostream>
#include <cmath>

using namespace std;

int main() {

    char operation;
    double number1, number2, result;

    cout << "Choose an operator: +, -, *, /, % (for modulo), or // (for floor division)" << endl;
    cin >> operation;

    cout << "Enter first number" << endl;
    cin >> number1;

    cout << "Enter second number" << endl;
    cin >> number2;

    switch (operation) {

        case '+':
            result = number1 + number2;
            cout << number1 << " + " << number2 << " = " << result << endl;
            break;

        case '-':
            result = number1 - number2;
            cout << number1 << " - " << number2 << " = " << result << endl;
            break;

        case '*':
            result = number1 * number2;
            cout << number1 << " * " << number2 << " = " << result << endl;
            break;

        case '/':
            if (number2 != 0) {
                result = number1 / number2;
                cout << number1 << " / " << number2 << " = " << result << endl;
            } else {
                cout << "Error: Cannot divide by zero!" << endl;
            }
            break;

        case '%':
            result = fmod(number1, number2);
            cout << number1 << " % " << number2 << " = " << result << endl;
            break;

        case '//':
            if (number2 != 0) {
                result = floor(number1 / number2);
                cout << number1 << " // " << number2 << " = " << result << endl;
            } else {
                cout << "Error: Cannot divide by zero!" << endl;
            }
            break;

        default:
            cout << "Invalid operator!" << endl;
            break;
    }

    return 0;
}
