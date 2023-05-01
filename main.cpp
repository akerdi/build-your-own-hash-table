#include <iostream>

#include "HashTable.h"

void operatorWithHashtable(HashTable& ht) {
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("11", "22");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("22", "33");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("11", "44");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("ab", "44");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("bc", "44");
    std::cout << "++++++++++++++++++++++" << std::endl;
    ht.ht_insert("c9", "44");
    std::cout << "++++++++++++++++++++++" << std::endl;

    char* value = ht.ht_search("11");
    std::cout << "value11: " << value << std::endl;
    value = ht.ht_search("22");
    std::cout << "value22: " << value << std::endl;
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
