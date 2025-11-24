#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <string>

// Абстрактний елемент бази даних (іграшка)
class AbstractItem {
public:
    // Повертає рядок для збереження в CSV
    virtual std::string ToString() const = 0;
    // Повертає артикул
    virtual std::string GetArticle() const = 0;
    virtual ~AbstractItem() = default;
};

#endif
