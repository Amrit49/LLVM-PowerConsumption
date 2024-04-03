#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    // Creating a HashMap to store vectors of integers
    std::unordered_map<std::string, std::vector<int>> map;

    // Creating and populating vectors
    std::vector<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    std::vector<int> list2;
    list2.push_back(40);
    list2.push_back(50);

    // Inserting vectors into the HashMap
    map["list1"] = list1;
    map["list2"] = list2;

    // Retrieving vectors from the HashMap and printing their elements
    std::cout << "Elements of list1:" << std::endl;
    for (int num : map["list1"]) {
        std::cout << num << std::endl;
    }

    std::cout << "Elements of list2:" << std::endl;
    for (int num : map["list2"]) {
        std::cout << num << std::endl;
    }

    return 0;
}
