#pragma once

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <exception>
#include <cmath>
#include <fstream>
#include <functional>

class ModifiableIntegerFunction {
    private:
    using LambdaFuncType = std::function<int16_t(int16_t)>;
    struct Point {
        int16_t number;
        int16_t result;
        bool isExcluded;
    };
    LambdaFuncType function;
    unsigned int capacity;
    unsigned int size;
    Point* valuesSet;

    // Помощни методи в "голямата четворка"
    void copy(const ModifiableIntegerFunction& other); 
    void destroy(); 
    void resize(); 
    // ====================================

    // Други помощни задачи, които са частни за класа и потребителят няма достъп до тях.
    void swap(Point& p1, Point& p2); 
    int16_t partion(Point* array, int16_t low, int16_t high); 
    void quickSort(int16_t pivot, int16_t right); 
    void sort();
    Point& find(int16_t number) const; 
    bool isFound(int16_t number) const;  
    // =====================================
    
    ModifiableIntegerFunction(); 

    public:
    ModifiableIntegerFunction(LambdaFuncType function); 
    ModifiableIntegerFunction(const ModifiableIntegerFunction& other); 
    ModifiableIntegerFunction& operator=(const ModifiableIntegerFunction& other); 
    ~ModifiableIntegerFunction(); 

    void add(int16_t number, bool isExcluded); 
    int16_t evaluate(int16_t number) const; 
    void setResult(int16_t number, int16_t result); 
    void excludePoint(int16_t number); 
    ModifiableIntegerFunction& operator+=(const ModifiableIntegerFunction& other); 
    ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& other) const; 
    ModifiableIntegerFunction& operator-=(const ModifiableIntegerFunction& other); 
    ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& other) const; 
    ModifiableIntegerFunction& compose(const ModifiableIntegerFunction& other);
    bool operator<(const ModifiableIntegerFunction& other) const; 
    bool operator<=(const ModifiableIntegerFunction& other) const; 
    bool operator>(const ModifiableIntegerFunction& other) const; 
    bool operator>=(const ModifiableIntegerFunction& other) const; 
    bool operator==(const ModifiableIntegerFunction& other) const; 
    bool operator!=(const ModifiableIntegerFunction& other) const; 
    bool isColinear(const ModifiableIntegerFunction& other) const; 
    ModifiableIntegerFunction& operator^=(int16_t power); 
    ModifiableIntegerFunction operator^(int16_t power) const; 
    ModifiableIntegerFunction inverse(); 
    bool isInjection() const; 
    bool isSurjection() const; 
    bool isBijection() const; 
    void serialize(const char* fileName) const; 
    ModifiableIntegerFunction& deserialize(const char* fileName); 
    void plot(int16_t x1, int16_t x2, int16_t y1, int16_t y2) const;
};