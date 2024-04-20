#pragma once

#include <iostream>
#include <stdexcept>
#include <exception>
#include <fstream>
#include <cmath>

class MultiSet {
    private:
    struct Pair {
        unsigned int number;
        unsigned char frequency;
    };
    unsigned int capacity;
    unsigned int size;
    unsigned int maxValue;
    unsigned int maxBits;
    Pair* data;

    // Помощни методи в "голямата четворка"
    void copy(const MultiSet& other);
    void destroy();
    void resize();
    // ====================================

    void remove(unsigned int number); // Този метод може да бъде и публичен, но туй като по условие не се изисква,
                                      // а ми трябваше в имплментацията, реших да го оставя частен и да се използва
                                      // като помощна функция вътре в самия клас.
    bool contains(unsigned int number) const; // Частен метод, който се използва от други публични методи за проверка
                                              // дадено число дали присъства в мултимножеството
    MultiSet(); 

    public:
    MultiSet(unsigned int n, unsigned char k);
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    void insert(unsigned int number);
    unsigned int countOccurrences(unsigned int number) const;
    void print() const;
    void printMemoryRepresentation() const;
    void serialize(const char* fileName) const;
    MultiSet& deserialize(const char* fileName);
    MultiSet intersection(const MultiSet& other) const;
    MultiSet difference(const MultiSet& other) const;
    MultiSet complement() const;
};