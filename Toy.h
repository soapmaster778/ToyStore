#ifndef TOY_H
#define TOY_H

#include <string>
#include <iostream>
#include "AbstractItem.h"
#include "ISearchable.h"

// Базовий клас іграшки
class Toy : public AbstractItem, public ISearchable {
protected:
    std::string article;     // артикул
    std::string name;        // назва
    int ageCategory;         // мінімальний вік дитини
    double price;            // ціна

public:
    Toy();
    Toy(std::string article, std::string name, int ageCategory, double price);
    Toy(const Toy& other);
    Toy(Toy&& other) noexcept;
    virtual ~Toy();

    std::string GetArticle() const override;
    std::string GetName() const;
    int GetAgeCategory() const;
    double GetPrice() const;

    void SetName(const std::string& newName);
    void SetAgeCategory(int newAge);
    void SetPrice(double newPrice);

    std::string ToString() const override;
    bool Matches(const std::string& query) const override;

    // Додаткові предметні методи
    void ApplyDiscount(double percent);
    void IncreasePrice(double amount);
    bool IsSuitableForAge(int childAge) const;
    std::string GetCategoryDescription() const;
    bool IsExpensive(double threshold) const;
};

#endif
