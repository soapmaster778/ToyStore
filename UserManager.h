#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>

// Клас для роботи з обліковими записами користувачів та адміністраторів
class UserManager {
private:
    std::string adminsFile = "admins.txt";
    std::string usersFile  = "users.txt";

    bool IsUserExistsInFile(const std::string& fileName, const std::string& login);
    void EnsureDefaultAdmin();

public:
    UserManager();

    // Авторизація: повертає true при успіху, записує логін та роль ("admin" або "user")
    bool Login(std::string& loggedUser, std::string& role);

    // Користувачі
    void AddUser();
    void ShowUsers();
    void RemoveUser();

    // Адміністратори
    void AddAdmin();
    void ShowAdmins();
    void RemoveAdmin();
};

#endif
