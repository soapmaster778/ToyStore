#include "Toy.h"

Toy::Toy() : article(""), name(""), ageCategory(0), price(0.0) {}

Toy::Toy(std::string article, std::string name, int ageCategory, double price)
        : article(std::move(article)), name(std::move(name)),
          ageCategory(ageCategory), price(price) {}

Toy::Toy(const Toy &other)
        : article(other.article), name(other.name),
          ageCategory(other.ageCategory), price(other.price) {}

Toy::Toy(Toy &&other) noexcept
        : article(std::move(other.article)), name(std::move(other.name)),
          ageCategory(other.ageCategory), price(other.price) {}

Toy::~Toy() {
    std::cout << "[INFO] Знищено об'єкт Toy: " << name << "\n";
}

std::string Toy::GetArticle() const { return article; }
std::string Toy::GetName() const { return name; }
int Toy::GetAgeCategory() const { return ageCategory; }
double Toy::GetPrice() const { return price; }

void Toy::SetName(const std::string &newName) { name = newName; }
void Toy::SetAgeCategory(int newAge) { ageCategory = newAge; }
void Toy::SetPrice(double newPrice) { price = newPrice; }

// Формат: тип;артикул;назва;вік;ціна
std::string Toy::ToString() const {
    return "Toy;" + article + ";" + name + ";" +
           std::to_string(ageCategory) + ";" + std::to_string(price);
}

bool Toy::Matches(const std::string &query) const {
    return article == query || name == query;
}

void Toy::ApplyDiscount(double percent) {
    if (percent >= 0 && percent <= 100) {
        price -= price * (percent / 100.0);
    }
}

void Toy::IncreasePrice(double amount) {
    if (amount > 0) {
        price += amount;
    }
}

bool Toy::IsSuitableForAge(int childAge) const {
    return childAge >= ageCategory;
}

std::string Toy::GetCategoryDescription() const {
    if (ageCategory <= 3) return "Для малюків (1–3 роки)";
    if (ageCategory <= 6) return "Для дошкільнят (3–6 років)";
    if (ageCategory <= 12) return "Для дітей (6–12 років)";
    return "Для підлітків (12+)";
}

bool Toy::IsExpensive(double threshold) const {
    return price >= threshold;
}
