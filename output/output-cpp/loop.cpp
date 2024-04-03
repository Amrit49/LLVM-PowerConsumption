#include <iostream>

int main() {
    int num = 10;
    if (num > 5) {
        std::cout << "Number is greater than 5." << std::endl;
    } else {
        std::cout << "Number is less than or equal to 5." << std::endl;
    }

    int i = 0;
    while (i < 5) {
        std::cout << "While loop iteration: " << i << std::endl;
        i++;
        int j = 0;
        while (j < 5) {
            std::cout << "While loop iteration: " << j << std::endl;
            j++;
        }
    }

    for (int j = 0; j < 5; j++) {
        std::cout << "For loop iteration: " << j << std::endl;
    }

    int a = 5;
    int b = 3;
    int result = (a * b) + (a / b);

    std::cout << "Result of arithmetic expression: " << result << std::endl;

    return 0;
}
