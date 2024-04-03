#include <iostream>
#include <vector>

// Parent class with a method to print Fibonacci sequence
class Fibonacci {
protected:
    std::vector<int> memo;

public:
    Fibonacci(int n) {
        memo.resize(n + 1);
    }

    void printFibonacci(int n) {
        for (int i = 1; i <= n; i++) {
            std::cout << fibonacci(i) << " ";
        }
    }

protected:
    int fibonacci(int n) {
        if (memo[n] != 0)
            return memo[n];
        if (n == 1 || n == 2)
            return 1;
        else {
            memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
            return memo[n];
        }
    }
};

// Subclass inheriting from the parent class
class GFG : public Fibonacci {
public:
    GFG(int n) : Fibonacci(n) {}

    // Override the printFibonacci method if necessary
    // void printFibonacci(int n) {
    //     Fibonacci::printFibonacci(n);
    // }
};

// Main class with the main method
int main() {
    int n = 10; // Number of terms to print
    GFG gfg(n);
    gfg.printFibonacci(n);

    return 0;
}
