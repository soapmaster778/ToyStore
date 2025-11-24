#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <limits>
#include <string>
#include <climits>

// Клас для безпечного зчитування даних з консолі
class InputValidator {
public:
    static int ReadInt(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
    static double ReadDouble(const std::string& prompt, double min = -1e9, double max = 1e9);
    static std::string ReadString(const std::string& prompt);
};

#endif
