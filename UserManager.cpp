#include "UserManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

UserManager::UserManager() {
    EnsureDefaultAdmin();
}

// Перевірка, чи існує користувач/адмін з таким логіном у вказаному файлі
bool UserManager::IsUserExistsInFile(const std::string& fileName, const std::string& login) {
    std::ifstream f(fileName);
    if (!f.is_open())
        return false;

    std::string line;
    while (std::getline(f, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string u, p, r;
        std::getline(ss, u, ':');
        std::getline(ss, p, ':');
        std::getline(ss, r);

        if (u == login)
            return true;
    }
    return false;
}

// Створюємо за замовчуванням адміністратора admin:admin123:admin у admins.txt (якщо його ще немає)
void UserManager::EnsureDefaultAdmin() {
    try {
        std::ifstream f(adminsFile);
        bool adminFound = false;
        std::string line;

        if (f.is_open()) {
            while (std::getline(f, line)) {
                if (line.empty())
                    continue;

                std::stringstream ss(line);
                std::string login, password, role;
                std::getline(ss, login, ':');
                std::getline(ss, password, ':');
                std::getline(ss, role);

                if (login == "admin") {
                    adminFound = true;
                    break;
                }
            }
            f.close();
        }

        if (!adminFound) {
            std::ofstream out(adminsFile, std::ios::app);
            if (!out.is_open()) {
                throw std::runtime_error("Не вдалося створити файл admins.txt");
            }
            out << "admin:admin123:admin\n";
            std::cout << "[INFO] Адміністратора 'admin' створено автоматично (admin/admin123).\n";
        }
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Авторизація: спочатку шукаємо в admins.txt, потім у users.txt
bool UserManager::Login(std::string& loggedUser, std::string& role) {
    try {
        std::string login, password;
        std::cout << "Логін: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;

        // 1) Перевірка серед адміністраторів
        {
            std::ifstream f(adminsFile);
            if (!f.is_open())
                throw std::runtime_error("Не вдалося відкрити admins.txt");

            std::string line;
            while (std::getline(f, line)) {
                if (line.empty())
                    continue;

                std::stringstream ss(line);
                std::string u, p, r;
                std::getline(ss, u, ':');
                std::getline(ss, p, ':');
                std::getline(ss, r);

                if (u == login && p == password) {
                    loggedUser = u;
                    role = "admin";
                    std::cout << "[INFO] Вхід як адміністратор: " << loggedUser << "\n";
                    return true;
                }
            }
        }

        // 2) Перевірка серед звичайних користувачів
        {
            std::ifstream f(usersFile);
            if (!f.is_open())
                throw std::runtime_error("Не вдалося відкрити users.txt");

            std::string line;
            while (std::getline(f, line)) {
                if (line.empty())
                    continue;

                std::stringstream ss(line);
                std::string u, p, r;
                std::getline(ss, u, ':');
                std::getline(ss, p, ':');
                std::getline(ss, r);

                if (u == login && p == password) {
                    loggedUser = u;
                    role = "user";
                    std::cout << "[INFO] Успішний вхід користувача: " << loggedUser << "\n";
                    return true;
                }
            }
        }

        std::cout << "[WARN] Невірний логін або пароль.\n";
        return false;
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
        return false;
    }
}

// Додавання нового користувача (role = user)
void UserManager::AddUser() {
    try {
        std::string login, pass;

        std::cout << "Новий логін користувача: ";
        std::cin >> login;

        if (IsUserExistsInFile(adminsFile, login) || IsUserExistsInFile(usersFile, login)) {
            std::cout << "[WARN] Користувач або адміністратор з таким логіном уже існує.\n";
            return;
        }

        std::cout << "Пароль: ";
        std::cin >> pass;

        std::ofstream out(usersFile, std::ios::app);
        if (!out.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt для запису");

        out << login << ":" << pass << ":user\n";
        std::cout << "[INFO] Користувача додано.\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Виведення списку користувачів
void UserManager::ShowUsers() {
    try {
        std::ifstream f(usersFile);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt");

        std::string line;
        std::cout << "--- СПИСОК КОРИСТУВАЧІВ ---\n";
        while (std::getline(f, line)) {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string u, p, r;
            std::getline(ss, u, ':');
            std::getline(ss, p, ':');
            std::getline(ss, r);

            std::cout << "Логін: " << u << " (роль: user)\n";
        }
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Видалення користувача
void UserManager::RemoveUser() {
    try {
        std::string toRemove;
        std::cout << "Логін користувача для видалення: ";
        std::cin >> toRemove;

        std::ifstream f(usersFile);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt");

        std::vector<std::string> lines;
        std::string line;
        bool removed = false;

        while (std::getline(f, line)) {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string u, p, r;
            std::getline(ss, u, ':');
            std::getline(ss, p, ':');
            std::getline(ss, r);

            if (u == toRemove) {
                removed = true;
                continue;
            }
            lines.push_back(line);
        }
        f.close();

        if (!removed) {
            std::cout << "[WARN] Користувача з таким логіном не знайдено.\n";
            return;
        }

        std::ofstream out(usersFile);
        if (!out.is_open())
            throw std::runtime_error("Не вдалося відкрити users.txt для запису");

        for (auto& l : lines)
            out << l << "\n";

        std::cout << "[INFO] Користувача видалено.\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Додавання адміністратора (role = admin)
void UserManager::AddAdmin() {
    try {
        std::string login, pass;

        std::cout << "Новий логін адміністратора: ";
        std::cin >> login;

        if (IsUserExistsInFile(adminsFile, login) || IsUserExistsInFile(usersFile, login)) {
            std::cout << "[WARN] Користувач або адміністратор з таким логіном уже існує.\n";
            return;
        }

        std::cout << "Пароль: ";
        std::cin >> pass;

        std::ofstream out(adminsFile, std::ios::app);
        if (!out.is_open())
            throw std::runtime_error("Не вдалося відкрити admins.txt для запису");

        out << login << ":" << pass << ":admin\n";
        std::cout << "[INFO] Адміністратора додано.\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Виведення списку адміністраторів
void UserManager::ShowAdmins() {
    try {
        std::ifstream f(adminsFile);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити admins.txt");

        std::string line;
        std::cout << "--- СПИСОК АДМІНІСТРАТОРІВ ---\n";
        while (std::getline(f, line)) {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string u, p, r;
            std::getline(ss, u, ':');
            std::getline(ss, p, ':');
            std::getline(ss, r);

            std::cout << "Логін: " << u << " (роль: admin)\n";
        }
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Видалення адміністратора
void UserManager::RemoveAdmin() {
    try {
        std::string toRemove;
        std::cout << "Логін адміністратора для видалення: ";
        std::cin >> toRemove;

        if (toRemove == "admin") {
            std::cout << "[WARN] Неможливо видалити базового адміністратора 'admin'.\n";
            return;
        }

        std::ifstream f(adminsFile);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити admins.txt");

        std::vector<std::string> lines;
        std::string line;
        bool removed = false;

        while (std::getline(f, line)) {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string u, p, r;
            std::getline(ss, u, ':');
            std::getline(ss, p, ':');
            std::getline(ss, r);

            if (u == toRemove) {
                removed = true;
                continue;
            }
            lines.push_back(line);
        }
        f.close();

        if (!removed) {
            std::cout << "[WARN] Адміністратора з таким логіном не знайдено.\n";
            return;
        }

        std::ofstream out(adminsFile);
        if (!out.is_open())
            throw std::runtime_error("Не вдалося відкрити admins.txt для запису");

        for (auto& l : lines)
            out << l << "\n";

        std::cout << "[INFO] Адміністратора видалено.\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}
