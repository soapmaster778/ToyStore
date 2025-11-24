#include "InputValidator.h"

int InputValidator::ReadInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max)
                return value;
            else
                std::cout << "[WARN] Значення має бути в діапазоні [" << min << ", " << max << "].\n";
        } else {
            std::cout << "[ERROR] Некоректне введення. Введіть ціле число.\n";
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double InputValidator::ReadDouble(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max)
                return value;
            else
                std::cout << "[WARN] Значення має бути в діапазоні [" << min << ", " << max << "].\n";
        } else {
            std::cout << "[ERROR] Некоректне введення. Введіть дійсне число.\n";
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string InputValidator::ReadString(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::cin >> s;
    while (s.empty()) {
        std::cout << "[WARN] Рядок не може бути порожнім.\n" << prompt;
        std::cin >> s;
    }
    return s;
}
