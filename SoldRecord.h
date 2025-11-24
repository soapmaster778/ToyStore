#ifndef SOLDRECORD_H
#define SOLDRECORD_H

#include <string>

// Запис про продаж іграшки
class SoldRecord {
private:
    std::string article;
    std::string name;
    double price;
    std::string seller;
    std::string time;

public:
    SoldRecord(std::string article, std::string name, double price, std::string seller);
    std::string ToCSV() const;
};

#endif
