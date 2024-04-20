#pragma once

#include <iostream>
#include <fstream>
/*

Напишете клас МultiSet, който съдържа мултимножество от числа в диапазона от 0 до n, където n е 
подадено в конструктора. В конструктора се подават 2 числа: n (най-голямото число в множеството) 
и k - колко най-много бита са необходими за запазването на броя срещания на едно число (1 <= k <= 8). 
Това означава, че всяко число може да се среща в множеството най-много 2^k-1  пъти. Класът ви трябва 
да е максимално оптимален откъм памет.

Трябва да поддържате следните функционалности:
Добавяне на число.
Проверка колко пъти се съдържа число.
Принтиране на всички числа, които се съдържат в мултимножеството.
Принтиране на това как мултимножеството е представено в паметта.
Сериализация/десериализация в/от двоичен файл.
Сечение/Разлика на две мултимножества.
Допълнение на мултимножество  (ако x се е срещал p пъти, то в допълнението се среща 2^k - 1 - p пъти)

*/

class MultiSet {
    private:
    struct Pair {
        unsigned int number;
        unsigned char frequency;
    };
    Pair* data;
    unsigned int capacity;
    unsigned int size;
    unsigned int maxNumber;
    unsigned int maxBytes;

    void copy(const MultiSet& other);
    void destroy();
    void resize();
    unsigned int calculateCapacity(unsigned char k) const;
    void remove(unsigned int number);

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
    void serilize(const char* fileName) const;
    void deserilize(const char* fileName);
    MultiSet intersection(const MultiSet& other) const;
    MultiSet difference(const MultiSet& other) const;
    MultiSet complement() const;
    unsigned int getMaxNumber() const;
    unsigned int getCapacity() const;
    bool contains(unsigned int number) const;
};