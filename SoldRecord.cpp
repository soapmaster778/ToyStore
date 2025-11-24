#include "SoldRecord.h"
#include <chrono>
#include <ctime>

SoldRecord::SoldRecord(std::string article, std::string name,
                       double price, std::string seller)
        : article(std::move(article)),
          name(std::move(name)),
          price(price),
          seller(std::move(seller)) {

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    time = std::string(std::ctime(&t));
    if (!time.empty() && time.back() == '\n')
        time.pop_back();
}

std::string SoldRecord::ToCSV() const {
    // article;name;price;seller;time
    return article + ";" + name + ";" + std::to_string(price) + ";" +
           seller + ";" + time;
}
