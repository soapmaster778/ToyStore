#include "ToyManager.h"
#include "InputValidator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

ToyManager::ToyManager() {
    Load();
}

ToyManager::~ToyManager() {
    Save();
    for (auto t : toys)
        delete t;
}

// Clean function
static std::string Clean(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}


// Завантаження іграшок з файлу
void ToyManager::Load() {
    try {
        std::ifstream f(toysFile);
        if (!f.is_open()) {
            std::cout << "[INFO] Файл toys.csv не знайдено. Починаємо з порожньої бази.\n";
            return;
        }

        if (f.peek() == std::ifstream::traits_type::eof()) {
            std::cout << "[INFO] Файл toys.csv порожній.\n";
            return;
        }

        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string type;
            std::getline(ss, type, ';');

            if (type == "Toy") {
                std::string a, n, age, price;
                if (!(std::getline(ss, a, ';') &&
                      std::getline(ss, n, ';') &&
                      std::getline(ss, age, ';') &&
                      std::getline(ss, price, ';'))) {
                    std::cout << "[WARN] Пошкоджений запис Toy, пропущено.\n";
                    continue;
                }
                a = Clean(a);
n = Clean(n);
age = Clean(age);
price = Clean(price);

toys.push_back(new Toy(a, n, std::stoi(age), std::stod(price)));
            } else if (type == "Luxury") {
                std::string a, n, age, price, man, rating, seg;
                if (!(std::getline(ss, a, ';') &&
                      std::getline(ss, n, ';') &&
                      std::getline(ss, age, ';') &&
                      std::getline(ss, price, ';') &&
                      std::getline(ss, man, ';') &&
                      std::getline(ss, rating, ';') &&
                      std::getline(ss, seg, ';'))) {
                    std::cout << "[WARN] Пошкоджений запис LuxuryToy, пропущено.\n";
                    continue;
                }
                a = Clean(a);
n = Clean(n);
age = Clean(age);
price = Clean(price);
man = Clean(man);
rating = Clean(rating);
seg = Clean(seg);

toys.push_back(new LuxuryToy(a, n, std::stoi(age), std::stod(price), man, std::stoi(rating), seg));
            }
        }
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Збереження колекції іграшок у файл
void ToyManager::Save() {
    try {
        bool exists = std::ifstream(toysFile, std::ios::binary).good();

        std::ofstream f;
        if (!exists) {
            f.open(toysFile, std::ios::binary);
            const unsigned char bom[3] = {0xEF, 0xBB, 0xBF};
            f.write(reinterpret_cast<const char*>(bom), 3);
        } else {
            f.open(toysFile, std::ios::binary | std::ios::trunc);
        }

        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити toys.csv для запису");

        for (auto t : toys)
            f << t->ToString() << "\n";
    }
    catch (std::exception &e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}


// Виведення всіх іграшок
void ToyManager::ShowAll() {
    if (toys.empty()) {
        std::cout << "База іграшок порожня.\n";
        return;
    }
    for (auto t : toys)
        std::cout << t->ToString() << "\n";
}

// Додавання звичайної іграшки
void ToyManager::AddToy() {
    std::string a = InputValidator::ReadString("Артикул: ");
    std::string n = InputValidator::ReadString("Назва: ");
    int age = InputValidator::ReadInt("Мінімальний вік дитини: ", 1, 18);
    double price = InputValidator::ReadDouble("Ціна: ", 0.1, 100000);

    toys.push_back(new Toy(a, n, age, price));
    Save();
    std::cout << "[INFO] Іграшку додано.\n";
}

// Додавання преміальної іграшки
void ToyManager::AddLuxuryToy() {
    std::string a = InputValidator::ReadString("Артикул: ");
    std::string n = InputValidator::ReadString("Назва: ");
    int age = InputValidator::ReadInt("Мінімальний вік дитини: ", 1, 18);
    double price = InputValidator::ReadDouble("Ціна: ", 1, 999999);
    std::string man = InputValidator::ReadString("Виробник: ");
    int rating = InputValidator::ReadInt("Рейтинг (0-10): ", 0, 10);
    std::string seg = InputValidator::ReadString("Сегмент (premium/exclusive/...): ");

    toys.push_back(new LuxuryToy(a, n, age, price, man, rating, seg));
    Save();
    std::cout << "[INFO] Преміальну іграшку додано.\n";
}

// Редагування іграшки
void ToyManager::EditToy() {
    std::string a = InputValidator::ReadString("Артикул іграшки для редагування: ");

    for (auto t : toys) {
        if (t->GetArticle() == a) {
            std::string newName = InputValidator::ReadString("Нова назва: ");
            int newAge = InputValidator::ReadInt("Новий мінімальний вік: ", 1, 18);
            double newPrice = InputValidator::ReadDouble("Нова ціна: ", 0.1, 999999);

            t->SetName(newName);
            t->SetAgeCategory(newAge);
            t->SetPrice(newPrice);
            Save();
            std::cout << "[INFO] Іграшку оновлено.\n";
            return;
        }
    }
    std::cout << "[WARN] Іграшку з таким артикулом не знайдено.\n";
}

// Видалення іграшки
void ToyManager::RemoveToy() {
    std::string a = InputValidator::ReadString("Артикул іграшки для видалення: ");

    for (size_t i = 0; i < toys.size(); ++i) {
        if (toys[i]->GetArticle() == a) {
            delete toys[i];
            toys.erase(toys.begin() + i);
            Save();
            std::cout << "[INFO] Іграшку видалено.\n";
            return;
        }
    }
    std::cout << "[WARN] Іграшку з таким артикулом не знайдено.\n";
}

// Пошук іграшки
void ToyManager::SearchToy() {
    std::string q = InputValidator::ReadString("Пошук за артикулом або назвою: ");
    bool found = false;
    for (auto t : toys) {
        if (t->Matches(q)) {
            std::cout << t->ToString() << "\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Нічого не знайдено.\n";
}

// Продаж іграшки
void ToyManager::SellToy() {
    try {
        std::string a = InputValidator::ReadString("Артикул проданої іграшки: ");

        for (auto t : toys) {
            if (t->GetArticle() == a) {
                std::string seller = InputValidator::ReadString("ПІБ продавця: ");

                SoldRecord rec(a, t->GetName(), t->GetPrice(), seller);
                std::ofstream out(soldFile, std::ios::app);
                if (!out.is_open())
                    throw std::runtime_error("Не вдалося відкрити sold.csv");
                out << rec.ToCSV() << "\n";
                std::cout << "[INFO] Продаж зареєстровано.\n";
                return;
            }
        }
        throw std::runtime_error("Іграшку не знайдено за вказаним артикулом");
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// Підрахунок кількості продажів за артиклем
void ToyManager::CountSold() {
    try {
        std::string a = InputValidator::ReadString("Артикул: ");
        std::ifstream f(soldFile);
        if (!f.is_open())
            throw std::runtime_error("Не вдалося відкрити sold.csv");

        int count = 0;
        std::string line;
        while (std::getline(f, line)) {
            if (line.rfind(a + ";", 0) == 0)
                count++;
        }
        std::cout << "Кількість проданих одиниць товару з артикулом " << a
                  << ": " << count << "\n";
    } catch (std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}

// --- Сортування ---

void ToyManager::SortMenu() {
    int choice = InputValidator::ReadInt(
        "\n=== МЕНЮ СОРТУВАННЯ ===\n"
        "1. Сортувати за ціною\n"
        "2. Сортувати за назвою\n"
        "3. Сортувати за віковою категорією\n"
        "0. Повернутися\n> ", 0, 3);

    switch (choice) {
        case 1: SortByPrice(); break;
        case 2: SortByName(); break;
        case 3: SortByAge(); break;
        case 0: return;
    }
}

void ToyManager::SortByPrice() {
    std::sort(toys.begin(), toys.end(),
              [](Toy* a, Toy* b) {
                  return a->GetPrice() < b->GetPrice();
              });
    std::cout << "[INFO] Впорядковано за ціною.\n";
    ShowAll();
}

void ToyManager::SortByName() {
    std::sort(toys.begin(), toys.end(),
              [](Toy* a, Toy* b) {
                  return a->GetName() < b->GetName();
              });
    std::cout << "[INFO] Впорядковано за назвою.\n";
    ShowAll();
}

void ToyManager::SortByAge() {
    std::sort(toys.begin(), toys.end(),
              [](Toy* a, Toy* b) {
                  return a->GetAgeCategory() < b->GetAgeCategory();
              });
    std::cout << "[INFO] Впорядковано за мінімальним віком.\n";
    ShowAll();
}

// --- Фільтрація ---

void ToyManager::FilterMenu() {
    int choice = InputValidator::ReadInt(
        "\n=== МЕНЮ ФІЛЬТРАЦІЇ ===\n"
        "1. Фільтр за максимальною ціною\n"
        "2. Фільтр за віком дитини\n"
        "3. Показати лише преміальні іграшки (Luxury)\n"
        "0. Повернутися\n> ", 0, 3);

    switch (choice) {
        case 1: FilterByMaxPrice(); break;
        case 2: FilterByAge(); break;
        case 3: FilterOnlyLuxury(); break;
        case 0: return;
    }
}

void ToyManager::FilterByMaxPrice() {
    double maxPrice = InputValidator::ReadDouble("Максимальна ціна: ", 0.1, 1e9);
    std::cout << "\n--- Іграшки дешевші або рівні " << maxPrice << " ---\n";
    for (auto t : toys) {
        if (t->GetPrice() <= maxPrice) {
            std::cout << t->ToString() << "\n";
        }
    }
}

void ToyManager::FilterByAge() {
    int age = InputValidator::ReadInt("Максимальний вік дитини: ", 1, 18);
    std::cout << "\n--- Іграшки, що підходять для віку до " << age << " років ---\n";
    for (auto t : toys) {
        if (t->GetAgeCategory() <= age) {
            std::cout << t->ToString() << "\n";
        }
    }
}

void ToyManager::FilterOnlyLuxury() {
    std::cout << "\n--- Лише преміальні іграшки (Luxury) ---\n";
    for (auto t : toys) {
        auto* lux = dynamic_cast<LuxuryToy*>(t);
        if (lux != nullptr) {
            std::cout << lux->ToString() << "\n";
        }
    }
}

// --- Допомога ---

void ToyManager::Help() {
    std::cout << "\n==================== ДОПОМОГА ====================\n";
    std::cout << "Це консольний додаток для керування базою даних\n";
    std::cout << "магазину іграшок. Можна зберігати іграшки, продавати їх\n";
    std::cout << "та переглядати статистику продажів.\n\n";

    std::cout << "Основні файли:\n";
    std::cout << "  - toys.csv  — список іграшок (Toy / Luxury)\n";
    std::cout << "  - sold.csv  — інформація про продажі\n";
    std::cout << "  - users.txt — облікові записи користувачів (login:password)\n\n";

    std::cout << "Після запуску програма просить логін і пароль.\n";
    std::cout << "За замовчуванням доступний користувач 'admin' з паролем 'admin123'.\n\n";

    std::cout << "У головному меню можна:\n";
    std::cout << "  1. Показати всі іграшки\n";
    std::cout << "  2. Додати звичайну іграшку\n";
    std::cout << "  3. Додати преміальну іграшку (Luxury)\n";
    std::cout << "  4. Редагувати параметри іграшки\n";
    std::cout << "  5. Видалити іграшку\n";
    std::cout << "  6. Виконати пошук\n";
    std::cout << "  7. Зареєструвати продаж\n";
    std::cout << "  8. Порахувати кількість проданих товарів за артиклем\n";
    std::cout << "  9. Сортувати список іграшок\n";
    std::cout << " 10. Фільтрувати іграшки за умовою\n";
    std::cout << " 11-13. Керування користувачами (лише для admin)\n";
    std::cout << " 14. Показати цю довідку\n";
    std::cout << "  0. Вийти з програми\n\n";

    std::cout << "Правила введення:\n";
    std::cout << "  • ціна — дійсне число > 0;\n";
    std::cout << "  • вік — ціле число в діапазоні 1–18;\n";
    std::cout << "  • артикль та назва — непорожні рядки без пробілів.\n";
    std::cout << "При некоректному введенні програма попросить повторити спробу.\n";
    std::cout << "===================================================\n\n";
}


