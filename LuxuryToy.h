#ifndef LUXURYTOY_H
#define LUXURYTOY_H

#include "Toy.h"

// Преміальна іграшка
class LuxuryToy : public Toy {
private:
    std::string manufacturer; // виробник
    int rating;               // рейтинг 0-10
    std::string segment;      // сегмент (premium, exclusive тощо)

public:
    LuxuryToy();
    LuxuryToy(std::string article, std::string name, int age, double price,
              std::string manufacturer, int rating, std::string segment);

    LuxuryToy(const LuxuryToy& other);
    LuxuryToy(LuxuryToy&& other) noexcept;

    ~LuxuryToy() override;

    std::string ToString() const override;
    bool Matches(const std::string& query) const override;

    // Додаткові методи для преміальних іграшок
    bool IsPremiumBrand() const;
    void IncreaseRating(int value);
    void DecreaseRating(int value);
    bool IsHighRated() const;
    std::string GetLuxuryDescription() const;
};

#endif
