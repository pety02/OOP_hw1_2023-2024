#include "1.cpp"

int main() {
    MultiSet m = MultiSet(100, 7);
    m.insert(1);
    m.insert(3);
    m.insert(5);
    m.insert(7);
    m.insert(0);
    m.insert(9);
    m.insert(2);
    //m.printMemoryRepresentation();

    MultiSet m2 = MultiSet(100, 7);
    m2.insert(0);
    m2.insert(9);
    m2.insert(2);
    m2.insert(6);
    m2.insert(8);
    m2.insert(12);
    m2.insert(100);
    //m2.printMemoryRepresentation();

    //m.complement().printMemoryRepresentation();
    //m.printMemoryRepresentation();

    m.serilize("function.dat");
    MultiSet deserialized = m.deserilize("function.dat");
    deserialized.print();
    deserialized.complement().print();


    return 0;
}