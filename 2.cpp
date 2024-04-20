#include "2.hpp"

void ModifiableIntegerFunction::copy(const ModifiableIntegerFunction& other) {
    this->function = other.function;
    this->valuesSet = new Point[other.capacity];
    for(unsigned int index = 0; index < other.size; ++index) {
        this->valuesSet[index].number = other.valuesSet[index].number;
        this->valuesSet[index].result = other.valuesSet[index].result;
        this->valuesSet[index].isExcluded = other.valuesSet[index].isExcluded;
    }
    this->capacity = other.capacity;
    this->size = other.size;
}
void ModifiableIntegerFunction::destroy() {
    delete[] this->valuesSet;
}
void ModifiableIntegerFunction::resize() {
    ModifiableIntegerFunction::Point* temp = new ModifiableIntegerFunction::Point[this->capacity];
    for(unsigned int index = 0; index < this->size; ++index) {
        temp[index].number = this->valuesSet[index].number;
        temp[index].result = this->valuesSet[index].result;
        temp[index].isExcluded = this->valuesSet[index].isExcluded;
    }
    destroy();
    this->capacity *= 2;
    this->valuesSet = temp;
}
void ModifiableIntegerFunction::swap(Point& p1, Point& p2) {
    Point temp = p2;
    p2 = p1;
    p1 = temp;
}
int16_t ModifiableIntegerFunction::partion(Point* array, int16_t low, int16_t high) {
    int16_t pivot = array[high].number; 
    int16_t i = low - 1; 

    for (int16_t j = low; j < high; j++) {
        if (array[j].number <= pivot) {
            this->swap(array[i], array[j]);
        }
    }
    this->swap(array[i + 1], array[high]);
    return i + 1;
}
void ModifiableIntegerFunction::quickSort(int16_t low, int16_t high) {
    if (low < high) {
        int16_t pi = this->partion(this->valuesSet, low, high);

        this->quickSort(low, pi - 1);
        this->quickSort(pi + 1, high);
    }
}
void ModifiableIntegerFunction::sort() {
    this->quickSort(1, this->size - 1);
}
ModifiableIntegerFunction::Point& ModifiableIntegerFunction::find(int16_t number) const {
    for(unsigned int index = 0; index < this->size; ++index) {
        if(this->valuesSet[index].number == number) {
            return this->valuesSet[index];
        }
    }

    throw std::runtime_error("Point not found!");
}
bool ModifiableIntegerFunction::isFound(int16_t number) const {
    for(unsigned int index = 0; index < this->size; ++index) {
        if(this->valuesSet[index].number == number) {
            return true;
        }
    }

    return false;
}
ModifiableIntegerFunction::ModifiableIntegerFunction() : function(nullptr), capacity(8), size(0), valuesSet(new ModifiableIntegerFunction::Point[this->capacity]) {

}
ModifiableIntegerFunction::ModifiableIntegerFunction(LambdaFuncType function) : function(function), capacity(8), size(0), valuesSet(new ModifiableIntegerFunction::Point[this->capacity]) {
    
}
ModifiableIntegerFunction::ModifiableIntegerFunction(const ModifiableIntegerFunction& other) {
    this->copy(other);
}
ModifiableIntegerFunction& ModifiableIntegerFunction::operator=(const ModifiableIntegerFunction& other) {
    if(this != &other) {
        this->destroy();
        this->copy(other);
    }

    return *this;
}
ModifiableIntegerFunction::~ModifiableIntegerFunction() {
    this->destroy();
}
void ModifiableIntegerFunction::add(int16_t number, bool isExcluded) {
    if(this->size == this->capacity) {
        this->resize();
    }

    this->valuesSet[this->size].number = number;
    try {
        this->valuesSet[this->size].result = this->function(number);
    } catch (std::runtime_error& ex) {
        this->valuesSet[this->size].isExcluded = true;
    }
    this->valuesSet[this->size].isExcluded = isExcluded;
    this->size++;
}
int16_t ModifiableIntegerFunction::evaluate(int16_t x) const {
    for(unsigned int i = 0; i < this->size; ++i) {
        if(this->valuesSet[i].number == x && !this->valuesSet[i].isExcluded) {
            return this->valuesSet[i].result;
        } else if(this->valuesSet[i].number == x && this->valuesSet[i].isExcluded) {
            return this->function(x);
        } 
    }
    throw std::runtime_error("Function is not defined for this x value!");
}
void ModifiableIntegerFunction::setResult(int16_t number, int16_t result) {
    try {
        Point& found = this->find(number);
        found.result = result;
    } catch (std::runtime_error& ex) {
        std::cout << "Runtime exception occured with message: " << ex.what() << std::endl;
    }
}
void ModifiableIntegerFunction::excludePoint(int16_t number) {
    try {
        Point& found = this->find(number);
        found.isExcluded = true;
    } catch (std::runtime_error& ex) {
        std::cout << "Runtime exception occured with message: " << ex.what() << std::endl;
    }
}
ModifiableIntegerFunction& ModifiableIntegerFunction::operator+=(const ModifiableIntegerFunction& other) {
    this->function = [&] (int16_t number) {
        return this->evaluate(number) + other.evaluate(number);
    };

    for(unsigned int ofi = 0; ofi < other.size; ++ofi) {
        if(!this->isFound(other.valuesSet[ofi].number)) {
            this->add(other.valuesSet[ofi].number, other.valuesSet[ofi].isExcluded);
        } else if(other.valuesSet[ofi].isExcluded) {
            this->excludePoint(other.valuesSet[ofi].number);
        } else {
            continue;
        }
    }
    return *this;
}
ModifiableIntegerFunction ModifiableIntegerFunction::operator+(const ModifiableIntegerFunction& other) const {
    ModifiableIntegerFunction sumFunction ([&] (int16_t number) {
        return this->evaluate(number) + other.evaluate(number);
    });

    for(unsigned int tfi = 0; tfi < this->size; ++tfi) {
        if(!sumFunction.isFound(this->valuesSet[tfi].number)) {
            sumFunction.add(this->valuesSet[tfi].number, this->valuesSet[tfi].isExcluded);
        }
    }
    for(unsigned int ofi = 0; ofi < other.size; ++ofi) {
        if(!sumFunction.isFound(other.valuesSet[ofi].number)) {
            sumFunction.add(other.valuesSet[ofi].number, other.valuesSet[ofi].isExcluded);
        } else if(other.valuesSet[ofi].isExcluded) {
            sumFunction.excludePoint(other.valuesSet[ofi].number);
        } else {
            continue;
        }
    }
    return sumFunction;
}
ModifiableIntegerFunction& ModifiableIntegerFunction::operator-=(const ModifiableIntegerFunction& other) {
    this->function = [&] (int16_t number) {
        return this->evaluate(number) - other.evaluate(number);
    };

    for(unsigned int ofi = 0; ofi < other.size; ++ofi) {
        if(!this->isFound(other.valuesSet[ofi].number)) {
            this->add(other.valuesSet[ofi].number, other.valuesSet[ofi].isExcluded);
        } else if(other.valuesSet[ofi].isExcluded) {
            this->excludePoint(other.valuesSet[ofi].number);
        } else {
            continue;
        }
    }
    return *this;
}
ModifiableIntegerFunction ModifiableIntegerFunction::operator-(const ModifiableIntegerFunction& other) const {
    ModifiableIntegerFunction substractionFunction ([&] (int16_t number) {
        return this->evaluate(number) - other.evaluate(number);
    });

    for(unsigned int tfi = 0; tfi < this->size; ++tfi) {
        if(!substractionFunction.isFound(this->valuesSet[tfi].number)) {
            substractionFunction.add(this->valuesSet[tfi].number, this->valuesSet[tfi].isExcluded);
        }
    }
    for(unsigned int ofi = 0; ofi < other.size; ++ofi) {
        if(!substractionFunction.isFound(other.valuesSet[ofi].number)) {
            substractionFunction.add(other.valuesSet[ofi].number, other.valuesSet[ofi].isExcluded);
        } else if(other.valuesSet[ofi].isExcluded) {
            substractionFunction.excludePoint(other.valuesSet[ofi].number);
        } else {
            continue;
        }
    }
    return substractionFunction;
}
ModifiableIntegerFunction& ModifiableIntegerFunction::compose(const ModifiableIntegerFunction& other) {
    ModifiableIntegerFunction f = ModifiableIntegerFunction(this->function);
    this->function = [&](int16_t x) {
        return f.function(other.function(x));
    };
    return *this;
}
bool ModifiableIntegerFunction::operator<(const ModifiableIntegerFunction& other) const {
    bool isSmaller = true;
    for(int16_t x = INT16_MIN; x <= INT16_MAX; ++x) {
        int16_t thisRes; int16_t otherRes;
        try {
            thisRes = this->function(x);
        } catch (std::runtime_error& ex) {
            isSmaller = true; 
        }

        try {
            otherRes = other.function(x);
        } catch (std::runtime_error& ex) {
            isSmaller = false; return isSmaller;
        }

        if(thisRes >= otherRes) {
            isSmaller = false; return isSmaller; 
        } 
    }

    return isSmaller;
}
bool ModifiableIntegerFunction::operator<=(const ModifiableIntegerFunction& other) const {
    return this->operator<(other) || this->operator==(other);
}
bool ModifiableIntegerFunction::operator>(const ModifiableIntegerFunction& other) const {
    return !(this->operator<(other) && this->operator==(other));
}
bool ModifiableIntegerFunction::operator>=(const ModifiableIntegerFunction& other) const {
    return this->operator>(other) || this->operator==(other);
}
bool ModifiableIntegerFunction::operator==(const ModifiableIntegerFunction& other) const {
    bool areEqual = false;
    for(int16_t x = INT16_MIN; x <= INT16_MAX; ++x) {
        int16_t thisRes; int16_t otherRes;
        try {
            thisRes = this->evaluate(x);
        } catch (std::runtime_error& ex) {
            areEqual = false;
        }

        try {
            otherRes = other.evaluate(x);
        } catch (std::runtime_error& ex) {
            areEqual = true; return areEqual;
        }

        if(thisRes != otherRes) {
            areEqual = false; return areEqual;
        } 
    }

    return areEqual;
}
bool ModifiableIntegerFunction::operator!=(const ModifiableIntegerFunction& other) const {
    return !this->operator==(other);
}
bool ModifiableIntegerFunction::isColinear(const ModifiableIntegerFunction& other) const {
    int16_t xCoord = other.valuesSet[0].number - this->valuesSet[0].number, yCoord = other.valuesSet[0].result - this->valuesSet[0].result;
    int16_t startLen = std::sqrt(xCoord*xCoord + yCoord*yCoord);
    for(unsigned int index = 1; index < this->size; ++index) {
        int16_t currXCoord = other.valuesSet[index].number - this->valuesSet[index].number, 
            currYCoord = other.valuesSet[index].result - this->valuesSet[index].result;
        int16_t currLen = std::sqrt(currXCoord*currXCoord + currYCoord*currYCoord);
        if(startLen != currLen) {
            return false;
        }
        startLen = currLen;
    }

    return true;
}
ModifiableIntegerFunction& ModifiableIntegerFunction::operator^=(int16_t power) {
    if (power <= 0) {
        return *this;
    }
    int16_t resTemp = 1;
        
    for(unsigned j = 0; j < this->size; ++j) {
        for(int16_t i = 0; i < power; ++i) {
            resTemp *= this->evaluate(this->valuesSet[j].number);
        }
        this->valuesSet[j].result = resTemp;
        resTemp = 1;
    }
    return *this;
}
ModifiableIntegerFunction ModifiableIntegerFunction::operator^(int16_t power) const {
    ModifiableIntegerFunction copy = ModifiableIntegerFunction(*this);
    if (power <= 0) {
        return copy;
    }
    int16_t resTemp = 1;
        
    for(unsigned j = 0; j < this->size; ++j) {
        for(int16_t i = 0; i < power; ++i) {
            resTemp *= copy.evaluate(copy.valuesSet[j].number);
        }
        copy.valuesSet[j].result = resTemp;
        resTemp = 1;
    }
    return copy;
}
ModifiableIntegerFunction ModifiableIntegerFunction::inverse() {
    ModifiableIntegerFunction inverseFunc([this](int16_t y) {
        for (int16_t x = INT16_MIN; x <= INT16_MAX; ++x) {
            try {
                if (this->evaluate(x) == y) {
                    return x;
                }
            } catch (...) {
                break;
            }
        }

        throw std::runtime_error("Function is not invertible!");
    });
    return inverseFunc;
}
bool ModifiableIntegerFunction::isInjection() const {
    for(int16_t xi = 0; xi < this->size - 1; ++xi) {
        for(int16_t xj = xi + 1; xj < this->size; ++xj) {
            if(this->function(this->valuesSet[xi].number) == this->function(this->valuesSet[xj].number)) {
                return false;
            }
        }
    }

    return true;
}
bool ModifiableIntegerFunction::isSurjection() const {
    for (unsigned int xi = 0; xi < this->size; ++xi) {
        if (function(this->valuesSet[xi].number) == this->valuesSet[xi].result) {
            return true;
        }
    }
    return false;
}
bool ModifiableIntegerFunction::isBijection() const {
    return this->isInjection() && this->isSurjection();
}
void ModifiableIntegerFunction::serialize(const char* fileName) const {
    std::ofstream out(fileName, std::ios::out | std::ios::binary);
    if(out.is_open()) {
        out.write(reinterpret_cast<const char*> (&this->function), sizeof(ModifiableIntegerFunction::LambdaFuncType));
        out.write(reinterpret_cast<const char*> (&this->capacity), sizeof(unsigned int));
        out.write(reinterpret_cast<const char*> (&this->size), sizeof(unsigned int));
        unsigned int dataLength = this->size * sizeof(ModifiableIntegerFunction::Point);
        out.write(reinterpret_cast<const char*>(&dataLength), sizeof(unsigned int));
        for(unsigned int index = 0; index < this->size; ++index) {
            out.write(reinterpret_cast<const char*> (&this->valuesSet[index]), sizeof(ModifiableIntegerFunction::Point));
        }
        out.close();
    } else {
        throw std::runtime_error("File is not opened for writing!");
    }
}
ModifiableIntegerFunction& ModifiableIntegerFunction::deserialize(const char* fileName) {
    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    if(in.is_open()) {
        in.read(reinterpret_cast<char*> (&this->function), sizeof(ModifiableIntegerFunction::LambdaFuncType));
        in.read(reinterpret_cast<char*> (&this->capacity), sizeof(unsigned int));
        in.read(reinterpret_cast<char*> (&this->size), sizeof(unsigned int));
        unsigned int dataLength;
        in.read(reinterpret_cast<char*> (&dataLength), sizeof(unsigned int));
        for(unsigned int index = 0; index < dataLength / sizeof(ModifiableIntegerFunction::Point); ++index) {
            in.read(reinterpret_cast<char*> (&this->valuesSet[index]), sizeof(ModifiableIntegerFunction::Point));
        }
        in.close();
        return *this;
    } else {
        throw std::runtime_error("File is not opened for reading!");
    }
}
void ModifiableIntegerFunction::plot(int16_t x1, int16_t x2, int16_t y1, int16_t y2) const {
    if(std::abs(x2 - x1) != 20 || std::abs(y2 - y1) != 20) {
        throw std::out_of_range("Invalid plot's coordinates!");
    }

    int16_t startX = std::min(x1, x2), startY = std::min(y1, y2), 
        endX = std::max(x1, x2), endY = std::max(y1, y2);
    for(int16_t xi = startX; xi <= endX; ++xi) {
        try {
        int16_t result = this->evaluate(xi);
        if(startY <= result && result <= endY) {
            int16_t stepsRight = xi, stepsDown = result;
            
                while(stepsRight > 0) {
                    if(stepsRight == 1) {
                        while(stepsDown > 0) {
                            if(stepsDown == 1) {
                                std::cout << '*' << std::endl;
                            }
                            stepsDown--;
                        }
                    }
                    std::cout << ' ';
                    stepsRight--;
                }
        }
        } catch (std::runtime_error& ex) {
            std::cout << 'o' << std::endl; 
        }
    }
}