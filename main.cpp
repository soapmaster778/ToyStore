#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include "UserManager.h"
#include "ToyManager.h"
#include "InputValidator.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 > nul");
#endif


    UserManager userManager;
    std::string loggedUser;

    int startChoice = -1;

    // Стартове меню: без входу — тільки Help або вихід
    while (true) {
        std::cout << "=== МАГАЗИН ІГРАШОК ===\n";
        std::cout << "1. Увійти\n";
        std::cout << "2. Допомога\n";
        std::cout << "0. Вийти\n";

        startChoice = InputValidator::ReadInt("> ", 0, 2);

        if (startChoice == 0) {
            std::cout << "До побачення!\n";
            return 0;
        }

        if (startChoice == 2) {
            // Показати довідку без авторизації
            ToyManager tmp;
            tmp.Help();
        } else if (startChoice == 1) {
            // Авторизація до успіху
            while (!userManager.Login(loggedUser)) {
                std::cout << "[WARN] Невірний логін або пароль. Спробуйте ще раз.\n";
            }
            break; // переходимо до основного меню
        }
    }

    // Після успішного входу працюємо зі спільною базою іграшок
    ToyManager toyManager;

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== МЕНЮ МАГАЗИНУ ІГРАШОК (користувач: "
                  << loggedUser << ") ===\n";

        if (loggedUser == "admin") {
            std::cout << " 1. Показати всі іграшки\n";
            std::cout << " 2. Додати іграшку\n";
            std::cout << " 3. Додати преміальну іграшку (Luxury)\n";
            std::cout << " 4. Редагувати іграшку\n";
            std::cout << " 5. Видалити іграшку\n";
            std::cout << " 6. Пошук іграшки\n";
            std::cout << " 8. Кількість продажів за артиклем\n";
            std::cout << " 9. Сортування іграшок\n";
            std::cout << "10. Фільтрація іграшок\n";
            std::cout << "11. Показати користувачів\n";
            std::cout << "12. Додати користувача\n";
            std::cout << "13. Видалити користувача\n";
            std::cout << "14. Допомога\n";
            std::cout << " 0. Вийти\n";
        } else {
            std::cout << " 1. Показати всі іграшки\n";
            std::cout << " 6. Пошук іграшки\n";
            std::cout << " 7. Купити іграшку\n";
            std::cout << " 9. Сортування іграшок\n";
            std::cout << "10. Фільтрація іграшок\n";
            std::cout << "14. Допомога\n";
            std::cout << " 0. Вийти\n";
        }

        choice = InputValidator::ReadInt("> ", 0, 14);

        switch (choice) {
            case 1:
                toyManager.ShowAll();
                break;

            case 2: // тільки адмін
                if (loggedUser == "admin")
                    toyManager.AddToy();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 3: // тільки адмін
                if (loggedUser == "admin")
                    toyManager.AddLuxuryToy();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 4: // тільки адмін
                if (loggedUser == "admin")
                    toyManager.EditToy();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 5: // тільки адмін
                if (loggedUser == "admin")
                    toyManager.RemoveToy();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 6: // пошук дозволений усім
                toyManager.SearchToy();
                break;

            case 7: // купівля/продаж — тільки звичайний користувач
                if (loggedUser != "admin")
                    toyManager.SellToy(); // всередині можна виводити "Купівля іграшки"
                else
                    std::cout << "[WARN] Адміністратор не може купувати іграшки.\n";
                break;

            case 8: // статистика продажів — тільки адмін
                if (loggedUser == "admin")
                    toyManager.CountSold();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 9:
                toyManager.SortMenu();
                break;

            case 10:
                toyManager.FilterMenu();
                break;

            case 11: // тільки адмін
                if (loggedUser == "admin")
                    userManager.ShowUsers();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 12: // тільки адмін
                if (loggedUser == "admin")
                    userManager.AddUser();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 13: // тільки адмін
                if (loggedUser == "admin")
                    userManager.RemoveUser();
                else
                    std::cout << "[WARN] Цей пункт доступний лише адміністратору.\n";
                break;

            case 14:
                toyManager.Help();
                break;

            case 0:
                std::cout << "До побачення!\n";
                break;

            default:
                std::cout << "[WARN] Невідомий пункт меню.\n";
                break;
        }
    }

    return 0;
}
