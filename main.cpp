#include "1.cpp"
#include "2.cpp"

int main() {
    // Първа задача - тестове
    MultiSet m = MultiSet(100, 7);
    m.insert(1);
    m.insert(3);
    m.insert(5);
    m.insert(7);
    m.insert(0);
    m.insert(9);
    m.insert(2);
    m.print();
    std::cout << "==================================================" << std::endl;

    MultiSet m2 = MultiSet(100, 7);
    m2.insert(0);
    m2.insert(9);
    m2.insert(2);
    m2.insert(6);
    m2.insert(8);
    m2.insert(12);
    m2.insert(100);
    m2.print();
    std::cout << "==================================================" << std::endl;

    m.complement().print();
    std::cout << "====================== MEMORY REPRESENTATION ============================" << std::endl;
    m.printMemoryRepresentation();
    std::cout << "==================================================" << std::endl;

    m.serialize("function.dat");
    MultiSet deserialized = m.deserialize("function.dat");
    deserialized.print();
    std::cout << "==================================================" << std::endl;
    std::cout << deserialized.complement().countOccurrences(3) << std::endl;
    std::cout << deserialized.complement().countOccurrences(4) << std::endl;

    // Втора задача - тестове
    ModifiableIntegerFunction fnc = ModifiableIntegerFunction([](int16_t x) {
        return x + 2;
    });
    fnc.add(1, false);
    fnc.add(2, false);
    fnc.add(3, false);
    fnc.add(4, false);
    fnc.add(5, false);
    fnc.add(6, false);
    fnc.add(7, false);
    fnc.add(8, false);
    fnc.add(9, false);
    fnc.add(10, false);
    fnc.plot(0, 20, 0, 20);
    std::cout << "Inection: " << std::boolalpha << fnc.isInjection() << std::endl;
    std::cout << "Surjection: " << std::boolalpha << fnc.isSurjection() << std::endl;
    std::cout << "Bijection: " << std::boolalpha << fnc.isBijection() << std::endl;

    ModifiableIntegerFunction fnc2 = ModifiableIntegerFunction([](int16_t x) {
        return x - 1;
    });
    fnc2.add(1, false);
    fnc2.add(2, false);
    fnc2.add(3, false);
    fnc2.add(4, false);
    fnc2.add(5, false);
    fnc2.plot(-1, 19, -1, 19);
    std::cout << "Colinear graphs: " << std::boolalpha << fnc.isColinear(fnc2) << std::endl;

    return 0;
}