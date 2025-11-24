#include "UserManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

UserManager::UserManager() {
    EnsureAdminExists();
}

// Переконуємось, що існує користувач admin
void UserManager::EnsureAdminExists() {
    try {
        std::ifstream f(file);
        bool adminFound = false;
        std::string line;

        if (f.is_open()) {
            while (std::getline(f, line)) {
                std::stringstream ss(line);
                std::string login, password;
                std::getline(ss, login, ':');
                std::getline(ss, password);
                if (login == "admin") {
                    adminFound = true;
                    break;
                }
            }
            f.close();
        }

        if (!adminFound) {
            std::ofstream out(file, std::ios::app);
            if (!out.is_open()) {
                throw std::runtime_error("Не вдалося створити файл users.txt");
            }
            out << "admin:admin123\n";
            std::cout << "[INFO] Користувача admin створено автоматично (admin/admin123).\n";
        }
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

bool UserManager::IsUserExists(const std::string& login) {
    std::ifstream f(file);
    std::string line;

    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string u, p;
        std::getline(ss, u, ':');
        std::getline(ss, p);
        if (u == login)
            return true;
    }
    return false;
}

// Авторизація користувача
bool UserManager::Login(std::string& loggedUser) {
    try {
        std::ifstream f(file);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt");

        std::string login, password;
        std::cout << "Логін: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;

        std::string line;
        while (std::getline(f, line)) {
            auto pos = line.find(':');
            if (pos == std::string::npos)
                continue;

            std::string u = line.substr(0, pos);
            std::string p = line.substr(pos + 1);

            if (u == login && p == password) {
                loggedUser = u;
                std::cout << "[INFO] Успішний вхід користувача: " << loggedUser << "\n";
                return true;
            }
        }

        std::cout << "[WARN] Невірний логін або пароль.\n";
        return false;
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
        return false;
    }
}

// Додавання нового користувача (admin)
void UserManager::AddUser() {
    try {
        std::string login, pass;

        std::cout << "Новий логін: ";
        std::cin >> login;

        if (login == "admin") {
            std::cout << "[WARN] Неможливо створити користувача з логіном 'admin'.\n";
            return;
        }

        if (IsUserExists(login)) {
            std::cout << "[WARN] Користувач уже існує.\n";
            return;
        }

        std::cout << "Пароль: ";
        std::cin >> pass;

        std::ofstream out(file, std::ios::app);
        if (!out.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt для запису");

        out << login << ":" << pass << "\n";
        std::cout << "[INFO] Користувача додано.\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Виведення списку користувачів
void UserManager::ShowUsers() {
    try {
        std::ifstream f(file);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt");

        std::string line;
        std::cout << "--- СПИСОК КОРИСТУВАЧІВ ---\n";
        while (std::getline(f, line))
            std::cout << line << "\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Видалення користувача (крім admin)
void UserManager::RemoveUser() {
    try {
        std::string toRemove;
        std::cout << "Логін користувача для видалення: ";
        std::cin >> toRemove;

        if (toRemove == "admin") {
            std::cout << "[WARN] Неможливо видалити адміністратора.\n";
            return;
        }

        std::ifstream f(file);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt");

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(f, line)) {
            std::stringstream ss(line);
            std::string u, p;
            std::getline(ss, u, ':');
            std::getline(ss, p);
            if (u != toRemove)
                lines.push_back(line);
        }
        f.close();

        std::ofstream out(file);
        if (!out.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt для запису");

        for (auto& l : lines)
            out << l << "\n";

        std::cout << "[INFO] Користувача видалено.\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}
