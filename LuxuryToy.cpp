#include "LuxuryToy.h"
#include <iostream>

LuxuryToy::LuxuryToy()
        : Toy(), manufacturer("Невідомий виробник"), rating(0), segment("Standard") {}

LuxuryToy::LuxuryToy(std::string article, std::string name, int age, double price,
                     std::string manufacturer, int rating, std::string segment)
        : Toy(std::move(article), std::move(name), age, price),
          manufacturer(std::move(manufacturer)),
          rating(rating),
          segment(std::move(segment)) {}

LuxuryToy::LuxuryToy(const LuxuryToy &other)
        : Toy(other),
          manufacturer(other.manufacturer),
          rating(other.rating),
          segment(other.segment) {}

LuxuryToy::LuxuryToy(LuxuryToy &&other) noexcept
        : Toy(std::move(other)),
          manufacturer(std::move(other.manufacturer)),
          rating(other.rating),
          segment(std::move(other.segment)) {}

LuxuryToy::~LuxuryToy() {
    std::cout << "[INFO] Знищено об'єкт LuxuryToy: " << name << "\n";
}

// Формат: Luxury;артикул;назва;вік;ціна;виробник;рейтинг;сегмент
std::string LuxuryToy::ToString() const {
    return "Luxury;" + article + ";" + name + ";" +
           std::to_string(ageCategory) + ";" +
           std::to_string(price) + ";" +
           manufacturer + ";" + std::to_string(rating) + ";" + segment;
}

bool LuxuryToy::Matches(const std::string &query) const {
    return article == query || name == query || manufacturer == query;
}

bool LuxuryToy::IsPremiumBrand() const {
    return (manufacturer == "Lego" ||
            manufacturer == "Hasbro" ||
            manufacturer == "Mattel" ||
            manufacturer == "Disney");
}

void LuxuryToy::IncreaseRating(int value) {
    if (value > 0) {
        rating += value;
        if (rating > 10) rating = 10;
    }
}

void LuxuryToy::DecreaseRating(int value) {
    if (value > 0) {
        rating -= value;
        if (rating < 0) rating = 0;
    }
}

bool LuxuryToy::IsHighRated() const {
    return rating >= 8;
}

std::string LuxuryToy::GetLuxuryDescription() const {
    return "Виробник: " + manufacturer +
           ", рейтинг: " + std::to_string(rating) +
           "/10, сегмент: " + segment +
           (IsPremiumBrand() ? " (топовий бренд)" : " (звичайний бренд)");
}
