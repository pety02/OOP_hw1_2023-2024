#include "2.cpp"

int16_t f(int16_t x) {
    return x+1;
}

int main() {
    
    ModifiableIntegerFunction f1(&f);
    f1.add(2, false);
    f1.add(3, false);
    f1.add(4, false);
    f1.add(5, false);
    f1.add(6, false);
    f1.add(7, false);
    f1.add(8, false);
    f1.add(9, false);
    f1.add(10, false);
    f1.add(11, false);
    f1.add(10, false);
    f1.add(11, false);
    f1.add(12, false);
    f1.add(13, false);
    f1.add(14, false);
    f1.add(15, false);
    f1.add(16, false);
    f1.add(17, false);
    f1.add(18, false);
    f1.add(19, false);
    f1.add(20, false);
    f1.print();
    
    try {
        f1.plot(2, 22, 2, 22);
    } catch (std::runtime_error& ex) {
        std::cout << "Error: " << ex.what()<< std::endl;
    }

    return 0;
}