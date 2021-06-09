#include <iostream>

int main()
{
    // need to tell the size.
    std::cout << "How long do you want the string? ";
    int size = 0;
    std::cin >> size;
    char *input = new char[size+1]();
    std::cin.ignore();
    std::cout << "input the string: ";
    std::cin.get(input, size+1);
    std::cout << input;
    delete [] input;
    // Test: if longer than the array size, we will lost the characters which are out of range.
}