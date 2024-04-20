#include "1.hpp"

void MultiSet::copy(const MultiSet &other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->maxNumber = other.maxNumber;
    this->maxBytes = other.maxBytes;
    this->valuesSet = new Pair[this->capacity];
    for (unsigned int index = 0; index < this->size; ++index)
    {
        this->valuesSet[index].number = other.valuesSet[index].number;
        this->valuesSet[index].frequency = other.valuesSet[index].frequency;
    }
}
void MultiSet::destroy()
{
    delete[] this->valuesSet;
}
void MultiSet::resize()
{
    Pair *temp = new Pair[this->capacity];
    for (unsigned int index = 0; index < this->size; ++index)
    {
        temp[index].number = this->valuesSet[index].number;
        temp[index].frequency = this->valuesSet[index].frequency;
    }
    destroy();
    this->valuesSet = temp;
    this->capacity = (this->size + 1) * calculateCapacity(this->maxBytes);
}
unsigned int MultiSet::calculateCapacity(unsigned char k) const
{
    unsigned int capacity = 1;
    while (0 < k)
    {
        capacity *= 2;
        --k;
    }

    return (capacity - 1);
}
void MultiSet::remove(unsigned int number)
{
    int index = -1;
    for (int i = 0; i < this->size; ++i)
    {
        if (this->valuesSet[i].number == number)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < this->size - 1; ++i)
        {
            this->valuesSet[i].number = this->valuesSet[i + 1].number;
            this->valuesSet[i].frequency = this->valuesSet[i + 1].frequency;
        }
        --this->size;
    }
}
MultiSet::MultiSet() : capacity(1 * calculateCapacity(1)), size(0), maxNumber(0), maxBytes(1), valuesSet(nullptr)
{
    valuesSet = new Pair[capacity];
}
MultiSet::MultiSet(unsigned int n, unsigned char k) : capacity(1 * calculateCapacity(k)), size(1), maxNumber(n), maxBytes(k), valuesSet(new Pair[k])
{
    this->valuesSet[0].number = n;
    this->valuesSet[0].frequency = 1;
}
MultiSet::MultiSet(const MultiSet &other)
{
    copy(other);
}
MultiSet &MultiSet::operator=(const MultiSet &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}
MultiSet::~MultiSet()
{
    destroy();
}
void MultiSet::insert(unsigned int number)
{
    if (countOccurrences(number) > (this->capacity / calculateCapacity(this->maxBytes)))
    {
        return;
    }
    if (this->size == this->capacity)
    {
        resize();
    }
    if (contains(number))
    {
        for (unsigned int index = 0; index < this->size; ++index)
        {
            if (this->valuesSet[index].number == number)
            {
                this->valuesSet[index].frequency++;
                return;
            }
        }
    }
    this->valuesSet[this->size].number = number;
    this->valuesSet[this->size].frequency = 1;
    this->size++;
    if (this->maxNumber < number)
    {
        this->maxNumber = number;
    }
}
unsigned int MultiSet::countOccurrences(unsigned int number) const
{
    for (unsigned int index = 0; index < this->size; ++index)
    {
        if (this->valuesSet[index].number == number)
        {
            return this->valuesSet[index].frequency;
        }
    }

    return 0;
}
void MultiSet::print() const
{
    if (this->size == 0 || this->valuesSet == nullptr)
    {
        std::cout << "{ }" << std::endl;
        return;
    }
    std::cout << "{";
    for (unsigned int index = 0; index < this->size; ++index)
    {
        std::cout << " " << this->valuesSet[index].number;
    }
    std::cout << " }" << std::endl;
}
void MultiSet::printMemoryRepresentation() const
{
    if (this->size == 0 || this->valuesSet == nullptr)
    {
        std::cout << "MultiSet Memory Representation [ ]" << std::endl;
        return;
    }
    std::cout << "MultiSet Memory Representation: [" << std::endl;
    for (unsigned int index = 0; index < this->size; ++index)
    {
        Pair currentPair = this->valuesSet[index];
        std::cout << "Number: " << currentPair.number << ", Frequency: " << (int)currentPair.frequency << std::endl;
    }
    std::cout << "]" << std::endl;
}
void MultiSet::serilize(const char *fileName) const
{
    if (fileName == nullptr)
    {
        return;
    }
    std::ofstream output(fileName, std::ios::out | std::ios::binary | std::ios::app);
    if (output.is_open())
    {
        output.write((char *)&this->capacity, sizeof(unsigned int));
        output.write((char *)&this->size, sizeof(unsigned int));
        output.write((char *)&this->maxNumber, sizeof(unsigned int));
        output.write((char *)&this->maxBytes, sizeof(unsigned int));

        unsigned int size = this->size * sizeof(MultiSet::Pair);
        output.write((char *)&size, sizeof(unsigned int));
        for (unsigned int index = 0; index < this->size; ++index)
        {
            output.write((char *)&this->valuesSet[index].number, sizeof(unsigned int));
            output.write((char *)&this->valuesSet[index].frequency, sizeof(unsigned int));
        }
        output.close();
        std::cout << "File stored successfully!" << std::endl;
    }
    else
    {
        std::cout << "File cannot be opened for writing!" << std::endl;
    }
}
void MultiSet::deserilize(const char *fileName)
{
    if (fileName == nullptr)
    {
        return;
    }
    std::ifstream input(fileName, std::ios::in | std::ios::binary);
    if (input.is_open())
    {
        input.read((char *)&this->capacity, sizeof(unsigned int));
        input.read((char *)&this->size, sizeof(unsigned int));
        input.read((char *)&this->maxNumber, sizeof(unsigned int));
        input.read((char *)&this->maxBytes, sizeof(unsigned int));

        unsigned int size;
        input.read((char *)&size, sizeof(unsigned int));
        delete[] this->valuesSet;
        this->valuesSet = new Pair[this->capacity];
        for (unsigned int index = 0; index < this->size; ++index)
        {
            unsigned int number;
            unsigned int frequency;
            input.read((char *)&number, sizeof(unsigned int));
            input.read((char *)&frequency, sizeof(unsigned int));
            this->valuesSet[index].number = number;
            this->valuesSet[index].frequency = frequency;
        }
        input.close();
        std::cout << "File read successfully!" << std::endl;
    }
    else
    {
        std::cout << "File cannot be opened for reading!" << std::endl;
    }
}
MultiSet MultiSet::intersection(const MultiSet &other) const
{
    MultiSet copyOfThis = MultiSet(*this);
    for (unsigned int index = 0; index <= copyOfThis.size; ++index)
    {
        unsigned int currentNumber = copyOfThis.valuesSet[index].number;
        if (!other.contains(currentNumber))
        {
            copyOfThis.remove(currentNumber);
        }
    }
    return copyOfThis;
}
MultiSet MultiSet::difference(const MultiSet &other) const
{
    MultiSet copyOfThis = *this;
    MultiSet copyOfOther = other;
    for (unsigned int index = 0; index < copyOfThis.size; ++index)
    {
        unsigned int currentNumber = copyOfThis.valuesSet[index].number;

        if (copyOfOther.contains(currentNumber))
        {
            copyOfThis.remove(currentNumber);
            --index;
            copyOfOther.remove(currentNumber);
        }
    }
    for (unsigned int index = 0; index < copyOfOther.size; ++index)
    {
        unsigned int currentNumber = copyOfOther.valuesSet[index].number;
        if (!copyOfThis.contains(currentNumber))
        {
            copyOfThis.insert(currentNumber);
        }
    }
    return copyOfThis;
}
MultiSet MultiSet::complement() const
{
    MultiSet copyOfThis = MultiSet(*this);
    for (unsigned int index = 0; index < copyOfThis.size; ++index)
    {
        unsigned int currentFrequency = copyOfThis.valuesSet[index].frequency;
        copyOfThis.valuesSet[index].frequency = copyOfThis.capacity - currentFrequency;
    }
    return copyOfThis;
}
unsigned int MultiSet::getMaxNumber() const
{
    return this->maxNumber;
}
unsigned int MultiSet::getCapacity() const
{
    return this->capacity;
}
bool MultiSet::contains(unsigned int number) const
{
    for (unsigned int index = 0; index < this->size; ++index)
    {
        if (this->valuesSet[index].number == number)
        {
            return true;
        }
    }

    return false;
}