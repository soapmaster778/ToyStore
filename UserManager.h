#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>

// Клас для роботи з обліковими записами користувачів
class UserManager {
private:
    std::string file = "users.txt";

    bool IsUserExists(const std::string& login);
    void EnsureAdminExists();

public:
    UserManager();

    bool Login(std::string& loggedUser);
    void AddUser();
    void ShowUsers();
    void RemoveUser();
};

#endif
