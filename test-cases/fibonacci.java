import java.io.*;

// Parent class with a method to print Fibonacci sequence
class Fibonacci {
    protected int[] memo;

    public Fibonacci(int n) {
        memo = new int[n + 1];
    }

    public void printFibonacci(int n) {
        for (int i = 1; i <= n; i++) {
            System.out.print(fibonacci(i) + " ");
        }
    }

    protected int fibonacci(int n) {
        if (memo[n] != 0)
            return memo[n];
        if (n == 1 || n == 2)
            return 1;
        else {
            memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
            return memo[n];
        }
    }
}

// Subclass inheriting from the parent class
class GFG extends Fibonacci {
    public GFG(int n) {
        super(n);
    }
    
    // Override the printFibonacci method if necessary
    // public void printFibonacci(int n) {
    //     super.printFibonacci(n);
    // }
}

// Main class with the main method
public class Main {
    public static void main(String[] args) {
        int n = 10; // Number of terms to print
        GFG gfg = new GFG(n);
        gfg.printFibonacci(n);
    }
}
