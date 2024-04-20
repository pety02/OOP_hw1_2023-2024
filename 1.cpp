#include "1.h"

void MultiSet::copy(const MultiSet &other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->maxValue = other.maxValue;
    this->maxBits = other.maxBits;
    this->data = new Pair[this->capacity];
    for (unsigned int index = 0; index < this->size; ++index)
    {
        this->data[index].number = other.data[index].number;
        this->data[index].frequency = other.data[index].frequency;
    }
}
void MultiSet::destroy()
{
    delete[] this->data;
}
void MultiSet::resize()
{
    Pair *temp = new Pair[this->capacity];
    for (unsigned int index = 0; index < this->size; ++index)
    {
        temp[index].number = this->data[index].number;
        temp[index].frequency = this->data[index].frequency;
    }
    destroy();
    this->data = temp;
    this->capacity *= 2;
}
void MultiSet::remove(unsigned int number)
{
    int index = -1;
    for (unsigned int i = 0; i < this->size; ++i)
    {
        if (this->data[i].number == number)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (unsigned int i = index; i < this->size - 1; ++i)
        {
            this->data[i].number = this->data[i + 1].number;
            this->data[i].frequency = this->data[i + 1].frequency;
        }
        --this->size;
    }
}
bool MultiSet::contains(unsigned int number) const
{
    for (unsigned int index = 0; index < this->size; ++index)
    {
        if (this->data[index].number == number)
        {
            return true;
        }
    }

    return false;
}
MultiSet::MultiSet() : capacity(8), size(0), maxValue(0), maxBits(0), data(new Pair[8])
{
    
}
MultiSet::MultiSet(unsigned int n, unsigned char k) : capacity(8), size(0), maxValue(n), maxBits(0), data(new Pair[8])
{
    if(1 <= k && k <= 8) {
        this->maxBits = k;
    }
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
    if(this->size == this->capacity) {
        this->resize();
    }
    if(number <= this->maxValue && !this->contains(number)) {
        this->data[this->size].number = number;
        this->data[this->size].frequency = 1;
        this->size++;
    } else if (number <= this->maxValue && this->contains(number)) {
        if(this->data[this->size].frequency > std::pow(2, this->maxBits) - 1) {
            throw std::out_of_range("Number limited insertions!");
        }
        this->data[this->size].frequency++;
    } else {
        throw std::invalid_argument("Number should be smaller!");
    }
}
unsigned int MultiSet::countOccurrences(unsigned int number) const
{
    for (unsigned int index = 0; index < this->size; ++index)
    {
        if (this->data[index].number == number)
        {
            return this->data[index].frequency;
        }
    }

    return 0;
}
void MultiSet::print() const
{
    if (this->size == 0 || this->data == nullptr)
    {
        std::cout << "MultiSet: [ ]" << std::endl;
        return;
    }
    std::cout << "MultiSet: [" << std::endl;
    for (unsigned int index = 0; index < this->size; ++index)
    {
        Pair currentPair = this->data[index];
        std::cout << "Number: " << currentPair.number << ", Frequency: " << (int)currentPair.frequency << std::endl;
    }
    std::cout << "]" << std::endl;
}
void MultiSet::printMemoryRepresentation() const
{
    unsigned char* rawDataPtr = reinterpret_cast<unsigned char*>(this->data);
    unsigned int totalSize = sizeof(MultiSet::Pair) * this->size;
    for (unsigned int index = 0; index < totalSize; ++index) {
        std::cout << "Byte " << index << ": " << static_cast<int>(rawDataPtr[index]) << std::endl;
    }
}
void MultiSet::serialize(const char *fileName) const
{
    std::ofstream output(fileName, std::ios::out | std::ios::binary | std::ios::app);
    if (output.is_open())
    {
        output.write((char *)&this->capacity, sizeof(unsigned int));
        output.write((char *)&this->size, sizeof(unsigned int));
        output.write((char *)&this->maxValue, sizeof(unsigned int));
        output.write((char *)&this->maxBits, sizeof(unsigned int));

        unsigned int size = this->size * sizeof(MultiSet::Pair);
        output.write((char *)&size, sizeof(unsigned int));
        for (unsigned int index = 0; index < this->size; ++index)
        {
            output.write((char *)&this->data[index].number, sizeof(unsigned int));
            output.write((char *)&this->data[index].frequency, sizeof(unsigned int));
        }
        output.close();
        std::cout << "File stored successfully!" << std::endl;
    }
    else
    {
        throw std::runtime_error("File cannot be opened for writing!");
    }
}
MultiSet& MultiSet::deserialize(const char *fileName)
{
    std::ifstream input(fileName, std::ios::in | std::ios::binary);
    if (input.is_open())
    {
        input.read((char *)&this->capacity, sizeof(unsigned int));
        input.read((char *)&this->size, sizeof(unsigned int));
        input.read((char *)&this->maxValue, sizeof(unsigned int));
        input.read((char *)&this->maxBits, sizeof(unsigned int));

        unsigned int size;
        input.read((char *)&size, sizeof(unsigned int));
        delete[] this->data;
        this->data = new Pair[this->capacity];
        for (unsigned int index = 0; index < this->size; ++index)
        {
            unsigned int number;
            unsigned int frequency;
            input.read((char *)&number, sizeof(unsigned int));
            input.read((char *)&frequency, sizeof(unsigned int));
            this->data[index].number = number;
            this->data[index].frequency = frequency;
        }
        input.close();
        std::cout << "File read successfully!" << std::endl;
    }
    else
    {
        throw std::runtime_error("File cannot be opened for reading!");
    }

    return *this;
}
MultiSet MultiSet::intersection(const MultiSet &other) const
{
    MultiSet copyOfThis = MultiSet(*this);
    for (unsigned int index = 0; index < copyOfThis.size; ++index)
    {
        unsigned int currentNumber = copyOfThis.data[index].number;
        if (!other.contains(currentNumber))
        {
            copyOfThis.remove(currentNumber);
            --index;
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
        unsigned int currentNumber = copyOfThis.data[index].number;

        if (copyOfOther.contains(currentNumber))
        {
            copyOfThis.remove(currentNumber);
            --index;
        }
    }

    return copyOfThis;
}
MultiSet MultiSet::complement() const
{
    MultiSet copyOfThis = MultiSet(*this);
    for(unsigned int index = 0; index < copyOfThis.size; ++index) {
        unsigned int currentFr = copyOfThis.data[index].frequency;
        copyOfThis.data[index].frequency = std::pow(2, this->maxBits) - currentFr - 1;
    }
    return copyOfThis;
}