# LLVM Power Consumption Analysis

This project implements an LLVM pass to analyze the power consumption of every basic block within a Java application. The pass is designed to work with LLVM's intermediate representation (IR) generated from Java byte code, allowing for power consumption analysis at a low-level code representation.

## Prerequisites

Ensure the following software is installed on your system:
1. LLVM
2. CLang
3. CPP
4. Java
5. Python
6. Selenium

## Installation

1. Install CLang and LLVM. For Ubuntu use the following commands:
    ```bash
    $ sudo apt-get update
    $ sudo apt-get install clang llvm
    ```

2. Install C++ compiler. For Ubuntu use the following command:
    ```bash
    $ sudo apt-get install g++
    ```

3. Install Java Development Kit (JDK). For Ubuntu use the following command:
    ```bash
    $ sudo apt-get install default-jdk
    ```

4. Install Python. For Ubuntu use the following command:
    ```bash
    $ sudo apt-get install python3
    ```

5. Follow the [Selenium documentation](https://selenium-python.readthedocs.io/) to set up Selenium on your system.

## Usage

1. Clone the repository and navigate to the project directory.
    ```bash
    $ git clone https://github.com/Amrit49/LLVM-PowerConsumption.git
    $ cd LLVM-PowerConsumption
    ```

2. Create a Java file and convert it to CPP.
    ```bash
    $ touch test.java
    $ nano test.java
    $ python3 javatocpp.py
    ```

3. Generate LLVM IR (.ll) file from the CPP file.
    ```bash
    $ clang++ -S -emit-llvm <filename>.cpp -o <filename>.ll
    ```

4. Execute the LLVM pass to get power consumption.
    ```bash
    $ clang++ -shared -o power-consumption.so power-consumption.cpp $(llvm-config --cxxflags --ldflags --libs) -lncurses -fPIC
    $ opt -enable-new-pm=0 -load ./<filename>.so -<filename> < <filename>.ll > /dev/null
    ```


5. (Additional) Execute the LLVM pass to get instruction information.
    ```bash
    $ clang++ -shared -o instruction-info.so instruction-info.cpp $(llvm-config --cxxflags --ldflags --libs) -lncurses -fPIC
    $ opt -enable-new-pm=0 -load ./<filename>.so -<filename> < <filename>.ll > /dev/null
    ```
   

## Files

1. **power-consumption.cpp** - This LLVM pass calculates the power consumption for each basic block within a function. It considers various factors such as instruction types, loop iterations, and recursion calls to compute an estimate of power consumption in the analyzed code.

2. **instruction-info.cpp** - This LLVM pass traverses through each function in the input code and prints out the LLVM IR representation of each instruction within every basic block, providing detailed information about the instructions present in the code.

3. **javatocpp.py** - This Python script utilizes the Selenium WebDriver to automate the conversion of Java code to C++ code using an online tool provided by CodePorting. This automation streamlines the process of converting Java code to C++, facilitating the use of C++ for LLVM Intermediate Representation (IR) generation without manual intervention.

## Power Consumption Calculation

The power consumption is calculated based on the following factors:

1. **HandleRecursion()** - This function iterates through each instruction in a basic block and checks if it corresponds to a function call. If the called function matches itself, it increments the value. Finally, it returns the accumulated value, which represents the power consumption attributed to recursive function calls within the basic block.

2. **IterationCount()** - This function counts the number of iterations for loops present within a given LLVM basic block and updates a global vector with the iteration counts or placeholders for loops with undetermined iteration counts.

3. **calculateLoopDepth()** - This function calculates the loop depth for a given LLVM basic block by utilizing LLVM's LoopInfo analysis.

4. **calculateBlockPower()** - This function calculates the power consumption for a given LLVM basic block by iterating over each instruction within the block. It assigns power values to different types of instructions based on their operation, such as arithmetic, memory access, control flow, type conversion, and others. The power values are determined according to the information in research papers and the complexity of each instructions operation.

5. **calculateFullBlockpower()** - This function calculates the power consumption for a given LLVM basic block within a function. It computes the power by considering the power contribution of each instruction in the block, adjusting for loop iterations and recursion if present. The power is determined based on how many times the loop is running or if any recursion is present, and multiplies the power by the corresponding loop iteration counts or recursion values.

## References

1. [Static analysis of energy consumption for LLVM IR programs Neville Grech, Kyriakos Georgiou, James Pallister, Steve Kerrison, Jeremy Morse and Kerstin Eder University of Bristol, Merchant Venturers Building, Woodland Road Bristol, BS8 1UB, United Kingdom](https://www.nevillegrech.com/assets/pdf/llvm-energy-scopes.pdf)

2. [Alexei Colin and Brandon Lucia. 2018. Termination checking and task decomposition for task-based intermittent programs. In Proceedings of the 27th International Conference on Compiler Construction (CC 2018). Association for Computing Machinery, New York, NY, USA, 116–127](https://dl.acm.org/doi/10.1145/3178372.3179525)
