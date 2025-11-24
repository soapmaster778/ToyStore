#ifndef TOYMANAGER_H
#define TOYMANAGER_H

#include <vector>
#include <string>
#include "Toy.h"
#include "LuxuryToy.h"
#include "SoldRecord.h"

// Менеджер для роботи з колекцією іграшок
class ToyManager {
private:
    std::vector<Toy*> toys;
    std::string toysFile = "toys.csv";
    std::string soldFile = "sold.csv";

public:
    ToyManager();
    ~ToyManager();

    void Load();
    void Save();

    void AddToy();
    void AddLuxuryToy();
    void EditToy();
    void RemoveToy();
    void ShowAll();
    void SearchToy();
    void SellToy();
    void CountSold();

    // Сортування
    void SortMenu();
    void SortByPrice();
    void SortByName();
    void SortByAge();

    // Фільтрація
    void FilterMenu();
    void FilterByMaxPrice();
    void FilterByAge();
    void FilterOnlyLuxury();

    // Допомога
    void Help();
};

#endif
