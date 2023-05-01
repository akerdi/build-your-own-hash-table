#include <iostream>

#include "HashTable.h"

void operatorWithDelHashtable(HashTable& ht) {
    ht.ht_print();
    ht.ht_del("11");
    ht.ht_del("22");
    ht.ht_del("ab");
    ht.ht_del("bc");
    ht.ht_print();
    ht.ht_del("c9");
    ht.ht_print();
    ht.ht_del("c8");
    ht.ht_print();
    ht.ht_del("c7");
    ht.ht_print();
    ht.ht_del("c6");
    ht.ht_print();
    ht.ht_del("c5");
    ht.ht_print();
    ht.ht_del("c4");
    ht.ht_print();
    ht.ht_del("c3");
    ht.ht_print();
    ht.ht_del("c2");
    ht.ht_print();
}

void operatorWithHashtable(HashTable& ht) {
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("11", "11");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("22", "22");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("11", "11a");
    ht.ht_print();
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("ab", "ab");
    ht.ht_print();
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("bc", "bc");
    ht.ht_print();
    ht.ht_insert("mybrujmaonutk", "11");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c9", "c9");
    ht.ht_print();
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c8", "c8");
    ht.ht_print();
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c7", "c7");
    ht.ht_print();
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c6", "c6");
    ht.ht_print();
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c5", "c5");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c4", "c4");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c3", "c3");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c2", "c2");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c1", "c1");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_print();

    std::cout << "======end insert" << std::endl;

    char* value = ht.ht_search("11");
    std::cout << "value11: " << value << std::endl;
    value = ht.ht_search("22");
    std::cout << "value22: " << value << std::endl;
    std::cout << "------going to delete" << std::endl;
    operatorWithDelHashtable(ht);
    std::cout << "------end delete" << std::endl;
}

int main(int argc, char** argv) {
    std::cout.setf(std::ios::unitbuf);
    std::cout << "start." << std::endl;
    HashTable& ht = HashTable::ht_new();

    operatorWithHashtable(ht);

    ht.ht_destroy();

    std::cout << "end" << std::endl;
    return 0;
}
