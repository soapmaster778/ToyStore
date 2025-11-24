#ifndef ISEARCHABLE_H
#define ISEARCHABLE_H

#include <string>

// Інтерфейс пошуку об'єктів
class ISearchable {
public:
    // Перевірка, чи об'єкт відповідає рядку запиту
    virtual bool Matches(const std::string& query) const = 0;
    virtual ~ISearchable() = default;
};

#endif
