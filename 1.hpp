#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

class MultiSet {
    private:
    struct Pair {
        unsigned int number;
        unsigned char frequency;
    };
    Pair* data;
    unsigned int capacity;
    unsigned int size;
    unsigned int maxValue;
    unsigned int maxBits;

    void copy(const MultiSet& other);
    void destroy();
    void resize();

    MultiSet();

    public:
    MultiSet(unsigned int n, unsigned char k);
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    void insert(unsigned int number);
    void remove(unsigned int number);
    unsigned int countOccurrences(unsigned int number) const;
    void print() const;
    void printMemoryRepresentation() const;
    void serilize(const char* fileName) const;
    MultiSet& deserilize(const char* fileName);
    MultiSet intersection(const MultiSet& other) const;
    MultiSet difference(const MultiSet& other) const;
    MultiSet complement() const;
    unsigned int getMaxNumber() const;
    unsigned int getCapacity() const;
    bool contains(unsigned int number) const;
};